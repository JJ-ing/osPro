#include "MyThread.h"
#include "dealFileHead.h"
#include "QtDebug"


MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

void MyThread::run(){
    qDebug()<<argc<<argv[0]<<argv[1]<<argv[2]<<argv[3]<<endl;
    //绑定共享内存并初始化flag
    int share_mem_id = shmget(KEY_SHARE_MEM_B, sizeof(ShareM), IPC_CREAT|0666);
    struct ShareM *share_buf =  (struct ShareM *)shmat(share_mem_id, 0, 0);

    //申请信号灯
    int light_id = semget(KEY_LIGHT, 4, IPC_CREAT|0666);

    //file from bufB to destination
    int fd; //文件描述符
    int num = 0;  //一次写的量
    int sum = 0;  //累计写的量
    if((fd = ::open(argv[2],O_WRONLY|O_CREAT, 0666))==-1){
        printf("打开目标文件失败！\n");
        exit(-1);
    }
    //读取原文件大小
    struct stat file_state;
    stat(argv[1], &file_state);
    int file_size = file_state.st_size;
    emit _fileSize(file_size);
    //誊写
    while(true){
//        printf("f3-1\n");
        P(light_id, 3); //bufB可读
//        printf("f3-2\n");
        if(share_buf->flag!=-1){ //end of file, maybe num is 0
            num = write(fd, share_buf->buf, share_buf->flag);
            sum += num;
            emit _copySum(sum);
            emit _copyContents(QString(share_buf->buf));
            V(light_id, 2); //bufB可写
            break;
        }
        else{
            num = write(fd, share_buf->buf, BUF_SIZE);
            sum += num;
            emit _copySum(sum);
            emit _copyContents(QString(share_buf->buf));
            V(light_id, 2);
        }
        msleep(100);
    }
    ::close(fd);
    emit _over();


}
