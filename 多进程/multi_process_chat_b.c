#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main(){

    //判断管道是否存在,并创建
    int ret = access("fifo1", F_OK);
    if (ret == -1) {
        ret = mkfifo("fifo1", 0644);
        if (ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }

     //判断管道是否存在,并创建
    ret = access("fifo2", F_OK);
    if (ret == -1) {
        ret = mkfifo("fifo2", 0644);
        if (ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }

    //创建子进程
    pid_t pid = fork();

    if (pid > 0) {
        //父进程read
        int fd = open("fifo1", O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(0);
        }

        char buf[1024] = {0};
        while(1) {
            int ret = read(fd, buf, sizeof(buf));
            if (ret == 0) {
                printf("读端关闭\n");
                exit(0);
            }
            printf("%s", buf);
            memset(buf, 0, sizeof(buf));
        }

    }else if (pid == 0) {
        //子进程write
        int fd = open("fifo2", O_WRONLY);
        if (fd == -1) {
            perror("open");
            exit(0);
        }

        char buf[1024] = {};
        while (1) {
            fgets(buf, sizeof(buf), stdin);
            int ret = write(fd, buf, sizeof(buf));
            memset(buf, 0, sizeof(buf));
        }
    }else {
        perror("fork");
        exit(0);
    }
    
    return 0;
}