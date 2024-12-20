#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <windows.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "calendrier.h"

//#include "main.c"

/*
#ifndef WIN32
    #include <sys\types.h>
#endif
*/




/// @brief  est utilisé pour retourner un élément de type dir dans le terminal
/// @param day 
/// @param month 
/// @param annee 
/// @return 
DIR* searchNote(int day ,int month,int annee) 
{
        char nomDuFichier[12] = "";
        sprintf(nomDuFichier, "%d_%d_%d.txt", day, month, annee);
        char chemin[50] = "C:\\Calendrier\\";
        //strcat(chemin,nomDuFichier);
        DIR *rep = NULL ;
        rep = opendir(chemin);
        if(rep == NULL)
        {
            switch (errno)
            {
            case EACCES:
                printf("\nL'acces au dossier a ete refuser..");
                printf("vous ne pouvez pas prendre de notes.Veuillez autorizer l'acces a ce dossier '%s' par ce programme.",chemin);
                
                //goto main_beginning ;
                exit(EXIT_FAILURE);
                break;
            
            default:
                printf("Impossible d'accéder au dossier '%s' où est stocké les notes..",chemin);
                //goto main_beginning ;
                exit(EXIT_FAILURE);
                break;
            }
        }
        else
        {
            return rep ;
        }
}



/// @brief permet de défiler parmi les notes d'un mois donné
/// @param month 
/// @param annee 
void afficher_note_du_mois(int month,int annee)
{
    if(verifier_présence_note_du_mois(month, annee))
    {
        int val = 0;
        for(int day = 0; day <= 31; day++)
        {
            if(verifierPresenceNoteDuJour(day, month, annee))
            {
                val++ ;
                system("cls");
                afficherContenufIchier( day, month, annee);
                printf("press 'q' to quit, 'm' to modify, 'n' to show the next note : ");
                
                while(1)
                {
                    char ch = getch() ;
                    switch (ch)
                    {
                        case 'q':
                        printf("\n\avous allez quitter cette partie dans quelques instants..");
                        sleep(1.5);
                            return;
                            break;
                        case 'm':
                            modifierNote(day, month, annee);
                            break;
                        case 'n' :
                        printf("affichage de la note suivante");
                        break;  // break inutile car "continue" fais passer la boucle for a l'itértion suivante

                        default:
                        printf("vous avez entrer un caractère incorrect.\nVeuillez la resaisir.");
                        //goto controleAffichageNoteSuivante ;
                        break;
                    }
                    if(strcmp(&ch,"n") == 0 || strcmp(&ch,"m") == 0 )  // permet de sortir de la boucle while
                    {
                        break;
                    }
                } 
            }

            if(val == 0)
            {
                printf("il n'existe aucune note pour ce mois.");
                sleep(1);
            }
        }
    }

    else
    {
        printf("Il n'existe aucune note pour ce mois.");
    }
}


int verifier_présence_note_du_mois(int month,int annee)
{
    char chemin[50] ;
    sprintf(chemin, "C:\\Calendrier\\%d_%d", month, annee);
               
    DIR *rep = NULL ;
    rep = opendir(chemin);

    if(rep == NULL) // cela veut dire que le dossier n'existe pas donc il n'y a pas de note
    {
        return 0;
    }
    else // donc le dossier existe.il faut ensuite vérifier son contenu s'il est vide ou pas.
    {
        int cpt = 0 ;
        struct dirent* fichierlu = NULL ;
        //struct stat info ;
        while ((fichierlu = readdir(rep))!=NULL)
        {
            //int valRetour = stat(fichierlu->d_name, &info) ;
            cpt++ ;
        }
    closedir(rep);
            

        if(cpt > 2){
            return 1;
        }
        else{
            return 0;
        }
        
    }


}


int verifierPresenceNoteDuJour(int day, int month, int year)
{
    char nomDuFichier[15] = "";
    sprintf(nomDuFichier, "%d_%d_%d.txt", day, month, year);
    char chemin[50] ;
    sprintf(chemin,  "C:\\Calendrier\\%d_%d", month, year);
    DIR *rep = NULL ;
    rep = opendir(chemin);

        if(rep == NULL) // cela veut dire que le dossier n'existe pas donc il n'y a pas de note
        {
            return 0;
        }
        else // donc le dossier existe.il faut ensuite vérifier son contenu s'il est vide ou pas.
        {
            struct dirent* fichierlu ;
            struct stat info ;
            while ((fichierlu = readdir(rep))!=NULL)
            {
                stat(fichierlu->d_name, &info);
                if(S_ISDIR(info.st_mode) != 1)
                {
                    if(0 == strcmp(fichierlu->d_name, nomDuFichier))  // le contenu lu doit être different du repertoire parent et du repertoire actuel
                    {
                        closedir(rep);
                        return 1 ;
                    }
                }  
            }
            closedir(rep);
            return 0;    // car il n'a été trouvé aucun fichier dans le repertoire ayant le nom qu'on voit
        }
}



