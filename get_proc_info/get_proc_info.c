#include <linux/kernel.h>
#include <linux/unistd.h>
#include <asm/current.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/errno.h>

struct proc_info { //info about a single process
	pid_t pid; //pid of the process
	char name[16]; //file name of the program executed
};
struct procinfos { //info about processes we need
	long studentID; //for the assignment testing  
	struct proc_info proc; //process with pid or current process
	struct proc_info parent_proc; //parent process
	struct proc_info oldest_child_proc; //oldest child process
};


SYSCALL_DEFINE2(get_proc_info, pid_t, pid, struct procinfos*, info) {
	struct task_struct *proc = NULL; //process with pid entered
	struct task_struct *parent = NULL; //parent of process
	struct task_struct *child = NULL; //oldest child of process
	struct procinfos temp_info;

	printk(KERN_INFO "PID: %d\n", pid);

	//Student ID
	temp_info.studentID = 1814220;

	//Exception
	if (pid < -1) return EINVAL;

	//Check pid entered from user
	if (pid == -1) proc = current;
	else proc = find_task_by_vpid(pid);
	if (proc == NULL) return EINVAL;

	//Infomation of process
	temp_info.proc.pid = proc->pid;
	strcpy(temp_info.proc.name, proc->comm);

	//Parent of process
	parent = proc->parent;
	if (proc == parent) {
		temp_info.parent_proc.pid = -1;
		strcpy(temp_info.parent_proc.name, "Not found");
	} else {
		temp_info.parent_proc.pid = parent->pid;
		strcpy(temp_info.parent_proc.name, parent->comm);
	}
	
	//Oldest child of process
	if (list_empty_careful(&proc->children)) {
		temp_info.oldest_child_proc.pid = -1;
		strcpy(temp_info.oldest_child_proc.name, "Not found");
	} else {
		child = list_first_entry(&proc->children, struct task_struct, sibling);
		temp_info.oldest_child_proc.pid = child->pid;
		strcpy(temp_info.oldest_child_proc.name, child->comm);
	}
	copy_to_user(info, &temp_info, sizeof(struct procinfos));
	return 0;
}

