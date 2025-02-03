#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define BUF_SIZE 4095
int main()
{
    int fd1, fd2, bytes_read;
    char buffer[BUF_SIZE];
    fd1 = open("inputtst", O_RDONLY);
    if (fd1 == -1)
    {
        perror("Error opening the first file");
        return 1;
    }
    fd2 = open("outputtst", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd2 == -1)
    {
        perror("Error opening the second file");
        close(fd1);
        return 1;
    }
    while ((bytes_read = read(fd1, buffer, BUF_SIZE)) > 0)
    {
        if (write(fd2, buffer, bytes_read) != bytes_read)
        {
            perror("Error writing to the second file");
            close(fd1);
            close(fd2);
            return 1;
        }
    }
    if (bytes_read == -1)
    {
        perror("Error reading from the first file");
        close(fd1);
        close(fd2);
        return 1;
    }
}