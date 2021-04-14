#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

#define BUFSIZE 128
typedef enum MTcommand {
    AND = 0,
    OR = 1,
    WAIT = 2,
    OPERATION = 3
} MTcommand;

typedef enum OutFormat {
    APPEND = 0,
    WRITE = 1
} OutFormat;

typedef struct OutputFile {
    OutFormat Status;
    char *Name;
} OutputFile;

typedef struct SubTokens {
    int Status;
    char *Token;
    char **Name;
    char *InputFile;
    OutputFile *OutputFile;
    struct SubTokens *Next;
    struct SubTokens *Prev;
} SubTokens;

typedef struct MainTokens {
    MTcommand Factor;
    struct SubTokens *Sub;
    struct MainTokens *Next;
    struct MainTokens *Prev;
} MainTokens;

MainTokens *Poliz = NULL;
int Background = 0;

int SizeMas(char **Str);

char **MasStringCat(char **Str, char *Token);

MainTokens *CreateMain(void);

void BackMain(void);

void BackSub(void);

void AddMain(void);

int DeleteMain(void);

SubTokens *CreateSub(void);

SubTokens *DeleteOperations(SubTokens *Ptr);

SubTokens *DeleteSub(struct SubTokens *Ptr);

void DeleteMainAll(void);

void AddSub(void);

OutputFile *SetOutput(OutFormat format, OutputFile *pFile, char *src);

int Finalize(void);

int Execute(SubTokens *Input);

int Run(void);

char *ReadLine(void);

int Tokenizer(char *Str);

int main(void) {
    char *a;
    while (1) {
        signal(SIGINT, SIG_IGN);
        Background = 0;
        printf(">>");
        while (1) {
            a = ReadLine();
            if (strlen(a) == 0) {
                free(a);
                printf(">>");
                continue;
            }
            break;
        }
        if (strcmp(a, "exit") == 0) {
            free(a);
            break;
        }
        if (Tokenizer(a) != 0) {
            DeleteMainAll();
            free(a);
            a = NULL;
            continue;
        }
        free(a);
        a = NULL;
        if (DeleteMain() != 0) {
            DeleteMainAll();
            continue;
        }
        if (Finalize() != 0) {
            DeleteMainAll();
            continue;
        }
        Run();
        DeleteMainAll();
    }
    return 0;
}

int SizeMas(char **Str) {
    int Size = 0;
    while (*(Str) != NULL) {
        Str++;
        Size++;
    }
    return Size;
}

char **MasStringCat(char **Str, char *Token) {
    if (Str == NULL) {
        Str = malloc(sizeof(char *) * 2);
        if (Str == NULL)
            exit(255);
        Str[0] = malloc((strlen(Token) + 1) * sizeof(char));
        if (Str[0] == NULL)
            exit(255);
        Str[1] = NULL;
        strcpy(Str[0], Token);
        return Str;
    }
    int Length = SizeMas(Str);
    Str = realloc(Str, (Length + 2) * sizeof(char *));
    if (Str == NULL)
        exit(255);
    Str[Length] = malloc((strlen(Token) + 1) * sizeof(char));
    if (Str[Length] == NULL)
        exit(255);
    strcpy(Str[Length], Token);
    Str[Length + 1] = NULL;
    return Str;
}

MainTokens *CreateMain(void) {
    struct MainTokens *NewNode = malloc(sizeof(struct MainTokens));
    if (NewNode == NULL)
        exit(255);
    NewNode->Next = NULL;
    NewNode->Prev = NULL;
    NewNode->Sub = NULL;
    return NewNode;
}

void BackMain(void) {
    if (Poliz != NULL) {
        while (Poliz->Prev)
            Poliz = Poliz->Prev;
    }
}

void BackSub(void) {
    if (Poliz->Sub != NULL) {
        while (Poliz->Sub->Prev)
            Poliz->Sub = Poliz->Sub->Prev;
    }
}

void AddMain(void) {
    if (Poliz == NULL)
        Poliz = CreateMain();
    else {
        Poliz->Next = CreateMain();
        Poliz->Next->Prev = Poliz;
        Poliz = Poliz->Next;
    }
}

