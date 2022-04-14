/*
    #include <stdio.h>
    int rename(const char *oldpath, const char *newpath);

*/
#include <stdio.h>

int main(int args,char *argv[]) {

    int ret = rename(argv[1], argv[2]);

    if(ret == -1) {
        perror("rename");

        return -1;
    }

    return 0;
}