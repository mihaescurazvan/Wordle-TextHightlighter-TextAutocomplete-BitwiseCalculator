#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dictionary_entry {
    char *word;
    int priority;
} dictionary_entry;
// functia pentru adaugarea unei noi entitati la dictionar
void adaugareDictionar(dictionary_entry **dictionar, int *n, char *cuvant) {
    // aloc dinamic un nou element de tip dictionary_entry
    dictionary_entry *nou_cuvant =
        (dictionary_entry *)malloc(sizeof(dictionary_entry));
    // initializez campul word al noului element cu valoarea parametrului cuvant
    // si prioritatea cu 1
    nou_cuvant->word = cuvant;
    nou_cuvant->priority = 1;
    // realoc memoria dictionarului, marind dimensiunea sa cu 1
    *dictionar = (dictionary_entry *)realloc(
        *dictionar, (*n + 1) * sizeof(dictionary_entry));
    // ultimului element din dictionar ii atribui valoarea noului cuvant
    (*dictionar)[*n] = *nou_cuvant;
    // maresc dimensiunea cu 1
    *n += 1;
}
// functia trateaza cazul in care este dat de la tastatura un cuvant urmat de *
char *cuvantSpecial(char *cuvant, dictionary_entry **dictionar, int *n) {
    int i;
    // sterg * din cuvantul respectiv
    cuvant[strlen(cuvant) - 1] = '\0';
    // daca cuvantul respectiv este in dictionar ii cresc prioritatea
    for (i = 0; i < (*n); i++) {
        if (strcmp(cuvant, (*dictionar)[i].word) == 0) {
            (*dictionar)[i].priority += 1;
            return cuvant;
        }
    }
    // daca cuvantul nu e in dictonar, il adaug la final cu prioritatea 1
    adaugareDictionar(dictionar, n, cuvant);
    return cuvant;
}
// functia care potriveste un cuvant dat ca input cu corespunzatorul lui din
// dictionar, daca exista
char *potrivireCuvant(char *cuvant, dictionary_entry *dictionar, int n,
                      char *potrivit) {
    // initializez prioritatea cea mai mare cu -1
    int ok = 0, max_pr = -1, i;
    for (i = 0; i < n; i++) {
        // daca cuvantul este subsirul de inceput unui cuvant din dictionar
        if (strlen(cuvant) <= strlen(dictionar[i].word) &&
            strncmp(cuvant, dictionar[i].word, strlen(cuvant)) == 0) {
            ok = 1;
            // daca prioritatea cuvantului gasit in dicitonar este mai mare
            // decat cea a unui cuvant din dictionar gasit anterior il asociem
            // pe acesta potrivirii si actualizam proritatea
            if (dictionar[i].priority > max_pr) {
                max_pr = dictionar[i].priority;
                strcpy(potrivit, dictionar[i].word);
            } else if (dictionar[i].priority == max_pr &&
                       strcmp(dictionar[i].word, potrivit) < 0) {
                // daca cuvantul gasit are aceeasi prioritate cu altul gasit
                // anterior, il potrivim cu cel mai mic, dpdv lexico-grafic
                strcpy(potrivit, dictionar[i].word);
            }
        }
    }
    // daca am gasit o potrivire in dictionar, ii cresc cu 1 prioritatea
    // cuvantului gasit
    if (ok) {
        for (i = 0; i < n; i++) {
            if (strcmp(dictionar[i].word, potrivit) == 0) {
                dictionar[i].priority += 1;
            }
        }
        return potrivit;
    }
    return NULL;
}
int main() {
    int n, m, i;
    dictionary_entry *dictionar;
    char cuvinte[5001][22], aux[21];
    scanf("%d", &n);
    // aloc dinamic dictionarul si cuvintele din dictioanar astfel incat sa nu
    // existe memorie neutilizata
    dictionar = (dictionary_entry *)malloc(n * sizeof(dictionary_entry));
    for (i = 0; i < n; i++) {
        scanf("%s", aux);
        dictionar[i].word = (char *)malloc((strlen(aux) + 1) * sizeof(char));
        strcpy(dictionar[i].word, aux);
        dictionar[i].priority = 0;
    }
    scanf("%d", &m);
    for (i = 0; i < m; i++) {
        scanf("%s", cuvinte[i]);
    }
    for (i = 0; i < m; i++) {
        // daca cuvantul actual este un semn de  punctuatie il afisam ca un
        // cuvant de sine statator
        if (strstr(",.:!?", cuvinte[i]) == NULL) {
            // daca cuvantul actual are la final * , apelam functia pentru cazul
            // respectiv
            if (cuvinte[i][strlen(cuvinte[i]) - 1] == '*') {
                printf("%s ", cuvantSpecial(cuvinte[i], &dictionar, &n));
            } else {
                // daca nu este un cuvant special si se gaseste o potrivire in
                // dictionar, afisam cuvantul gasit
                char potrivit[21];
                if (potrivireCuvant(cuvinte[i], dictionar, n, potrivit) !=
                    NULL) {
                    printf("%s ", potrivit);
                } else {
                    // daca nu este nici cuvant special, nici nu am gasit vreo
                    // potrivire in dictionar, afisam cuvantul asa cum este si
                    // il adaugam la final in dictionar cu prioritatea 1
                    adaugareDictionar(&dictionar, &n, cuvinte[i]);
                    printf("%s ", cuvinte[i]);
                }
            }

        } else {
            printf("%s ", cuvinte[i]);
        }
    }
    return 0;
}