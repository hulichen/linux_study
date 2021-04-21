#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() 
{
    char *str = NULL;
    memcpy(str, "nihaoa", 1);
    int i;
    for (i = 0; i <= 255; i++) {
        printf("%s\n", strerror(i));
    }
    /*
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork error");
        return -1;
    }
    perror("fork error");
    */
    return 0;
}
