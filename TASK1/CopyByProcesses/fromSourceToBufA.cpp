//
// Created by luo on 2020/3/5.
//
#include "head.h"

int main(int argc, char* argv[]){
//    printf("%s %s \n", argv[1], argv[2]);
    //绑定共享内存并初始化flag
    int share_mem_id = shmget(KEY_SHARE_MEM_A, sizeof(ShareM), IPC_CREAT|0666);
    struct ShareM *share_buf =  (struct ShareM *)shmat(share_mem_id, 0, 0);
    share_buf->flag = -1;   //当flag>=0时，读完

    //申请信号灯
    int light_id = semget(KEY_LIGHT, 4, IPC_CREAT|0666);

    //file from source to bufA
    int fd; //文件描述符
    int num = 0;  //一次写的量
    int sum = 0;  //累计写的量
    if((fd = open(argv[1],O_RDONLY|O_CREAT, 0666))==-1){
        printf("打开原文件失败！\n");
        exit(-1);
    }
    //读取原文件大小
    struct stat file_state;
    stat(argv[1], &file_state);
    int file_size = file_state.st_size;
    //誊写
    while(true){
        P(light_id, 0); //bufA可写
        num = read(fd, share_buf->buf, BUF_SIZE);
        sum += num;
        if(num<BUF_SIZE){ //end of file, maybe num is 0
            share_buf->flag = num;
            V(light_id, 1);
//            printf("f1 has V(1):num=%d\n", share_buf->flag);
            break;
        }
        V(light_id, 1); //bufA可读
    }

    close(fd);
//    printf("f1OK \n");
    return 0;
}

