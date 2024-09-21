#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

/*1-Commencez par écrire un premier programme non-parallèle qui alloue un grand tableau, le remplis
d’entiers aléatoires et recherche toutes les occurences de la valeur 0. Pour chaque occurence trouvée,
affichez un message indiquant son indice.*/

void first_try(int tableau[1000])
{

    for (int i = 0; i < 1000; i++)
    {
        usleep(10000);
        if (tableau[i] == 0)
        {
            printf("Trouver a l'indice : %d \n", i);
        }
    }
}

int fork_try(int tableau[1000])
{

    pid_t pid = fork();
    if (pid == -1)
    {
        fprintf(stderr, "fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        for (int i = 0; i < 500; i++)
        {
            usleep(10000);
            if (tableau[i] == 0)
            {
                printf("Trouver a l'indice : %d (executer par le fils : %d)\n", i, getpid());
            }
        }
        return 0;
    }
    else
    {
        for (int i = 500; i < 1000; i++)
        {
            usleep(10000);
            if (tableau[i] == 0)
            {
                printf("Trouver a l'indice : %d (executer par le père : %d)\n", i, getpid());
            }
        }
        wait(NULL); 
    }
    return 0;
}

int main(void)
{
    srand(time(NULL));
    int tableau[1000];
    for (int i = 0; i < 1000; i++)
    {
        tableau[i] = rand() % 101;
    }
    clock_t start_time = clock();
    first_try(tableau);
    //fork_try(tableau);
    clock_t end_time = clock();
    float temps = (float)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Temps d'exécution : %f secondes\n", temps);
    return 0;
}