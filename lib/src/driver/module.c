#include "module.h"

struct file_operations fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = mydriver_ioctl
};

static struct miscdevice device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "driver",
    .fops = &fops
};

static int __init mydriver_init(void) { return misc_register(&device); }

static void __exit mydriver_exit(void) { misc_deregister(&device); }

static long mydriver_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    void __user *user_arg = (void __user *)arg;

    switch (cmd)
    {
    case IOCTL_BUFFER_OVERFLOW:
        return buffer_overflow_handler(user_arg);    
    default:
        return -ENOIOCTLCMD;
    }
}

module_init(mydriver_init);
module_exit(mydriver_exit);

MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Goliguzov Aleksei");
MODULE_DESCRIPTION("driver");
