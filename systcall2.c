#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

int main()
{
    struct dirent *entry;
    DIR *dir = opendir(".");

    if (dir == NULL)
    {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        struct stat file_stat;
        stat(entry->d_name, &file_stat);
        printf("Name: %s, Size: %ld bytes.\n", entry->d_name, file_stat.st_size);
    }

    closedir(dir);
    return 0;
}
