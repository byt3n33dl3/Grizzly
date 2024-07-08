#ifndef __MODULE_H_INCLUDED__
#define __MODULE_H_INCLUDED__

#include "handlers.h"

#include <linux/ioctl.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/version.h>

#define _IOCTL(id) _IOWR('h', (id), struct driver_io)
#define IOCTL_BUFFER_OVERFLOW _IOCTL(0)

static int __init mydriver_init(void);
static void __exit mydriver_exit(void);
static long mydriver_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

#endif /* !__MODULE_H_INCLUDED__ */