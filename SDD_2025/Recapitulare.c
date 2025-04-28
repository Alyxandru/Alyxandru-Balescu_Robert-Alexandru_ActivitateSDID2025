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
//
//
//struct Eveniment {
//	char* nume;
//	char deshis_la[11];
//	char* status;
//	int nr_persoane;
//};
//struct Nod {
//	Eveniment eveniment;
//	Nod* next;
//};
//Eveniment citireEveniment(FILE* f){
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
//Nod* inserareLista(Nod* list, Eveniment eveniment) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->eveniment = eveniment;
//	nou->next = NULL;
//	if (list == NULL) {
//		return nou;
//	}
//	Nod* temp = list;
//	while (temp->next != NULL) {
//		temp = temp->next;
//	}
//	temp->next = nou;
//	return list;
//}
//Nod* citireDinFisier(char* numeTxt, Nod* list) {
//	FILE* f = fopen(numeTxt, "r");
//	if (f != NULL) {
//		while (!feof(f)) {
//			Eveniment eveniment = citireEveniment(f);
//			list = inserareLista(list, eveniment);
//		}
//	}
//	return list;
//}
//void afisareLista(Nod* list) {
//	Nod* temp = list;
//	while (temp != NULL) {
//		printf("Evenimentul %s are loc pe data de %s si are statusul %s. Numarul maxim de persoane este %d.\n",
//			temp->eveniment.nume, temp->eveniment.deshis_la, temp->eveniment.status, temp->eveniment.nr_persoane);
//		temp = temp->next;
//	}
//}
//int main() {
//	Eveniment eveniment1;
//	Nod* list1 = NULL;
//	list1 = citireDinFisier("EvenimentRecap.txt", list1);
//	afisareLista(list1);
//}