#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {    

    // 1.获取一个共享内存
    int shmid = shmget(100, 0, 0);
    if(shmid == -1) {
        perror("shmget");
        exit(0);
    }
    printf("shmid : %d\n", shmid);

    // 2.和当前进程进行关联
    void * ptr = shmat(shmid, NULL, 0);

    // 3.读数据
    printf("%s\n", (char *)ptr);
    
    printf("按任意键接触关联\n");
    getchar();

    // 4.解除关联
    shmdt(ptr);

    //memcpy(ptr, "hello", 6);
    printf("%s", (char *)ptr);

    printf("按任意键标记删除\n");
    getchar();
    // 5.删除共享内存
    int ret = shmctl(shmid, IPC_RMID, NULL);
    if(ret == -1) {
        perror("shmctl");
        exit(0);
    }

    ret = shmctl(shmid, IPC_RMID, NULL);
    if(ret == -1) {
        perror("shmctl");
        exit(0);
    }


    return 0;
}