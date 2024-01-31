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

typedef struct {
    char titre[50];
    char description[200];
    char priorite[30];
    char status[15];  // Utiliser une chaîne de caractères pour représenter le statut
    DateEcheance Date;
} Tache;

int taille = 0;
Tache T[4];

bool estDateValide(int jour, int mois, int annee) {
    if (annee < 2024) {
        return false;  // Année invalide
    }

    if (mois < 1 || mois > 12) {
        return false;  // Mois invalide
    }

    switch (mois) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return (jour >= 1 && jour <= 31);  // Mois avec 31 jours
        case 4: case 6: case 9: case 11:
            return (jour >= 1 && jour <= 30);  // Mois avec 30 jours
        case 2:
            // Ignorer la condition de l'année bissextile
            return (jour >= 1 && jour <= 29);  // Février avec 29 jours (maximum)
    }

    return false;  // Conditions par défaut, au cas où
}

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

    // Choisissez la priorité
    int choixPriorite;
    printf("Choisissez la priorite :\n");
    printf("1- Faible\n");
    printf("2- Moyenne\n");
    printf("3- Haute\n");
    scanf("%d", &choixPriorite);

    switch (choixPriorite) {
        case 1:
            strcpy(T[taille].priorite, "Faible");
            break;
        case 2:
            strcpy(T[taille].priorite, "Moyenne");
            break;
        case 3:
            strcpy(T[taille].priorite, "Haute");
            break;
        default:
            strcpy(T[taille].priorite, "Non specifiee");
            break;
    }

    // Saisie de la date d'échéance avec vérification
    do {
        printf("Veuillez entrer la date d'echeance (jj/mm/yy)\n");
        scanf("%d/%d/%d", &T[taille].Date.jour, &T[taille].Date.mois, &T[taille].Date.annee);
    } while (!estDateValide(T[taille].Date.jour, T[taille].Date.mois, T[taille].Date.annee));

    // Choisissez le statut comme une chaîne de caractères
    printf("Veuillez choisir le statut de la tache (A venir, En cours, Complete): ");
    scanf(" %[^\n]s", T[taille].status);

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

        // Choisissez le statut comme une chaîne de caractères
        printf("Nouveau statut (A venir, En cours, Complete): ");
        scanf(" %[^\n]s", T[ires].status);

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
            // Copier le statut en tant que chaîne de caractères
            strcpy(T[i].status, T[i + 1].status);
        }

        // Vider les valeurs de la dernière tâche
        strcpy(T[taille - 1].titre, "");
        strcpy(T[taille - 1].description, "");
        strcpy(T[taille - 1].priorite, "");
        // Statut à vider également comme une chaîne de caractères
        strcpy(T[taille - 1].status, "");

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

                // Échange des tâches
                Tache temp = T[j + 1];
                T[j + 1] = T[j];
                T[j] = temp;
            }
            // Ajout d'une condition de comparaison du statut
            else if (T[j].Date.annee == T[j + 1].Date.annee && T[j].Date.mois == T[j + 1].Date.mois &&
                     T[j].Date.jour == T[j + 1].Date.jour && strcmp(T[j].status, T[j + 1].status) > 0) {
                // Échange des tâches
                Tache temp = T[j + 1];
                T[j + 1] = T[j];
                T[j] = temp;
            }
        }
    }

    printf("Les taches ont ete triees par date d'echeance.\n");
}

void Ordonner_Date_D() {
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (T[j].Date.annee < T[j + 1].Date.annee ||
                (T[j].Date.annee == T[j + 1].Date.annee && T[j].Date.mois < T[j + 1].Date.mois) ||
                (T[j].Date.annee == T[j + 1].Date.annee && T[j].Date.mois == T[j + 1].Date.mois &&
                 T[j].Date.jour < T[j + 1].Date.jour)) {

                // Échange des tâches
                Tache temp = T[j];
                T[j] = T[j + 1];
                T[j + 1] = temp;
            }
            // Ajout d'une condition de comparaison du statut
            else if (T[j].Date.annee == T[j + 1].Date.annee && T[j].Date.mois == T[j + 1].Date.mois &&
                     T[j].Date.jour == T[j + 1].Date.jour && strcmp(T[j].status, T[j + 1].status) < 0) {
                // Échange des tâches
                Tache temp = T[j];
                T[j] = T[j + 1];
                T[j + 1] = temp;
            }
        }
    }

    printf("Les taches ont ete triees par date d'echeance.\n");
}

void Ordonner() {
    int ChoixOrdre;
    printf("***********Ordonner******* \n 1- Selon Date echeance \n 2-Selon titre \n 3-Retour au Menu Principal\n");
    scanf("%d", &ChoixOrdre);
    switch (ChoixOrdre) {
        case 1:
            Ordonner_Date_C();
            break;
        case 2:
            Ordonner_Date_D();
            break;
        case 3:
            break;
        default:
            printf("Choix invalide.\n");
            break;
    }
}

