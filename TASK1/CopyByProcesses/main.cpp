
#include "head.h"

int main() {
    //申请共享内存，创建信号灯并初始化
    int shareMemIdA = shmget(KEY_SHARE_MEM_A, sizeof(struct ShareM),IPC_CREAT|0666);
    int shareMemIdB = shmget(KEY_SHARE_MEM_B, sizeof(struct ShareM),IPC_CREAT|0666);

    int semId = semget(KEY_LIGHT, 4, IPC_CREAT|0666);
    if(semId==-1){
        printf("SemGet error!");
        exit(-1);
    }
    union semun value;
    value.val = 1;      //semiId[0] BufA是否可写
    if(semctl(semId, 0, SETVAL, value)==-1){
        printf("SemCtl error!");
        exit(-1);
    }
    value.val = 0;      //semiId[1] BufA是否可读
    if(semctl(semId, 1, SETVAL, value)==-1){
        printf("SemCtl error!");
        exit(-1);
    }
    value.val = 1;      //semiId[2] BufB是否可写
    if(semctl(semId, 2, SETVAL, value)==-1){
        printf("SemCtl error!");
        exit(-1);
    }
    value.val = 0;      //semiId[3] BufB是否可读
    if(semctl(semId, 3, SETVAL, value)==-1){
        printf("SemCtl error!");
        exit(-1);
    }

    //文件路径
    char source_file_path[100];
    char destination_file_path[100];
    scanf("%s", source_file_path);
    scanf("%s", destination_file_path);

    //尝试打开文件
    int source_fd, destination_fd;
    if((source_fd=open(source_file_path,O_RDONLY))==-1){
        fprintf(stderr, "Open\'%s\'Error:%s\n", source_file_path, strerror(errno));
        return -1;
    }
    close(source_fd);
    if((destination_fd=open(destination_file_path, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR))==-1){
        fprintf(stderr, "Open\'%s\'Error:%s\n", destination_file_path, strerror(errno));
        return -1;
    }
    close(destination_fd);

    //创建文件誊写子进程
    pid_t pid_s_a, pid_a_b, pid_b_d;
    int status_s_a, status_a_b, status_b_d;
    if((pid_s_a=fork())==0){
        //process from source to bufA
        char * argv[] = {(char *)"f1", source_file_path, destination_file_path, nullptr};
        execv("./f1", argv);
        printf("fork1 error!\n");
    }
    else if((pid_a_b=fork())==0){
        //process from bufA to bufB
        char * argv[] = {(char *)"f2", source_file_path, destination_file_path, nullptr};
        execv("./f2", argv);
        printf("fork2 error!\n");
    }
    else if((pid_b_d=fork())==0){
        //process from bufB to destination
        char * argv[] = {(char *)"f3", source_file_path, destination_file_path, nullptr};
        execv("./f3", argv);
        printf("fork3 error!\n");
    }

    //等待子进程结束
    waitpid(pid_s_a, &status_s_a, 0);
    waitpid(pid_a_b, &status_a_b, 0);
    waitpid(pid_b_d, &status_b_d, 0);

    //释放信号灯
    if(semctl(semId, 0, IPC_RMID)==-1){
        printf("semCtl:%s\n", strerror(errno));
        exit(-1);
    }

    //回收共享内存
    shmctl(shareMemIdA, IPC_RMID, 0);
    shmctl(shareMemIdB, IPC_RMID, 0);


    return 0;
}
