#pragma once
#include <dirent.h>


typedef struct year {
	int number ;
	struct year* next_year;
	struct month* first_month;
}year;

typedef struct month {
	int nbr_day;
	struct year* year_parent;
	struct month* next_month;
	struct day* first_day;
	struct dirent  *note ;
}month;

typedef struct day {
	FILE* note ;
	struct day* next_day;
} day;



// fichier calendrier.c

year initialisation_annee(int number);

month* initialisation_month(int is_leap);

void supprimer_year(year my_year );



// fichier fonctions_usuelle_calendrier.c

void gotoxy (int x, int y);


int is_leap_year(int nbr_year );

void setConsoleColor(int textColor, int background);

int number_month(month my_mth);

int index_day(int year, int monthIndex, int daynumber );

const char** creation_liste_de_nom_des_mois(void);




//fichier affichage_du_calendrier.c

void affichage_calendrier(void);

void affichage_month(year my_year, int number) ;

int read_year(void);

int read_month(void);

int read_day(int month);

month* mois_a_afficher(year year, int number );

//fichier afficher_notes.c

DIR* searchNote(int day ,int month,int annee) ;

void afficher_note_du_mois(int month,int annee);

int verifier_présence_note_du_mois(int month,int annee);

int verifierPresenceNoteDuJour(int day, int month, int year) ;

void afficherContenufIchier( int day, int month, int year);

void modifierNote(int day, int month, int year);

int choixUser(int indice1, int indice2);


//supprimer_note_d'une_date

void supprimer_note(void);


// fichier afficher_note_d_une_date.c

int saisi_user(char* chaine );

void afficher_note_date(void);

// fichier void enregistrer_nouvelle_note.c

void save_nouvelle_note(void);


