#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void execute(char *command)
{
    execl("/bin/sh", "sh", "-c", command, NULL);
    fprintf(stderr, "Erreur lors de exec\n");
    exit(EXIT_FAILURE); // ou un truc > 0
}

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("La commande doit etre sous ces formats : \n si <commande1> (Pour executer que la commande 1) \n si <commande1> alors <commande2> \n si <commande1> alors <commande2> sinon <commande3>\n");
        return 1;
    }

    pid_t pid = fork();
    int status;

    if (pid < 0)
    {
        // Si le fork ne réussie pas
        perror("Le fork a planter !!!\n");
        exit(1);
    }
    else if (pid == 0)
    {
        char resultat[100] = "";
        int i = 2; // Index pour parcourir les arguments

        while (argc > i)
        {
            if (strcmp(argv[i], "alors") == 0)
            {
                break;
            }
            strcat(resultat, argv[i]);
            strcat(resultat, " ");
            i++;
        }

        execute(resultat);
    }
    else if (pid > 0)
    {
        // On attend la fin du fils
        wait(&status);

        // Vérifier si il a bien terminer le fils
        if (WIFEXITED(status))
        {
            // ici c'est le alors <commande2> sinon quand la commande1 a reussi
            if (WEXITSTATUS(status) == EXIT_SUCCESS) // Ou 0
            {
                char resultat[100] = "";
                int i = 2; // Index pour parcourir les arguments

                while (i < argc && strcmp(argv[i], "alors") != 0)
                {
                    i++;
                }
                i++;

                while (i < argc && strcmp(argv[i], "sinon") != 0)
                {
                    strcat(resultat, argv[i]);
                    strcat(resultat, " ");
                    i++;
                }

                execute(resultat);
            }
            // ici c'est le sinon <commande>
            else
            {
                char resultat[100] = "";
                int i = 2; // Index pour parcourir les arguments

                while (i < argc && strcmp(argv[i], "sinon") != 0)
                {
                    i++;
                }
                i++;

                while (i < argc)
                {
                    strcat(resultat, argv[i]);
                    strcat(resultat, " ");
                    i++;
                }

                execute(resultat);
            }
        }
    }
    else
    {
        perror("Un probléme avec le fils !!!\n");
    }

    return 0;
}
