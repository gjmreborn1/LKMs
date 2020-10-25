#include <linux/init.h>
#include <linux/module.h>
#include <linux/current.h>
#include <linux/kernel.h>
#include <unistd.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Grzegorz Malyska");
MODULE_DESCRIPTION("Process info iteration.");
MODULE_VERSION("0.01");

static int __init init(void) {
	// Create second process
	pid_t pid = fork();
	if(pid == 0) {
		execve("/bin/ls", NULL, NULL);
	} else if(pid < 0) {
		printk(KERN_ERR "fork error\n");
	}

	printk(KERN_INFO "PID = %d\n", current->pid);

	// Play with current process state
	printk(KERN_INFO "Process state = %d\n", current->state);
	set_current_state(TASK_INTERRUPTIBLE);
	printk(KERN_INFO "Process state = %d\n", current->state);
	set_current_state(TASK_RUNNING);
	printk(KERN_INFO "Process state = %d\n", current->state);

	printk(KERN_INFO "Parent PID = %d\n", current->real_parent->pid);

	// iterate over process children
	struct task_struct *task;
	struct list_head *list;
	list_for_each(list, &current->children) {
		task = list_entry(list, struct task_struct, sibling);
		printk(KERN_INFO "Child PID = %d\n", task->pid);
	}

	// iterating from current process to init (init is parent of all processes)
	for(task = current; task != &init_task; task = task->real_parent)
		;
	printk(KERN_INFO "Init PID = %d\n", task->pid);

	// next task
	task = next_task(current);
	printk(KERN_INFO "Next task's PID = %d\n", task->pid);

	// previous task
	task = prev_task(current);
	printk(KERN_INFO "Previous task's PID = %d\n", task->pid);

	printk(KERN_INFO "Preempt count = %d\n", current_thread_info()->preempt_count);

	// iterate over all processes
	for_each_process(task) {
		printk(KERN_INFO "%s[%d]\n", task->comm, task->pid);
	}

	return 0;
}

static void __exit deinit(void) {
}

module_init(init);
module_exit(deinit);