void FiltrerParDate() {
    DateEcheance dateFiltre;
    printf("Veuillez entrer la date d'echeance pour filtrer (jj/mm/yy): ");
    scanf("%d/%d/%d", &dateFiltre.jour, &dateFiltre.mois, &dateFiltre.annee);

    printf("Taches avec la date d'echeance %d/%d/%d :\n", dateFiltre.jour, dateFiltre.mois, dateFiltre.annee);
    for (int i = 0; i < taille; i++) {
        if (T[i].Date.jour == dateFiltre.jour && T[i].Date.mois == dateFiltre.mois && T[i].Date.annee == dateFiltre.annee) {
            printf("Titre: %s\n", T[i].titre);
            printf("Description: %s\n", T[i].description);
            printf("Priorite: %s\n", T[i].priorite);
            printf("Status: %s\n", T[i].status);
            printf("Date d'echeance: %d/%d/%d\n", T[i].Date.jour, T[i].Date.mois, T[i].Date.annee);
        }
    }
}

void MenuPrincipal() {
    int choix;
    do {
        printf("***********Menu Principal******* \n 1- Ajouter une tache\n 2- Afficher les taches\n 3- Modifier une tache\n 4- Supprimer une tache\n 5- Ordonner les taches\n 6- Filtrer les taches par date\n 7- Quitter\n");
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
                FiltrerParDate();
                break;
            case 7:
                printf("Merci d'avoir utilise l'application\n");
                break;
            default:
                printf("Choix invalide.\n");#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int i,ipro,istatus;
int ires = 0;
int temp;
int choixPriorite;
int choixStatus;

typedef struct {
    int heure;
    int jour;
    int mois;
    int annee;
} DateEcheance;

typedef struct {
    char titre[50];
    char description[200];
    char priorite[30];
    char status[15];
    DateEcheance Date;
} Tache;

int taille = 0;
Tache T[4];

bool estDateValide(int jour, int mois, int annee) {
    if (annee < 2024) {
        return false;
    }

    if (mois < 1 || mois > 12) {
        return false;
    }

    switch (mois) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return (jour >= 1 && jour <= 31);
        case 4: case 6: case 9: case 11:
            return (jour >= 1 && jour <= 30);
        case 2:

            return (jour >= 1 && jour <= 29);
    }

    return false;
}
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

void  Prioritee(i){  ///////////////////////////////////////////////
    printf("1- Faible\n");
    printf("2- Moyenne\n");
    printf("3- Haute\n");
    scanf("%d", &choixPriorite);
    switch (choixPriorite) {
        case 1:
            strcpy(T[i].priorite, "Faible");
            break;
        case 2:
            strcpy(T[i].priorite, "Moyenne");
            break;
        case 3:
            strcpy(T[i].priorite, "Haute");
            break;
        default:
            strcpy(T[i].priorite, "Non specifiee");
            break;
    }

       ipro=i;

//    printf("+++++++++++Priorite: %s\n", T[taille].priorite);
}
void FStatus(i){
    printf(" \n1-En cours\n2-Terminee\n3-Blockage: ");
    scanf("%d", &choixStatus);
    switch (choixStatus) {
        case 1:
            strcpy(T[i].status, "En Cours");
            break;
        case 2:
            strcpy(T[i].status, "Terminee");
            break;
        case 3:
            strcpy(T[i].status, "Blocage");
            break;
        default:
            strcpy(T[i].status, "Non specifiee");
            break;
    }
     istatus=i;
}

void Ajouter() {
    printf("Entrer le titre de la tache\n");
    scanf(" %[^\n]s", T[taille].titre);

    printf("Entrer la description de la tache\n");
    scanf(" %[^\n]s", T[taille].description);

    int choixStatus;

    printf("Choisissez la priorite :\n");
    Prioritee(taille);
    strcpy(T[taille].priorite, T[ipro].priorite);
    printf("++-------Priorite: %s\n", T[taille].priorite);
/////////////////////////////////////////////////////

     do {
        printf("Veuillez entrer la date d'echeance (jj/mm/yy)\n");
        scanf("%d/%d/%d", &T[taille].Date.jour, &T[taille].Date.mois, &T[taille].Date.annee);
    } while (!estDateValide(T[taille].Date.jour, T[taille].Date.mois, T[taille].Date.annee));


    printf("Veuillez choisir le statut de la tache\n");
    FStatus(taille);
    strcpy(T[taille].status, T[istatus].status);
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

        printf("Nouvelle priorite: \n ");
         Prioritee(ires);
        ////////////////////////////////////////////
        ////////////////////////////////////////////////////////
        ///////////////////////////////////////////

        do {
        printf("Nouvelle date d'echeance (jj/mm/yy): ");
        scanf("%d/%d/%d", &T[ires].Date.jour, &T[ires].Date.mois, &T[ires].Date.annee);
    } while (!estDateValide(T[ires].Date.jour, T[ires].Date.mois, T[ires].Date.annee));


        printf("Nouveau statut :\n ");
        FStatus(ires);

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
            strcpy(T[i].status, T[i + 1].status);
        }


        strcpy(T[taille - 1].titre, "");
        strcpy(T[taille - 1].description, "");
        strcpy(T[taille - 1].priorite, "");

        strcpy(T[taille - 1].status, "");

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


                Tache temp = T[j + 1];
                T[j + 1] = T[j];
                T[j] = temp;
            }

            else if (T[j].Date.annee == T[j + 1].Date.annee && T[j].Date.mois == T[j + 1].Date.mois &&
                     T[j].Date.jour == T[j + 1].Date.jour && strcmp(T[j].status, T[j + 1].status) > 0) {

                Tache temp = T[j + 1];
                T[j + 1] = T[j];
                T[j] = temp;
            }
        }
    }

    printf("Les taches ont ete triees par date d'echeance.\n");
}

