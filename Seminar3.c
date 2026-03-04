#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

void afisareMasina(Masina masina) {
	printf("\nId: %d", masina.id);
	printf("\nnr usi: %d", masina.nrUsi);
	printf("\npret: %f", masina.pret);
	printf("\nmodel: %s", masina.model);
	printf("\nnumeSofer: %s", masina.numeSofer);
	printf("\nserie: %c", masina.serie);
	printf("\n--------------------\n");
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	//afiseaza toate elemente de tip masina din vector
	//prin apelarea functiei afisareMasina()
	for (int i = 0; i < nrMasini; i++)
	{
		afisareMasina(masini[i]);
	}
}

void adaugaMasinaInVector(Masina** masini, int * nrMasini, Masina masinaNoua) {
	//adauga in vectorul primit o noua masina pe care o primim ca parametru
	//ATENTIE - se modifica numarul de masini din vector;

	(*nrMasini)++;
	Masina* aux = malloc(sizeof(Masina) * *(nrMasini));
	for (int i = 0; i < *nrMasini - 1; i++)
	{
		aux[i] = (*masini)[i]; // shallow copy
	}
	aux[(*nrMasini)-1] = masinaNoua;
	free(*masini);
	*masini = aux;
	
}

Masina citireMasinaFisier(FILE* file) {
	//functia citeste o masina dintr-un strceam deja deschis
	//masina citita este returnata;

	char linie[50];
	fgets(linie, 50, file);
	Masina masina;
	char delimitatori[3] = ",\n";
	masina.id = atoi(strtok(linie, delimitatori));
	masina.nrUsi = atoi(strtok(NULL, delimitatori));
	masina.pret = atof(strtok(NULL, delimitatori));

	char* model = strtok(NULL, delimitatori);
	masina.model = malloc((strlen(model) + 1) * sizeof(char));
	strcpy(masina.model, model);
	
	char* numeSofer = strtok(NULL, delimitatori);
	masina.numeSofer = malloc((strlen(numeSofer) + 1) * sizeof(char));
	strcpy(masina.numeSofer, numeSofer);

	char* serie = strtok(NULL, delimitatori);
	masina.serie = serie[0];


	return masina;
	
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaFisier()
	//numarul de masini este determinat prin numarul de citiri din fisier
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* file = fopen(numeFisier, "r");
	Masina* masini = NULL;
	int k = 0;
	*nrMasiniCitite = 0;
	while (!feof(file))
	{
		adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(file));
	}
	fclose(file);
	return masini;

}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
}

int main() {
	int nr =0;
	Masina* masina = citireVectorMasiniFisier("masini.txt", &nr);
	afisareVectorMasini(masina, nr);
	return 0;
}