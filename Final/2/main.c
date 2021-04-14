#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
typedef enum SizeUnion {
    OPERATION = 0,
    NUMBER = 1,
    VARIABLE = 2
} SizeUnion;

typedef struct VarInfo {
    char *Name;
    double *Value;
} VarInfo;

typedef union PolizBlock {
    VarInfo Variable;
    double Num;
    char Operation;
} PolizBlock;

typedef struct List {
    SizeUnion Sz;
    PolizBlock Data;
    struct List *Next;
    struct List *Prev;
} List;

typedef struct Database {
    double Num;
    char Name[7];
    struct Database *Child;
    struct Database *Parent;
} Database;

typedef struct Stack {
    double Value;
    struct Stack *Next;
} Stack;

int Input, Error, Counter;
Database *Db = NULL;
List *Poliz = NULL;

void FinalCheck(void);
void Expression(void);
void Term(void);
void Multiplier(char z);
void Number(char z);
void PushStack(Stack **head, double value);
double PopStack(Stack **head);
Database *BackDb(Database *gr);
List *BackList(List *gr);
Database *CreateRandomEdge(void);
Database *InEdge(Database *gr, const char _name[6]);
List *CreateRandomList(void);
void AddVariable(void);
void AddElem(void);
void DeleteAllPoints(Database **gr);
void DeleteAllList(List **gr);
double InputDouble(void);
void ErrorCheck(void);
double Calculate(void);
void Full(void);

int main(void) {
    int a=1;
    char start[2],*end;
    Error = 0;
    printf("--------------------------------------------------------\n");
    printf("Enter start line\n");
    FinalCheck();
    if (Error != 0) {
        ErrorCheck();
        while ((Input != '\n') && (Input != EOF))
            Input = getchar();
    }
    else {
        Full();
        while(a==1) {
            printf("1:Repeat with new values\nNot 1:Exit\n");
            fgets(start, 3, stdin);
            a = (int) strtol(start, &end, 10);
            if (a==1) {
                while ((Input != '\n') && (Input != EOF))
                    Input = getchar();
                Full();
            }
        }
    }
    DeleteAllList(&Poliz);
    DeleteAllPoints(&Db);
    return 0;
}
void PushStack(Stack **head, double value) {
    Stack *buf = malloc(sizeof(Stack));
    if (buf == NULL) {
        exit(255);
    }
    buf->Next = *head;
    buf->Value = value;
    *head = buf;
}

double PopStack(Stack **head) {
    Stack *buf;
    double value;
    if (*head == NULL)
        return 0;
    value = (*head)->Value;
    buf = *head;
    *head = (*head)->Next;
    free(buf);
    buf = NULL;
    return value;
}

Database *BackDb(Database *gr) {
    if (gr == NULL)
        return gr;
    while (gr->Parent)
        gr = gr->Parent;
    return gr;
}

List *BackList(List *gr) {
    if (gr == NULL)
        return gr;
    while (gr->Prev)
        gr = gr->Prev;
    return gr;
}

Database *CreateRandomEdge(void) {
    struct Database *newNode = malloc(sizeof(struct Database));
    if (newNode == NULL)
        exit(255);
    newNode->Num = 1;
    newNode->Child = NULL;
    newNode->Parent = NULL;
    return newNode;
}

Database *InEdge(Database *gr, const char _name[6]) {
    gr = BackDb(gr);
    if (gr == NULL)
        return 0;
    if (strcmp(gr->Name, _name) == 0)
        return gr;
    while (gr->Child) {
        gr = gr->Child;
        if (strcmp(gr->Name, _name) == 0) {
            return gr;
        }
    }
    return NULL;
}

List *CreateRandomList(void) {
    struct List *newNode = malloc(sizeof(struct List));
    if (newNode == NULL)
        exit(255);
    newNode->Next = NULL;
    newNode->Prev = NULL;
    return newNode;
}

void AddVariable(void) {
    if (Db == NULL)
        Db = CreateRandomEdge();
    else {
        Db->Child = CreateRandomEdge();
        Db->Child->Parent = Db;
        Db = Db->Child;
    }
}

