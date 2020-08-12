//
// Created by luo on 2020/3/5.
//
#include<cstdio>
#include<unistd.h>
#include<cstring>
#include <string>
#include <cstdlib>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <fcntl.h>
#include <wait.h>
#include <cerrno>

#define BUF_SIZE 10     //缓存区大小
#define KEY_LIGHT 666        //信号灯键值
#define KEY_SHARE_MEM_A 9394      //第一块共享缓存的键值
#define KEY_SHARE_MEM_B 1105      //第二块共享缓存的键值

//共享缓存区结构
struct ShareM{
    char buf[BUF_SIZE];
    int flag;   //是否达到文件结尾，初始值为0
};

//semctl()的参数
//在新版内核中关于union sem_union这个联合体已经被注释了,需要自己写这个联合体.
//否则报错“incomplete type is not allowed“
union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// PV操作
void P(int semid, int index){
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
}
void V(int semid, int index){
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = +1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
}



