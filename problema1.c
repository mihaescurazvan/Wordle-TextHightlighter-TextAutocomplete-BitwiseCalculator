#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// functia daca cuvantul dat ca parametru se gaseste in lista cuvintelor cheie,
// returnand 1 in caz afirmativ si 0 in caz negativ
int cuvinteCheie(char *cuvant) {
    int i;
    char lista_keywords[16][10] = {"first of", "for",    "for each", "from",
                                   "in",       "is",     "is a",     "list of",
                                   "unit",     "or",     "while",    "int",
                                   "float",    "double", "string"};
    for (i = 0; i < 16; i++) {
        if (strcmp(cuvant, lista_keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
// care subliniaza cuvintele cheie
char *subliniereCuivinteCheie(char *linie, char *subliniere) {
    // in ant retin cuvantul anterior gasit
    char ant[101] = "";
    // despart linia in cuvinte
    char *p = strtok(linie, " ");
    // in antpoz retin pozitia cuvantului anterior
    int antpoz = 0, i;
    while (p != NULL) {
        // daca cuvantul e in lista cuvintelor cheie, retin adresa sa de inceput
        // si de final, si il subliniez in vectorul subliniere
        if (cuvinteCheie(p)) {
            for (i = p - linie; i < p - linie + strlen(p); i++) {
                subliniere[i] = '_';
            }
        } else if (strcmp(p, "of") == 0 || strcmp(p, "each") == 0 ||
                   strcmp(p, "a") == 0) {
            // daca cuvantul gasit e unul dintre cele 3 de mai sus, iar prin
            // concatenare cu cel anterior obtin unul dintre cuvintele cheie
            // compuse, subliniez de la pozitia de inceput a cuvantului anterior
            // pana la pozitia de final a cuvantului actual
            strcat(ant, " ");
            strcat(ant, p);
            if (cuvinteCheie(ant)) {
                for (i = antpoz; i < p - linie + strlen(p); i++) {
                    subliniere[i] = '_';
                }
            }
        }
        strcpy(ant, p);
        antpoz = p - linie;
        p = strtok(NULL, " ");
    }
    return subliniere;
}
int main() {
    int n, i, j;
    // folosesc 2 vectori de cuvinte alocati dinamic, unul pentru liniile
    // citite, si unul pentru sublinierea liniilor corespunzatoare
    char **linie, aux[102], **sublinieri;
    scanf("%d", &n);
    getc(stdin);
    linie = (char **)malloc(n * sizeof(char *));
    sublinieri = (char **)malloc(n * sizeof(char *));
    for (i = 0; i < n; i++) {
        fgets(aux, 102, stdin);
        aux[strlen(aux) - 1] = '\0';
        linie[i] = (char *)malloc((strlen(aux) + 1) * sizeof(char));
        sublinieri[i] = (char *)malloc((strlen(aux) + 1) * sizeof(char));
        strcpy(linie[i], aux);
        // initial fiecare caracter din vectorul de sublinieri va fi spatiu
        for (j = 0; j < strlen(linie[i]); j++) {
            sublinieri[i][j] = ' ';
        }
    }
    for (i = 0; i < n; i++) {
        strcpy(aux, linie[i]);
        // pentru fiecare linie apelez functia care creeaza sublinierile
        subliniereCuivinteCheie(aux, sublinieri[i]);
        puts(linie[i]);
        puts(sublinieri[i]);
    }
    return 0;
}