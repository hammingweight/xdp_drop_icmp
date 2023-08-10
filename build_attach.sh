# Extract the BPF Type Format (BTF) types for the kernel.
bpftool btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h

# Compile to BPF byte code.
clang -O2 -g -Wall -target bpf -c xdp_drop_icmp.c -o xdp_drop_icmp.o

# Attach the filter to XDP events for the specified interface.
sudo ip link set enp0s3 xdpgeneric obj xdp_drop_icmp.o sec xdp_drop
