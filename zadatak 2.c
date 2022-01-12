#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 50

typedef struct osoba* Person;
typedef struct osoba {
    char ime[MAX_NAME];
    char prezime[MAX_NAME];
    int godina;
    Person next;
};

int DodajNaPocetak(Person head);
Person Alociraj();
int Print(Person prvi);
int DodajNaKraj(Person head);
Person Trazi(Person head);
int Brisi(Person head);

int main()
{
    int br;
    Person head = Alociraj();


    printf("Unesite br ");
    scanf("%d", &br);

    switch (br)
    {
    case 1: DodajNaPocetak(head);
        break;

    case 2: Print(head->next);
        break;

    case 3: DodajNaKraj(head);
        break;

    case 4: Trazi(head);
        break;

    case 5: Brisi(head);
        break;

    default: printf("Falila si!");
    }


    return 0;
}


int DodajNaPocetak(Person head) {
    Person New;
    New = Alociraj();
    printf("Unesite ime prez i god ");
    scanf(" %s %s %d", &New->ime, &New->prezime, &New->godina);
    New->next = head->next;
    head->next = New;

    Print(head->next);

    return 0;
}

Person Alociraj()
{
    Person NewP = NULL;
    NewP = (Person)malloc(sizeof(struct osoba));

    if (!NewP)
    {
        printf("Nije uspjelo!");
        return NULL;
    }

    strcpy(NewP->ime, " ");
    strcpy(NewP->prezime, " ");
    NewP->godina = 0;
    NewP->next = NULL;


}

int Print(Person prvi)
{
    while (prvi->next != NULL)
    {
        printf(" %s %s %d", prvi->ime, prvi->prezime, prvi->godina);
        prvi = prvi->next;
    }
    printf(" %s %s  %d", prvi->ime, prvi->prezime, prvi->godina);
    return 0;
}

int DodajNaKraj(Person head)
{
    Person New;
    New = Alociraj();

    while (head->next != NULL)
    {
        head = head->next;
    }

    /*  head->next=New;
      New->next=NULL;*/

    printf("Unesite ime prez i god ");
    scanf(" %s %s %d", &New->ime, &New->prezime, &New->godina);
    New->next = head->next;
    head->next = New;

    return 0;
}

Person Trazi(Person head)
{
    char prez[MAX_NAME];

    printf("Unesite prezime: ");
    scanf(" %s", prez);

    while (head->next != NULL && strcmp(head->prezime, prez) != 0)
    {
        head = head->next;
    }
    if (strcmp(head->prezime, prez) == 0) {
        printf("Pronadjeno");
        return head;
    }
    else
        printf("ne postoji");


}

int Brisi(Person head)
{
    Person Izb = NULL;
    Izb = Trazi(head);

    while (head->next != Izb)
    {
        head = head->next;
    }

    head->next = Izb->next;
    free(Izb);

    return 0;
}
