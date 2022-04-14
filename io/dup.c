/*
    #include <unistd.h>
    int dup(int oldfd);
        作用：复制一个新的文件描述符
        fd=3, int fd1 = dup(fd),
        fd指向的是a.txt, fd1也是指向a.txt
        从空闲的文件描述符表中找一个最小的，作为新的拷贝的文件描述符
        进程的文件描述符指向一个文件描述结构体,多个文件描符符可以指向同一个文件描述结构体

        通过dup的指向同一个文件描述结构题,共享读写指针


*/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {

    int fd = open("a.txt", O_RDWR | O_CREAT, 0664);


    int fd1 = dup(fd);

    if(fd1 == -1) {
        perror("dup");
        return -1;
    }

    printf("fd : %d , fd1 : %d\n", fd, fd1);

    int ret = write(fd, "666\n", 4);
    if(ret == -1) {
        perror("write");
        return -1;
    }

    close(fd);

#ifdef debug
    int fd3 = open("a.txt", O_RDWR);
    ret = write(fd3, "777\n", 4);
    if(ret == -1) {
        perror("write");
        return -1;
    }
#endif

    int fd2 = dup(fd1);

    printf("fd2 : %d , fd1 : %d\n", fd2, fd1);

    close(fd2);

    char * str = "hello,world\n";
    ret = write(fd1, str, strlen(str));
    if(ret == -1) {
        perror("write");
        return -1;
    }

    close(fd1);

    return 0;
}