int DeleteMain(void) {
    if (Poliz == NULL)
        return 0;
    struct MainTokens *Ptr = Poliz;
    while (Ptr != NULL) {
        if (Ptr->Factor != OPERATION) {
            struct MainTokens *Temp = Ptr;
            if ((Ptr->Prev == NULL) || (Ptr->Next == NULL) || (Ptr->Next->Factor != OPERATION)) {
                perror("Logic error\n");
                return -1;
            }
            Ptr->Prev->Factor = Ptr->Factor;
            Ptr->Prev->Next = Ptr->Next;
            Ptr->Next->Prev = Ptr->Prev;
            Ptr = Ptr->Prev;
            free(Temp->Sub->Token);
            free(Temp->Sub);
            free(Temp);
            Temp = NULL;
        }
        Ptr = Ptr->Next;
    }
    return 0;
}

SubTokens *CreateSub(void) {
    struct SubTokens *NewNode = malloc(sizeof(struct SubTokens));
    if (NewNode == NULL)
        exit(255);
    NewNode->Next = NULL;
    NewNode->Prev = NULL;
    NewNode->Token = NULL;
    NewNode->Name = NULL;
    NewNode->InputFile = NULL;
    NewNode->OutputFile = NULL;
    NewNode->Status = 0;
    return NewNode;
}

SubTokens *DeleteOperations(SubTokens *Ptr) {
    SubTokens *temp = Ptr;
    if ((Ptr->Prev == NULL) || (Ptr->Next == NULL)) {
        perror("Orerations error");
        return NULL;
    }
    Ptr->Prev->Next = Ptr->Next;
    Ptr->Next->Prev = Ptr->Prev;
    Ptr = Ptr->Prev;
    free(temp->Token);
    free(temp);
    temp = NULL;
    return Ptr;
}

SubTokens *DeleteSub(SubTokens *Ptr) {
    SubTokens *temp = Ptr;
    if (Ptr->Prev != NULL)
        Ptr->Prev->Next = Ptr->Next;
    if (Ptr->Next != NULL)
        Ptr->Next->Prev = Ptr->Prev;
    if (Ptr->Prev != NULL)
        Ptr = Ptr->Prev;
    else if (Ptr->Next != NULL)
        Ptr = Ptr->Next;
    else Ptr = NULL;
    free(temp->Token);
    if (temp->OutputFile != NULL)
        free(temp->OutputFile->Name);
    free(temp->OutputFile);
    free(temp->InputFile);
    if (temp->Name != NULL) {
        for (int i = 0; i < SizeMas(temp->Name); i++)
            free(temp->Name[i]);
        free(temp->Name);
    }
    free(temp);
    temp = NULL;
    return Ptr;
}

void DeleteMainAll(void) {
    while (Poliz != NULL) {
        struct MainTokens *temp = Poliz;
        while (Poliz->Sub != NULL)
            Poliz->Sub = DeleteSub(Poliz->Sub);
        if (Poliz->Prev != NULL)
            Poliz->Prev->Next = Poliz->Next;
        if (Poliz->Next != NULL)
            Poliz->Next->Prev = Poliz->Prev;
        if (Poliz->Prev != NULL)
            Poliz = Poliz->Prev;
        else if (Poliz->Next != NULL)
            Poliz = Poliz->Next;
        else
            Poliz = NULL;
        free(temp);
        temp = NULL;
    }
}

void AddSub(void) {
    if (Poliz->Sub == NULL)
        Poliz->Sub = CreateSub();
    else {
        Poliz->Sub->Next = CreateSub();
        Poliz->Sub->Next->Prev = Poliz->Sub;
        Poliz->Sub = Poliz->Sub->Next;
    }
}

OutputFile *SetOutput(OutFormat format, OutputFile *pFile, char *src) {
    if (pFile == NULL) {
        pFile = malloc(sizeof(OutputFile));
        if (pFile == NULL)
            exit(255);
        pFile->Name = malloc((strlen(src) + 1) * sizeof(char));
        if (pFile->Name == NULL)
            exit(255);
        strcpy(pFile->Name, src);
        pFile->Status = format;
    } else {
        pFile->Name = realloc(pFile->Name, (strlen(src) + 1) * sizeof(char));
        if (pFile->Name == NULL)
            exit(255);
        strcpy(pFile->Name, src);
        pFile->Status = format;
    }
    return pFile;
}

