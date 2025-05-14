#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct Eveniment Eveniment;
typedef struct NodAVL NodAVL;

struct Eveniment {
    int idEveniment;
    char* nume;
    char data[11];
    int nrMaximPersoane;
};

struct NodAVL {
    Eveniment eveniment;
    int ge;
    NodAVL* left;
    NodAVL* right;
};

Eveniment citireEveniment(FILE* f) {
    Eveniment eveniment;
    char separator[] = ";";
    char buffer[100];
    fgets(buffer, 100, f);

    int id = atoi(strtok(buffer, separator));
    eveniment.idEveniment = id;

    char* nume = strtok(NULL, separator);
    eveniment.nume = (char*)malloc(strlen(nume) + 1);
    strcpy(eveniment.nume, nume);

    char* data = strtok(NULL, separator);
    strcpy(eveniment.data, data);

    int nrMaximPersoane = (int)atoi(strtok(NULL, separator));
    eveniment.nrMaximPersoane = nrMaximPersoane;

    return eveniment;
}

NodAVL* inserareAVL(NodAVL* rad, Eveniment eveniment) {
    if (rad != NULL) {
        if (eveniment.idEveniment < rad->eveniment.idEveniment) {
            rad->left = inserareAVL(rad->left, eveniment);
        }
        else if (eveniment.idEveniment > rad->eveniment.idEveniment) {
            rad->right = inserareAVL(rad->right, eveniment);
        }
        else {
            printf("Evenimentul exista deja!\n");
        }
        return rad;
    }
    else {
        NodAVL* nou = (NodAVL*)malloc(sizeof(NodAVL));
        nou->eveniment = eveniment;
        nou->left = nou->right = NULL;
        nou->ge = 0;
        return nou;
    }
}

int maxim(int a, int b) {
    int max;
    if (a < b) {
        max = b;
    }
    else {
        max = a;
    }
    return max;
}

int inaltime(NodAVL* rad) {
    if (rad) {
        return 1 + maxim(inaltime(rad->left), inaltime(rad->right));
    }
    else {
        return 0;
    }
}

void calculGE(NodAVL* rad) {
    if (rad) {
        rad->ge = inaltime(rad->right) - inaltime(rad->left);
        calculGE(rad->left);
        calculGE(rad->right);
    }
}

NodAVL* rotireDreapta(NodAVL* rad) {
    NodAVL* subArbore = rad->left; //2
    rad->left = subArbore->right; // NULL
    subArbore->right = rad; //3
    rad = subArbore; //2

    return rad;
}

NodAVL* rotireStanga(NodAVL* rad) {
    NodAVL* subarbore = rad->right; //2
    rad->right = subarbore->left;
    subarbore->left = rad;
    rad = subarbore;

    return rad;
}

NodAVL* rotireDreaptaStanga(NodAVL* rad) {
    rad->right = rotireDreapta(rad->right);
    rad = rotireStanga(rad);

    return rad;
}

NodAVL* rotireStangaDreapta(NodAVL* rad) {
    rad->left = rotireStanga(rad->left);
    rad = rotireDreapta(rad);

    return rad;
}

NodAVL* echilibrare(NodAVL* rad) {
    calculGE(rad);
    if (rad->ge <= -2 && rad->left->ge <= -1) {
        rad = rotireDreapta(rad);
        calculGE(rad);
    }
    else if (rad->ge >= 2 && rad->right->ge >= 1) {
        rad = rotireStanga(rad);
        calculGE(rad);
    }
    else if (rad->ge >= 2 && rad->right->ge <= -1) {
        rad = rotireDreaptaStanga(rad);
        calculGE(rad);
    }
    else if (rad->ge <= -2 && rad->left->ge >= 1) {
        rad = rotireStangaDreapta(rad);
        calculGE(rad);
    }

    return rad;
}

NodAVL* citireFisierAVL(NodAVL* rad, char* numeFisier) {
    FILE* f = fopen(numeFisier, "r");
    if (f != NULL) {
        while (!feof(f)) {
            Eveniment eveniment = citireEveniment(f);
            rad = inserareAVL(rad, eveniment);
            rad = echilibrare(rad);
        }
    }
    fclose(f);
    return rad;
}

void afisarePreordine(NodAVL* rad) { //RSD
    if (rad) {
        printf("%d -- Evenimentul %s are loc pe data de %s. Numarul maxim de persoane este %d.\n", rad->eveniment.idEveniment, rad->eveniment.nume, rad->eveniment.data, rad->eveniment.nrMaximPersoane);
        afisarePreordine(rad->left);
        afisarePreordine(rad->right);
    }
}

void afisareInordine(NodAVL* rad) { //SRD
    if (rad) {
        afisareInordine(rad->left);
        printf("%d -- Evenimentul %s are loc pe data de %s. Numarul maxim de persoane este %d.\n", rad->eveniment.idEveniment, rad->eveniment.nume, rad->eveniment.data, rad->eveniment.nrMaximPersoane);
        afisareInordine(rad->right);
    }
}

void afisarePostordine(NodAVL* rad) { //SDR
    if (rad) {
        afisarePostordine(rad->left);
        afisarePostordine(rad->right);
        printf("%d -- Evenimentul %s are loc pe data de %s. Numarul maxim de persoane este %d.\n", rad->eveniment.idEveniment, rad->eveniment.nume, rad->eveniment.data, rad->eveniment.nrMaximPersoane);
    }
}

void main() {
    NodAVL* rad = NULL;
    rad = citireFisierAVL(rad, "Evenimente.txt");

    printf("Preordine:\n");
    afisarePreordine(rad); // Radacina -> Stanga -> Dreapta (RSD)
    printf("Inordine:\n");
    afisareInordine(rad); // Stanga -> Radacina -> Dreapta (SRD)
    printf("Postordine:\n");
    afisarePostordine(rad); // Stanga -> Dreapta -> Radacina (SDR)
}