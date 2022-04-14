#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
ulimit -c unlimited
gcc core.c -o coreapp -g
./coreapp
gdb coreapp
(gdb) core-file core
*/

int main() {

    char * buf = malloc(1);
    free(buf);

    strcpy(buf, "hello");
    printf("%s", buf);

    return 0;
}