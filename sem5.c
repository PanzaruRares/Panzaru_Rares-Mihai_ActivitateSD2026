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
typedef struct ListaDubla ListaDubla;
typedef struct Nod Nod;

//creare structura pentru un nod dintr-o lista dublu inlantuita
struct Nod
{
	Masina info;
	struct Nod* next;
	struct Nod* prev;
};

struct ListaDubla
{
	struct Nod* prim;
	struct Nod* ultim;
};

//creare structura pentru Lista Dubla 

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(/*lista dubla de masini*/ ListaDubla lista) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
	Nod* p = lista.prim;
	while (p)
	{
		afisareMasina(p->info);
		p = p->next;
	}

}

void adaugaMasinaInLista(/*lista dubla de masini*/ ListaDubla* ld, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* nou = malloc(sizeof(Nod));
	nou->info = masinaNoua; // shallow
	nou->next = NULL;
	nou->prev = ld->ultim;
	if (ld->ultim)
	{
		ld->ultim->next = nou;
	}
	else
	{
		ld->prim = nou;
	}
	ld->ultim = nou;
}

void adaugaLaInceputInLista(/*lista dubla de masini*/ListaDubla* ld, Masina masinaNoua) {
	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
	Nod* nou = malloc(sizeof(Nod));
	nou->info = masinaNoua; // shallow
	nou->next = ld->prim;
	nou->prev = NULL;
	if (ld->prim)
	{
		ld->prim->prev= nou;
	}
	else
	{
		ld->ultim = nou;
	}
	ld->prim = nou;
}

ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	if (f)
	{
		ListaDubla ld;
		ld.prim = ld.ultim = NULL;
		while (!feof(f))
		{
			adaugaMasinaInLista(&ld, citireMasinaDinFisier(f));
		}
		fclose(f);
		return ld;
	}
}

void dezalocareLDMasini(/*lista dubla de masini*/ListaDubla* ld) {
	//sunt dezalocate toate masinile si lista dublu inlantuita de elemente
	while (ld->prim && ld->prim->next)
	{
		free(ld->prim->info.numeSofer);
		free(ld->prim->info.model);
		ld->prim = ld->prim->next;
		free(ld->prim->prev);
	}
	if (ld->prim)
	{
		free(ld->prim->info.numeSofer);
		free(ld->prim->info.model);
		free(ld->prim);

	}
	ld->prim = ld->ultim = NULL;

}

float calculeazaPretMediu(/*lista de masini*/ListaDubla ld) {
	//calculeaza pretul mediu al masinilor din lista.
	float pret = 0;
	float nr = 0;
	Nod* p = ld.prim;
	while (p)
	{
		pret += p->info.pret;
		nr++;
		p = p->next;
	}
	return pret / nr;
}

void stergeMasinaDupaID(/*lista masini*/ListaDubla* ld, int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
	if (ld->prim &&  ld->prim->info.id == id )
	{
		free(ld->prim->info.model);
		free(ld->prim->info.numeSofer);
		ld->prim = ld->prim->next;
		if (ld->prim)
		{
			free(ld->prim->prev);
		}
		else
		{
			free(ld->ultim);
			ld->ultim = NULL;
		}
		return;
	}

	Nod* p = ld->prim;
	while (p && p->info.id !=id)
	{
		if (p->info.id == id)
		{

		}
		p = p->next;
	}
	if (p)
	{
		if (p->prev)
		{
			p->prev->next = p->next;
		}
		if (p->next)
		{
			p->next->prev = p->prev;
		}
		else
		{
			p->prev->next = NULL;
			ld->ultim = p->prev;
		}
		free(p->info.model);
		free(p->info.numeSofer);
		free(p);
		
	}
}

char* getNumeSoferMasinaScumpa(/*lista dublu inlantuita*/ListaDubla ld) {
	float max = -1;
	char masina[100];
	Nod* p = ld.prim;
	while (p)
	{
		if (max < p->info.pret)
		{
			max = p->info.pret;
			strcpy(masina, p->info.numeSofer);

		}
		
		p = p->next;
	}

	return masina;

}

int main() {

	ListaDubla lista = citireLDMasiniDinFisier("masini.txt");
	/*afisareListaMasini(lista);*/
	/*printf("nume: %s", getNumeSoferMasinaScumpa(lista));
	printf("pret: %5.2f", calculeazaPretMediu(lista));*/
	stergeMasinaDupaID(&lista, 10);
	afisareListaMasini(lista);

	


	return 0;
}