#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define DIM_HTABLE 100

typedef struct Eveniment Eveniment;
typedef struct NodH NodH;

struct Eveniment {
	char* nume;
	char data[11];
	char* status;
	int nrMaximPersoane;
};
struct NodH {
	char* cheie;//nume
	NodH* next;
	Eveniment eveniment;
};
Eveniment citireFisier(FILE* f) {
	Eveniment eveniment;
	char separator[] = ";";
	char buffer[100];
	fgets(buffer, 100, f);

	char* nume = strtok(buffer, separator);
	eveniment.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(eveniment.nume, nume);

	char* data = strtok(NULL, separator);
	strcpy(eveniment.data, data);

	char* status = strtok(NULL, separator);
	eveniment.status = (char*)malloc(strlen(status) + 1);
	strcpy(eveniment.status, status);

	int nrMaximPersoane = (int)atoi(strtok(NULL, separator));
	eveniment.nrMaximPersoane = nrMaximPersoane;

	return eveniment;
}
int functieHash(char* cheie) {
	int suma = cheie[0] * 48;
	for (int i = 1; i < strlen(cheie); i++) {
		suma = suma + cheie[i];
	}
	return suma % DIM_HTABLE;
}
NodH* inserareListaS(NodH* list, Eveniment eveniment) {
	NodH* nou = (NodH*)malloc(sizeof(NodH));
	nou->cheie = (char*)malloc(strlen(eveniment.nume)+1);
	strcpy(nou->cheie, eveniment.nume);
	nou->next = NULL;
	nou->eveniment = eveniment;
	if (list == NULL) {
		return nou;
	}
	NodH* temp = list;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = nou;
	return list;

}
void afisareLS(NodH* list) {
	NodH* temp = list;
	while (temp != NULL) {
		printf("Evenimentul %s are loc pe data de %s si are statusul %s. Numarul maxim de persoane este %d.\n", temp->eveniment.nume, temp->eveniment.data, temp->eveniment.status, temp->eveniment.nrMaximPersoane);
		temp = temp->next;
	}
}
void afisare(NodH** nodH) {
	for (int i = 0; i < DIM_HTABLE; i++) {
		if(nodH[i])printf("POz: %d, ", i);
		afisareLS(nodH[i]);
	}
}
void inserareHtable(NodH** nodH, Eveniment eveniment) {
	int poz = functieHash(eveniment.nume);
	nodH[poz] = inserareListaS(nodH[poz], eveniment);
}
void citireHtableDinFisier(char* numeFisier, NodH** nodH) {
	FILE* f = fopen(numeFisier, "r");
	if (f != NULL) {
		while (!feof(f)) {
			Eveniment eveniment = citireFisier(f);
			inserareHtable(nodH, eveniment);
		}
	}
	fclose(f);
}
int main() {
	NodH** nodH = (NodH**)malloc(sizeof(NodH*) * DIM_HTABLE);
	for (int i = 0; i < DIM_HTABLE; i++) {
		nodH[i] = NULL;
	}
	citireHtableDinFisier("Evenimente.txt", nodH);
	printf("%p\n", nodH);
	afisare(nodH);
}
