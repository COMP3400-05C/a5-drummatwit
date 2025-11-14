#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    // TODO: Complete and document
    if (argc != 3) {
        fprintf(stderr, "USAGE: partb FILEIN FILEOUT\n");
        return 1;
    }

    char *input_filename = argv[1];
    char *output_filename = argv[2];

    char *parta_args[3];
    parta_args[0] = "./parta";
    parta_args[1] = input_filename;
    parta_args[2] = NULL;

    // Open output file
    int fd = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0770);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("dup2");
        return 1;
    }
    close(fd);
    printf("Category,Count\n");
    fflush(stdout);
    int eret = execv("./parta", parta_args);
    perror("execv");

    return 1;
}

