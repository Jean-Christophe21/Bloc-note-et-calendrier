#include <stdio.h>
#include <dirent.h>
#include "calendrier.h"


void affichage_calendrier(void)
{
    while(1)
    {
        year user_year;
        int annee = 0, mois = 0;
        annee = read_year();
        mois = read_month() ;
        // réduction de 1 le nombre d'un mois car le mois dans le programme va de 0 à 11 .
        mois-=1 ;
 
        initialize_and_show_month :
        user_year = initialisation_annee(annee);

        show_month_only :
        //month* mthaAfficher = mois_a_afficher(user_year, mois);o
        printf("\n\n");
        system("cls");
        affichage_month(user_year, mois) ;
        setConsoleColor(6,1);
        printf("\n\n            ");
        printf("Press 'n' to next, 'p' to previous, 'q' to Quit\n");
        printf("            and 's' to show the note :");
        char ch = getch();
        
        reenter_text :
            switch (ch)
            {
            case 'n':
                if(mois == 11)
                {
                    mois = 0;
                    annee +=1 ;
                    supprimer_year(user_year );
                    goto initialize_and_show_month ;
                }
                else   
                {
                    mois+=1 ;
                    goto show_month_only ;
                }
            
            case 'p':
                if(mois == 1)
                {
                    mois = 11 ;
                    annee-= 1 ;
                    supprimer_year(user_year);
                    goto initialize_and_show_month ;
                }
                else
                {
                    mois -= 1 ;
                    goto show_month_only ;
                }

            case 's':
                afficher_note_du_mois(mois, annee);
                
                goto show_month_only ;

            case 'q':
                printf("\nvous allez quitter cette partie dans quelques secondes...");
                sleep(1);
                system("cls");
                return ;
                break;
            default :
                printf("\nvous avez entrer un caractère incorrecte.\n");
                system("cls") ;
                goto reenter_text ;
            }
    }
}




/// @brief permet de dresser la liste des jour d'un mois. 0<=monthNumber<= 11
/// @param my_year 
/// @param monthNumber 
void affichage_month(year my_year, int monthNumber)
{
    int annee = my_year.number ;              // destinée a contenir l'année qui sera initialisé avec l'allocation dynamique

    // récupération du mois a afficher
    month *currentMth = my_year.first_month ;
    
    const char **name_month = creation_liste_de_nom_des_mois() ;    // initialisation de la liste des mois dans un tableau

    int cpt = 0 ;
    while(cpt < monthNumber )   // permet de pointer currentMth vers le mois a afficher
    {
        currentMth = currentMth->next_month ;
        cpt++ ;
    }


    // création d'un pointeur qui contient le nom de mois et permet de référencer les mots

    int nbr_day = currentMth->nbr_day ;
    int indice_first_day = index_day(my_year.number, monthNumber, 1);  // récupération de l'indice du jour du premier jour du mois(0 pour le dimancche 1 pour le lundi...)

    //int annee = my_mth->year_parent->number ;
    gotoxy(20,0);
    printf("----------------------------------------------------------\n");
    gotoxy(48,1);
    printf("%s %d\n",name_month[monthNumber],annee);     
    gotoxy(20,2);
    printf("----------------------------------------------------------\n");
    gotoxy(20,3);
    printf("S        M        T        W        T        F        S\n");


    gotoxy((16+indice_first_day*8),4);
    int lignes = 4 ;
    
    for(cpt = 1; cpt <= nbr_day; cpt++)
    {
        if((index_day(2024, monthNumber, 1) + cpt ) % 7 == 0 )   // permet de vérifier si l'élement est un dimanche
        {
            setConsoleColor(4, 1);    // changement de la couleur d'écriture dans le terminal
            if(cpt <= 9 ){
                printf("       0%d",cpt);
            }
            
            else{
                printf("       %d",cpt);
            }
            setConsoleColor(7,1);  //redéfinition de la couleur du terminal sur un fond bleu et le texte en blanc
        }
        else
        {
            setConsoleColor(7,1);
            if(cpt <= 9 ){
                printf("       0%d",cpt);
            }
            
            else{
                printf("       %d",cpt);
            }
        }
        if((indice_first_day + cpt) % 7 == 0)   // retour a la ligne au besoin
        {

            printf("\n             ") ;
            lignes++ ;
            gotoxy(lignes,20);
        }                                               
                                                                            
                                                                            
    /*first_day_month + 1 car l'indice du jour va de 0 a 6 or on a besoin de chiffre de 1 à 7                                                                              
    après le dernier nombre on retourne à la ligne et on laisse l'ecart entre le bord et le 
    mais on laisse un ept de place car l'écriture du nombre va écrire "       %d" et c'est pour cela qu'il ne faut pas
    laisser l'écart total qu'il faut entre le bord et le calendrier. 
    */
    }
}





int read_year(void)
{
    int annee = 0;
    printf("\n\tl'année entrer doit etre superieur a 1900.\n");
    read_year :
    while (1)
    {
        printf("veuiller entrer l'année de votre choix :");
        scanf("%d",&annee);
        if(annee >= 1900){
            break;
        }
        else{
            printf("choix incorrect.\non vous rappelle que l'annee doit etre superieur a 1900.");
            goto read_year;
        }
}
return annee;
}


int read_month(void)
{
    int mois = 0;
    printf("\n\tle mois entrer doit etre superieur a 0 et inferieur a 13.\n");
    while (1)
    {
        printf("veuiller entrer le moix de votre choix :");
        scanf("%d",&mois);
        if(mois >= 1 && mois <= 12 ){
            break;
        }
        else{
            printf("\nchoix incorrect.\non vous rappelle que le mois doit etre superieur a 0 et inferieur a 13.\n");
        }
    }
    return mois;
}

int read_day(int month)
{
    int day = 0;
    int nbrDayMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    printf("\n\tle jour entrer doit etre superieur a 0 et inferieur a %d.\n", nbrDayMonth[month-1]+1);
    while (1)
    {
        printf("veuiller entrer le jour de votre choix :");
        scanf("%d",&day);
        if(day >= 1 && day <= nbrDayMonth[month-1] ){
            break;
        }
        else{
            printf("\nchoix incorrect.\non vous rappelle que le jour doit etre superieur a 0 et inferieur a %d.\n",nbrDayMonth[month]+1);
        }
    }
    return day;
}



month* mois_a_afficher(year year, int number )
{
    month *currentMth = year.first_month ;
    for(int cpt = 0; cpt < number-1; cpt++)
    {
        currentMth = currentMth->next_month ;
    }
    return currentMth ;
}

