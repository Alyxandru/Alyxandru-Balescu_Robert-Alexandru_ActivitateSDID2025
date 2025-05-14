//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <malloc.h>
//
//typedef struct Automobil Automobil;
//typedef struct Nod Nod;
//
//struct Automobil {
//	char* type_automobil;
//	int wheels;
//};
//struct Nod {
//	Automobil automobil;
//	Nod* next;
//};
//
//Automobil citireAutomobil(FILE* f) {
//	Automobil automobil;
//	char buffer[100];
//	char sep[] = ";";
//	fgets(buffer, 100, f);
//
//	char* type_automobil = strtok(buffer, sep);
//	automobil.type_automobil = (char*)malloc(strlen(type_automobil) + 1);
//	strcpy(automobil.type_automobil, type_automobil);
//
//	int wheels = atoi(strtok(NULL, sep));
//	automobil.wheels = wheels;
//
//
//	return automobil;
//}
//Nod* inserareLista(Nod* list, Automobil automobil) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->automobil = automobil;
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
//
//Nod* citireFisier(char* numeFisier, Nod* list) {
//	FILE* f = fopen(numeFisier, "r");
//	if (f != NULL) {
//		while (!feof(f)) {
//			Automobil automobil = citireAutomobil(f);
//			list = inserareLista(list, automobil);
//		}
//	}
//	//fclose(f);
//	return list;
//}
//void afisareLista(Nod* list) {
//	Nod* temp = list;
//	while (temp != NULL) {
//		printf("Automobilu' este un %s si are %d roti.\n", temp->automobil.type_automobil, temp->automobil.wheels);
//		temp = temp->next;
//	}
//}
//int main() {
//	Nod* list1 = NULL;
//	list1 = citireFisier("Automobile.txt", list1);
//	afisareLista(list1);
//}