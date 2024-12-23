# Bloc-note-et-calendrier

Ce fichier contient et rassemble mes opinions par rapport au projet `Bloc-note-et-calendrier`

## Remarques 

Tout d'abord je tiens à féliciter l'auteur pour tout le code qu'il a écrit et ainsi que pour le rendu, la logique impéccable ainsi que les multiples mécanismes mis en place ainsi que les vérifications mises en place

**je tiens notamment à ajouter que j'ai modifié le code, notamment le chemin d'accès du fichier calendrier qui était de base : "C\\calendrier"**

## Ajout et avis personnels

Tout d'abord je tiens à m'excuser d'avoir modifier le code et ajouter des commentaires qui ne sont pas vraiment utiles au code mais qui m'ont permis de mieux comprendre le code dont il est question.
Dans ce qui suit, je tiens à préciser que je ne suis que débutant et que les solutions proposées ne sont pas les plus optimales

### Gestion des chemins d'accès

D'abord, je tiens à dire que la gestion des chemins d'accès pourrait être améliorer dans le sens où au lieu d'utiliser un dossier comme `C:\\Calendrier\\` ou le chemin que j'ai choisi d'adopter, il pourrait être préférable d'avoir un dossier présent dans le dossier du projet dans le main pour qu'il soit directement utilisable et pour éviter la modification éventuelle d'un dossier de l'utilisateur nommé `Calendrier` qui serait éventuellement déjà présent. 

Ensuite, je pense qu'il serait préferable de contenir le chemin d'accès du dossier principale dans une constante pour éviter de réecrire plusieurs fois le même chemin d'accès et eviter les erreus de syntaxe

### affichage_calendrier.c

1. la `Ligne 13` est inutile car juste après, on appelle la fonction de nettoyage de terminal : 
    ```c
    system("cls");
    ```

2. la `Ligne 32` : inclure le saisi de caractère pour éviter une boucle infini dans 
    ```c
    reenter_text
    ```

3. la `Ligne 50` : Ici il faudrait plutôt gérer le cas mois=0 qui représente janvier au lieu de gérer le cas mois = 1 
 
4. `Ligne 113` à `Ligne 120` : Choisir la méthode à utiliser entre le retour à la ligne ou l'appel à la fonction gotoxy(), car les deux fonctions permettent d'éffectuer la même chose 

5. `Ligne 120`, `Ligne 132` : éviter d'utiliser des espace vides et utiliser des des tabulations comme \t ou opter pour laisser des espaces vides à travers des méthodes comme "%7d"

    Au lieu de : 
    ```c
    printf("       %d",cpt);
    ```
    Opter pour : 
    ```c
    printf("%7d",cpt);
    ```

6. `Ligne 156` : l'une des lignes à l'origine des erreurs d'affichage

    Au lieu de :
    ```c
    gotoxy(lignes, 20);
    ```
    Ecire plutôt : 

    ```c
    gotoxy(20, lignes);
    ```

### Afficher_note_d_une_date.c

1. `Ligne 43` : La fonction sleep prend en paramètre un entier, donc quand on lui passe en pramètre un float, le float est lui-même cast en int et donc ```sleep(0.75)``` == ```sleep(0)```

### Afficher_notes.c

1. `Ligne 9` : Ajout de l'import ```#include <errno.h>``` à cause de EACCES 

2. `Ligne 29` : Modification de 
    ```c
        char nomDuFichier[12] = "";
    ```
    à
    ```c
        char nomDuFichier[15] = "";
    ```
    pour eviter un débordement du tableau

### supprimer_note_d'une_date.c

1. `Ligne 42` :  La fonction sleep prend en paramètre un entier

## Bug et constat 

### Bug lié au terminal: 

En fonction du terminal utilisé pour exécuter le code en question, il pourrait y avoir notamment des erreurs dans l'affichage. En effet, la fonction appelée : 
```c
system("cls");
```
ne peut effectuer un nettoyage du terminal que dans certains terminal. Il est notamment inutile pour les terminals linux et ios mais peut créer des comportements inattendus en fonction du terminal windows, d'où le bug liée au terminal rencontré. Donc avant d'utiliser une telle fonction, il serait préférable de le tester sur le terminal en question au préalable: 

Une méthode pour résoudre ce bug serait de remplacer l'appel de la fonction `system("cls")` par : 
```c
printf("\033[H\033[J"); 
```

### Constat par rapport à l'affichage

Dans certains cas, il serait préférable d'initialiser des retours à la ligne avant d'effectuer certains affichages afin d'améliorer la lisibilité. 
Egalement, à la fin de la fonction affichage_month(), il serait préférable de ramener les couleurs du terminal à l'initial

## Conclusion 

Je tiens à préciser que ces remarques sont purement subjectifs, même si j'ai effectué des tests du mieux que je peux, il se peut que la modification du code selon mes recommandations ne soit à l'origine de certains.  
