# xdp_drop_icmp
Red Hat have a tutorial to [get started with XDP](https://developers.redhat.com/blog/2021/04/01/get-started-with-xdp) that 
 * Creates an eBPF/XDP program that drops all ethernet traffic
 * Compiles the program to BPF byte code
 * Attaches the BPF program to an Ethernet interface so that all traffic on the device is dropped

This tutorial builds on that basis by showing a few more details of eBPF/XDP by dropping only every second ethernet frame where the frame contains an ICMP packet; i.e. TCP and UP traffic aren't affected by this filter.
