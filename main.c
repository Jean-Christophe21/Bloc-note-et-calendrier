#include <stdio.h>
#include <conio.h>

#include "calendrier.h"
#include "calendrier.c"
#include "affichage_du_calendrier.c"
#include "fonction_usuelle_calendrier.c"
#include "afficher_notes.c"
#include "afficher_note_d_une_date.c"
#include "supprimer_note_d'une_date.c"
#include "enregistrer_nouvelle_note.c"



int main()
{
    while(1)
    {
        printf("\n====================================Programme Calendar====================================\n\n");
        printf("1- Afficher le calendrier d'un mois entier\n");
        printf("2- Afficher les notes d'une date\n");
        printf("3- Enregistrer une nouvelle note \n");
        printf("4- Supprimer une note existante\n");
        printf("5- Quitter\n");
        int choix = 0;
        while(1)
        {
            choix = choixUser(1,5);
            switch (choix)
            {
            case 1:
                affichage_calendrier();
                break;
            case 2 :
                //int  jour, mois, annee;
                afficher_note_date();
                
                break;
            case 3 :
                save_nouvelle_note();
                
                break;
            
            case 4 :

                supprimer_note();

                break;
            
            case 5 :

                break;


            default:
                printf("\nChoix incorrecte....");
                sleep(1.3);
                system("cls");
                //goto main_beginning ;
            }
            break;
        }
        if(choix == 5)  // sortir et mettre fin au programme quand l'option 5 est choisi
        {
            printf("vous allez quitter le programme dans quelques instants...");
            sleep(1.5);
            break;
        }
    }
    

    return 0 ;
}