int Finalize(void) {
    char Ignore[5] = {'>', '>', '<', '|', '\0'};
    OutFormat Flag;
    MainTokens *temp = Poliz;
    if (temp->Sub == NULL)
        return 0;
    while (temp != NULL) {
        char ShitFlag = 0;
        SubTokens *Ptr = temp->Sub;
        if (Ptr->Token[0] == '(')
            Ptr->Status = 1;
        if (strstr(Ignore, Ptr->Token) != NULL)
            return -1;
        Ptr->Name = MasStringCat(Ptr->Name, Ptr->Token);
        Ptr = Ptr->Next;
        while (Ptr != NULL) {
            if (strcmp(Ptr->Token, "<") == 0) {
                ShitFlag = 1;
                Ptr = DeleteOperations(Ptr);
                if (Ptr == NULL)
                    return -1;
                Ptr = Ptr->Next;
                if (strstr(Ignore, Ptr->Token) == NULL) {
                    Ptr->Prev->InputFile = malloc((strlen(Ptr->Token) + 1) * sizeof(char));
                    if (Ptr->Prev->InputFile == NULL)
                        exit(255);
                    strcpy(Ptr->Prev->InputFile, Ptr->Token);
                } else return -1;
                Ptr = DeleteSub(Ptr);
            } else if ((strcmp(Ptr->Token, ">>") == 0) || (strcmp(Ptr->Token, ">") == 0)) {
                ShitFlag = 1;
                if (strcmp(Ptr->Token, ">>") == 0)
                    Flag = APPEND;
                else
                    Flag = WRITE;
                Ptr = DeleteOperations(Ptr);
                if (Ptr == NULL)
                    return -1;
                Ptr = Ptr->Next;
                if (strstr(Ignore, Ptr->Token) == NULL) {
                    Ptr->Prev->OutputFile = SetOutput(Flag, Ptr->Prev->OutputFile, Ptr->Token);
                } else return -1;
                Ptr = DeleteSub(Ptr);
            } else if (strcmp(Ptr->Token, "|") == 0) {
                ShitFlag = 0;
                Ptr = DeleteOperations(Ptr);
                if (Ptr == NULL)
                    return -1;
                Ptr = Ptr->Next;
                if (Ptr->Token[0] == '(')
                    Ptr->Status = 1;
                if (strstr(Ignore, Ptr->Token) != NULL)
                    return -1;
                Ptr->Name = MasStringCat(Ptr->Name, Ptr->Token);
            } else if (strcmp(Ptr->Token, "&") == 0) {
                if ((Ptr->Next != NULL) || (temp->Next != NULL))
                    return -1;
                else Background = 1;
                Ptr = DeleteSub(Ptr);
            } else {
                if (ShitFlag != 0)
                    return -1;
                else if (Ptr->Prev != NULL) {
                    Ptr->Prev->Name = MasStringCat(Ptr->Prev->Name, Ptr->Token);
                    Ptr = DeleteSub(Ptr);
                }
            }
            Ptr = Ptr->Next;
        }
        temp = temp->Next;
    }
    return 0;
}

int Execute(SubTokens *Input) {
    if (Input->Status == 1) {
        Input->Token[strlen(Input->Token) - 1] = ' ';
        if (execlp("./Stak", "./Stak", Input->Token + 1, NULL) != 0) {
            return -1;
        }
        return 0;
    } else {
        if (execvp(Input->Name[0], Input->Name) != 0)
            return -1;
    }
    return 0;
}


int Run(void) {
    pid_t pid;
    int Status;
    int Safe, ChDirFlag = 0;
    int fd[2];
    struct MainTokens *temp = Poliz;
    while (temp != NULL) {
        struct SubTokens *Ptr = temp->Sub;
        pipe(fd);
        Safe = dup(0);
        while (Ptr != NULL) {
            pipe(fd);
            if (strcmp(Ptr->Name[0], "cd") == 0) {
                if ((Ptr->Name[2] == NULL) && (Ptr->Next == NULL) && (Ptr->OutputFile == NULL) &&
                    (Ptr->InputFile == NULL) && (Ptr->Name[1] != NULL)) {
                    Status = chdir(Ptr->Name[1]);
                    ChDirFlag = 1;
                    Ptr = Ptr->Next;
                } else {
                    Status = 1;
                    Ptr = Ptr->Next;
                }
            } else {
                pid = fork();
                if (pid == 0) {
                    signal(SIGINT, SIG_DFL);
                    if (Ptr->InputFile != NULL)
                        freopen(Ptr->InputFile, "r", stdin);
                    if (Ptr->OutputFile != NULL) {
                        if (Ptr->OutputFile->Status == APPEND)
                            freopen(Ptr->OutputFile->Name, "a", stdout);
                        else
                            freopen(Ptr->OutputFile->Name, "w", stdout);
                    }
                    if ((Ptr->Next != NULL) && (Ptr->OutputFile == NULL)) {
                        dup2(fd[1], 1);
                    }
                    close(fd[1]);
                    close(fd[0]);
                    if (Background == 1) {
                        if (fork() == 0) {
                            signal(SIGINT, SIG_IGN);
                            if (fork() == 0) {
                                Execute(Ptr);
                                exit(0);
                            } else
                                kill(getpid(), SIGKILL);
                        }
                    }
                    else if (Execute(Ptr) != 0) {
                        perror("Bad Arguments\n");
                        dup2(Safe, 0);
                        exit(1);
                    }

                    exit(0);
                }
                dup2(fd[0], 0);
                close(fd[1]);
                close(fd[0]);
                Ptr = Ptr->Next;
            }
        }
        if (ChDirFlag == 0) {
            while (wait(&Status) != -1)
                Status = WEXITSTATUS(Status);
        }
        ChDirFlag = 0;
        dup2(Safe, 0);
        if (((temp->Factor == AND) && (Status == 0)) || ((temp->Factor == OR) && (Status != 0)) ||
            ((temp->Factor == WAIT)))
            temp = temp->Next;
        else return 0;
    }
    return 0;
}

