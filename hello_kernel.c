#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Grzegorz Malyska");
MODULE_DESCRIPTION("Hello world Linux kernel module.");
MODULE_VERSION("0.01");

static int __init init(void) {
	/*
		It inserts code into syslog.

		priorities:
			KERN_INFO
			KERN_ERR
	*/

	printk(KERN_INFO "Hello world!\n");
	printk(KERN_ERR "Some error occurred!\n");

	return 0;
}

static void __exit deinit(void) {
	printk(KERN_INFO "Goodbye world!\n");
}

module_init(init);
module_exit(deinit);
