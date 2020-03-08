#include "unistd.h"
#include "fcntl.h"
#include "cstdio"
#include "sys/stat.h"
#include "cerrno"
#include "cstring"

#define  BUF_SIZE 1024


int main(int argc, char ** argv) {
    int from_fd, to_fd;
    int bytes_read, bytes_write;
    char buf[BUF_SIZE];
    char *ptr;

    //cp
    if(argc!=4 && argc!=5){
        fprintf(stderr, "Format error\nUsage: cp source destination\n       cp -i source destination\n");
        return -1;
    }
    if(strcmp(argv[1], "cp")){
        fprintf(stderr, "Command \'%s\' not found\n\a", argv[1]);
        return -1;
    }
    // cp source destination
    if(argc == 4){
        if((from_fd=open(argv[2], O_RDONLY)) == -1){
            fprintf(stderr, "Open%sError:%s\n", argv[2], strerror(errno));
            return -1;
        }
        if((to_fd=open(argv[3], O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR)) == -1){    //#
            fprintf(stderr, "Open%sError:%s\n", argv[3], strerror(errno));
            return -1;
        }
    }

    // cp -i source destination
    if(argc == 5){
        if(strcmp(argv[2], "-i")){
            fprintf(stderr, "Format error\n\a");
            return -1;
        }
        if((from_fd=open(argv[3], O_RDONLY)) == -1){
            fprintf(stderr, "Open%sError:%s\n", argv[3], strerror(errno));
            return -1;
        }
        //目标文件如果存在,询问是否覆盖
        if(access(argv[4], F_OK)==0){
            fprintf(stdout,"cp：是否覆盖\'%s\'？ " ,argv[4] );
            if(getchar()!='y'){
                return 1;
            }
            //对目标文件是否有写权限
            if(access(argv[4], W_OK)!=0){
                fprintf(stderr, "cp:无写权限\'%s\'\n", argv[4]);
                return -1;
            }
        }
        if((to_fd=open(argv[4], O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR)) == -1){    //#
            fprintf(stderr, "Open%sError:%s\n", argv[4], strerror(errno));
            return -1;
        }
    }

    //开始文件复制
    while((bytes_read=read(from_fd, buf, BUF_SIZE))){
        //如果出现异常且不是由中断信号引起的,则出错;否则可以继续运行
        if(bytes_read==-1 && errno==!EINTR){
            break;
        }
        else if(bytes_read > 0){
            ptr = buf;
            while((bytes_write=write(to_fd, ptr, bytes_read))){
                //出现错误
                if(bytes_read==-1 && errno==!EINTR){
                    break;
                }
                //一次性写完
                else if(bytes_read == bytes_write){
                    break;
                }
                //继续写
                else if(bytes_write > 0){
                    ptr += bytes_write;
                    bytes_read -= bytes_write;
                }
            }
            if(bytes_write == -1){
                break;
            }
        }
    }
    close(from_fd);
    close(to_fd);
    return 1;
}
