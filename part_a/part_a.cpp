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

    char output[100] = { '\0' };

    int pid = fork();
    if (pid > 0) // parent process
    {
        close(fd1[0]);
        close(fd2[1]);

        string input;
        getline (cin, input);
        write(fd1[1], input.c_str(), input.length());
        close(fd1[1]);

        int file = open(output_file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
        dup2(file, STDOUT_FILENO);
        
        read(fd2[0], output, sizeof(output));
        close(fd2[0]);
    }
    else // child process
    {
        close(fd1[1]);
        close(fd2[0]);
        
        dup2(fd1[0], STDIN_FILENO);
        
        dup2(fd2[1], STDERR_FILENO);
        dup2(fd2[1], STDOUT_FILENO);
        
        execlp(blackbox, "blackbox", NULL);
    }


    int status;
    waitpid(pid, &status, 0);
    if(status == 0) {
        printf("SUCCESS:\n");
    } 
    else
    {
        printf("FAIL:\n");
    }

    printf("%s", output);

    
}