void afficherContenufIchier( int day, int month, int year)
{
    char chemin[50];
    sprintf(chemin, "C:\\Calendrier\\%d_%d\\%d_%d_%d.txt",month, year, day, month, year);
    FILE* mon_fichier = NULL;
    mon_fichier = fopen(chemin, "r");
    if(mon_fichier == NULL)
    {
        printf("\nErreur lors de l'ouverture du fichier contenant les notes");
        //goto main_fuction ;
        exit(EXIT_FAILURE);
    }
    else
    {
        char contenu[200];
        printf("Contenu de la note du %d/%d/%d\n",day, month, year);
        while(fgets(contenu, sizeof(contenu), mon_fichier) != NULL)
        {
            printf("%s",contenu);
        }
        printf("\n\nFin de la note.\n");
    }
    printf("\n\apress any key to continue.");
    
    fclose(mon_fichier);
}


/// @brief permet de modifier un fichier soit en y ajoutant du contenu ou en y supprimant le contenu et en écrivant le nouveau contenu
/// @param day 
/// @param month 
/// @param year 
void modifierNote(int day, int month, int year)
{
    int choix = 0 ;
    FILE* fic = NULL;

    char nom[50];
    sprintf(nom, "C:\\Calendrier\\%d_%d\\%d_%d_%d.txt",month, year, day, month, year);
    system("cls");
    printf("\n***************MODIIFICATION DES NOTES EXISTANTES*****************\n\n");
    printf("\a1* Modifier la note existant pour se jour \n");
    printf("2* reecrire une nouvelle note pour ce jour\n");
    printf("3*Abandonner les modifications\n");

    choix = choixUser(1,3); // lecture de la valeur de  choix 1<= choix <= 3

    switch (choix)
    {
    case 1 :
        fic = fopen(nom, "a+");
        printf("voici le contenu de la note du %d/%d/%d:\n",day, month, year);
        char lignes[200];
        while(fgets(lignes, sizeof(lignes), fic) != NULL )   // affichage du contenu du fichier avant d'y écrire
        {
            printf("%s", lignes);
        }

        printf("\n\tveuillez saisir la suite des notes de ce jour\n(retour a la ligne + Ctrl + z + Entree pour arreter la saisie du texte) :\n");
        while(fgets(lignes, sizeof(lignes), stdin))
        {
            fprintf(fic,"%s", lignes);
        }
        printf("Nouvelle note enregistrer avec succces.\n");
        printf("retour au menu precedent...");
        sleep(1);
        fclose(fic);
        break;

    case 2 :
        fic = fopen(nom, "w");
        printf("veuillez saisir votre note\n(retour a la ligne + Ctrl + z + Entree pour arreter la saisie):\n\n");
        while(fgets(lignes, sizeof(lignes), stdin))
        {
            fprintf(fic,"%s", lignes);
        }
        printf("Nouvelle note enregistrer avec succces.\n");
        printf("retour au menu precedent...");
        sleep(1);
        fclose(fic);
        break;
    case 3 :
        printf("retour au menu precedent...");
        sleep(1);
        break;
    }
    return ;

}



/// @brief permet de récuperer grace a une saisie sécurisé un nombre entré au clavier et qui doit appartenir à [indice1, indice2] 
/// @param indice1 
/// @param indice2 
/// @return 
int choixUser(int indice1, int indice2)
{
    int choix = 0 ;
    int valretour = 0 ;
    while(1)
    {
        printf("\nle nombre entrer doit appartenir a l'intervalle [%d, %d]\n",indice1, indice2);
        printf("\n\tQuel est votre choix:");
        valretour = scanf("%d",&choix);
        if(valretour!=1)     // le caractère n'a pas été lu
        {
            char c ;
            printf("vous avez entrer un caractere incorrecte..\n");
            printf("veuillez reessayer\n");

            while((c = getchar())!= '\n' && c != EOF)   // permet de vider le buffer
            {
            }
        }
        else
        {
            if(choix >= indice1 && choix <= indice2)
            {
                break;
            } 
            else
            {
                // l'utilisateur doit entrer
                printf("vous avez entrer un nombre incorrecte.\nVeuillez reessayer...\n\n");
                sleep(1);
            }
        }
    }
    return choix ;
}