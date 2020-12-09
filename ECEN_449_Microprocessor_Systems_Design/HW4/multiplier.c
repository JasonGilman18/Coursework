#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
//#include <asm/io.h>
#include <linux/moduleparam.h>
//#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/slab.h>


#define DEVICE_NAME "multiplier"    //name of module
#define BUF_LEN 80  //length of the reading buffer

static int Major;   //major number returned from the device registration
static int Device_Open = 0; //keep track of if the device is open or closed.
char* msg_buffer;

//function headings
static int __init my_init(void);
static void __exit my_exit(void);
static int device_open(struct inode *inode, struct file *file);
static int device_release(struct inode *inode, struct file *file);
static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t* offset);
static ssize_t device_write(struct file *file, const char __user *buffer, size_t length, loff_t offset);

/* This structure defines the function pointers to our functions for
   opening, closing, reading and writing the device file.  There are
   lots of other pointers in this structure which we are not using,
   see the whole definition in linux/fs.h */
static struct file_operations fops = {
  .read = device_read,
  .write = device_write,
  .open = device_open,
  .release = device_release
};

//setup all data structures, this is run when the module first loads
static int __init my_init(void)
{
    //map virtual to physical address before registering the device
    //printk(KERN_INFO "multiplier virtual address 0x%x\n", virt_addr);
    
    //register the device, negative return number mean failure
    Major = register_chrdev(0, DEVICE_NAME, &fops);
    
    if(Major < 0)   //handle failure, and output the number
    {
        printk(KERN_ALERT "Registering char device failed with %d\n", Major);
        return Major;
    }
    else    //handle success and output 
    {
        printk(KERN_INFO "Registered a device with dynamic Major number of %d\n", Major);
        printk(KERN_INFO "Create a device file for this device with this command:\n'mknod /dev/%s c ?d 0'.\n", DEVICE_NAME, Major);
    }
    return 0;
}

//function is run when the module is unloaded from system. cleanup and data structs used
static void __exit my_exit(void)
{
    //unregister since device has been registered
    unregister_chrdev(Major, DEVICE_NAME);
    
    //unmap the virt pointer
    //iounmap((void*)virt_addr);
}

//This is called when the device is trying to open
static int device_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "The device has been opened");
    
    return 0;
}

//called when the device is closed
static int device_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "The device has been closed");
    
    return 0;
}


//called when a process using the device tries to make a read call
static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t* offset)
{
    /*
    int bytes_read = 0; //keep track of the number of bytes written to the buffer
    
    int* readBuffer = (int*)kmalloc(length*sizeof(int), GFP_KERNEL);    //allocate space to for buffer to read numbers from memeory
    //readBuffer[0] = ioread32(virt_addr+0);  //read in ints from kernel memory
    //readBuffer[1] = ioread32(virt_addr+4);
    //readBuffer[2] = ioread32(virt_addr+8);
    char* charBuffer = (char*)readBuffer; //cast read in ints to char
    
    int i;
    for(i=0;i<length;i++)
    {
        //data is in kernel segment, so it needs to be moved to the user segment
        put_user(*(charBuffer++), buffer++);
        bytes_read++;
    }
    
    kfree(readBuffer);
    return bytes_read;
    */

   int i;
   for(i=0;i<length;i++)
   {
       put_user(*(msg_buffer++), buffer++);
   }

   return i;

}

//called when a process tries to write to the device file
static ssize_t device_write(struct file *file, const char __user *buffer, size_t length, loff_t offset)
{
    /*
    char* charBuffer = (char*)kmalloc((length+1) * sizeof(char), GFP_KERNEL);   //write from this buffer to user buffer
    
    int i;
    for(i = 0; i<length; i++)
    {
        get_user(charBuffer[i], buffer + i); //place char from user space to kernel buffer
    }
    
    charBuffer[length] = '\0';
    int* intBuffer = (int*)charBuffer;
    
    //write to reg0
    iowrite32(intBuffer[0], virt_addr+0);
    //write to reg1
    iowrite32(intBuffer[1], virt_addr+4);
    
    printk(KERN_INFO "Writing %d to reg0\n Writing %d to reg1\n", intBuffer[0], intBuffer[1]);
    
    kfree(intBuffer);
    return i; //number of times written
    */

    msg_buffer = (char*)kmalloc((length+1))*sizeof(char)+4, GFP_KERNEL);

    int i;
    for(i=0;i<length;i++)
    {
        get_user(msg_buffer[i], buffer + i);
    }

    msg_buffer[length] = '\0';
    int* temp_buffer = (int*)msg_buffer;

    int mult_result = temp_buffer[0] * temp_buffer[1];

    msg_buffer[i+1] = mult_result;

    return i;

}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jason Gilman (and others)");
MODULE_DESCRIPTION("multiplier module");

module_init(my_init);
module_exit(my_exit);
