#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

static void sighandler(int signo){
    if(signo == SIGINT){
        int fd = open("./out.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
        char out[] = "Program terminated with SIGINT\n";

        printf("%d\n",fd );
        write(fd, out, sizeof(out));
        close(fd);

        exit(0);
    }
    else if(signo == SIGUSR1){
        printf("PPID:\t%d\n", getppid());
    }
}

int main(int argc, char const *argv[]) {
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);

    while(1){
        printf("PID:\t%d\n", getpid());
        sleep(1);
    }

    return 0;
}
