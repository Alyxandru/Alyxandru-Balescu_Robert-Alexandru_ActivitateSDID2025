//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//#include <malloc.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Eveniment Eveniment;
//typedef struct NodABC NodABC;
//
//struct Eveniment {
//    int idEveniment;
//    char* nume;
//    char data[11];
//    int nrMaximPersoane;
//};
//
//struct NodABC {
//    Eveniment eveniment;
//    NodABC* left;
//    NodABC* right;
//};
//
//Eveniment citireEveniment(FILE* f) {
//    Eveniment eveniment;
//    char separator[] = ";";
//    char buffer[100];
//    fgets(buffer, 100, f);
//
//    int id = atoi(strtok(buffer, separator));
//    eveniment.idEveniment = id;
//
//    char* nume = strtok(NULL, separator);
//    eveniment.nume = (char*)malloc(strlen(nume) + 1);
//    strcpy(eveniment.nume, nume);
//
//    char* data = strtok(NULL, separator);
//    strcpy(eveniment.data, data);
//
//    int nrMaximPersoane = (int)atoi(strtok(NULL, separator));
//    eveniment.nrMaximPersoane = nrMaximPersoane;
//
//    return eveniment;
//}
//
//NodABC* inserareABC(NodABC* rad, Eveniment eveniment) {
//    if (rad != NULL) {
//        if (eveniment.idEveniment < rad->eveniment.idEveniment) {
//            rad->left = inserareABC(rad->left, eveniment);
//        }
//        else if (eveniment.idEveniment > rad->eveniment.idEveniment) {
//            rad->right = inserareABC(rad->right, eveniment);
//
//        }
//        else {
//            printf("something\n");
//        }
//        return rad;
//
//    }
//    NodABC* nou = (NodABC*)malloc(sizeof(NodABC));
//    nou->eveniment = eveniment;
//    nou->left = nou->right = NULL;
//    return nou;
//}
//
//NodABC* citireFisierABC(NodABC* rad, char* numeFisier) {
//    FILE* f = fopen(numeFisier, "r");
//    if (f != NULL) {
//        while (!feof(f)) {
//            Eveniment eveniment = citireEveniment(f);
//            rad = inserareABC(rad, eveniment);
//        }
//    }
//    fclose(f);
//    return rad;
//}
//
//void afisarePreordine(NodABC* rad) {
//    if(rad){ 
//        printf("\n%d -- Evenimentul %s are loc pe data de %s. Numarul maxim de persoane este %d.\n", rad->eveniment.idEveniment, rad->eveniment.nume, rad->eveniment.data, rad->eveniment.nrMaximPersoane);
//        afisarePreordine(rad->left);
//        afisarePreordine(rad->right);
//    }
//}
//void afisareInordine(NodABC* rad) {
//    if (rad) {
//        afisareInordine(rad->left);
//        printf("\n%d -- Evenimentul %s are loc pe data de %s. Numarul maxim de persoane este %d.\n", rad->eveniment.idEveniment, rad->eveniment.nume, rad->eveniment.data, rad->eveniment.nrMaximPersoane);
//        afisareInordine(rad->right);
//    }
//}
//void afisarePostordine(NodABC* rad) {
//    if (rad) {
//        afisarePostordine(rad->left);
//        afisarePostordine(rad->right);
//        printf("\n%d -- Evenimentul %s are loc pe data de %s. Numarul maxim de persoane este %d.\n", rad->eveniment.idEveniment, rad->eveniment.nume, rad->eveniment.data, rad->eveniment.nrMaximPersoane);
//    }
//}
//
//void cautareEveniment(NodABC* rad, int id) {
//    if (rad) {
//        if (id < rad->eveniment.idEveniment) {
//            cautareEveniment(rad->left, id);
//        }
//        else if (id > rad->eveniment.idEveniment) {
//            cautareEveniment(rad->right, id);
//        }
//        else {
//            printf("%d -- Evenimentul %s are loc pe data de %s. Numarul maxim de persoane este %d.\n", rad->eveniment.idEveniment, rad->eveniment.nume, rad->eveniment.data, rad->eveniment.nrMaximPersoane);
//        }
//    }
//    else {
//        printf("Nu s-a gasit\n");
//    }
//}
//
////Modificare nr maxim de persoane
//NodABC* modificareNrMaximPers(NodABC* rad, int id, int nrMaximPersoane) {
//    if (rad) {
//        if (id < rad->eveniment.idEveniment) {
//            rad->left = modificareNrMaximPers(rad->left, id, nrMaximPersoane);
//        }
//        else if (id > rad->eveniment.idEveniment) {
//            rad->right = modificareNrMaximPers(rad->right, id, nrMaximPersoane);
//        }
//        else {
//            rad->eveniment.nrMaximPersoane = nrMaximPersoane;
//        }
//    }
//
//    return rad;
//}
//
//
//NodABC* stergereRadacina(NodABC* rad) {
//    NodABC* temp = rad;
//    if (temp->left != NULL) {
//        temp = temp->left;
//        while (temp->right != NULL) {
//            temp = temp->right;
//        }
//        temp->right = rad->right;
//        temp = rad->left;
//    }
//    else if (temp->right != NULL) {
//        temp = temp->right;
//    }
//    else {
//        temp = NULL;
//    }
//    free(rad->eveniment.nume);
//    free(rad);
//    return temp;
//}
//NodABC* stergereNod(NodABC* rad, int id) {
//    if (rad) {
//        if (id < rad->eveniment.idEveniment) {
//            rad->left = stergereNod(rad->left, id);
//        }
//        else if (id > rad->eveniment.idEveniment) {
//            rad->right = stergereNod(rad->right, id);
//        }
//        else {
//            rad = stergereRadacina(rad);
//        }
//    }
//}
//
//void main() {
//    NodABC* rad = NULL;
//    rad = citireFisierABC(rad, "Events.txt");
//
//    printf("\nPre: \n");
//    afisarePreordine(rad); // Radacina -> Stanga -> Dreapta
//    printf("\nIn: \n");
//    afisareInordine(rad); //Stanga -> Radacina -> Dreapta
//    printf("\nPost: \n");
//    afisarePostordine(rad); // Stanga -> Dreapta -> Radacina
//
//    printf("\nCautare: \n");
//    cautareEveniment(rad, 35);
//
//
//    printf("\nCeva: \n");
//    rad = stergereRadacina(rad);
//    printf("\nPre: \n");
//    afisarePreordine(rad); // Radacina -> Stanga -> Dreapta
//    printf("\nIn: \n");
//    afisareInordine(rad); //Stanga -> Radacina -> Dreapta
//    printf("\nPost: \n");
//    afisarePostordine(rad); // Stanga -> Dreapta -> Radacina
//}