#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>

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

        string input;
        getline (cin, input);
        write(fd[1], input.c_str(), input.length());
    }
    else // child process
    {
        close(fd[1]);

        int file = open(output_file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
        
        dup2(fd[0], STDIN_FILENO);
        dup2(file, STDERR_FILENO);
        dup2(file, STDOUT_FILENO);


        int result = execlp(blackbox, "blackbox", NULL);
    }
}