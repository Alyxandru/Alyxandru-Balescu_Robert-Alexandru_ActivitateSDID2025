#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>



typedef struct User User;
typedef struct Nod Nod;

struct User {
    char* nume;
    unsigned int varsta;
    char deschis_la[11];
    int nrTickete;
    int* tickets;
};

struct Nod {
    User user;
    Nod* next;
};

Nod* inserare_sfarsit(Nod* list, User user) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->user = user;
    nou->next = NULL;

    if (list == NULL) {
        return nou;
    }
    Nod* temp = list;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = nou;
    return list;
}
void afisareListaSimpla(Nod* list) {
    Nod* temp = list;
    while (temp != NULL) {
        printf("Nume: %s, Varsta: %d, Contul a fost deschis la: %s. Tickete: ", temp->user.nume, temp->user.varsta, temp->user.deschis_la);
        for (int i = 0; i < temp->user.nrTickete;i++) {
            printf("%d, ", temp->user.tickets[i]);
        }
        printf("\n");
        temp = temp->next;
    }
}


void main() {
    FILE* f = fopen("Accounts.txt", "r");
    char buffer[1000];
    char separator[] = ";";
    Nod* list = NULL;

    while (fgets(buffer, sizeof(buffer), f)) {
        User user;
        char* token = strtok(buffer, separator);
        user.nume = (char*)malloc(strlen(token) + 1);
        strcpy(user.nume, token);
        //printf("%s\n", user.nume);

}