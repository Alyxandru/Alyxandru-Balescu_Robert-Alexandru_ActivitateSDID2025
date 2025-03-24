//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//#include <malloc.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define DIM_HTABLE 100
//
//typedef struct User User;
//typedef struct Htable Htable;
//typedef struct NodLS NodLS;
//
//struct User {
//    char* nume;
//    unsigned int varsta;
//    char deschis_la[11];
//};
//
//struct Htable {
//    User user;
//    char* cheie;
//};
//struct NodLS {
//    User user;
//    NodLS* next;
//};
//
//NodLS* inserareLS_end(NodLS* lista, User user) {
//    NodLS* nou = (NodLS*)malloc(sizeof(NodLS));
//    nou->next = NULL;
//    nou->user = user;
//
//    if (lista == NULL) {
//        return nou;
//    }
//    NodLS* temp = lista;
//    while (temp->next != NULL) {
//        temp = temp->next;
//    }
//    temp->next = nou;
//    return lista;
//}
//void afisareLS(NodLS* lista) {
//    NodLS* temp = lista;
//    while (temp != NULL) {
//        printf("Varsta utilizatorului %s este %d si a deschis contul la %s.\n", temp->user.nume, temp->user.varsta, temp->user.deschis_la);
//        temp = temp->next;
//    }
//}
//
//NodLS* filtruAge(Htable* htable) {
//    NodLS* lista = NULL;
//    for (int i = 0; i < DIM_HTABLE; i++) {
//        if (htable[i].cheie != NULL && htable[i].user.varsta <30) {
//            lista = inserareLS_end(lista, htable[i].user);
//        }
//    }
//    return lista;
//}
//
//User citireUserFisier(FILE* f) {
//    User user;
//    char buffer[100];
//    char sep[] = ";";
//    fgets(buffer, 100, f);
//
//    char* nume = strtok(buffer, sep);
//    user.nume = (char*)malloc(strlen(nume) + 1);
//    strcpy(user.nume, nume);
//
//    unsigned int varsta = (unsigned int)atoi(strtok(NULL, sep));
//    user.varsta = varsta;
//
//    char* deschis_la = strtok(NULL, sep);
//    strcpy(user.deschis_la, deschis_la);
//
//    return user;
//
//    /*char* nume;
//    unsigned int varsta;
//    char deschis_la[11];
//    int nrTickete;
//    int* tickets;*/
//}
//int functieHash(char* cheie) {
//    unsigned int suma = cheie[0] * 31;
//    for (unsigned char i = 1; i < strlen(cheie); i++) {
//        suma += cheie[i];
//    }
//
//    return suma % DIM_HTABLE;
//}
////quadratic probing:
//
////Htable* inserareHtable(Htable* htable, User user) {
////    int poz = functieHash(user.nume);
////    int aux = poz;
////    int i = 1;
////    while (htable[poz].cheie != NULL) {
////        poz = aux + i * i;
////        i++;
////    }
////    htable[poz].user = user;
////    htable[poz].cheie = (char*)malloc(strlen(user.nume) + 1);
////    strcpy(htable[poz].cheie, user.nume);
////
////    return htable;
////}
//
//
//
////double hashing:
//
//
////int functieHash2(int poz) {
////    return 7 - (poz % 7);
////}
////
////Nod* inserareHtable(Nod* htable, User user) {
////    int poz = functieHash1(user.nume);
////    int hash2 = functieHash2(poz);
////    while (htable[poz].cheie != NULL) {
////        poz = (poz + hash2) % DIM_HTABLE;
////    }
////    htable[poz].user = user;
////    htable[poz].cheie = (char*)malloc(strlen(user.nume) + 1);
////    strcpy(htable[poz].cheie, user.nume);
////
////    return htable;
////}
//Htable* inserareHtable(Htable* htable, User user) {
//    int poz = functieHash(user.nume);
//    while (htable[poz].cheie != NULL) {
//        poz++;
//    }
//    htable[poz].user = user;
//    htable[poz].cheie = (char*)malloc(strlen(user.nume) + 1);
//    strcpy(htable[poz].cheie, user.nume);
//
//    return htable;
//}
//struct Htable* citireHtableDinFisier(const char* numeFisier, Htable* htable) {
//    FILE* f = fopen(numeFisier, "r");
//    if (f != NULL) {
//        while (!feof(f)) {
//            User user = citireUserFisier(f);
//            htable = inserareHtable(htable, user);
//        }
//    }
//    fclose(f);
//    return htable;
//}
//void afisare(Htable* htable) {
//    for (int i = 0; i < DIM_HTABLE; i++) {
//        Htable temp = htable[i];
//        if (temp.cheie != NULL) {
//            printf("Poz: %d, Varsta utilizatorului %s este %d si a deschis contul la %s.\n", i, temp.user.nume, temp.user.varsta, temp.user.deschis_la);
//        }
//    }
//}
//
//User cautareUser(Htable* htable, char* cheie) {
//    int poz = functieHash(cheie);
//    while (strcmp(htable[poz].cheie, cheie) != 0) {
//        poz++;
//    }
//    return htable[poz].user;
//}
//
//void modificareData(Htable* htable, char* cheie, char* new_date){
//    int poz = functieHash(cheie);
//    while (strcmp(htable[poz].cheie, cheie) != 0) {
//        poz++;
//    }
//    strcpy(htable[poz].user.deschis_la, new_date);
//}
//
//
//int main() {
//    Htable* htable = NULL;
//    htable = (Htable*)malloc(sizeof(Htable) * DIM_HTABLE);
//    for (int i = 0; i < DIM_HTABLE; i++) {
//        htable[i].cheie = NULL;
//    }
//    htable = citireHtableDinFisier("Accounts.txt", htable);
//    //afisare(htable);
//
//    User user = cautareUser(htable, "pope9_s");
//    printf("Varsta utilizatorului %s este %d si a deschis contul la %s.\n", user.nume, user.varsta, user.deschis_la);
//    afisare(htable);
//    /*modificareData(htable, "pope9_s", "17.04.2024");
//    afisare(htable);*/
//    printf("\n");
//    NodLS* lista = filtruAge(htable);
//    afisareLS(lista);
//
//    return 0;
//}
