#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define NUM_CHILDREN 10

const char* commands[NUM_CHILDREN][4] = {
    {"echo", "Hello + Isaac Darlington", NULL},     // Unique task
    {"ls", "-l", NULL},
    {"date", NULL},
    {"whoami", NULL},
    {"pwd", NULL},
    {"uname", "-a", NULL},
    {"id", NULL},
    {"hostname", NULL},
    {"echo", "Child process 8 running", NULL},
    {"echo", "Child process 9 complete", NULL}
};

int main() {
    pid_t pids[NUM_CHILDREN];
    int status;

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            printf("[Child %d] PID: %d executing: %s\n", i, getpid(), commands[i][0]);
            execvp(commands[i][0], (char* const*)commands[i]);
            perror("execvp failed");
            exit(EXIT_FAILURE);
        }
        else if (pid > 0) {
            // Parent process
            pids[i] = pid;
        }
        else {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for each child and report
    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t wpid = waitpid(pids[i], &status, 0);
        if (WIFEXITED(status)) {
            printf("[Parent] Child PID %d exited with status %d\n", wpid, WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)) {
            printf("[Parent] Child PID %d terminated by signal %d\n", wpid, WTERMSIG(status));
        }
    }

    return 0;
}
