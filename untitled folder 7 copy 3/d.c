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
    int fdd = dup(1);
    int ff = open("out", O_RDWR, 0777);
    dup2(ff, 1);
    write(1, "rgfviwuegvieryghviuqroejdghvwruei", 100);
    dup2(fdd, 1);
    write(1, "egtefvewf\n", 11); 
 }