void Ordonner_Date_D() {
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (T[j].Date.annee < T[j + 1].Date.annee ||
                (T[j].Date.annee == T[j + 1].Date.annee && T[j].Date.mois < T[j + 1].Date.mois) ||
                (T[j].Date.annee == T[j + 1].Date.annee && T[j].Date.mois == T[j + 1].Date.mois &&
                 T[j].Date.jour < T[j + 1].Date.jour)) {


                Tache temp = T[j];
                T[j] = T[j + 1];
                T[j + 1] = temp;
            }

            else if (T[j].Date.annee == T[j + 1].Date.annee && T[j].Date.mois == T[j + 1].Date.mois &&
                     T[j].Date.jour == T[j + 1].Date.jour && strcmp(T[j].status, T[j + 1].status) < 0) {

                Tache temp = T[j];
                T[j] = T[j + 1];
                T[j + 1] = temp;
            }
        }
    }

    printf("Les taches ont ete triees par date d'echeance.\n");
}

void Ordonner() {
    int ChoixOrdre;
    printf("***********Ordonner******* \n 1- Selon Date croissante \n 2-Selon Date decroissante \n 3-Retour au Menu Principal\n");
    scanf("%d", &ChoixOrdre);
    switch (ChoixOrdre) {
        case 1:
            Ordonner_Date_C();
            break;
        case 2:
            Ordonner_Date_D();
            break;
        case 3:
            break;
        default:
            printf("Choix invalide.\n");
            break;
    }
}

void FiltrerParDate() {
    DateEcheance dateFiltre;
    printf("Veuillez entrer la date d'echeance pour filtrer (jj/mm/yy): ");
    scanf("%d/%d/%d", &dateFiltre.jour, &dateFiltre.mois, &dateFiltre.annee);

    printf("Taches avec la date d'echeance %d/%d/%d :\n", dateFiltre.jour, dateFiltre.mois, dateFiltre.annee);
    for (int i = 0; i < taille; i++) {
        if (T[i].Date.jour == dateFiltre.jour && T[i].Date.mois == dateFiltre.mois && T[i].Date.annee == dateFiltre.annee) {
            printf("Titre: %s\n", T[i].titre);
            printf("Description: %s\n", T[i].description);
            printf("Priorite: %s\n", T[i].priorite);
            printf("Status: %s\n", T[i].status);
            printf("Date d'echeance: %d/%d/%d\n", T[i].Date.jour, T[i].Date.mois, T[i].Date.annee);
        }
    }
}
void FiltrerParPriorite() {
    printf("Choisir la priorite : ");
    Prioritee(ipro); // Appel de la fonction pour définir la priorite
    for ( i = 0; i < taille; i++) {
        if (i == ipro) {
            printf("Titre: %s\n", T[i].titre);
            printf("Description: %s\n", T[i].description);
            printf("Priorite: %s\n", T[i].priorite);
            printf("Status: %s\n", T[i].status);
            printf("Date d'echeance: %d/%d/%d\n", T[i].Date.jour, T[i].Date.mois, T[i].Date.annee);
        }

        }
    }

void Filtrer(){
    int ChoixFiltrage;
    printf("comment vous voulez fitrer les taches ? \n1-Par Date\n2-Par priorite\n");
    scanf("%d",&ChoixFiltrage);
    switch(ChoixFiltrage){
        case 1:
        FiltrerParDate();
        break;
        case 2 :
        FiltrerParPriorite();
        break;
    }
}
void MenuPrincipal() {
    int choix;
    do {
        printf("***********Menu Principal******* \n 1- Ajouter une tache\n 2- Afficher les taches\n 3- Modifier une tache\n 4- Supprimer une tache\n 5- Ordonner les taches\n 6- Filtrer les taches par date\n 7- Quitter\n");
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
                Filtrer();
                break;
            case 7:
                printf("Merci d'avoir utilise l'application\n");
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }
    } while (choix != 7);
}

int main() {
    MenuPrincipal();

    return 0;
}

                break;
        }
    } while (choix != 7);
}

int main() {
    MenuPrincipal();

    return 0;
}
