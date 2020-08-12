#include "MyThread.h"
#include "dealFileHead.h"
#include "QtDebug"


MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

void MyThread::run(){
    qDebug()<<argc<<argv[0]<<argv[1]<<argv[2]<<argv[3]<<endl;
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
//    qDebug()<<"1"<<endl;
    if((fd = ::open(argv[1],O_RDONLY|O_CREAT, 0666))==-1){
        printf("打开原文件失败！\n");
//        qDebug()<<"2"<<endl;
        exit(-1);
    }
//    qDebug()<<"3"<<endl;
    //读取原文件大小
    struct stat file_state;
    stat(argv[1], &file_state);
    int file_size = file_state.st_size;
    emit _fileSize(file_size);
    //誊写
    while(true){
        P(light_id, 0); //bufA可写
        num = read(fd, share_buf->buf, BUF_SIZE);
        sum += num;
        emit _copySum(sum);
        qDebug()<<sum<<endl;
        emit _copyContents(QString(share_buf->buf));

        if(num<BUF_SIZE){ //end of file, maybe num is 0
            share_buf->flag = num;
            V(light_id, 1);
            break;
        }
        V(light_id, 1); //bufA可读
        msleep(1);
    }

    ::close(fd);
    emit _over();

//    return ;

}
