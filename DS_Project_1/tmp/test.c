#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BS 100

void _itoa(int n, char s[])
{
    int i = 0, j = 0, sign;

    do
    {                          /* generate digits in reverse order */
        s[i++] = n % 10 + '0'; /* get next digit */
    } while ((n /= 10) > 0);   /* delete it */
    s[i] = '\0';

    char c;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

const char *get_process_name(pid_t pid, char *buff)
{
    char str[BS], tmp[BS];

    _itoa((int)pid, tmp);
    strcat(tmp, " -o comm= | tr -d '\n'");
    strcat(str, "ps -p ");
    strcat(str, tmp);
    FILE *fp = popen(str, "r");
    if (fp == NULL)
    {
        perror("popen() 실패\n");
        return NULL;
    }
    fgets(buff, BS, fp);
    pclose(fp);
    return (buff);
}

int main()
{
    char buff[BS];
    // int pid = atoi(av[1]);
    // printf("THIS is PID: %d\n", pid);
    // printf("THIS is PNAME: %s\n", gpn(pid));
    // system("ps -p 2816 -o comm= ");
    printf("%s", get_process_name(1, buff));
    sleep(10);
    int fd = open("abc.txt", O_RDWR);
    sleep(5);
    close(fd);
    return (0);
}