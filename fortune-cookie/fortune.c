#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/string.h>

#define PROC_NAME "fortune"

static struct proc_dir_entry *proc_file;

static const char *message = "Hello World!\n";
static int message_len;

static ssize_t proc_read(struct file* file, char __user* ubuf, size_t count, loff_t* ppos) {
    if (*ppos > 0) {
        return 0;
    }

    if (copy_to_user(ubuf, message, message_len)) {
        return -EFAULT;
    }

    *ppos = message_len;

    return message_len;
}

static const struct proc_ops my_fops = {
    .proc_read = proc_read,
};


static int __init fortune_start(void) {

    proc_file = proc_create(PROC_NAME, 0444, NULL, &my_fops);
    if (proc_file == NULL) {
        return -ENOMEM;
    }

    message_len = strlen(message);
    printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
    return 0;
}

static void __exit fortune_end(void) {
    proc_remove(proc_file);
    printk(KERN_INFO "/proc/%s removed\n", PROC_NAME);
}



module_init(fortune_start);
module_exit(fortune_end);


//Module description
MODULE_LICENSE("GPL");
MODULE_AUTHOR("TheVideoFelix");
MODULE_DESCRIPTION("My first Arch Linux kernel module.");
