#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdlib.h>

#define SIZE 200

struct proc_info{
	char name[16];
	pid_t pid;
};

struct procinfos{
	long studentID;
	struct proc_info proc;
	struct proc_info parent_proc;
	struct proc_info oldest_child_proc;
};

int main(int argc, char* argv[]) {
	long sys_return_value;
	struct procinfos info;
	//info = (struct procinfos*) malloc(sizeof(struct procinfos));
	//unsigned long info1[SIZE];
	sys_return_value = syscall(335, -2, &info);
	if (sys_return_value ==0 ){
	//printf("My student ID: %lu\n", info1[1]);
	printf("My SID: %lu\n", info.studentID);
	printf("PID_proc: %d\n", info.proc.pid);
	printf("Name_proc: %s\n", info.proc.name);
	printf("PID_parent_proc: %d\n", info.parent_proc.pid);
	printf("Name_parent_proc: %s\n", info.parent_proc.name);
	printf("PID_oldest_child_proc: %d\n", info.oldest_child_proc.pid);
	printf("Name_oldest_child_proc: %s\n", info.oldest_child_proc.name);}
	else printf("Fault\n");
	return 0;
}
