#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>    // Pour les fork
#include <sys/types.h> // Pour le pid

int first_fork()
{
    printf("Avant exec\n"); // Pour faire la vérification 
    // On lance exec 
    if (execl("/home/boualili/Bureau/Système/TP01/exo03", "exo03", NULL) == -1)
    {
        perror("Erreur lors de exec");
        exit(EXIT_FAILURE);
    }

    printf("Après exec \n");// Pour faire la vérification 
    fork();
    fork();
    fork();
    fork();

    return EXIT_SUCCESS;
}

int second_fork()
{
    fork();
    printf("Avant exec\n");// Pour faire la vérification 
    if (execl("/home/boualili/Bureau/Système/TP01/exo03", "exo03", NULL) == -1)
    {
        perror("Erreur lors de exec");
        exit(EXIT_FAILURE);
    }

    printf("Après exec \n");// Pour faire la vérification 
    fork();
    fork();

    return EXIT_SUCCESS;
}

int main(void)
{
    //first_fork();
    second_fork();
    return 0;
}
