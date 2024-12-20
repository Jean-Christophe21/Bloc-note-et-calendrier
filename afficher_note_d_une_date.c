#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

int saisi_user(char* chaine )
{
    printf("Veuillez entrer la valeur %s :", chaine);
    int val = 0, valretour = 0;
    while((valretour = scanf("%d",&val)) == 0 )
    {
        printf("vous avez entrer un caractere incorrect.\nVeuillez ressaisir la valeur %s :", chaine);
    }
    return val ;
}


void afficher_note_date(void)
{
    system("cls");
    int day , month, year ;
    day = saisi_user("du jour");
    month = saisi_user("du mois");
    year  = saisi_user("de l'annee");

    int val = verifier_présence_note_du_mois(month, year);
    if(val)
    {
        FILE* fic = NULL ;
        val = verifierPresenceNoteDuJour(day, month, year);
            if(val)
            {
                if(fic == NULL)
                afficherContenufIchier( day, month, year);
                modifierNote(day, month, year);


                    char ch = getch() ;
                    switch (ch)
                    {
                        case 'q':
                        printf("\n\avous allez quitter cette partie dans quelques instants..");
                        sleep(0.75);
                            return;
                            break;
                        case 'n' :
                        printf("affichage de la note suivante");
                        
                        break;

                        default:
                        printf("vous avez entrer un caractère incorrect.\nVeuillez la resaisir.");
                        //goto controleAffichageNoteSuivante ;
                        break;
                    }
            }
            else
            {
                printf("il n'existe aucune note pour ce jour");
            }
    }
    else
    {
        printf("Il n'existe aucune note pour le mois.");
    }
    
}

