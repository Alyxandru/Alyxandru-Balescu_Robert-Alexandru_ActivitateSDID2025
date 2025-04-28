//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <malloc.h>
//
//
//typedef struct Nod Nod;
//typedef struct Eveniment Eveniment;
//typedef struct LD LD;
//
//struct Eveniment {
//	char* nume;
//	char deshis_la[11];
//	char* status;
//	int nr_persoane;
//};
//
//struct Nod {
//	Eveniment eveniment;
//	Nod* next;
//	Nod* prev;
//};
//struct LD
//{
//	Nod* firstNod;
//	Nod* lastNod;
//};
//Eveniment citireEveniment(FILE* f) {
//	Eveniment eveniment;
//	char buffer[100];
//	char separator[] = ";";
//	fgets(buffer, 100, f);
//
//	char* nume = strtok(buffer, separator);
//	eveniment.nume = (char*)malloc(strlen(nume) + 1);
//	strcpy(eveniment.nume, nume);
//
//	char* deschis_la = strtok(NULL, separator);
//	strcpy(eveniment.deshis_la, deschis_la);
//
//	char* status = strtok(NULL, separator);
//	eveniment.status = (char*)malloc(strlen(status) + 1);
//	strcpy(eveniment.status, status);
//
//	int nr_persoane = atoi(strtok(NULL, separator));
//	eveniment.nr_persoane = nr_persoane;
//
//	return eveniment;
//}
//LD inserareListaD_sfarsit(LD list, Eveniment eveniment) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->eveniment = eveniment;
//	nou->next = NULL;
//	nou->prev = list.lastNod;
//	if (list.lastNod == NULL) {
//		list.firstNod = list.lastNod = nou;
//		return list;
//	}
//
//	list.lastNod->next = nou;
//	list.lastNod = nou;
//
//	return list;
//}
//LD citireDinFisier(char* numeTxt, LD list) {
//	FILE* f = fopen(numeTxt, "r");
//	if (f != NULL) {
//		while (!feof(f)) {
//			Eveniment eveniment = citireEveniment(f);
//			list = inserareListaD_sfarsit(list, eveniment);
//		}
//	}
//	return list;
//}
//void afisareLista(LD list) {
//	Nod* temp = list.firstNod;
//	while (temp != NULL) {
//		printf("Evenimentul %s are loc pe data de %s si are statusul %s. Numarul maxim de persoane este %d.\n",
//			temp->eveniment.nume, temp->eveniment.deshis_la, temp->eveniment.status, temp->eveniment.nr_persoane);
//		temp = temp->next;
//	}
//}
//int main() {
//	Eveniment eveniment1;
//	LD list1;
//	list1.firstNod = list1.lastNod = NULL;
//	list1 = citireDinFisier("EvenimentRecap.txt", list1);
//	afisareLista(list1);
//}