#include <stdio.h>
#include <windows.h>
#include "calendrier.h"


/// @brief permet de positionner le curseur a une position donnée dans le terminal
/// @param x 
/// @param y 
void gotoxy (int x, int y)
{
    COORD coord = {0, 0}; // définit les coordonnées sur (0,0) comme variables globales
    coord.X = x; coord.Y = y; // X et Y sont les coordonnées
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


/// @brief permet de fixer les couleurs du terminal et du texte écrit dans le terminal
/// @param textColor
/// @param background 
void setConsoleColor(int textColor, int background)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (background << 4) | textColor);
}



/// @brief return the number of the month in a list.NB:return 0 for the first element
/// @param my_mth 
/// @return nbr
int number_month(month my_mth)
{
    
    month *cpt = &my_mth ;
    int nbr = 0 ;
    while(cpt != NULL)
    {
        nbr++;
        cpt = cpt->next_month ;
    }
    return 12 - nbr ;
}



/// @brief retourne l'indice du jour dans la semaine. 0<= dayIndex<=6 
/// @param year 
/// @param monthIndex 
/// @param daynumber 
/// @return 
int index_day(int year, int monthIndex, int daynumber )
{
    
    int _M[] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};

    int dayIndex = (daynumber+(year-1900)+((year-1900)/4)+_M[monthIndex])%7;

    return dayIndex;
}


/// @brief définition d'une fonction qui retourne un tableau de pointeur static contenant les noms des mois de l'année
/// @return un tableau de pointeur static
const char** creation_liste_de_nom_des_mois(void)
{
    static const char *month_name[] = {"Janvier","Fevrier","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Decembre"} ;
    
    return month_name ;
}


/// @brief permit to verify is year is a leap year
/// @param nbr_year 
/// @return 
int is_leap_year(int nbr_year )
{
	if (nbr_year % 4 != 0) {
		return 0;
	}
	else {
		if (nbr_year % 100 == 0) {
			if (nbr_year % 400 == 0) {
				return 1 ;
			}
            else{
                return 0 ;
            }
		}
		else {
			return 1 ;
		}
	}
}


