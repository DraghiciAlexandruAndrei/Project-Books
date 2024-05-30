#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED

// Definim structura pentru o carte
struct book {
    char nume[101];
    int pages;
};

void introducereManuala(struct book **carti, int *nrCarti);
struct book generareCarte();
void introducereMixta(struct book **carti, int *nrCarti);
void afisareCarti(struct book *carti, int nrCarti);
int sumaPagini(struct book *carti, int nrCarti);
void imparteCarti(struct book *carti, int nrCarti, int prag, int *countMaiMic, int *countMaiMare);
void imparteSectiuni(struct book *carti, int nrCarti, int totalPages, int* sectiuni);
void printSectiuni(struct book *carti, int nrCarti, int* sectiuni);
void eliminareCarte(struct book **carti, int *nrCarti);
int cautaCarte(struct book *carti, int nrCarti, char *nume, int* sectiuni);
#endif // BOOK_H_INCLUDED
