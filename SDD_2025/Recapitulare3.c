#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define DIMENSION_HTABLE 100

typedef struct Eveniment Eveniment;
typedef struct Htable Htable;

struct Eveniment {
	char* nume;
	char deshis_la[11];
	char* status;
	int nr_persoane;
};
struct Htable {
	Eveniment eveniment;
	char* key;
};
Eveniment citireEveniment(FILE* f) {
	Eveniment eveniment;
	char buffer[100];
	char separator[] = ";";
	fgets(buffer, 100, f);

	char* nume = strtok(buffer, separator);
	eveniment.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(eveniment.nume, nume);

	char* deschis_la = strtok(NULL, separator);
	strcpy(eveniment.deshis_la, deschis_la);
	
	char* status = strtok(NULL, separator);
	eveniment.status = (char*)malloc(strlen(status) + 1);
	strcpy(eveniment.status, status);
	
	int nr_persoane = atoi(strtok(NULL, separator));
	eveniment.nr_persoane = nr_persoane;
	
	return eveniment;
}
int functieHash(char* key) {
	int suma = 0;
	for (int i = 0; i < strlen(key); i++) {
		suma = suma + (i + key[i]);
	}
	return suma % 100;
}
Htable* inserareHtable(Htable* htable, Eveniment eveniment) {
	int poz = functieHash(eveniment.nume);
	while (htable[poz].key != NULL) {
		poz++;
	}
	htable[poz].eveniment = eveniment;
	htable[poz].key = (char*)malloc(strlen(eveniment.nume) + 1);
	strcpy(htable[poz].key, eveniment.nume);
	return htable;
}


Htable* citireFisier(char* numeFisier, Htable* htable) {
	 FILE* f = fopen(numeFisier, "r");
	 if (f != NULL) {
		 while (!feof(f)) {
			 Eveniment eveniment = citireEveniment(f);
			 htable = inserareHtable(htable, eveniment);
		 }
	 }
	 return htable;
}
void afisare(Htable* htable) {
	 for (int i = 0; i < DIMENSION_HTABLE; i++) {
		 if (htable[i].key != NULL) {
			 printf("Poz: %d, Evenimentul %s are loc pe data de %s si are statusul %s. Numarul maxim de persoane este %d.\n", i, htable[i].eveniment.nume, htable[i].eveniment.deshis_la, htable[i].eveniment.status, htable[i].eveniment.nr_persoane);
		 }
	 }
}
void cautareEveniment(Htable* htable, char* key) {
	 if (key != NULL) {
		 int poz = functieHash(key);
		 if (htable[poz].key != NULL) {
			 while (strcmp(htable[poz].key, key) && htable[poz].key != NULL) {
				 poz++;
				 if (htable[poz].key != NULL) {
					 break;
				 }
			 }
			 printf("Poz: %d, Evenimentul %s are loc pe data de %s si are statusul %s. Numarul maxim de persoane este %d.\n", poz, htable[poz].eveniment.nume, htable[poz].eveniment.deshis_la, htable[poz].eveniment.status, htable[poz].eveniment.nr_persoane);
		 }
		 else {
			 printf("\nceva nu mere\n");
		 }
	 }
	 else {
		 printf("\nceva nu mere");
	 }
}
void modificareNrPersoane(Htable* htable, char* key, int nr_persoane) {
	if (key != NULL) {
		int poz = functieHash(key);
		if (htable[poz].key != NULL) {
			while (strcmp(htable[poz].key, key)) {
				poz++;
				if (htable[poz].key != NULL) {
					break;
				}
			}
			htable[poz].eveniment.nr_persoane = nr_persoane;
		}
		
	}
	if(key == NULL){
		printf("\nceva nu mere");
	}
}


int main() {
	 Htable* htable = NULL;
	 htable = (Htable*)malloc(sizeof(Htable) * DIMENSION_HTABLE);
	 for (int i = 0; i < DIMENSION_HTABLE; i++) {
		 htable[i].key = NULL;
	 }
	 htable = citireFisier("EvenimentRecap.txt", htable);
	 afisare(htable);
	 cautareEveniment(htable, "Festival Jzzaa");
	 modificareNrPersoane(htable, "Festival Jzza", 489);
	 cautareEveniment(htable, "Festival Jzza");
}