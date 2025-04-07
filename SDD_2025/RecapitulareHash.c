//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//#include <malloc.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define DIM_HTABLE 100
//
//typedef struct Eveniment Eveniment;
//typedef struct NodH NodH;
//typedef struct NodLD NodLD;
//typedef struct ListaD ListaD;
//
//struct Eveniment {
//	char* nume;
//	char data[11];
//	char* status;
//	int nrMaximPersoane;
//};
//struct NodLD {
//	Eveniment eveniment;
//	NodLD* next;
//	NodLD* previos;
//};
//struct ListaD {
//	NodLD* primul;
//	NodLD* ultimul;
//};
//struct NodH {
//	char* cheie;//nume
//	NodH* next;
//	Eveniment eveniment;
//};
//Eveniment citireFisier(FILE* f) {
//	Eveniment eveniment;
//	char separator[] = ";";
//	char buffer[100];
//	fgets(buffer, 100, f);
//
//	char* nume = strtok(buffer, separator);
//	eveniment.nume = (char*)malloc(strlen(nume) + 1);
//	strcpy(eveniment.nume, nume);
//
//	char* data = strtok(NULL, separator);
//	strcpy(eveniment.data, data);
//
//	char* status = strtok(NULL, separator);
//	eveniment.status = (char*)malloc(strlen(status) + 1);
//	strcpy(eveniment.status, status);
//
//	int nrMaximPersoane = (int)atoi(strtok(NULL, separator));
//	eveniment.nrMaximPersoane = nrMaximPersoane;
//
//	return eveniment;
//}
//int functieHash(char* cheie) {
//	int suma = cheie[0] * 48;
//	for (int i = 1; i < strlen(cheie); i++) {
//		suma = suma + cheie[i];
//	}
//	return suma % DIM_HTABLE;
//}
//NodH* inserareListaS(NodH* list, Eveniment eveniment) {
//	NodH* nou = (NodH*)malloc(sizeof(NodH));
//	nou->cheie = (char*)malloc(strlen(eveniment.nume)+1);
//	strcpy(nou->cheie, eveniment.nume);
//	nou->next = NULL;
//	nou->eveniment = eveniment;
//	if (list == NULL) {
//		return nou;
//	}
//	NodH* temp = list;
//	while (temp->next != NULL) {
//		temp = temp->next;
//	}
//	temp->next = nou;
//	return list;
//
//}
//void afisareLS(NodH* list) {
//	NodH* temp = list;
//	while (temp != NULL) {
//		printf("Evenimentul %s are loc pe data de %s si are statusul %s. Numarul maxim de persoane este %d.\n", temp->eveniment.nume, temp->eveniment.data, temp->eveniment.status, temp->eveniment.nrMaximPersoane);
//		temp = temp->next;
//	}
//}
//void afisare(NodH** nodH) {
//	for (int i = 0; i < DIM_HTABLE; i++) {
//		if(nodH[i])printf("POz: %d, ", i);
//		afisareLS(nodH[i]);
//	}
//}
//void inserareHtable(NodH** nodH, Eveniment eveniment) {
//	int poz = functieHash(eveniment.nume);
//	nodH[poz] = inserareListaS(nodH[poz], eveniment);
//}
//void citireHtableDinFisier(char* numeFisier, NodH** nodH) {
//	FILE* f = fopen(numeFisier, "r");
//	if (f != NULL) {
//		while (!feof(f)) {
//			Eveniment eveniment = citireFisier(f);
//			inserareHtable(nodH, eveniment);
//		}
//	}
//	fclose(f);
//}
//
//void cautareEveniment(NodH** nodH, char* nume) {
//	int poz = functieHash(nume);
//	NodH* temp = nodH[poz];
//	while (temp != NULL) {
//		if (strcmp(temp->cheie, nume) == 0) {
//			printf("\nEvenimentul %s are loc pe data de %s si are statusul %s. Numarul maxim de persoane este %d.\n", temp->eveniment.nume, temp->eveniment.data, temp->eveniment.status, temp->eveniment.nrMaximPersoane);
//			return;
//		}
//		temp = temp->next;
//	}
//	printf("\nEveniment nu sa gasit");
//	return;
//}
//void modificareNrMax(NodH** nodH, char* nume, int modificare) {
//	int poz = functieHash(nume);
//	NodH* temp = nodH[poz];
//	while (temp != NULL) {
//		if (strcmp(temp->cheie, nume) == 0) {
//			temp->eveniment.nrMaximPersoane = modificare;
//			return;
//		}
//		temp = temp->next;
//	}
//
//}
//ListaD inserareLD(ListaD lista, Eveniment eveniment) {
//	NodLD* nou = (NodLD*)malloc(sizeof(NodLD));
//	nou->eveniment = eveniment;
//	nou->next = NULL;
//	nou->previos = lista.ultimul;
//
//	if (lista.primul == NULL) {
//		lista.primul = lista.ultimul = nou;
//		return lista;
//	}
//	lista.ultimul->next = nou;
//	return lista;
//}
//
//ListaD listaPTStatusAnulat(NodH** nodH) {
//	ListaD lista; 
//	lista.primul = lista.ultimul = NULL;
//
//	for (int i = 0; i < DIM_HTABLE; i++) {
//		if (nodH[i] != NULL) {
//			NodH* temp = nodH[i];
//			while (temp != NULL) {
//				if (strcmp(temp->eveniment.status, "anulat") == 0) {
//					lista = inserareLD(lista, temp->eveniment);
//				}
//				temp = temp->next;
//			}
//		}
//	}
//	return lista;
//}
//
//void afisareLD(ListaD lista) {
//	NodLD* temp = lista.primul;
//	while (temp != NULL) {
//		printf("\nEvenimentul %s are loc pe data de %s si are statusul %s. Numarul maxim de persoane este %d.\n", temp->eveniment.nume, temp->eveniment.data, temp->eveniment.status, temp->eveniment.nrMaximPersoane);
//		temp = temp->next;
//	}
//}
//
//int main() {
//	NodH** nodH = (NodH**)malloc(sizeof(NodH*) * DIM_HTABLE);
//	for (int i = 0; i < DIM_HTABLE; i++) {
//		nodH[i] = NULL;
//	}
//	citireHtableDinFisier("Evenimente.txt", nodH);
//	printf("%p\n", nodH);
//	afisare(nodH);
//	cautareEveniment(nodH, "Festival Jzza"); 
//	
//	modificareNrMax(nodH, "Festival Jzza", 600);
//	afisare(nodH);
//	printf("\n\n");
//	ListaD lista = listaPTStatusAnulat(nodH);
//	afisareLD(lista);
//	
//}
