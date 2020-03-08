#include "MyThread.h"
#include "dealFileHead.h"
#include "QtDebug"


MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

void MyThread::run(){
    qDebug()<<argc<<argv[0]<<argv[1]<<argv[2]<<argv[3]<<endl;
    //绑定共享内存并初始化
    int share_mem_id_a = shmget(KEY_SHARE_MEM_A, sizeof(ShareM), IPC_CREAT|0666);
    qDebug()<<"2:-1"<<endl;
    struct ShareM *share_buf_a =  (struct ShareM *)shmat(share_mem_id_a, 0, 0);
    qDebug()<<"2:-2"<<endl;
    int share_mem_id_b = shmget(KEY_SHARE_MEM_B, sizeof(ShareM), IPC_CREAT|0666);
    qDebug()<<"2:-3"<<endl;
    struct ShareM *share_buf_b =  (struct ShareM *)shmat(share_mem_id_b, 0, 0);
    qDebug()<<"2:-4"<<endl;
    qDebug()<<share_buf_b->flag<<endl;
    share_buf_b->flag = -1;

    qDebug()<<"2:1"<<endl;
    //申请信号灯
    int light_id = semget(KEY_LIGHT, 4, IPC_CREAT|0666);

    //file from bufB to bufA
    int num = 0;  //一次写的量
    int sum = 0;  //累计写的量
    //读取原文件大小
    struct stat file_state;
    stat(argv[1], &file_state);
    int file_size = file_state.st_size;
    emit _fileSize(file_size);

    qDebug()<<"2:2"<<endl;
    //誊写
    while(true){
        qDebug()<<"2:3"<<endl;
        P(light_id, 1); //bufA可读
        qDebug()<<"2:4"<<endl;
        P(light_id, 2); //bufB可写
        qDebug()<<"2:5"<<endl;
        if(share_buf_a->flag!=-1){ ////end of file, maybe num is 0
            strncpy(share_buf_b->buf, share_buf_a->buf, share_buf_a->flag);
            sum += share_buf_a->flag;
            emit _copySum(sum);
            emit _copyContents(QString(share_buf_a->buf));
            share_buf_b->flag = share_buf_a->flag;
            V(light_id, 0);
            V(light_id, 3);
            break;
        }
        else{
            strncpy(share_buf_b->buf, share_buf_a->buf, BUF_SIZE);
            sum += BUF_SIZE;
            emit _copySum(sum);
            emit _copyContents(QString(share_buf_a->buf));
            V(light_id, 0); //bufA可写
            V(light_id, 3); //bufB可读
        }
        msleep(1);
    }
    emit _over();
    shmdt(0);
    shmdt(0);
//    return;

}
