/*
    #include <unistd.h>
    int dup2(int oldfd, int newfd);
        作用：重定向文件描述符
        oldfd 指向 a.txt, newfd 指向 b.txt
        调用函数成功后：newfd 指向oldfd 所指的文件描述结构体
            - 实际上newfd指向的文件描述结构体关掉,让newfd指向 oldfd所指的文件描述结构体
            - newfd的值是不变的 
            - 返回值就是newfd,失败-1

        oldfd 必须是一个有效的文件描述符
        oldfd和newfd值相同，相当于什么都没有做
*/
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {

    int fd = open("1.txt", O_RDWR | O_CREAT, 0664);
    if(fd == -1) {
        perror("open");
        return -1;
    }
    printf("fd=%d\n",fd);
    

    int fd1 = open("2.txt", O_RDWR | O_CREAT, 0664);
    if(fd1 == -1) {
        perror("open");
        return -1;
    }
    printf("fd1=%d\n",fd1);

    int fd3 = dup(fd1);
    if (fd3 == -1) {
        perror("dup");
        return -1;
    }
    printf("fd3=%d\n",fd3);

    close(fd1);
    int fd2 = dup2(fd, fd3);
    if(fd2 == -1) {
        perror("dup2");
        return -1;
    }
    printf("fd=%d\n",fd);
    printf("fd3=%d\n",fd3);
    printf("fd2=%d\n",fd2);

    // 通过fd1去写数据，实际操作的是1.txt，而不是2.txt
    char * str = "hello, dup2";
    int len = write(fd, str, strlen(str));


    if(len == -1) {
        perror("write");
        return -1;
    }

    len = write(fd3, str, strlen(str));
    if(len == -1) {
        perror("write");
        return -1;
    }

    close(fd);

    return 0;
}