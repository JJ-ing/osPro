    obj-m := MyDriver.o    #������������������c�ļ���.o
    PWD := $(shell pwd)
    KERNELDIR := /lib/modules/5.3.0-46-generic/build   #��Ҫ��װmod���ں˰汾 
all:
	make -C $(KERNELDIR) M=$(PWD) modules
 
 
.PHONY: clean
clean:
	rm -rf *.o *~ core *.ko *.mod.c modules.order Module.symvers
