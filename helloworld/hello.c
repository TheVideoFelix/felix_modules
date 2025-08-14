#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

//Module description
MODULE_LICENSE("GPL");
MODULE_AUTHOR("TheVideoFelix");
MODULE_DESCRIPTION("My first Arch Linux kernel module.");

//Module parms

static char* kernel_name = "Kernel";
module_param(kernel_name, charp, 0664);

//Module parms description

MODULE_PARM_DESC(kernel_name, "An string, wich will be display in the loading/unloading message.");

static int __init hello_start(void) {
    printk(KERN_INFO "Hello, %s! I am loaded.\n", kernel_name);
    return 0;
}

static void __exit hello_end(void) {
    printk(KERN_INFO "Goodbye, %s. I am unloaded.\n", kernel_name);
}

module_init(hello_start);
module_exit(hello_end);