void AddElem(void) {
    if (Poliz == NULL)
        Poliz = CreateRandomList();
    else {
        Poliz->Next = CreateRandomList();
        Poliz->Next->Prev = Poliz;
        Poliz = Poliz->Next;
    }
}

void DeleteAllPoints(Database **gr) {
    Database *temp;
    if (*gr != NULL) {
        while ((*gr)->Child != NULL) {
            temp = (*gr)->Child;
            free(*gr);
            *gr = NULL;
            *gr = temp;
        }
        free(*gr);
        *gr = NULL;
    }
}

void DeleteAllList(List **gr) {
    List *temp;
    if (*gr != NULL) {
        while ((*gr)->Next != NULL) {
            temp = (*gr)->Next;
            free(*gr);
            *gr = NULL;
            *gr = temp;
        }
        free(*gr);
        *gr = NULL;
    }
}

void FinalCheck(void) {
    Input = getchar();
    Expression();
    if ((Input != '\n') && (Input != EOF)) {
        if (Input >= '0' && Input <= '9' && Error == 0)
            Error = 1;
        else if (Input == ')' && Error == 0)
            Error = 6;
        else if (Error == 0)
            Error = 3;
    }
    Poliz = BackList(Poliz);
    Db = BackDb(Db);
}

void Expression(void) {
    Counter = 0;
    Term();
    while (Input == '+' || Input == '-' || Input == ' ') {
        if ((Input == '+') || (Input == '-')) {
            int buf = Input;
            Input = getchar();
            Counter = 0;
            Term();
            AddElem();
            if (buf == '+')
                Poliz->Data.Operation = '+';
            else
                Poliz->Data.Operation = '-';
            Poliz->Sz = OPERATION;
        } else if (Input == ' ')
        {
            Input = getchar();
        }
        if (Error != 0)
            break;
    }
}

void Term(void) {
    Counter = 0;
    Multiplier(1);
    while (Input == '*' || Input == ' ' || Input == '/') {
        if ((Input == '*') || (Input == '/'))
        {
            int buf = Input;
            Input = getchar();
            Counter = 0;
            Multiplier(1);
            AddElem();
            if (buf == '*')
                Poliz->Data.Operation = '*';
            else
                Poliz->Data.Operation = '/';
            Poliz->Sz = OPERATION;
        } else if (Input == ' ') {
            Input = getchar();
        }
        if (Error != 0)
            break;
    }
}

void Multiplier(char z) {
    while (Input == ' ') {
        Input = getchar();
    }
    if ((Input >= '0' && Input <= '9') || (Input == '.') || (Input >= 'a' && Input <= 'z') || (Input >= 'A' && Input <= 'Z')) {
        Number(z);
    } else if (Input == '(') {
        if (Counter > 0 && Error == 0) {
            Error = 2;
            while ((Input != '\n') && (Input != EOF))
                Input = getchar();
        } else {
            Input = getchar();
            Expression();
            if (Input == ')')
                Input = getchar();
            else {
                if (Error == 0)
                    Error = 5;
            }
        }
    } else if (Input == '-' && Counter < 2 && Error == 0) {
        Counter++;
        if (Counter == 2) {
            Error = 2;
        }
        if (Error != 2) {
            Input = getchar();
            Multiplier(-1);
        }
    } else if (((Input == '\n') || (Input == EOF)) && Error == 0)
        Error = 7;
    else if (Input == '+' || Input == '*' || Input == '/')
        Error = 2;
    else if (Error == 0)
        Error = 3;


}

