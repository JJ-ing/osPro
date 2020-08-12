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
char* DevBuffP = NULL;  //�豸������
static int file_end = 0;     //�豸�ļ�βλ��

static struct cdev *DevP = NULL;
static int major = 0;
static int minor = 0;
const int count = 2;


//���豸
static int my_open(struct inode *inode, struct file *file){
    //���豸������
    file->private_data = DevBuffP;
    file_end = 0;
    //get major and minor from inode
    printk(KERN_INFO "(major=%d, minor=%d), %s : %s : %d\n", 
        imajor(inode), iminor(inode), __FILE__, __func__, __LINE__);
    return 0;
}

//�ر��豸
static int my_release(struct inode *inode, struct file *filp){
    //get major and minor from inode 
    printk(KERN_INFO "(major=%d, minor=%d), %s : %s : %d\n", 
        major, minor, __FILE__, __func__, __LINE__);
    return 0;
}

//���豸
static ssize_t my_read(struct file *file, char __user *buf, size_t count, loff_t *p_cfo){   //ע��bufǰû��const���Σ�
    int ret = 0;
    //���ں�copy���û��ռ�
    if(copy_to_user(buf,(file->private_data)+(*p_cfo), count)){
        ret = -EFAULT;
    }
    else{
        (*p_cfo) += count;  //�ļ�ָ��ƫ��
        ret = count;
    }
    return ret;
}

//д�豸
static ssize_t my_write(struct file *file, const char __user *buf, size_t count, loff_t *p_cfo){
    int ret = 0;
    if(copy_from_user((file->private_data)+(*p_cfo), buf, count)){
        ret = -EFAULT;
    }
    else{
        (*p_cfo) += count;  //�ļ�ָ��ƫ��
        file_end += count;
        ret = count;
    }
    return ret;
}

//��дָ���ƶ�
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
    if(cfo<0 || cfo>DEV_BUFF_SIZE){//Խ��
        return -EFAULT;
    }
    file->f_pos = cfo;
    return cfo;
}

//�豸����������
struct file_operations fops={
        .owner = THIS_MODULE,
        .open = my_open,
        .release= my_release,
        .read = my_read,
        .write = my_write,
        .llseek = my_llseek,
        };


//�豸��ʼ��
static int __init my_init(void){
    /* �Ϸ��� */
    //  dev_num = register_chrdev(0,"MyDeviceDriver",&fops);
    /* �·��� */
    dev_t dev_num;
    int ret;

    //1. ��̬����cdev���� 
    DevP = cdev_alloc(); 
    if(NULL == DevP) { 
        return -ENOMEM; 
    }

    //2. ��ʼ��cdev����
    cdev_init(DevP, &fops);
    ret = alloc_chrdev_region(&dev_num, minor, count, DEV_NAME);//��̬�����豸��
    if(ret){//ʧ�ܷ���
        cdev_del(DevP);//��cdev�����ϵͳ���Ƴ���ע�� ��
        return ret;
    }
    major = MAJOR(dev_num);  //ȡ�����豸��

    //3. ע��cdev����
    ret = cdev_add(DevP, dev_num, count);//���豸�ŵ�count�����豸��
    if(ret){//ʧ�ܷ���
        unregister_chrdev_region(dev_num, count);// �ͷ��豸��
        cdev_del(DevP);
        return ret;
    }

    //get command and pid
    // printk(KERN_INFO "(%s:pid=%d), %s : %s : %d - ok.\n", current->comm, current->pid, __FILE__, __func__, __LINE__);
    
    //Ϊ�豸����������ռ䣬open()ʱ�󶨵�file->private_data
    DevBuffP = kmalloc(sizeof(DEV_BUFF_SIZE), GFP_KERNEL);
    if (!DevBuffP){ 
        printk(KERN_INFO "MyDev: FAIL to get memory\n");
        return -ENOMEM;
        } 
    memset(DevBuffP, 0, DEV_BUFF_SIZE);// ��ʼ��Ϊ 0
    return 0;
}     


//�豸ע��
static void __exit my_exit(void){
    unregister_chrdev_region(MKDEV(major, minor), count);// �ͷ��豸��
    cdev_del(DevP);//��cdev�����ϵͳ���Ƴ�(ע��)
    kfree(DevBuffP);//ע���豸����ռ� 
}


module_init(my_init);
module_exit(my_exit);




