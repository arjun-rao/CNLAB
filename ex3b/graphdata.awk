{
    packetType = $5
    event = $1
    if(packetType == "tcp"){
        if(event == "r")
            TCPtimePacketCountRecieved[int($2)] = ++TCPtimePacketCount[int($2)]
    }else if(packetType == "cbr"){
        if(event == "r")
            UDPtimePacketCountRecieved[int($2)] = ++UDPtimePacketCount[int($2)]
    }
}
END{
    n = asort(TCPtimePacketCountRecieved);
    for (i = 1; i <= n; i++)
        print(i "\t" TCPtimePacketCountRecieved[i]) >> "tcp.xg"
    n = asort(UDPtimePacketCountRecieved)
    for (i = 1; i <= n; i++)
        print(i "\t" UDPtimePacketCountRecieved[i]) >> "udp.xg"
}
