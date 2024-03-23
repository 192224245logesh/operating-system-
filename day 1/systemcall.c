#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t child_pid;

    
    child_pid = fork();

    if (child_pid == -1) {
        
        perror("fork");
        return 1;
    } else if (child_pid == 0) {
       
        printf("Child process:\n");
        printf("PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    } else {
    
        printf("Parent process:\n");
        printf("PID: %d\n", getpid());
        printf("Child PID: %d\n", child_pid);
    }

    return 0;
}
