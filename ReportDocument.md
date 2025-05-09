Tools and Environment:
Operating System: Ubuntu using WSL
Compiler: GCC
IDE: Visual Studio with Linux
Language: C

Program Overview:
The program will create 10 child processes using the fork() function. Each child process performs a task using the execvp() function to execute system commands such as ls, echo, date, etc. After spawning each child, the parent process waits for it to complete using waitpid(). When the child is terminated the parent will report whether the child exited normally and the exit code/termination signal. The children will print their own PID and command executed.

Key Code Features:
Process creation- pid_t pid = fork()
Child execution- execvp(commands[i][0], (char * const *)commands[i]);
Parent synchronization- pid_t wpid = waitpid(pids[i], &status, 0);
Status reporting- if (WIFEXITED(status))
    printf("Exited with status: %d", WEXITSTATUS(status));

Sample Output:
[Child 0] PID: 15423 executing: echo
Hello + Cal
[Child 1] PID: 15424 executing: ls
[Parent] Child PID 15423 exited with status 0
[Parent] Child PID 15424 exited with status 0

Conclusion:
This project was able to demonstrate the inter-process communication. It properly helped make clear how commands like fork(), execpv() and waitpid() are used in Linux like environments.
