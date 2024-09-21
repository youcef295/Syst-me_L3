#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>    // Pour les fork
#include <sys/types.h> // Pour le pid
#include <sys/wait.h>  // Pour le wait

/*Écrivez en C un programme qui affiche “Bonjour”, attend 5 secondes et affiche “Au revoir” avant
de se terminer.*/
void question01()
{
    printf("Bonjours\n");
    sleep(5);
    printf("Au revoir\n");
}

int question02()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        fprintf(stderr, "fork failed\n");
        return 1;
    }
    // On est sur le fils
    if (pid == 0)
    {
        printf("%d : Je suis le processus fils et %d est mon pére\n", getpid(), getppid());
        sleep(2);
        printf("Je suis le fils et je termine !!!\n");
        return 0;
    }
    // On est sur le père
    else
    {
        printf("%d : Je suis le processus pére et %d est mon fils\n", getpid(), pid);
        sleep(5);
        printf("Je suis le père et je termine !!!\n");
        wait(NULL);
    }
    return 0;
}

int main(void)
{

    // Question 01
    question01();

    // Question 02
    question02();

    return 0;
}