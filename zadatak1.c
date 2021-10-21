#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_SIZE 128
#define MAX_LINE 1024



typedef struct _student {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
}student;

//prototip
int procitajDat(char* nazivDat);
student* AlocirajIProcitaj(int brStud, char* nazivDat);

int main() {
	int brRedaka = 0;
	int brojac = 0;
	char nazivDat[] = "studenti.txt";
	student* a = NULL;

	brRedaka = procitajDat(nazivDat);

	if (brRedaka <= 0) {
		printf("Prazno!");

	}

	a = AlocirajIProcitaj(brRedaka, nazivDat);

	if (a == NULL) {
		printf("Neuspjesno alociranje");
		free(a);
	}

	for (brojac = 0; brojac < brRedaka; brojac++) {
		printf("Ime: %s  \t  Prezime:%s   \t   Abs:%lf   \t   Rel:%lf%%\n", a[brojac].ime, a[brojac].prezime, a[brojac].bodovi, (a[brojac].bodovi) / 2);
	}

	free(a);

	return 0;

}

int procitajDat(char* nazivDat) {
	int brojac = 0;
	char buffer[MAX_LINE] = { 0 };
	FILE* datoteka = NULL;
	datoteka = fopen(nazivDat, "r");
	if (!datoteka) {
		printf("Neuspjesno otvaranje dat");
			return -1; }
	while (!feof(datoteka)) {
		fgets(buffer, MAX_LINE, datoteka);
		brojac++;
		}
	fclose(datoteka);

	return brojac;
	}

student* AlocirajIProcitaj(int brStud, char* nazivDat) {
	int brojac = 0;
	FILE* datoteka = NULL;
	student* Studenti = NULL;

	Studenti = (student*)malloc(brStud * sizeof(student));

	datoteka = fopen(nazivDat, "r");
	if (!datoteka) {
		printf("Neuspjesno alociranje");
		free(Studenti);
		return NULL;
	}
	while (!feof(datoteka)) {
		fscnaf(datoteka, " %s %s %lf", Studenti[brojac].ime, Studenti[brojac].prezime, Studenti[brojac].bodovi);
		brojac++;
	}
	fclose(datoteka);

	return Studenti;

}