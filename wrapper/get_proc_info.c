#include "get_proc_info.h"
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

#define SIZE 200

long sys_get_proc_info(pid_t pid, struct procinfos *info) {
	long sys_return_value;
	//unsigned long info[SIZE];
	sys_return_value = syscall(335, pid, info);
	/*printf("PID: %d\n", pid);
	printf("My SID: %lu\n", info->studentID);
	printf("Pid proc: %d\n", info->proc.pid);
	printf("Name proc: %s\n", info->proc.name);
	printf("Pid parent proc: %d\n", info->parent_proc.pid);
	printf("Name parent proc: %s\n", info->parent_proc.name);
	printf("Pid oldest child proc: %d\n", info->oldest_child_proc.pid);
	printf("Name oldest child proc: %s\n", info->oldest_child_proc.name);*/
	return sys_return_value;
}
