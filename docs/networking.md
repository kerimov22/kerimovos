# KerimovOS Networking

## Network Drivers

### Intel E1000 (Primary, QEMU)
```
qemu-system-x86_64 -netdev user,id=n0 -device e1000,netdev=n0
```
Features: DMA, RX/TX descriptor rings, interrupts, link status

### Realtek RTL8139 (Optional)
Features: PIO, basic RX/TX

### virtio-net (TODO)
Not yet implemented.

## Network Stack (IPv4)
- Ethernet II framing
- ARP (Address Resolution Protocol)
- IPv4 (packet forwarding, ICMP)
- ICMP (echo request/reply — ping)
- UDP (connectionless datagrams)
- TCP (3-way handshake, ACK, retransmit, connection close)
- DHCP client (automatic IP configuration)
- DNS client (A record queries)

## Socket API
- socket(domain, type, protocol)
- connect(fd, addr, addrlen)
- send(fd, buf, len, flags)
- recv(fd, buf, len, flags)
- close(fd)
- gethostbyname(name)

## Configuration Files
- /etc/network.conf — network configuration
- /etc/resolv.conf — DNS resolvers
- /etc/hosts — hostname resolution

## Shell Commands
- ifconfig / ip addr — show interface configuration
- ip route — show routing table
- ping <host> — ICMP echo
- dhcp — request IP via DHCP
- nslookup / dig <host> — DNS query

## curl HTTP Client
```
curl http://example.com/          GET request
curl -O http://example.com/file   Download file
curl -I http://example.com/       Headers only
curl -L -s http://example.com/    Follow redirects, silent
```
HTTPS returns: curl: (35) SSL/TLS not supported yet

## QEMU Network Test
```
qemu-system-x86_64 ... -netdev user,id=n0 -device e1000,netdev=n0
```
Provides real internet access via QEMU user-mode NAT.
