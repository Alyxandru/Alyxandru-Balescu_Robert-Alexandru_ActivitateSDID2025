#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define DIM_HTABLE 100

typedef struct User User;
typedef struct Htable Htable;

struct User {
    char* nume;
    unsigned int varsta;
    char deschis_la[11];
};

struct Htable {
    User user;
    char* cheie;
};

User citireUserFisier(FILE* f) {
    User user;
    char buffer[100];
    char sep[] = ";";
    fgets(buffer, 100, f);

    char* nume = strtok(buffer, sep);
    user.nume = (char*)malloc(strlen(nume) + 1);
    strcpy(user.nume, nume);

    unsigned int varsta = (unsigned int)atoi(strtok(NULL, sep));
    user.varsta = varsta;

    char* deschis_la = strtok(NULL, sep);
    strcpy(user.deschis_la, deschis_la);

    return user;

    /*char* nume;
    unsigned int varsta;
    char deschis_la[11];
    int nrTickete;
    int* tickets;*/
}
int functieHash(char* cheie) {
    unsigned int suma = cheie[0] * 31;
    for (unsigned char i = 1; i < strlen(cheie); i++) {
        suma += cheie[i];
    }

    return suma % DIM_HTABLE;
}

Htable* inserareHtable(Htable* htable, User user) {
    int poz = functieHash(user.nume);
    while (htable[poz].cheie != NULL) {
        poz++;
    }
    htable[poz].user = user;
    htable[poz].cheie = (char*)malloc(strlen(user.nume) + 1);
    strcpy(htable[poz].cheie, user.nume);

    return htable;
}
struct Htable* citireHtableDinFisier(const char* numeFisier, Htable* htable) {
    FILE* f = fopen(numeFisier, "r");
    if (f != NULL) {
        while (!feof(f)) {
            User user = citireUserFisier(f);
            htable = inserareHtable(htable, user);
        }
    }
    return htable;
}
void afisare(Htable* htable) {
    for (int i = 0; i < DIM_HTABLE; i++) {
        Htable temp = htable[i];
        if (temp.cheie != NULL) {
            printf("Poz: %d, Varsta utilizatorului %s este %d si a deschis contul la %s.\n", i, temp.user.nume, temp.user.varsta, temp.user.deschis_la);
        }
    }
}

int main() {
    Htable* htable = NULL;
    htable = (Htable*)malloc(sizeof(Htable) * DIM_HTABLE);
    for (int i = 0; i < DIM_HTABLE; i++) {
        htable[i].cheie = NULL;
    }
    htable = citireHtableDinFisier("Accounts.txt", htable);
    afisare(htable);
}
