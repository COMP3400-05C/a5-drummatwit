#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // Declare the buffer to use. Do NOT change!
    enum { BUFSIZE = 8 };
    char buffer[BUFSIZE];
    // TODO: Complete and document
    if(argc != 2) { 
        printf("USAGE: parta FILEIN\n");
        return 1;
    }
    
    char *filename = argv[1];

    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        printf("ERROR: %s not found\n", filename);
        return 2; 
    }

    int upper = 0;
    int lower = 0;
    int number = 0;
    int space = 0;
    int others = 0;
    ssize_t bytes_read; 

    while((bytes_read = read(fd, buffer, BUFSIZE)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            if (isupper(buffer[i])) {
                upper++;
            } else if (islower(buffer[i])) {
                lower++;
            } else if (isdigit(buffer[i])) {
                number++;
            } else if (isspace(buffer[i])) {
                space++;
            } else {
                others++;
            }
        }
    }

        if (bytes_read < 0) {
            perror("Error reading file");
            close(fd);
            return 1;
        }
        close(fd);
        printf("Upper,%d\n", upper);
        printf("Lower,%d\n", lower);
        printf("Number,%d\n", number);
        printf("Space,%d\n", space);
        printf("Other,%d\n", others);
        
        return 0; 
    }
