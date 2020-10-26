#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Grzegorz Malyska");
MODULE_DESCRIPTION("Linux kernel threads playground.");
MODULE_VERSION("0.01");

int kthread_fn(void *data) {
	int *val = (int *) data;
	
	printk(KERN_INFO "data = %d\n", *val);
	return 0;
}

static int __init init(void) {
	struct task_struct *kthread_ts;
	
	int data = 10;
	kthread_ts = kthread_run(kthread_fn, &data, "my_kthread");
	printk(KERN_INFO "mm = %p\n", kthread_ts->mm);
	
	mdelay(2000);
//	kthread_stop(kthread_ts);


	return 0;
}

static void __exit deinit(void) {
}

module_init(init);
module_exit(deinit);