char *ReadLine(void) {
    int Bufsize = BUFSIZE;
    int Position = 0;
    char *Buffer = NULL;
    int c;
    Buffer = malloc(sizeof(char) * Bufsize);
    if (Buffer == NULL)
        exit(255);
    while (1) {
        c = fgetc(stdin);
        if (c == '\0' || c == '\n' || c == '\t') {
            Buffer[Position] = '\0';
            return Buffer;
        }
        else if ((Position!=0) || c != ' ') {
            Buffer[Position] = c;
            Position++;
        }
        if (Position >= Bufsize) {
            Bufsize += BUFSIZE;
            Buffer = realloc(Buffer, Bufsize * sizeof(char));
            if (Buffer == NULL)
                exit(255);
        }
    }
}

int Tokenizer(char *Str) {
    int Bufsize = BUFSIZE;
    int Position = 0;
    char *Buffer = NULL;
    int CommaCounter = 0;
    AddMain();
    Buffer = malloc(sizeof(char) * Bufsize);
    if (Buffer == NULL)
        exit(255);
    for (int i = 0; i < strlen(Str) + 1; i++) {
        if (((Str[i] != ' ') || CommaCounter != 0) && (Str[i] != '\n') && (Str[i] != '\t') && (Str[i] != '\0')) {
            Buffer[Position] = Str[i];
            Position++;
        }
        if (Position >= Bufsize) {
            Bufsize += BUFSIZE;
            char *Real = realloc(Buffer, Bufsize * sizeof(char));
            if (Real == NULL)
                exit(255);
            Buffer = Real;
        }
        if (Str[i] == '(')
            CommaCounter++;
        if (Str[i] == ')')
            CommaCounter--;
        if ((((Str[i] == ' ') && (strlen(Buffer) != 0)) || (Str[i] == '\n') || (Str[i] == '\t') || (Str[i] == '\0')) &&
            (CommaCounter == 0)) {
            Buffer[Position] = 0;
            Position++;
            if (strcmp(Buffer, "||") == 0 || strcmp(Buffer, "&&") == 0 || strcmp(Buffer, ";") == 0) {
                BackSub();
                AddMain();
                AddSub();
                Poliz->Sub->Token = malloc((strlen(Buffer) + 1) * sizeof(char));
                if (Poliz->Sub->Token == NULL)
                    exit(255);
                strcpy(Poliz->Sub->Token, Buffer);
                if (strcmp(Buffer, "||") == 0)
                    Poliz->Factor = OR;
                else if (strcmp(Buffer, "&&") == 0)
                    Poliz->Factor = AND;
                else
                    Poliz->Factor = WAIT;
                Position = 0;
                memset(Buffer, 0, strlen(Buffer));
                AddMain();
            } else if (strlen(Buffer) > 0) {
                AddSub();
                Poliz->Sub->Token = malloc((strlen(Buffer) + 1) * sizeof(char));
                if (Poliz->Sub->Token == NULL)
                    exit(255);
                strcpy(Poliz->Sub->Token, Buffer);
                Poliz->Factor = OPERATION;
                Position = 0;
                memset(Buffer, 0, strlen(Buffer));
            }
        }
    }
    if (strlen(Buffer) != 0) {
        free(Buffer);
        return 1;
    }
    BackSub();
    BackMain();
    free(Buffer);
    return 0;
}
