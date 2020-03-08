//
// Created by luo on 2020/3/5.
//
#include "head.h"

int main(int argc, char* argv[]){
    //绑定共享内存并初始化
    int share_mem_id_a = shmget(KEY_SHARE_MEM_A, sizeof(ShareM), IPC_CREAT|0666);
    struct ShareM *share_buf_a =  (struct ShareM *)shmat(share_mem_id_a, 0, 0);
    int share_mem_id_b = shmget(KEY_SHARE_MEM_B, sizeof(ShareM), IPC_CREAT|0666);
    struct ShareM *share_buf_b =  (struct ShareM *)shmat(share_mem_id_b, 0, 0);
    share_buf_b->flag = -1;

    //申请信号灯
    int light_id = semget(KEY_LIGHT, 4, IPC_CREAT|0666);

    //file from bufB to bufA
    int num = 0;  //一次写的量
    int sum = 0;  //累计写的量
    //读取原文件大小
    struct stat file_state;
    stat(argv[1], &file_state);
    int file_size = file_state.st_size;
    //誊写
    while(true){
//        printf("1\n");
        P(light_id, 1); //bufA可读
//        printf("2\n");
        P(light_id, 2); //bufB可写
//        printf("3\n");
//        printf("f2:%d\n", share_buf_a->flag);
        if(share_buf_a->flag!=-1){ ////end of file, maybe num is 0
            strncpy(share_buf_b->buf, share_buf_a->buf, share_buf_a->flag);
            sum += share_buf_a->flag;
            share_buf_b->flag = share_buf_a->flag;
            V(light_id, 0);
            V(light_id, 3);
            break;
        }
        else{
            strncpy(share_buf_b->buf, share_buf_a->buf, BUF_SIZE);
            sum += BUF_SIZE;
            V(light_id, 0); //bufA可写
            V(light_id, 3); //bufB可读
        }
    }

//    printf("f2OK \n");
    return 0;
}
