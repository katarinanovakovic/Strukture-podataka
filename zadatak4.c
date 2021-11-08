#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct polinom* pozicija;
typedef struct polinom{
    int koef;
    int eksp;
    pozicija next;

}Polinom;

int umetniElementSortirano(Polinom* head, int koef, int eksp);
int procitajRed(Polinom *head, char* red);
int procitajDatoteku(Polinom *head1, Polinom *head2);
int ispis(Polinom * head);
int zbrojiPolinome( Polinom* head1, Polinom * head2, Polinom * headZbr);
int pomnoziPolinome(Polinom * head1, Polinom * head2, Polinom * headUmn);



int main(){
    Polinom *head1=(Polinom*)malloc(sizeof(Polinom));
     Polinom *head2=(Polinom*)malloc(sizeof(Polinom));
    Polinom *headZbr=(Polinom*)malloc(sizeof(Polinom));
    Polinom *headUmn=(Polinom*)malloc(sizeof(Polinom));

    procitajDatoteku(head1, head2);
    printf("Prvi polinom je:\n");
    ispis(head1);
    printf("DRugi polinom:\n ");
    ispis(head2);

    zbrojiPolinome(head1, head2, headZbr);
    printf("Zbroj polinoma je: \n");
    ispis(headZbr);

    pomnoziPolinome(head1, head2, headUmn);
    printf("Umnozak polinoma je. \n");
    ispis(headUmn);





    return 0;
}

int procitajDatoteku(Polinom *head1, Polinom *head2){
    FILE* datoteka;
    
    int n;
    char linija[MAX];

    datoteka=fopen("polinomi.txt", "r");
    if(datoteka==NULL){
        printf("Neuspjesno otvaranje datoteke");
    }


    fgets(linija, MAX, datoteka);
    procitajRed(head1,linija);
    fgets(linija, MAX, datoteka);
    procitajRed(head2, linija);



}

int procitajRed(Polinom *head, char* red){
    int koeficijent = 0;
    int eksponent = 0;
    char * pRed = red;

    do {
        int n = 0;

        sscanf(pRed, " %d %d%n", &koeficijent, &eksponent, &n);
        pRed += n;

        umetniElementSortirano(head, koeficijent, eksponent);
    } while (strlen(pRed)>1);
    
    return 0;

}
int umetniElementSortirano(Polinom *head, int koef, int eksp)
{
    Polinom* P=head;
    Polinom* novi; 


    while(P->next!=NULL && (P->next->eksp) > eksp)
        P=P->next;

    if (P->next != NULL && P->next->eksp == eksp) {
            P->next->koef+=koef;
    }
    else {
         
        novi=(Polinom *)malloc(sizeof(Polinom));

        if (!novi)
            return -1;

        novi->next=P->next;
        P->next=novi;

        novi->koef=koef;
        novi->eksp=eksp;
    }

    return 0;
}

int ispis(Polinom * head)
{
    Polinom * P = head->next;

    while(P!=NULL) {
        printf("%dx^%d", P->koef, P->eksp);
        if (P->next != NULL)
        
        P=P->next;
    }

	return 0;
}

int zbrojiPolinome( Polinom* head1, Polinom * head2, Polinom * headZbr)
{
    Polinom * Phead1 = head1->next;
    Polinom * Phead2 = head2->next;

    while(Phead1 != NULL) {
        umetniElementSortirano(headZbr, Phead1->koef, Phead1->eksp);
        Phead1 = Phead1->next;
    }

    while(Phead2 != NULL) {
        umetniElementSortirano(headZbr, Phead2->koef, Phead2->eksp);
        Phead2 = Phead2->next;
    }

    return 0;
}

int pomnoziPolinome(Polinom * head1, Polinom * head2, Polinom * headUmn)
{
     Polinom *Phead1 = head1->next;
     Polinom *Phead2 = head2->next;
     
     while(Phead1 != NULL) {
         Phead2=head2->next;
         while(Phead2 != NULL) {
             umetniElementSortirano(headUmn, Phead1->koef*Phead2->koef, Phead1->eksp+Phead2->eksp);
             Phead2=Phead2->next;
         }
         Phead1=Phead1->next;
     }

     return EXIT_SUCCESS;}