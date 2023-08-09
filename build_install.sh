
bpftool btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h
clang -O2 -g -Wall -target bpf -c xdp_drop_icmp.c -o xdp_drop_icmp.o
sudo ip link set enp0s3 xdpgeneric obj xdp_drop_icmp.o sec xdp_drop
