#include <get_proc_info.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	pid_t mypid = atoi(argv[1]);
	printf("PID: %d\n", mypid);
	struct procinfos info;

	if (sys_get_proc_info(mypid, &info) == 0) {
		printf("My SID: %lu\n", info.studentID);
		printf("Pid proc: %d\n", info.proc.pid);
		printf("Name proc: %s\n", info.proc.name);
		printf("Pid parent: %d\n", info.parent_proc.pid);
		printf("Name parent: %s\n", info.parent_proc.name);
		printf("Pid oldest_chid: %d\n", info.oldest_child_proc.pid);
		printf("Name oldest_child: %s\n", info.oldest_child_proc.name);
	}else{
		printf("Cannot get info\n");
	}
}
