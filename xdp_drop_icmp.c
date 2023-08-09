#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>

#define ETH_P_IP 0x0800

int count = 0;

SEC("xdp_drop")
int xdp_drop_icmp(struct xdp_md *ctx)
{
    void *data = (void *)(long)ctx->data;
    void *data_end = (void *)(long)ctx->data_end;
    struct ethhdr *eth = data;

    // The eBPF Verifier will reject this program unless
    // we explicitly check memory bounds.
    if (data + sizeof(struct ethhdr) > data_end)
        return XDP_PASS;

    if (bpf_ntohs(eth->h_proto) != ETH_P_IP)
        return XDP_PASS;

    struct iphdr *iph = data + sizeof(struct ethhdr);
    // We need this to make the eBPF verifier happy.
    if (data + sizeof(struct ethhdr) + sizeof(struct iphdr) > data_end)
        return XDP_PASS;

    unsigned char protocol = iph->protocol;
    if (protocol == IPPROTO_ICMP)
    {
        count++;
        if (count % 2 == 0)
            return XDP_DROP;
    }

    return XDP_PASS;
}

char _license[] SEC("license") = "GPL";
