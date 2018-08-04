#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define CMD_LINE    "sudo python -c \"import time; print time.time()\""

int main(int argc, const char * const argv[]) {
    errno = 0;
    int pid = fork();
    if (pid == -1) {
        // error
        printf("fork return an error: errno=%d.", errono);
        return -1;
    } else if (pid == 0) {
        // child is here
    } else {
        // father is here
        printf("child proccess is alive and well, pid = %d", pid);
    }
        
    
    return 0;
}