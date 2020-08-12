#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1024
char read_from_dev[BUFSIZE];
char write_to_dev[BUFSIZE];

int main(){
    int num = 0;
    char c;
    int dev;
    printf("请输入写入设备的字符流：\n");
    while((c=getchar())!='`'){
        write_to_dev[num++] = c;
    }

    if((dev=open("/dev/MyDev", O_RDWR))==-1){
        printf("打开设备失败\n");
        return -1;
    }
    printf("打开设备成功\n");
    write(dev, write_to_dev, num);  //写设备
    lseek(dev, 0, SEEK_SET);
    read(dev, read_from_dev, num);  //读设备
    printf("读出设备内容为：\n");
    printf("%s", read_from_dev);

    return 0;
}