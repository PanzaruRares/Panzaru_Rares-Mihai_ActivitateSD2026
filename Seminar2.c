#include<stdio.h>
#include<malloc.h>

struct Film {
	int id;
	int durata;
	char* denumire;
	float buget;
	char varstaMinima;
};
struct Film initializare(int _id, int _durata, char* _denumire, float _buget, char _varstaMinima) {
	struct Film s;
	s.id = 1;
	s.id = _id;
	s.durata = _durata;
	s.denumire = malloc((strlen(_denumire) + 1) * sizeof(char));
	strcpy(s.denumire, _denumire);
	s.buget = _buget;
	s.varstaMinima = _varstaMinima;
	return s;
}

struct Film copyFilm(struct Film s)
{
	return initializare(s.id, s.durata, s.denumire, s.buget, s.varstaMinima);
}

void afisare(struct Film s) {
	printf("-------------------------------\n");
	printf("ID: %d", s.id);
	printf("Nume: %s", s.denumire);
	printf("\ndurata: %d", s.durata);
	printf("\nbuget: %f", s.buget);
	printf("\nVarsta minima: %d", s.varstaMinima);
}


struct Film* copiazaPrimeleNElemente(struct Film* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Film *vectorNou=malloc(nrElementeCopiate * sizeof(struct Film) );
	for (int i = 0; i < nrElementeCopiate; ++i)
	{
		vectorNou[i] = copyFilm(vector[i]);
	}


	return vectorNou;
}

void dezalocare(struct Film** vector, int* nrElemente) {
	//dezalocam elementele din vector si vectorul
	for (int i = 0; i < *nrElemente; i++)
	{
		free((*(vector)[i]).denumire);
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void copiazaAnumiteElemente(struct Film* vector, char nrElemente, float bugetMax, struct Film** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
	*dimensiune = 0;
	
	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].buget < bugetMax)
		{
			*(dimensiune)++;
		}
	}
	*dimensiune = 0;
	(*vectorNou) = malloc((*dimensiune) * sizeof(struct Film));
	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].buget < bugetMax)
		{
			(*vectorNou)[i] = copyFilm(vector[i]);
			*(dimensiune)++;
		}
	}


}

struct Film getPrimulElementConditionat(struct Film* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Film s;
	s.id = -1;
	for (int i = 0; i < nrElemente; i++)
	{
		if (!strcmp(*vector[i].denumire, *conditie))
		{
			return vector[i];
		}
	}
	return s;
}

void afisareFilme(struct Film* vector, int nrElemente)
{
	for (int i = 0; i < nrElemente; i++)
	{
		afisare(vector[i]);
	}
}
	


int main() {

	struct Film f = initializare(1, 120, "Dune", 5000.6, 12);
	afisare(f);
	struct Film* vector;
	int nrFilme = 3;
	vector = malloc(nrFilme * sizeof(struct Film));
	vector[0] = f;
	vector[1] = initializare(2, 150, "Avatar", 600, 9);
	vector[2] = initializare(3, 189, "Star Wars", 500, 10);
	printf("\n");
	afisareFilme(vector, nrFilme);
	int nrFilmeCopiate = 2;
	struct Film* vectorNou;
	vectorNou = copiazaPrimeleNElemente(vector, nrFilme, nrFilmeCopiate);
	afisareFilme(vectorNou,nrFilmeCopiate);
	dezalocare(&vectorNou, &nrFilmeCopiate);
	struct Film* vectorIeftin;
	int dimIeftin;
	float prag = 550;
	copiazaAnumiteElemente(vector, 50, prag, &vectorIeftin, &dimIeftin);
	afisareFilme(vectorIeftin,dimIeftin);
	afisare(getPrimulElementConditionat(vector, nrFilme, "Dune"));
	dezalocare(&vector, &nrFilme);
	return 0;
}