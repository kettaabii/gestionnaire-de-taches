#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int ires = 0;

typedef struct {
    int heure;
    int jour;
    int mois;
    int annee;
} DateEcheance;

typedef enum {
    Pas_Encore=0,
    IN_PROGRESS=1,
    COMPLETED=2
} TaskStatus;

typedef struct {
    char titre[50];
    char description[200];
    char priorite[30];
    DateEcheance Date;
    TaskStatus status;
} Tache;

int taille = 0;
Tache T[4];

void Afficher() {
    printf("Les taches sont\n");
    for (int i = 0; i < taille; i++) {
        printf("Titre: %s\n", T[i].titre);
        printf("Description: %s\n", T[i].description);
        printf("Priorite: %s\n", T[i].priorite);
        printf("Status: %s\n", T[i].status);
        printf("Date d'echeance: %d/%d/%d\n", T[i].Date.jour, T[i].Date.mois, T[i].Date.annee);
    }
}

void Ajouter() {
    printf("Entrer le titre de la tache\n");
    scanf(" %[^\n]s", T[taille].titre);

    printf("Entrer la description de la tache\n");
    scanf(" %[^\n]s", T[taille].description);

    printf("Veuillez choisir la priorite\n");
    scanf(" %[^\n]s", T[taille].priorite);

    printf("Veuillez entrer la date d'echeance (jj/mm/yy)\n");
    scanf("%d/%d/%d", &T[taille].Date.jour, &T[taille].Date.mois, &T[taille].Date.annee);

    printf("Veuillez choisir le statut de la tache (0: A venir, 1: En cours, 2: Complete)\n");
    scanf("%d", &T[taille].status);

    taille++;
}

void rechercher() {
    char Nom_Chercher[50];
    printf("Rentrer le titre de la tache a rechercher: ");
    scanf(" %[^\n]s", Nom_Chercher);

    ires = -1;
    for (int i = 0; i < taille; i++) {
        if (strcmp(T[i].titre, Nom_Chercher) == 0) {
            ires = i;
            break;
        }
    }
}

void Modifier() {
    rechercher();

    if (ires != -1) {
        printf("La tache existe a l'indice %d.\n", ires + 1);
        printf("Veuillez entrer la nouvelle information pour la tache:\n");

        printf("Nouveau titre: ");
        scanf(" %[^\n]s", T[ires].titre);

        printf("Nouvelle description: ");
        scanf(" %[^\n]s", T[ires].description);

        printf("Nouvelle priorite: ");
        scanf(" %[^\n]s", T[ires].priorite);

        printf("Nouvelle date d'echeance (jj/mm/yy): ");
        scanf("%d/%d/%d", &T[ires].Date.jour, &T[ires].Date.mois, &T[ires].Date.annee);

        printf("Nouveau statut (0: a venir , 1: En cours, 2: faite): ");
        scanf("%d", &T[ires].status);

        printf("La tache a ete modifiee avec succes.\n");
    } else {
        printf("La tache n'existe pas.\n");
    }
}

void Supprimer() {
    rechercher();

    if (ires != -1) {
        for (int i = ires; i < taille - 1; i++) {
            strcpy(T[i].titre, T[i + 1].titre);
            strcpy(T[i].description, T[i + 1].description);
            strcpy(T[i].priorite, T[i + 1].priorite);
            T[i].Date = T[i + 1].Date;
            T[i].status = T[i + 1].status;
        }

        strcpy(T[taille - 1].titre, "");
        strcpy(T[taille - 1].description, "");
        strcpy(T[taille - 1].priorite, "");

        taille--;

        printf("La tache a ete supprimee avec succes.\n");
    } else {
        printf("La tache n'existe pas.\n");
    }
}

void Ordonner_Date_C() {
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (T[j].Date.annee > T[j + 1].Date.annee ||
                (T[j].Date.annee == T[j + 1].Date.annee && T[j].Date.mois > T[j + 1].Date.mois) ||
                (T[j].Date.annee == T[j + 1].Date.annee && T[j].Date.mois == T[j + 1].Date.mois &&
                 T[j].Date.jour > T[j + 1].Date.jour)) {


                Tache temp = T[j+1];
                T[j+1] = T[j];
                T[j ] = temp;
            }
        }
    }
    
     }
void Ordonner_Date_D() {
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (T[j].Date.annee > T[j + 1].Date.annee ||
                (T[j].Date.annee == T[j + 1].Date.annee && T[j].Date.mois > T[j + 1].Date.mois) ||
                (T[j].Date.annee == T[j + 1].Date.annee && T[j].Date.mois == T[j + 1].Date.mois &&
                 T[j].Date.jour > T[j + 1].Date.jour)) {


                Tache temp = T[j];
                T[j] = T[j+1];
                T[j+1 ] = temp;
            }
        }
    }

    printf("Les taches ont ete triees par date d'echeance.\n");
}
void Ordonner(){
    int ChoixOrdre; 
    printf("***********Ordonner******* \n 1- Selon Date echeance \n 2-Selon titre \n 3-Retour au Menu Principal\n" );
    scanf("%d",&ChoixOrdre);
    switch (ChoixOrdre)
    {
    case 1:
        Ordonner_Date_C();
        break;
    case 2:
        Ordonner_Date_D();
        break;
    case 3:
        menu();
        break;
    
    default:
        printf("llayhdik");
        break;
    }
}
void menu() {
    int choix;

    do {
        printf("#############<<To Do List>>###############\n");
        printf("Veuillez choisir:\n 1- Ajouter une tache\n 2- Afficher la liste des Taches\n");
        printf(" 3- Modifier une Tache\n 4- Supprimer une Tache\n 5- Ordonner les taches\n 6- Quitter\n");

        scanf("%d", &choix);

        switch (choix) {
            case 1:
                Ajouter();
                break;
            case 2:
                Afficher();
                break;
            case 3:
                Modifier();
                break;
            case 4:
                Supprimer();
                break;
            case 5:
                Ordonner();
                break;
            case 6:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while (choix != 6);
}




int main() {
    menu();
    return 0;
}

