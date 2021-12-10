#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "part_b.h"

output *
part_b_1_svc(input *argp, struct svc_req *rqstp)
{
	static output  result;
	
	int number1 = argp->number1;
	int number2 = argp->number2;
	char *blackbox = argp->path;
	write(1, blackbox, sizeof(blackbox));

	int fd1[2];
	int fd2[2];
    pipe(&fd1[0]);
    pipe(&fd2[0]);

	char output[100] = { '\0' };

	int pid;
	if ((pid = fork()) == 0) // child process
    {
        close(fd1[1]);
        close(fd2[0]);

		dup2(fd1[0], STDIN_FILENO);

        dup2(fd2[1], STDERR_FILENO);
        dup2(fd2[1], STDOUT_FILENO);

        execlp(blackbox, "blackbox", NULL);
    }

	close(fd1[0]);
    close(fd2[1]);

	char s1[20] = { '\n' };
	char s2[20] = { '\n' };

	sprintf(s1, "%d", number1);
	sprintf(s2, "%d", number2);

	strcat(s1, " ");
	strcat(s1, s2);


	write(fd1[1], s1, sizeof(s1));
    close(fd1[1]);

	read(fd2[0], output, sizeof(output));
	close(fd2[0]);

	write(1, output, sizeof(output));

	int status;
    waitpid(pid, &status, 0);
    result.message = output;
	result.status_code = status;

	return &result;
}
