#Q2. Simulate the different types of internet traffic such as ftp and telnet over netwrok and analyze the throughput


#Create a simulator object
set ns [new Simulator]


#set up trace files
set traceFile [open 2.tr w]
$ns trace-all $traceFile
set namFile [open 2.nam w]
$ns namtrace-all $namFile

proc finish {} {
	global ns namFile traceFile

    $ns flush-trace

	#Close the trace files
    close $traceFile
    close $namFile
	exec awk -f stats.awk 2.tr &
	#exec nam 2.nam &
    exit 0
}




#Create four nodes
for {set i 0} {$i < 4} {incr i} {
        set n($i) [$ns node]
}

#Create links between the nodes
$ns duplex-link $n(0) $n(2) 2Mb 10ms DropTail
$ns duplex-link $n(1) $n(2) 2Mb 10ms DropTail
$ns duplex-link $n(2) $n(3) 900kb 10ms DropTail


#Set queue size
$ns queue-limit $n(0) $n(2) 10


#Set TCP TELNET Connection between n(0) and n(3)
set tcp0 [new Agent/TCP]
$ns attach-agent $n(0) $tcp0
set sink0 [new Agent/TCPSink]
$ns attach-agent $n(3) $sink0
$ns connect $tcp0 $sink0

#Attach TELNET Application over TCP
set telnet [new Application/Telnet]
$telnet attach-agent $tcp0
$telnet set interval_ 0
#$ftp0 set type_ FTP

#Set TCP FTP Connection between n(1) and n(3)
set tcp1 [new Agent/TCP]
$ns attach-agent $n(1) $tcp1
set sink1 [new Agent/TCPSink]
$ns attach-agent $n(3) $sink1
$ns connect $tcp1 $sink1

#Attach Telnet Application over TCP
set ftp [new Application/FTP]
$ftp attach-agent $tcp1
$ftp set type_ FTP

#Schedule Events
$ns at 0.5 "$telnet start"
$ns at 0.6 "$ftp start"
$ns at 24.5 "$telnet stop"
$ns at 24.5 "$ftp stop"
$ns at 25.0 "finish"

#Run Simulation
$ns run
