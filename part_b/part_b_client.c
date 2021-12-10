#include <fcntl.h>
#include <unistd.h>
#include "part_b.h"


void
part_b_program_1(char *host, char *blackbox, int number1, int number2, char* output_file)
{
	CLIENT *clnt;
	output  *result_1;
	input  part_b_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, PART_B_PROGRAM, PART_B_VERSION, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	part_b_1_arg.number1 = number1;
	part_b_1_arg.number2 = number2;
	part_b_1_arg.path = blackbox;
	result_1 = part_b_1(&part_b_1_arg, clnt);
	if (result_1 == (output *) NULL) {
		clnt_perror (clnt, "call failed");
	} else {
		int file = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		dup2(file, STDOUT_FILENO);
		printf("%s", result_1->result);
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;
	char *blackbox;
	char *output_file;

	if (argc < 4) {
		printf ("arg error\n");
		exit (1);
	}


	int number1;
    int number2;

    scanf("%d", &number1);
    scanf("%d", &number2);

	printf("%d, %d\n", number1, number2);
	
	blackbox = argv[1];
	output_file = argv[2];
	host = argv[3];

	part_b_program_1 (host, blackbox, number1, number2, output_file);
exit (0);
}
