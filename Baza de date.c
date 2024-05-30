    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <malloc.h>
    #include "book.h"
  // Introducere carti manual
void introducereManuala(struct book **carti, int *nrCarti) {
    char continua[3];

    do {
        *carti = realloc(*carti, (*nrCarti + 1) * sizeof(struct book));
        if (*carti == NULL) {
            printf("Memorie insuficienta!\n");
            return;
        }

        printf("Introduceti numele cartii:\n");
        scanf("%s", (*carti)[*nrCarti].nume);

        printf("Introduceti numarul de pagini al cartii:\n");
        scanf("%d", &((*carti)[*nrCarti].pages));

        (*nrCarti)++;

        printf("Doriti sa introduceti alta carte? (da/nu): ");
        scanf("%s", continua);
        getchar(); // Consumăm caracterul newline

    } while (strcmp(continua, "da") == 0);
}

// Funcție pentru generarea aleatoare a unei cărți
struct book generareCarte() {
    struct book carte;
    char nume[101];
    sprintf(nume, "Carte%d", rand() % 1000); // Concatenăm "Carte" cu un număr aleatoriu între 0 și 999
    strcpy(carte.nume, nume);
    carte.pages = rand() % 1000 + 1; // Generăm un număr aleatoriu de pagini între 1 și 1000
    return carte;
}

// Funcție pentru introducerea mixtă a cărților (manuală și aleatoare)
void introducereMixta(struct book **carti, int *nrCarti) {
    char optiune[2];

    printf("Doriti sa introduceti manual (m) sau aleatoriu (a)? ");
    scanf("%s", optiune);

    if (strcmp(optiune, "m") == 0) {
        introducereManuala(carti, nrCarti);
    } else if (strcmp(optiune, "a") == 0) {
        printf("Introduceti numarul de carti aleatorii pe care doriti sa le generati: ");
        int nrAleatorii;
        scanf("%d", &nrAleatorii);
        getchar(); // Consumăm caracterul newline

        for (int i = 0; i < nrAleatorii; i++) {
            *carti = realloc(*carti, (*nrCarti + 1) * sizeof(struct book));
            if (*carti == NULL) {
                printf("Memorie insuficienta!\n");
                return;
            }
            (*carti)[*nrCarti] = generareCarte();
            (*nrCarti)++;
        }
    } else {
        printf("Optiune invalida.\n");
    }
}

// Afisare carti
void afisareCarti(struct book *carti, int nrCarti) {
    for (int i = 0; i < nrCarti; i++) {
        printf("Cartea %d: %s, %d pagini\n", i + 1, carti[i].nume, carti[i].pages);
    }
}

// Calculare suma paginilor
int sumaPagini(struct book *carti, int nrCarti) {
    int total = 0;
    for (int i = 0; i < nrCarti; i++) {
        total += carti[i].pages;
    }
    return total;
}

// Impartirea cartilor in functie de prag
void imparteCarti(struct book *carti, int nrCarti, int prag, int *countMaiMic, int *countMaiMare) {
    *countMaiMic = 0;
    *countMaiMare = 0;

    for (int i = 0; i < nrCarti; i++) {
        if (carti[i].pages < prag) {
            (*countMaiMic)++;
        } else {
            (*countMaiMare)++;
        }
    }
}

// Impartirea cartilor pe sectiuni
void imparteSectiuni(struct book *carti, int nrCarti, int totalPages, int* sectiuni) {
    int prag = totalPages / 3;
    int currentPages[3] = {0, 0, 0};
    int currentCount[3] = {0, 0, 0};

    for (int i = 0; i < nrCarti; i++) {
        int minSection = 0;
        for (int j = 1; j < 3; j++) {
            if (currentPages[j] < currentPages[minSection]) {
                minSection = j;
            }
        }
        currentPages[minSection] += carti[i].pages;
        sectiuni[minSection * nrCarti + currentCount[minSection]] = i;
        currentCount[minSection]++;
    }
}

// Afisarea sectiunilor
void printSectiuni(struct book *carti, int nrCarti, int* sectiuni) {
    for (int i = 0; i < 3; i++) {
        printf("Sectiunea %d:\n", i + 1);
        for (int j = 0; j < nrCarti; j++) {
            if (sectiuni[i * nrCarti + j] != -1) {
                int idx = sectiuni[i * nrCarti + j];
                printf("  Cartea %s, %d pagini\n", carti[idx].nume, carti[idx].pages);
            }
        }
    }
}

// Eliminare carte
void eliminareCarte(struct book **carti, int *nrCarti) {
    char nume[100];
    printf("Introduceti numele cartii pe care doriti sa o eliminati:\n");
    scanf("%99s", nume); // Ensure not to overflow the buffer

    int index = -1;
    for (int i = 0; i < *nrCarti; i++) {
        if (strcmp((*carti)[i].nume, nume) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Cartea nu a fost gasita.\n");
        return;
    }

    // Move the last book into the position of the deleted book
    (*carti)[index] = (*carti)[*nrCarti - 1];

    // Reallocate memory to shrink the array
    struct book *temp = realloc(*carti, (*nrCarti - 1) * sizeof(struct book));
    if (temp == NULL && *nrCarti > 1) {
        printf("Memorie insuficienta!\n");
        return;
    }

    *carti = temp;
    (*nrCarti)--;

    printf("Cartea a fost eliminata cu succes.\n");
}

// Cauta carte si afiseaza sectiunea
int cautaCarte(struct book *carti, int nrCarti, char *nume, int* sectiuni) {
    for (int i = 0; i < nrCarti; i++) {
        if (strcmp(carti[i].nume, nume) == 0) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < nrCarti; k++) {
                    if (sectiuni[j * nrCarti + k] == i) {
                        return j + 1; // Return the section number (1-based)
                    }
                }
            }
        }
    }
    return -1; // Cărțile nu au fost găsite
}
