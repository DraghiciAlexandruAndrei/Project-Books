#include <stdio.h>
#include <stdlib.h>
#include "book.h"

int main() {
    int choice;
    int nrCarti = 0;
    struct book *carti = NULL;
    int *sectiuni = NULL;

    do {
        printf("===================================================================\n");
        printf("                      Meniu de selectie\n");
        printf("===================================================================\n");

        printf("1. Introduceti carti in biblioteca\n"); ///introducerea cartilor manual sau random
        printf("2. Lista carti\n");/// lista cartilor
        printf("3. Nr total pagini\n"); /// nr pagini total
        printf("4. Impartire pe sectiuni\n"); /// impart nr paginilor la nr de angajati
        printf("5. Eliminare carti din biblioteca\n");
        printf("6. Cauta carti in biblioteca\n");
        printf("0. Iesire din meniu\n");
        printf("Va rog alegeti o comanda pentru a incepe:\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Introducere carti
                introducereMixta(&carti, &nrCarti);
                break;
            case 2:
                // Afisare carti
                if (nrCarti > 0) {
                    afisareCarti(carti, nrCarti);
                } else {
                    printf("Nu exista carti pe raft\n");
                }
                break;
            case 3:
                // Numar total pagini
                if (nrCarti > 0) {
                    int totalPages = sumaPagini(carti, nrCarti);
                    printf("Numarul total de pagini: %d\n", totalPages);
                } else {
                    printf("Nu exista carti pe raft\n");
                }
                break;
            case 4:
                // Impartire pe sectiuni
                if (nrCarti > 0) {
                    int totalPages = sumaPagini(carti, nrCarti);
                    int prag = totalPages / 3;
                    int countMaiMic = 0, countMaiMare = 0;

                    imparteCarti(carti, nrCarti, prag, &countMaiMic, &countMaiMare);

                    printf("Numarul de carti cu pagini mai mici decat %d: %d\n", prag, countMaiMic);
                    printf("Numarul de carti cu pagini mai mari sau egale cu %d: %d\n", prag, countMaiMare);

                    // Allocate array for sections
                    sectiuni = (int*)malloc(3 * nrCarti * sizeof(int));
                    if (sectiuni == NULL) {
                        printf("Memorie insuficienta!\n");
                        free(carti);
                        return 1;
                    }

                    for (int i = 0; i < 3 * nrCarti; i++) {
                        sectiuni[i] = -1;
                    }

                    // Distribute books into sections
                    imparteSectiuni(carti, nrCarti, totalPages, sectiuni);

                    // Print the sections
                    printSectiuni(carti, nrCarti, sectiuni);

                } else {
                    printf("Nu exista carti pe raft\n");
                }
                break;
            case 5:
                // Eliminare carti
                if (nrCarti > 0) {
                    eliminareCarte(&carti, &nrCarti);
                } else {
                    printf("Nu exista carti pe raft\n");
                }
                break;
            case 6:
                // Cautare carte
                if (nrCarti > 0 && sectiuni != NULL) {
                    char nume[100];
                    printf("Introduceti numele cartii de cautat:\n");
                    scanf("%s", nume);
                    int sectiune = cautaCarte(carti, nrCarti, nume, sectiuni);
                    if (sectiune != -1) {
                        printf("Cartea \"%s\" se afla in sectiunea %d.\n", nume, sectiune);
                    } else {
                        printf("Cartea \"%s\" nu a fost gasita.\n", nume);
                    }
                } else {
                    printf("Nu exista carti pe raft sau sectiunile nu au fost calculate\n");
                }
                break;
        }
    } while (choice != 0);

    free(carti);
    free(sectiuni);
    return 0;
}
