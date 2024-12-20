#include <stdio.h>
#include <stdlib.h>
#include "calendrier.h"


month* initialisation_month(int is_leap)
{
    int nbr_mois = 0 ;
    int val_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int cpt = 0 ;
    month* pre_month = NULL, *previous_mth = NULL, *my_month = NULL;

    // initialisation du premier élément de la liste
    pre_month = malloc(sizeof(month));
    pre_month->nbr_day = val_month[cpt] ;
    nbr_mois++ ;

    //initialisation du deuxieme elmt de la liste et association au premier
    my_month = malloc(sizeof(month));

    if(is_leap) my_month->nbr_day = 29;
    else my_month->nbr_day = 28;

    pre_month->next_month = my_month;
    previous_mth = my_month ;
    nbr_mois++ ;

    //initialisation du reste de la liste et leur association a la liste
    for (cpt = 2; cpt <= 11; cpt++)
    {
        my_month = malloc(sizeof(month));
        my_month->nbr_day = val_month[cpt];
        previous_mth->next_month = my_month ;
        previous_mth = my_month ;
        nbr_mois++ ;
    }
    my_month->next_month = NULL ;
    return pre_month ;
}

/// @brief retourne un pointeur vers une structur de type year initialisé
/// @param number  qui est le numero de l'annee
/// @return 
year initialisation_annee(int number)
{
    year my_year;
    my_year.number = number ;
    my_year.next_year = NULL;
	my_year.first_month = initialisation_month(is_leap_year(number));
    month *cpt = NULL ;
    cpt = my_year.first_month ;
    while(cpt != NULL)
    {
        cpt->year_parent = &my_year ;
        cpt = cpt->next_month ;
    } 
    return my_year ;
}

void supprimer_year(year my_year )
{
    month *previous = NULL , *current = NULL ;
    current = my_year.first_month ;
    while(current != 0)
    {
        previous = current;
        current = current->next_month ;
        free(previous);
    }
}

