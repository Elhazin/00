#include <stdio.h>
 #include <unistd.h>
 #include <string.h>
#include <limits.h>
 #include <stdlib.h>
 #include <sys/wait.h>
 #include <fcntl.h>
 #include <signal.h>
 #include <readline/history.h>
 #include <readline/readline.h>
 #include <fcntl.h>
 int main()
 {
    int fd = open("wc.c", O_RDWR);
    int d = open("wc.c", O_RDWR);
    printf("%d   %d", fd, d);
 }