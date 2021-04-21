#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int func() {
    _exit(257);
}
int main()
{
    fork();
    perror("fork error");
    printf("leihou~");
    //sleep(3);
    func();
    printf("nihaoa~~\n");
    return 0;
}
