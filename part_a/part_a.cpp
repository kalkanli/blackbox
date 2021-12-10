#include <unistd.h>
#include <iostream>
#include <fcntl.h>

using namespace std;

int main(int argc, char *argv[])
{
    char *blackbox = argv[1];
    char *output_file_name = argv[2];

    int fd[2];
    pipe(&fd[0]);

    int pid = fork();
    if (pid > 0) // parent process
    {
        close(fd[0]);

        int input[2];
        scanf("%d %d", &input[0], &input[1]);
        write(fd[1], input, sizeof(input));
    }
    else // child process
    {

        close(fd[1]);

        int buffer[2];
        read(fd[0], buffer, sizeof(buffer));

        int file = open(output_file_name, O_RDWR | O_CREAT, 666);
        int file2 = dup2(file, 1);
        int file3 = dup2(file, 2);

        

        printf("%d, %d", *buffer, *(buffer + 1));
    }
}