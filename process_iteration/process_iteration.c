#include <linux/init.h>
#include <linux/module.h>
#include <asm/current.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/init_task.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Grzegorz Malyska");
MODULE_DESCRIPTION("Process info iteration.");
MODULE_VERSION("0.01");

static int __init init(void) {
	struct task_struct *task;
	struct list_head *list;

	printk(KERN_INFO "PID = %d\n", current->pid);

	// Play with current process state
	printk(KERN_INFO "Process state = %ld\n", current->state);
	set_current_state(TASK_INTERRUPTIBLE);
	printk(KERN_INFO "Process state = %ld\n", current->state);
	set_current_state(TASK_RUNNING);
	printk(KERN_INFO "Process state = %ld\n", current->state);

	printk(KERN_INFO "Parent PID = %d\n", current->real_parent->pid);

	// iterate over process children
	printk("Children:\n");
	list_for_each(list, &current->children) {
		task = list_entry(list, struct task_struct, sibling);
		printk(KERN_INFO "\tChild PID = %d\n", task->pid);
	}

	// iterating from current process to init (init is parent of all processes)
	for(task = current; task != &init_task; task = task->real_parent)
		;
	printk(KERN_INFO "Init PID = %d\n", task->pid);

	printk("All processes:\n");
	for_each_process(task) {
		printk(KERN_INFO "Name = %s; PID = %d\n", task->comm, task->pid);
	}

	return 0;
}

static void __exit deinit(void) {
}

module_init(init);
module_exit(deinit);
