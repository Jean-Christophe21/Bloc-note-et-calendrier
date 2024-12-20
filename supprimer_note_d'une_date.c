#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "calendrier.h"


void supprimer_note(void)
{
    int year = read_year();
    int month = read_month();
    int day = read_day(month);
    struct stat info ;
    char fichier[50];
    char chemin[50];
    sprintf(chemin, "C:\\Calendrier\\%d_%d", month, year);
    sprintf(fichier, "C:\\Calendrier\\%d_%d\\%d_%d_%d.txt",month, year, day, month, year);
    FILE* fic = NULL;

    if(stat(chemin, &info) == -1 )
    {
        printf("le dossier contenant le fichier n'a pas ete trouve.");
        return ;
    }
    else
    {
        fic = fopen(fichier, "r");
        if(fic == NULL)
        {
            printf("la note a supprimer n'existe pas.");
        }
        else
        {
            fclose(fic);    // il faut le faire sinon fait l'acces sera refuse au programme lorsqu'il va vouloir supprimer le fichier
            int valRetour = remove(fichier);
            if(valRetour == 0)
            {
                printf("Fichier Supprimé avec succes..\n");
                printf("retour au menu principal...\n");
                sleep(0.75);
            }
            else
            {
                printf("hello\n");
                perror("errno");
                return ;
            }
        }
    }
}

/*
int main()
{
    supprimer_note();
}
*/