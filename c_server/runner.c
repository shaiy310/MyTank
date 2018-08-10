#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

int start_process(char * prog_name, bool should_wait) {
    errno = 0;
    pid_t pid = fork();
    if (pid < 0) {
        // error
        printf("fork return an error: errno=%d.\n", errno);
        return -1;
    } else if (pid == 0) {
        // child is here
        char * internal_argv[] = {
            prog_name,
            NULL
        };
        if (execvp(internal_argv[0], internal_argv) < 0) {
            printf("ERROR: Invalid command\n");
        }
    } else {
        // father is here
        printf("child proccess is alive and well, pid = %d\n", pid);
        if (should_wait) {
            wait(NULL);
            pid = -1;
        }
        printf("finished\n");
    }

    return pid;
}

//int main(int argc, const char * const argv[]) {
//    start_process(false);
//}
