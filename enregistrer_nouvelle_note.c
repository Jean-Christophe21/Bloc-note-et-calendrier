#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <windows.h>
#include "calendrier.h"



void save_nouvelle_note(void)
{
    int year = read_year();
    int month = read_month();
    int day = read_day(month);
    struct stat info ;
    char fichier[250];
    char chemin[250];
    sprintf(chemin, "D:\\programmation\\c_programm\\Advanced_Programms\\Bloc-note-et-calendrier\\Calendrier%d_%d", month, year);
    sprintf(fichier, "D:\\programmation\\c_programm\\Advanced_Programms\\Bloc-note-et-calendrier\\Calendrier%d_%d\\%d_%d_%d.txt",month, year, day, month, year);
    FILE* fic = NULL;
    fic = fopen(fichier, "r" );
    if(fic != NULL)
    {
        printf("Impossible de créé une nouvelle note pour le %d/%d/%d\n.Il existe déjà une note pour le %d/%d/%d",day, month, year, day, month, year);
        return;
        fclose(fic);
    }


    if(stat(chemin, &info)== -1) //Si le repertoire n'existe pas, on crée le repertoire
    {
        if(CreateDirectory(chemin, NULL)|| ERROR_ALREADY_EXISTS == GetLastError())
        {
            printf("\t\aDossier %d_%d cree avec succes.\n", month, year);
        }
        else
        {
            printf("Erreur lors de la création du repertoire qui va contenir les notes de ce mois.");
            return;
        }
    }
    else
    {
        printf("\n\ale dossier %d_%d existe deja \n", month, year);

    }
    char contenu[200];
    fic = fopen(fichier, "w");
    printf("\n\tveuillez saisir la suite des notes de ce jour\n(retour a la ligne + Ctrl + z + Entree pour arreter la saisie du texte) :\n");
    while(fgets(contenu, sizeof(contenu), stdin)!= NULL)
    {
        /*
        if(strcmp(contenu, "fin") == 0)
        {
            break;
        }
        */
        fprintf(fic, "%s", contenu);
        //fputs(contenu, fic) ;
    }
    fclose(fic);
    printf("Note sauvegarder avec succes.");
}
