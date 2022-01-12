#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 50

typedef struct osoba* Person;
typedef struct osoba {
    char ime[MAX_NAME];
    char prezime [MAX_NAME];
    int godina;
    Person next;
}osoba;

int DodajNaPocetak(Person head);
Person Alociraj();
int Print(Person prvi);
int DodajNaKraj(Person head);
Person Trazi(Person head);
int Brisi(Person head);

//za 3. zadatak

int DodajIspred(Person odredjeni);
Person TraziPrethodnog(Person head);
int DodajIza(Person head);
int UpisUDatoteku(Person head);
int CitajIzDatoteke(Person head);
int SortirajPoPrezimenu(Person head);

int main()
{
    int br;
    Person head=Alociraj();
    Person odredjeni= Alociraj();


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

case 6: 
    odredjeni=Trazi(head);
    DodajIspred(odredjeni);
    break;

case 7: DodajIza(head);
        break;

case 8: UpisUDatoteku(head);
    break;

case 9: CitajIzDatoteke(head);
        break;

case 10: SortirajPoPrezimenu(head);
        break;

default: printf("Pogresan broj");
}


    return 0;
}


int DodajNaPocetak(Person head){
    Person New;
    New= Alociraj();
    printf("Unesite ime, prezime i godinu rodjenja");
    scanf(" %s %s %d", &New->ime, &New->prezime, &New->godina);
    New->next=head->next;
    head->next= New;

return 0;
}

Person Alociraj()
{
    Person NewP=NULL;
    NewP=(Person)malloc(sizeof(struct osoba));

    if(!NewP)
    {
        printf("Nije uspjelo!");
        return NULL;
    }

    strcpy(NewP->ime, " ");
    strcpy(NewP->prezime, " ");
    NewP->godina=0;
    NewP->next=NULL;


}

int Print(Person prvi)
{   
    while(prvi->next!=NULL)  
    {
        printf(" %c %c %d", prvi->ime, prvi->prezime, prvi->godina);
        prvi=prvi->next;
    }  
 printf(" %c %c %d", prvi->ime, prvi->prezime, prvi->godina);
 return 0;
}

int DodajNaKraj(Person head)
{
    Person New;
    New=Alociraj();

    while(head->next!=NULL)
    {
        head=head->next;
    }

  /*  head->next=New;
    New->next=NULL;*/

    New->next=head->next;
    head->next=New;

return 0;
}

Person Trazi(Person head)
{
    char prez[MAX_NAME];

    printf("Unesite prezime: ");
    scanf(" %s",prez);

    while(head->next!=NULL && strcmp(head->prezime,prez)!=0)
    {
        head=head->next;
    }
if(strcmp(head->prezime, prez)==0){
    printf("Pronadjeno");
    return head;
}
else printf("ne postoji");
}


Person TraziPrethodnog(Person head){
    char prez[MAX_NAME];

    printf("Unesite prezime: ");
    scanf(" %s",prez);

    while(head->next!=NULL && strcmp(head->next->next->prezime,prez)!=0)
    {
        head=head->next;
    }
if(strcmp(head->next->next->prezime, prez)==0){
    printf("Pronadjeno");
    return head;
}
else 
printf("ne postoji");


}


int Brisi(Person head)
{
    Person Izb=NULL;
    Izb=Trazi(head);

while(head->next!=Izb)
{
    head=head->next;
}

head->next=Izb->next;
free(Izb);

return 0;
}

int DodajIspred(Person odredjeni)
{
Person NewP=Alociraj();
NewP= TraziPrethodnog(odredjeni);
if(NewP==NULL) {printf("greska");}
else {
     printf("Unesite ime, prezime i godinu rodjenja: ");
    scanf(" %s %s %d", NewP->ime, NewP->prezime, &NewP->godina);
     NewP->next= odredjeni->next;
     odredjeni->next= NewP;   

}

return 0;
}

int DodajIza(Person head){
    Person NewOdredjeni;
    NewOdredjeni= Trazi(head);

    Person Novi=Alociraj();

    printf("Unesite podatke(ime, prezime, godina): ");
    scanf(" %s %s %d", Novi->ime, Novi->prezime, &Novi->godina);
    Novi->next=NewOdredjeni->next;
    NewOdredjeni->next=Novi;

}

int UpisUDatoteku(Person head)
{
    Person temp= head->next;
    FILE* fp=NULL;
    fp=fopen("Novadatoteka.txt", "w");
    if(!fp) 
    {
        printf("Greska pri otvaranju");
         return -1;
    }
    
    while(temp!=NULL){
    fprintf(fp, " %s %s %d", temp->ime, temp->prezime, &temp->godina);
    temp=temp->next;
    }


return 0;

}

int CitajIzDatoteke(Person head)
{
    Person temp=head->next;
    Person NewP=NULL;

    FILE* fp=NULL;
    fp=fopen("datoteka.txt", "r");

    if(!fp)
    {
         printf("Greska pri otvaranju!");
         return -1;
    }

    while(!feof(fp))
    {
        NewP=Alociraj();
        fscanf(fp, " %s %s %d", NewP->ime, NewP->prezime, &NewP->godina);
        NewP->next=temp->next;
        temp->next=NewP;
        temp=temp->next; //pomicemo se na sljedeci u listi
    }

}

int SortirajPoPrezimenu(Person head)
{
	Person temp = head;
	Person q = NULL;
	Person p = NULL;
	Person last = NULL;

	while (temp->next != last)
	{
		p = temp;
		q = p->next;

		while (q->next != last)
		{
			if (strcmp(q->prezime, q->next->prezime) > 0)
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