void Number(char z) {
    double number = 0;
    int ncheck = 0, i = 0;
    if ((Input >= 'a' && Input <= 'z') || (Input >= 'A' && Input <= 'Z')) {
        if ((z < 0) && (Error == 0)) {
            Error = 4;
            return;
        }
        char _name[7] = {0, 0, 0, 0, 0, 0, 0};
        Database *ptr = Db;
        while ((Input >= 'a' && Input <= 'z') || (Input >= 'A' && Input <= 'Z')) {
            _name[i] = (char) Input;
            Input = getchar();
            i++;
            if (i > 6) {
                Error=3;
                return;
            }
        }
        if (InEdge(ptr, _name) == NULL) {
            AddVariable();
            ptr = Db;
            strcpy(Db->Name, _name);
            Db->Num = 0;
        }
        AddElem();
        Poliz->Sz = VARIABLE;
        Poliz->Data.Variable.Name = ptr->Name;
        Poliz->Data.Variable.Value = &ptr->Num;
    } else {
        while (Input >= '0' && Input <= '9') {
            number = number * 10 + Input - '0';
            Input = getchar();
            ncheck = 1;
        }
        if (Input == '.') {
            Input = getchar();
            double drob = 1;
            while (Input >= '0' && Input <= '9') {
                drob = drob / 10;
                number = number + (Input - '0') * drob;
                Input = getchar();
                ncheck = 1;
            }
            if (ncheck == 0)
                Error = 3;
        }
        AddElem();
        Poliz->Data.Num = number * z;
        Poliz->Sz = NUMBER;
    }
}

double InputDouble(void) {
    char minuscheck = 1, ncheck = 0;
    double output = 0;
    Input = getchar();
    if ((Input == '\n') || (Input == EOF)) {
        printf("Empty string, reset variable to default value 0\n");
        return 0;
    }
    while (Input == ' ')
        Input = getchar();
    if (Input == '-') {
        minuscheck = -1;
        Input = getchar();
    } else if (Input >= '0' && Input <= '9') {
        output = output * 10 + Input - '0';
        ncheck = 1;
        Input = getchar();
    }
    while (Input >= '0' && Input <= '9') {
        output = output * 10 + Input - '0';
        ncheck = 1;
        Input = getchar();
    }
    if (Input == '.') {
        Input = getchar();
        double drob = 1;
        while (Input >= '0' && Input <= '9') {
            drob = drob / 10;
            output = output + (Input - '0') * drob;
            Input = getchar();
            ncheck = 1;
        }
    }
    while (Input == ' ')
        Input = getchar();
    if ((ncheck == 0) || ((Input != '\n') && (Input != EOF))) {
        while ((Input != '\n') && (Input != EOF))
            Input = getchar();
        printf("Wrong input, return 0\n");
        return 0;
    }
    return output * minuscheck;
}

void ErrorCheck(void) {
    if (Error == 1)
        printf("Missing operator  \n");
    else if (Error == 2)
        printf("Missing operand  \n");
    else if (Error == 3)
        printf("Unexpected character \n");
    else if (Error == 4)
        printf("Banned binary operation \n");
    else if (Error == 5)
        printf("Missing ')' \n");
    else if (Error == 6)
        printf("Missing '(' \n");
    else if (Error == 7)
        printf("Sudden EOl or EOF \n");
}

double Calculate(void) {
    double op1, op2;
    List *ptr = Poliz;
    Stack *calc = NULL;
    while (ptr != NULL) {
        if (ptr->Sz == NUMBER)
            PushStack(&calc, ptr->Data.Num);
        if (ptr->Sz == VARIABLE)
            PushStack(&calc, *ptr->Data.Variable.Value);
        if (ptr->Sz == OPERATION) {
            op2 = PopStack(&calc);
            op1 = PopStack(&calc);
            switch (ptr->Data.Operation) {
                case '+':
                    op1 = op1 + op2;
                    break;
                case '-':
                    op1 = op1 - op2;
                    break;
                case '*':
                    op1 = op1 * op2;
                    break;
                case '/':
                    if (fabs(op2)<FLT_EPSILON)
                        op2 = 1;
                    op1 = op1 / op2;
                    break;
                default :
                    return 1;
            }
            PushStack(&calc, op1);
        }
        ptr = ptr->Next;
    }
    return PopStack(&calc);
}

void Full(void) {
    Database *ptr = Db;
    while (ptr != NULL) {
        printf("\nEnter value of %s variable\n", ptr->Name);
        ptr->Num = InputDouble();
        ptr = ptr->Child;
    }
    printf("\nResult: %f\n", Calculate());
}