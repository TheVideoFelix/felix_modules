#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/random.h>


#ifndef PROC
#define PROC_NAME "fortune"
#define NUM_MESSAGES 20
#define PROC 1
#endif

static struct proc_dir_entry *proc_file;

static const char *messages[NUM_MESSAGES] = {
    "Hello World!\n",
    "Fortune favors the bold.\n",
    "Linux is awesome!\n",
    "Arch Linux rocks!\n",
    "Kernel modules are fun!\n",
    "Stay curious, keep learning.\n",
    "The journey is the reward.\n",
    "Code is poetry.\n",
    "Open source for the win!\n",
    "Arch: Keep it simple.\n",
    "Every bug is an opportunity.\n",
    "Reboot and try again.\n",
    "Hack the planet!\n",
    "Kernel hacking is cool.\n",
    "Read the docs.\n",
    "Don't panic.\n",
    "Think twice, code once.\n",
    "Keep calm and sudo.\n",
    "The cake is a lie.\n",
    "May the source be with you.\n"
};

static ssize_t proc_read(struct file* file, char __user* ubuf, size_t count, loff_t* ppos) {
    char msg_buf[128];
    int msg_idx;
    size_t msg_len;
    
    if (*ppos > 0) {
        return 0;
    }

    get_random_bytes(&msg_idx, sizeof(msg_idx));
    msg_idx = msg_idx & 0x7FFFFFFF;
    msg_idx = msg_idx % NUM_MESSAGES;

    msg_len = strlen(messages[msg_idx]);
    if (msg_len > sizeof(msg_buf) - 1) {
        msg_len = sizeof(msg_buf) -1;
    }

    strncpy(msg_buf, messages[msg_idx], msg_len);
    msg_buf[msg_len] = '\0';

    if (copy_to_user(ubuf, message, message_len)) {
        return -EFAULT;
    }

    *ppos = msg_len;
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
