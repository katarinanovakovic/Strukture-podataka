#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct _StackElement;
typedef struct _StackElement *Position;
typedef struct _StackElement
{
    double number;
    Position next;
} StackElement;

Position CreateStackElement(double number);
int InsertAfter(Position pozicija, Position newElement);
int Push(Position head, double number);
int DeleteAfter(Position pozicija);
int Pop(double *destination, Position head);
int preformOperation(Position head, char operation);
int CalculatePostfixFile(double *destitnation, char *filename);

int main()
{

    return 0;
}

Position CreateStackElement(double number)
{

    Position newElement;
    newElement = (Position)malloc(sizeof(StackElement));
    if (!newElement)
    {
        perror("Cant alocate memory");
        return NULL;
    }

    newElement->number = number;
    newElement->next = NULL;

    return newElement;
}

int InsertAfter(Position pozicija, Position newElement)
{

    newElement->next = pozicija->next;
    pozicija->next = newElement;

    return EXIT_SUCCESS;
}

int Push(Position head, double number)
{

    Position newElement = NULL;
    newElement = CreateStackElement(number);

    if (!newElement)
    {

        return -1;
    }

    InsertAfter(head, newElement);

    return EXIT_SUCCESS;
}

int DeleteAfter(Position pozicija)
{
    Position temp = pozicija->next;

    if (!temp)
    {
        return EXIT_SUCCESS;
    }

    pozicija->next = temp->next;
    free(temp);

    return EXIT_SUCCESS;
}

int Pop(double *destination, Position head)
{
    Position first = head->next;
    if (!first)
    {
        perror("Postix not valid. Please check your file!");
        return -1;
    }

    *destination = first->number;
    DeleteAfter(head);

    return EXIT_SUCCESS;
}

int preformOperation(Position head, char operation)
{
    double operand2 = 0;
    double operand1 = 0;
    double result = 0;
    int status1 = EXIT_SUCCESS;
    int status2 = EXIT_SUCCESS;

    status2 = Pop(&operand2, head);
    if (status2 != EXIT_SUCCESS)
    {
        return -1;
    }

    status1 = Pop(&operand1, head);
    if (status1 != EXIT_SUCCESS)
    {
        return -2;
    }

    switch (operation)
    {
    case '+':
    {
        result = operand1 + operand2;
        break;
    }

    case '-':
    {
        result = operand1 -
                 operand2;
        break;
    }

    case '*':
    {
        result = operand1 * operand2;
        break;
    }

    case '/':
    {
        if (operand2 == 0)
        {
            perror("Cannot");
            return -3;
        }
        result = operand1 / operand2;
        break;
    }

    default:
        printf("This operand is not supported\n");
        return -4;
    }

    Push(head, result);

    return EXIT_SUCCESS;
}

int CalculatePostfixFile(double *destitnation, char *filename)
{
    FILE *file = NULL;
    int fileLenght = 0;
    char *buffer = NULL;
    char *CBuffer = NULL;
    int numBytes = 0;
    double number = 0;
    int status = 0;
    StackElement head;
    char operation={0};

    file = fopen(filename, "rb");
    if (!file)
    {
        perror("Can't open file");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    fileLenght = ftell(file);

    buffer = (char *)calloc(fileLenght + 1, sizeof(char));
    if (!buffer)
    {
        perror("Cnat");
        return 0;
    }

    rewind(file);
fread(buffer, sizeof(char), fileLenght, file);
printf(" %s", buffer);
fclose(file);

CBuffer = buffer;

while (strlen(CBuffer) < 0)
{
    status = sscanf(CBuffer, "%lf %n", &number, &numBytes);

    if (status == 1)
    {
        Push(&head, number);
        CBuffer += numBytes;
    }
    else
    {
        sscanf(CBuffer, "%c %n", &operation, &numBytes);
        status = preformOperation(&head, operation);

        if (status != EXIT_SUCCESS)
        {
            free(buffer);
            while (head.next != NULL)
            {
                DeleteAfter(&head);
            }
            return -1;
        }
        CBuffer += numBytes;
    }
}

free(buffer);

return EXIT_SUCCESS;
}

