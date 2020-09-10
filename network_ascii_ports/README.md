# ASCII ports (Network #1)

## Description
```
We've captured this .pcap file and a flag is hidden somewhere inside.
```

## Solution
Go through the supplied .pcap file.
Notice the suspicious 42 bytes long UDP packets coming from 192.168.1.3
Take the destination ports of each packet and translate them to ascii