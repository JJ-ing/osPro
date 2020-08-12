#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <asm/current.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/sched.h>
MODULE_LICENSE("GPL");

#define DEV_BUFF_SIZE 1024  
#define DEV_NAME "MyDev"
char* DevBuffP = NULL;  //设备缓冲区
static int file_end = 0;     //设备文件尾位置

static struct cdev *DevP = NULL;
static int major = 0;
static int minor = 0;
const int count = 2;


//打开设备
static int my_open(struct inode *inode, struct file *file){
    //绑定设备缓冲区
    file->private_data = DevBuffP;
    file_end = 0;
    //get major and minor from inode
    printk(KERN_INFO "(major=%d, minor=%d), %s : %s : %d\n", 
        imajor(inode), iminor(inode), __FILE__, __func__, __LINE__);
    return 0;
}

//关闭设备
static int my_release(struct inode *inode, struct file *filp){
    //get major and minor from inode 
    printk(KERN_INFO "(major=%d, minor=%d), %s : %s : %d\n", 
        major, minor, __FILE__, __func__, __LINE__);
    return 0;
}

//读设备
static ssize_t my_read(struct file *file, char __user *buf, size_t count, loff_t *p_cfo){   //注意buf前没有const修饰！
    int ret = 0;
    //从内核copy到用户空间
    if(copy_to_user(buf,(file->private_data)+(*p_cfo), count)){
        ret = -EFAULT;
    }
    else{
        (*p_cfo) += count;  //文件指针偏移
        ret = count;
    }
    return ret;
}

//写设备
static ssize_t my_write(struct file *file, const char __user *buf, size_t count, loff_t *p_cfo){
    int ret = 0;
    if(copy_from_user((file->private_data)+(*p_cfo), buf, count)){
        ret = -EFAULT;
    }
    else{
        (*p_cfo) += count;  //文件指针偏移
        file_end += count;
        ret = count;
    }
    return ret;
}

//读写指针移动
static loff_t my_llseek(struct file* file, loff_t offset, int whence){
    loff_t cfo = 0;//current file offset
    if(whence==0){//SEEK_SET
        cfo = offset;
    }
    else if(whence==1){//SEEK_CUR
        cfo = file->f_pos + offset;
    }
    else if(whence==2){//SEEK_END
        cfo = file_end + offset;
    }
    else{
        return -EINVAL;
    }
    if(cfo<0 || cfo>DEV_BUFF_SIZE){//越界
        return -EFAULT;
    }
    file->f_pos = cfo;
    return cfo;
}

//设备操作方法集
struct file_operations fops={
        .owner = THIS_MODULE,
        .open = my_open,
        .release= my_release,
        .read = my_read,
        .write = my_write,
        .llseek = my_llseek,
        };


//设备初始化
static int __init my_init(void){
    /* 老方法 */
    //  dev_num = register_chrdev(0,"MyDeviceDriver",&fops);
    /* 新方法 */
    dev_t dev_num;
    int ret;

    //1. 动态创建cdev对象 
    DevP = cdev_alloc(); 
    if(NULL == DevP) { 
        return -ENOMEM; 
    }

    //2. 初始化cdev对象
    cdev_init(DevP, &fops);
    ret = alloc_chrdev_region(&dev_num, minor, count, DEV_NAME);//动态分配设备号
    if(ret){//失败返回
        cdev_del(DevP);//将cdev对象从系统中移除（注销 ）
        return ret;
    }
    major = MAJOR(dev_num);  //取得主设备号

    //3. 注册cdev对象
    ret = cdev_add(DevP, dev_num, count);//主设备号的count个次设备号
    if(ret){//失败返回
        unregister_chrdev_region(dev_num, count);// 释放设备号
        cdev_del(DevP);
        return ret;
    }

    //get command and pid
    // printk(KERN_INFO "(%s:pid=%d), %s : %s : %d - ok.\n", current->comm, current->pid, __FILE__, __func__, __LINE__);
    
    //为设备缓冲区分配空间，open()时绑定到file->private_data
    DevBuffP = kmalloc(sizeof(DEV_BUFF_SIZE), GFP_KERNEL);
    if (!DevBuffP){ 
        printk(KERN_INFO "MyDev: FAIL to get memory\n");
        return -ENOMEM;
        } 
    memset(DevBuffP, 0, DEV_BUFF_SIZE);// 初始化为 0
    return 0;
}     


//设备注销
static void __exit my_exit(void){
    unregister_chrdev_region(MKDEV(major, minor), count);// 释放设备号
    cdev_del(DevP);//将cdev对象从系统中移除(注销)
    kfree(DevBuffP);//注销设备缓冲空间 
}


module_init(my_init);
module_exit(my_exit);




