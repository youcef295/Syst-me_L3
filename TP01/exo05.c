#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void fin_programme(int sig)
{
    printf("\n Au revoir !\n");
    exit(25);
}

void test01()
{
    printf("Debut du programme !\n");
    sleep(10);
    printf("Fin du programme !\n");
}

void test02()
{
    printf("Debut du programme !\n");
    pid_t pid = fork();
    if (pid == 0)
    {
        printf("je suis le fils j'attend 5s !\n");
        sleep(5);
        kill(getppid(), SIGINT);
    }
    else
    {
        signal(SIGINT, fin_programme);
        sleep(10);
        printf("Fin du programme !\n");
        wait(NULL);
    }
}

int main(void)
{
    signal(SIGINT, fin_programme);

    test01();
    //test02();

    return 0;
}
