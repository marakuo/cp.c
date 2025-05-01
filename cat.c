#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {  
        int fd = open(argv[i], O_RDONLY);
        if (fd == -1) {
            printf("failed to open the file\n");
            return 1;
        }
        char buf[1024];
        int readcount, writecount;
        while ((readcount = read(fd, buf, 1024)) > 0) {
            writecount = write(1, buf, readcount);
            if (writecount == -1) {
               printf("failed to write\n");
                return 1;
            }
        }
        if (readcount == -1) {  
            printf("failed to read\n");
            close(fd);
            return 1;
        }
        close(fd);  
    }
    return 0;
}
