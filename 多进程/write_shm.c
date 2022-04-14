#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {    

    // 1.创建一个共享内存
    int shmid = shmget(100, 4096, IPC_CREAT|0664);
    if(shmid == -1) {
        perror("shmget");
        exit(0);
    }
    printf("shmid : %d\n", shmid);
    
    // 2.和当前进程进行关联
    void * ptr = shmat(shmid, NULL, 0);

    char * str = "helloworld";


    // 3.写数据
    memcpy(ptr, str, strlen(str) + 1);

    printf("按任意键解除关联\n");
    getchar();

    // // 4.解除关联
    // shmdt(ptr);

    // printf("关联已经解除, 按任意键重新关联\n");
    // getchar();

    // ptr = shmat(shmid, NULL, 0);
    
    // printf("重新关联成功, 按任意键继续删除\n");
    // getchar();

    // // 5.删除共享内存
  
    // shmctl(shmid, IPC_RMID, NULL);

    // printf("标记删除成功, 按任意键解除关联\n");
    // getchar();
    // shmdt(ptr);

    // printf("按任意键继续\n");
    // getchar();

    // ptr = shmat(shmid, NULL, 0);
    // if(ptr == (void *)-1) {
    //     perror("shmat");
    // }

    // printf("按任意键继续\n");
    // getchar();

    return 0;
}