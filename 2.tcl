#Q2. Simulate the different types of internet traffic such as ftp and telnet over netwrok and analyze the throughput


#Create a simulator object
set ns [new Simulator]


#set up trace files
set traceFile [open 2.tr w]
$ns trace-all $traceFile
set namfile [open 2.nam w]
$ns namtrace-all $namfile

#Finish Procedure
proc Finish {} {
	global ns traceFile namfile

	#Dump all trace data and close the files
	$ns flush-trace
	close $traceFile
	close $namfile

	#Execute the nam animation file
	exec nam 2.nam &

	#Calculate throughput = (number of packets received/time taken for simulation)
	set numTcp [exec grep "^r" 2.tr | grep "tcp" | tail -n 1 | cut -d " " -f 6]
	set TcpSize [exec grep "^r" 2.tr | grep -c "tcp"]
	set tcpTime 24.0
	set numUdp [exec grep "^r" 2.tr | grep "udp" | tail -n 1 | cut -d " " -f 6]
	set UdpSize [exec grep "^r" 2.tr | grep -c "udp"]
	set udpTime 23.9
	puts "The throughput of FTP is "
	puts "[expr ($numTcp*$TcpSize)/$tcpTime] bytes per second"
	puts "The throughput of Telnet is "
	puts "[expr ($numUdp*$UdpSize)/$udpTime] bytes per second"
	exit 0
}





#Create four nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

#Create links between the nodes
$ns duplex-link $n0 $n2 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail
$ns simplex-link $n2 $n3 1Mb 10ms DropTail
$ns simplex-link $n3 $n2 1Mb 10ms DropTail

#Set queue size and Monitor the queue
$ns queue-limit $n0 $n2 10
$ns simplex-link-op $n0 $n2 queuePos 0.5

#Set TCP Connection between n0 and n3
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
set sink0 [new Agent/TCPSink]
$ns attach-agent $n3 $sink0
$ns connect $tcp0 $sink0

#Attach FTP Application over TCP
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
$ftp0 set type_ FTP

#Set UDP Connection between n1 and n3
set udp0 [new Agent/UDP]
$ns attach-agent $n1 $udp0
set null0 [new Agent/Null]
$ns attach-agent $n3 $null0
$ns connect $udp0 $null0

#Attach Telnet Application over UDP
set telnet [new Application/Telnet]
$telnet attach-agent $udp0
$telnet set type_ Telnet

#Schedule Events
$ns at 0.1 "$telnet start"
$ns at 0.5 "$ftp0 start"
$ns at 10.0 "$telnet stop"
$ns at 10.5 "$ftp0 stop"
$ns at 11.0 "Finish"

#Run Simulation
$ns run
