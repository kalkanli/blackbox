#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[])
{
    char *blackbox = argv[1];
    char *output_file_name = argv[2];

    int fd1[2];
    int fd2[2];
    pipe(&fd1[0]);
    pipe(&fd2[0]);

    char output[100] = {'\0'};

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

    string number1;
    string number2;
    getline(cin, number1);
    getline(cin, number2);
    string input = number1 + " " + number2;
    write(fd1[1], input.c_str(), input.length());
    close(fd1[1]);

    int file = open(output_file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
    dup2(file, STDOUT_FILENO);

    read(fd2[0], output, sizeof(output));
    close(fd2[0]);

    int status;
    waitpid(pid, &status, 0);
    if (status == 0)
    {
        printf("SUCCESS:\n");
    }
    else
    {
        printf("FAIL:\n");
    }

    printf("%s", output);
}