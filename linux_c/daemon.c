#include <stdio.h>
#include <sys/types.h>
#include <sys/param.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <syslog.h>
#include <time.h>
#include <stdlib.h>
int init_daemon()
{
    int pid;
    int i;

    signal(SIGTTOU,SIG_IGN);
    signal(SIGTTIN,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);
    signal(SIGHUP,SIG_IGN);
    
    pid = fork();
    if(pid > 0) exit(0);
    else if(pid < 0) return -1;

    setsid();

    pid = fork();
    if(pid > 0) exit(0);
    else if(pid < 0) return -1;

    for(i = 0; i < NOFILE; close(i++));

    chdir("/");

    umask(0);

    signal(SIGCHLD,SIG_IGN);

    return 0;
}
int main()
{
    time_t now;
    init_daemon();
    syslog(LOG_USER | LOG_INFO,"TEST! \n");
    while(1)
    {
        sleep(8);
        time(&now);
        syslog(LOG_USER | LOG_INFO,"time: \t%s\t\t\n",ctime(&now));
    }
}