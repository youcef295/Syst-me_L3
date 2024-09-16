#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>    // Pour les fork
#include <sys/types.h> // Pour le pid

/*Écrivez en C un programme qui affiche “Bonjour”, attend 5 secondes et affiche “Au revoir” avant
de se terminer.*/
int test(){
    printf("Avant exec\n");
    execl("~/Bureau/Système/TP01", "tp01", NULL); // Remplacement du processus
    printf("Après exec (ne devrait jamais être affiché)\n");
    fork();
    fork();
    fork();
    fork(); 
    return EXIT_SUCCESS;
}

int main(void)
{
    // printf("Bonjours\n");
    // sleep(5);
    // printf("Au revoir\n");

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
        printf("Je termine !!!\n");
        exit(5);
    }
    //On est sur le père
    else
    {
        printf("%d : Je suis le processus pére et %d est mon fils\n", getpid(), pid);
        sleep(5);
        printf("Je termine !!!\n");
    }
    test();

    return 0;
}