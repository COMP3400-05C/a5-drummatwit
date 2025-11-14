#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    // TODO: Complete and document
    if (argc != 2) {
        fprintf(stderr, "USAGE: partc FILEIN\n");
        return 1;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1){
        perror("pipe");
        return 1;
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0){
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) == -1){
            perror("dup2");
            exit(1);
        }
        close(pipefd[0]);

        execlp("sort", "sort", "-t,", "-k2,2n", NULL);
        perror("execlp sort");
    } else {
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1){
            perror("dup2");
            exit(1);
        }
        close(pipefd[1]);

        execl("./parta", "parta", argv[1], NULL);
        perror("execl parta");
        exit(1);
    }
    wait(NULL);
    return 0;
}
