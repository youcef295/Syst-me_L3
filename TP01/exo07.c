#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    pid_t pid = fork();
    int fd;
    int status;

    if (pid < 0)
    {
        // Si le fork ne réussie pas
        perror("Le fork a planter !!!\n");
        exit(1);
    }
    else if (pid == 0)
    {
        // On est dans le fils
        // Créer puis lire et ecrire dans le fichier
        fd = open("stdout.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            perror("Erreur d'ouverture du fichier");
            exit(1);
        }

        //Après cette ligne, toutes les écritures sur stdout iront dans le fichier, 
        // permet de capturer d’une commande dans un fichier
        dup2(fd, STDOUT_FILENO);

        execl("/bin/ls", "ls", NULL);
        // Si execl ne marche pas
        perror("execl a planter !!!\n");
        exit(1);
    }
    else
    {
        // J'attend la fin du fils
        wait(&status);
        // Vérifier si l'enfant c'est terminer normalement
        if (WIFEXITED(status))
        {
            // Vérifier la valeur de retour de l'enfant (0 réussi)
            if (WEXITSTATUS(status) == 0)
            {
                printf("Le fils a réussi !!!\n");
            }
            else
            {
                printf("Le fils a échouer !!!\n");
            }
        }
    }
    /*
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
        // On est dans le fils

        execl("/bin/ls", "ls", NULL);
        // Si execl ne marche pas
        perror("execl a planter !!!\n");
        exit(1);
    }
    else
    {
        // J'attend la fin du fils
        wait(&status);
        // Vérifier si l'enfant c'est terminer normalement
        if (WIFEXITED(status))
        {
            // Vérifier la valeur de retour de l'enfant (0 réussi)
            if (WEXITSTATUS(status) == 0)
            {
                printf("Le fils a réussi !!!\n");
            }
            else
            {
                printf("Le fils a échouer !!!\n");
            }
        }
    }
*/
    return 0;
}