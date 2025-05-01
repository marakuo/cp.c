
#include<stdio.h>
#include <fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if(argc < 3){
        printf("usage: ./copy source dest\n");
        return 1;
    }
    
    int fds = open(argv[1], O_RDONLY);
    if (fds == -1){
        printf("failed to open source file\n");
        return 1;
    }
    
    int fddest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fddest == -1){
        printf("failed to create destination file\n");
        close(fds);
        return 1;
    }
    
    char buf[1024];
   int  readcount;
    while((readcount = read(fds, buf, 1024)) > 0){
        if(write(fddest, buf, readcount) == -1){
            perror("write failed");
            close(fds);
            close(fddest);
            return 1;
        }
    }
    
    if(readcount == -1){
        printf("failed to read\n");
        close(fds);
        close(fddest);
        return 1;
    }
    
    close(fds);
    close(fddest);
    return 0;
}
