#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc,char* argv[]) {
	int pid = fork();
	if(pid < 0)
		printf(1,"Fork failed");
	else if(pid == 0) {
		exec(argv[1],argv + 1);
	}
	else {
		int wtime[1];
		int rtime[1];
		waitx(wtime,rtime);
		printf(1,"Wait Time: %d\nRun Time: %d\n",wtime[0],rtime[0]);
	}
}