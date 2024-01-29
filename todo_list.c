#include <stdio.h>
#include <string.h>
typedef struct {
    int heure;
    int jour;
    int mois;
    int annee;
} DateEcheance;

typedef enum {
    NOT_STARTED,
    IN_PROGRESS,
    COMPLETED
} TaskStatus;
typedef struct {
    char titre[50];
    char description[200];
    char priorite[30];
    DateEcheance Date;
    TaskStatus status;
} Tache;
}Tache;
int main() {

    printf("Les taches sont\n");
    for (int i = 0; i < taille; i++) {
        printf("Titre: %s\n", T[i].titre);
        printf("Description: %s\n", T[i].description);
        printf("Priorite: %s\n", T[i].priorite);
        printf("Status: %d\n", T[i].status);
        printf("Date d'echeance: %d/%d/%d\n", T[i].Date.jour, T[i].Date.mois, T[i].Date.annee);
    }
}

    return 0;
}