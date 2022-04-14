/*
    #include <unistd.h>
       #include <sys/types.h>

       int truncate(const char *path, off_t length);
       int ftruncate(int fd, off_t length);

       On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.

       也可以使用命令
       truncate fileName -s  newSize
*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    int fd = open("trun", O_RDWR | O_CREAT, 0666);
    truncate("trun", 20);
    lseek(fd, 20, SEEK_END);
    return 0;
}