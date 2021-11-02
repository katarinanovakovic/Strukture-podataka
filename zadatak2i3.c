#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
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
position findbysurname(position first, char* surname);
position findbefore(position first);
int deleteperson(position head, position per);
int save(position head, char * filename);
int read(position head, char* buffer);
int sortbysurname(position head);


int main() {


	person Head = {.name = {0}, .surname = {0}, .year = 0, .next = NULL};
    position pHead = &Head;
    person Ana, Marko;
    position pAna= &Ana;
	position pMarko = &Marko;
    FILE *fp = NULL;

    pAna = createperson("Ana", "Anic", 1999);
    pMarko = createperson("Marko", "Markic", 1998);
	

    insertafter(pAna, pMarko);
    printlist(pHead); 
    prepandlist(pHead, "Ante", "Antic", 1997);
    appendlist(pHead, "Mara", "Maric", 1996);
    printf("\n\nIspis liste nakon unosa nove osobe na pocetak i na kraj liste:");
    printlist(pHead);
    save(pHead, fp);
    sortbysurname(pHead);

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
return EXIT_SUCCESS;
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
		//return -1;
	}

	strcpy_s(newperson->name,10, name);
	strcpy_s(newperson->surname,10, surname);
	newperson->year = year;
	newperson->next = NULL;

return newperson;
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
	insertafter(last, newperson);

	return EXIT_SUCCESS;
}

position findbysurname(position first, char* surname) {
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

int insertfront(position  head, position element)
{
    position P = head;
    position newElement = (position)malloc(sizeof(position));

    while (P != NULL && P->next != element)
        P=P->next;

    if (P == NULL) {
        free(newElement);
        return -1;
    }

    insertafter(P, createperson("Ana", "Anic", 12));

    return 0;
}

int save(position head, char* filename)
{
    position P = head->next;
    FILE * fp = NULL;
    fp = fopen(filename, "w");

    if (fp==NULL)
        return -1;

    while (P!=NULL) {
        fprintf(fp, "Ime: %s, Prezime: %s, Godina rodenja: %d\n", P->name, P->surname, P->year);
        P=P->next;
    }

    fclose(fp);

    return 0;
}

int read(position head, char* buffer) {
	FILE* fp = NULL;
	fp = fopen("Person.txt", "r");
	//char buffer[MAX_SIZE]={0};
    char *name={0};
    char *surname={0};
    int year=0;
    int i=0;
    int n=0;
	if (!fp) {
		printf("Greska pri alociranju.\n");
		return -1;
	}

	while (!feof(fp)) {
		fscanf(fp, " %s %s %d\n", name, surname, &year);
		appendlist(head, name, surname, year);
	}

    for(i=0; i<n-1; i++){
        fgets(buffer, MAX_SIZE, fp);
        printf("%s", buffer);
    }
	fclose(fp);
	return EXIT_SUCCESS;
}

int sortbysurname(position head)
{
	position temp = head;
	position q = NULL;
	position p = NULL;
	position last = NULL;

	while (temp->next != last)
	{
		p = temp;
		q = p->next;

		while (q->next != last)
		{
			if (strcmp(q->surname, q->next->surname) > 0)
			{
				p->next = q->next;
				q->next = q->next->next;
				p->next->next = q;
				q = p->next;
			}
			p = q;
			q = q->next;
		}
		last = q;
	}
	return EXIT_SUCCESS;
}