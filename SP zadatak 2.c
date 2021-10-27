#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CRT_SECUR_NO_WARNINGS
#define MAX_SIZE 50

struct _person;
typedef struct _person* position;

typedef struct _person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int year;
	position next;

}person;

int prepandlist(position head, char* name, char* surname, int year);
int printlist(position first);
position createperson(char* name, char* surname, int year);
int insertafter(position pos, position newperson);
position findlast(position head);
int appendlist(position head, char* name, char* surname, int year); 
int findbysurname(position first, char* surname);


int main() {
	//person osoba = { .name = {0}, .surname = {0}, .next = NULL, .year = 0 };
	person* osoba = (person*)malloc(sizeof(person));

	

	return 0;
}

int prepandlist(position head, char* name, char* surname, int year) {

	position newperson = NULL;
	newperson = (position)malloc(sizeof(person));
	if (!newperson) {
		printf("Greska u alociranju memorije");
	}

	strcpy_s(newperson->name,10, name);
	strcpy_s(newperson->surname, 10, surname);
	newperson->year = year;
	newperson->next = NULL;

}

int printlist(position first) {
	position temp = first; //argument treba ostat netaknut
	while (temp) {
	
		printf("Name: %s, surname: %s, year: %d", temp->name, temp->surname, temp->year);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

position createperson(char* name, char* surname, int year) {
	position newperson = NULL;

	if (!newperson)
	{
		perror("Cant alocate memory");
		return -1;
	}

	strcpy_s(newperson->name,10, name);
	strcpy_s(newperson->surname,10, surname);
	newperson->year = year;
	newperson->next = NULL;

}

int insertafter(position pos, position newperson) {
	newperson->next = pos->next;
	pos->next = newperson;

	return EXIT_SUCCESS;
}

position findlast(position head) {
	position temp = head;

	while (temp->next) {
		temp = temp->next;
	}

	return temp;
}


int appendlist(position head, char* name, char* surname, int year) {
	position newperson = NULL;
	position last = NULL;

	newperson = createperson(name, surname, year);

	if (!newperson) {
	
		return -1;
	}

	last = findlast(head);
	inserafter(last, newperson);

	return EXIT_SUCCESS;
}

int findbysurname(position first, char* surname) {
	position temp = first;

	while (temp) {
	
		if (strcmp(temp->surname, surname)) {
			return temp;
		}

	}
	return EXIT_SUCCESS;
}

int deleteperson(position head, position per)
{
	position P = head;

	while (P != NULL && (P->next) != per) {
		P = P->next;
	}

	if (P == NULL)
		return -1;
	else
	{
		P->next = P->next->next;
		free(per);
	}

	return 0;
}

