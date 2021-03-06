#include "bytecode.h"
#include <string.h>
#include <stdbool.h>

int getVariableId(char *variableName)
{
    for (int i = 0; i < 100; i++)
    {
        if (strlen(variableMap[i]) == 0 || strcmp(variableMap[i], variableName) == 0)
        {
            strcpy(variableMap[i], variableName);
            return i + 1;
        }
    }

    return -1;
}

void inicializarBytecodeFile()
{
    strcpy(bytecodeFileContent, ".class public java_class\n.super java/lang/Object\n\n.method public <init>()V\naload_0\ninvokenonvirtual java/lang/Object/<init>()V\nreturn\n.end method\n\n.method public static main([Ljava/lang/String;)V\n.limit locals 100\n.limit stack 100\n.line 1\n");

    strcat(bytecodeFileContent, "\nnew java/util/Scanner\ndup\ngetstatic java/lang/System/in Ljava/io/InputStream;\ninvokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V");

    for (int i = 0; i < 100; i++)
    {
        strcpy(variableMap[i], "");
        variableTypes[i] = ' ';
    }

    char intStr[12];
    int scannerId = getVariableId("scanner");
    sprintf(intStr, "%i", scannerId);
    strcat(bytecodeFileContent, "\nastore_");
    strcat(bytecodeFileContent, intStr);

    labelCount = 1;
    strcpy(lastIfCmp, " ");

    mark1.start = 0;
    mark1.end = 0;
    mark2.start = 0;
    mark2.end = 0;
}

void finalizarBytecodeFile()
{
    strcat(bytecodeFileContent, "\n.end method");

    FILE *bytecodeFile = fopen("java_bytecode.j", "w");

    fputs(bytecodeFileContent, bytecodeFile);

    fclose(bytecodeFile);
}

void atribuiValorIntParaVariavel(int valorInt, char *nomeVariavel)
{
    char intStr[12];

    strcat(bytecodeFileContent, "\nbipush ");
    sprintf(intStr, "%i", valorInt);
    strcat(bytecodeFileContent, intStr);

    strcat(bytecodeFileContent, "\nistore ");
    int idVariavel = getVariableId(nomeVariavel);
    sprintf(intStr, "%i", idVariavel);
    strcat(bytecodeFileContent, intStr);
}

void printaInt(int valorInt)
{
    char intStr[12];

    strcat(bytecodeFileContent, "\ngetstatic java/lang/System/out Ljava/io/PrintStream;");

    strcat(bytecodeFileContent, "\nbipush ");
    sprintf(intStr, "%i", valorInt);
    strcat(bytecodeFileContent, intStr);

    strcat(bytecodeFileContent, "\ninvokevirtual java/io/PrintStream/println(I)V");
}

void printaVariavel(char *nomeVariavel)
{
    char intStr[12];

    strcat(bytecodeFileContent, "\ngetstatic java/lang/System/out Ljava/io/PrintStream;");

    strcat(bytecodeFileContent, "\niload ");
    int idVariavel = getVariableId(nomeVariavel);
    sprintf(intStr, "%i", idVariavel);
    strcat(bytecodeFileContent, intStr);

    strcat(bytecodeFileContent, "\ninvokevirtual java/io/PrintStream/println(I)V");
}

void bytecodeReturn()
{
    strcat(bytecodeFileContent, "\nreturn");
}

void pushInt(int intValue)
{
    char intStr[12];
    strcat(bytecodeFileContent, "\nbipush ");
    sprintf(intStr, "%i", intValue);
    strcat(bytecodeFileContent, intStr);
}

void pushFloat(float floatValue)
{
    char floatStr[12];
    strcat(bytecodeFileContent, "\nldc ");
    sprintf(floatStr, "%f", floatValue);
    strcat(bytecodeFileContent, floatStr);
}

void pushChar(char charValue)
{
    char stringValue[4];
    stringValue[0] = '\"';
    stringValue[1] = charValue;
    stringValue[2] = '\"';
    stringValue[3] = '\0';

    strcat(bytecodeFileContent, "\nldc ");
    strcat(bytecodeFileContent, stringValue);
}

void pushBool(bool boolValue)
{
    char boolStr[12];
    strcat(bytecodeFileContent, "\nbipush ");
    sprintf(boolStr, "%i", boolValue);
    strcat(bytecodeFileContent, boolStr);
}

void saveTypeToVariables(char variableType, lista_t *inics)
{
    for (size_t i = 0; i < lista_tamanho(inics, NULL); i++)
    {
        /* Obtencao do proximo identificador da lista. */
        char *variableName;
        lista_buscar(inics, i, &variableName);
        int variableId = getVariableId(variableName);
        variableTypes[variableId] = variableType;
    }
}

char getVariableType(int variableId)
{
    if (variableTypes[variableId] == ' ')
    {
        return lastUsedType;
    }
    else
    {
        return variableTypes[variableId];
    }
}

void storeVariable(char *variableName)
{
    int variableId = getVariableId(variableName);
    char variableType = getVariableType(variableId);

    switch (variableType)
    {
    case 'C':
        strcat(bytecodeFileContent, "\nastore ");
        break;

    case 'F':
        strcat(bytecodeFileContent, "\nfstore ");
        break;

    default:
        strcat(bytecodeFileContent, "\nistore ");
        break;
    }

    char intStr[12];
    sprintf(intStr, "%i", variableId);
    strcat(bytecodeFileContent, intStr);
}

void loadVariable(char *variableName)
{
    int variableId = getVariableId(variableName);
    char variableType = getVariableType(variableId);

    switch (variableType)
    {
    case 'C':
        strcat(bytecodeFileContent, "\naload ");
        break;

    case 'F':
        strcat(bytecodeFileContent, "\nfload ");
        break;

    default:
        strcat(bytecodeFileContent, "\niload ");
        break;
    }

    char intStr[12];
    sprintf(intStr, "%i", variableId);
    strcat(bytecodeFileContent, intStr);
}

int lastIndexOfCharInString(char searched, char *string)
{
    int size = strlen(string);

    for (int i = size - 1; i >= 0; i--)
    {
        if (string[i] == searched)
        {
            return i;
        }
    }

    return -1;
}

void substring(char s[], char sub[], int p, int l)
{
    int c = 0;

    while (c < l)
    {
        sub[c] = s[p + c];
        c++;
    }
    sub[c] = '\0';
}

void printHeadStack(char printType)
{
    if (printType != 'C' && printType != 'F')
    {
        printType = 'I';
    }

    char printTypeStr[100] = "\0";
    printTypeStr[0] = printType;

    if (printType == 'C')
    {
        strcpy(printTypeStr, "Ljava/lang/String;");
    }

    char lastLoadCommand[100];
    int lastIndexOfCommand = lastIndexOfCharInString('\n', bytecodeFileContent);
    substring(bytecodeFileContent, lastLoadCommand, lastIndexOfCommand, strlen(bytecodeFileContent) - lastIndexOfCommand + 1);

    bytecodeFileContent[lastIndexOfCommand] = '\0';
    strcat(bytecodeFileContent, "\ngetstatic java/lang/System/out Ljava/io/PrintStream;");
    strcat(bytecodeFileContent, lastLoadCommand);
    strcat(bytecodeFileContent, "\ninvokevirtual java/io/PrintStream/println(");
    strcat(bytecodeFileContent, printTypeStr);
    strcat(bytecodeFileContent, ")V");
}

void setLastUsedType(char type)
{
    lastUsedType = type;
}

void bytecodeAdd()
{
    switch (lastUsedType)
    {
    case 'F':
        strcat(bytecodeFileContent, "\nfadd");
        break;

    default:
        strcat(bytecodeFileContent, "\niadd");
        break;
    }
}

void bytecodeSub()
{
    switch (lastUsedType)
    {
    case 'F':
        strcat(bytecodeFileContent, "\nfsub");
        break;

    default:
        strcat(bytecodeFileContent, "\nisub");
        break;
    }
}

void bytecodeMul()
{
    switch (lastUsedType)
    {
    case 'F':
        strcat(bytecodeFileContent, "\nfmul");
        break;

    default:
        strcat(bytecodeFileContent, "\nimul");
        break;
    }
}

void bytecodeDiv()
{
    switch (lastUsedType)
    {
    case 'F':
        strcat(bytecodeFileContent, "\nfdiv");
        break;

    default:
        strcat(bytecodeFileContent, "\nidiv");
        break;
    }
}

void bytecodeNeg()
{
    switch (lastUsedType)
    {
    case 'F':
        strcat(bytecodeFileContent, "\nfneg");
        break;

    default:
        strcat(bytecodeFileContent, "\nineg");
        break;
    }
}

void bytecodeRest()
{
    char lastLoadCommand[100];
    int lastIndexOfCommand = lastIndexOfCharInString('\n', bytecodeFileContent);
    substring(bytecodeFileContent, lastLoadCommand, lastIndexOfCommand, strlen(bytecodeFileContent) - lastIndexOfCommand + 1);

    char bytecodeFileContentWithoutLastCommand[100000];
    substring(bytecodeFileContent, bytecodeFileContentWithoutLastCommand, 0, lastIndexOfCommand);
    char penultimateLoadCommand[100];
    int penultimateIndexOfCommand = lastIndexOfCharInString('\n', bytecodeFileContentWithoutLastCommand);
    substring(bytecodeFileContentWithoutLastCommand, penultimateLoadCommand, penultimateIndexOfCommand, strlen(bytecodeFileContentWithoutLastCommand) - penultimateIndexOfCommand + 1);

    bytecodeDiv();

    strcat(bytecodeFileContent, lastLoadCommand);

    bytecodeMul();

    strcat(bytecodeFileContent, penultimateLoadCommand);

    bytecodeSub();

    bytecodeNeg();
}

void bytecodeAnd()
{
    strcat(bytecodeFileContent, "\niand");
}

void bytecodeOr()
{
    strcat(bytecodeFileContent, "\nior");
}

void addLabel()
{
    strcat(bytecodeFileContent, "\nl");

    char intStr[12];
    sprintf(intStr, "%i", labelCount);
    strcat(bytecodeFileContent, intStr);

    strcat(bytecodeFileContent, ":");

    labelCount++;
}

void setLastIfCmp(char *type)
{
    strcpy(lastIfCmp, type);
}

void bytecodeIf()
{
    char mappedType[5] = "";

    if (strcmp(lastIfCmp, "eq") == 0)
    {
        strcpy(mappedType, "ne");
    }
    else if (strcmp(lastIfCmp, "ne") == 0)
    {
        strcpy(mappedType, "eq");
    }
    else if (strcmp(lastIfCmp, "lt") == 0)
    {
        strcpy(mappedType, "ge");
    }
    else if (strcmp(lastIfCmp, "le") == 0)
    {
        strcpy(mappedType, "gt");
    }
    else if (strcmp(lastIfCmp, "gt") == 0)
    {
        strcpy(mappedType, "le");
    }
    else if (strcmp(lastIfCmp, "ge") == 0)
    {
        strcpy(mappedType, "lt");
    }
    else if (strcmp(lastIfCmp, " ") == 0)
    {
        strcpy(mappedType, "eq");
        strcat(bytecodeFileContent, "\nbipush 0");
    }
    strcpy(lastIfCmp, " ");

    strcat(bytecodeFileContent, "\nif_icmp");
    strcat(bytecodeFileContent, mappedType);
    strcat(bytecodeFileContent, " l");

    char intStr[12];
    sprintf(intStr, "%i", labelCount);
    strcat(bytecodeFileContent, intStr);
}

void gotoNextLabel()
{
    strcat(bytecodeFileContent, "\ngoto l");

    char intStr[12];
    sprintf(intStr, "%i", labelCount + 1);
    strcat(bytecodeFileContent, intStr);
}

void gotoLastLabel()
{
    strcat(bytecodeFileContent, "\ngoto l");

    char intStr[12];
    sprintf(intStr, "%i", labelCount - 1);
    strcat(bytecodeFileContent, intStr);
}

void saveMarkStart(int index)
{
    if (index == 1)
    {
        mark1.start = strlen(bytecodeFileContent);
    }
    else
    {
        mark2.start = strlen(bytecodeFileContent);
    }
}

void saveMarkEnd(int index)
{
    if (index == 1)
    {
        mark1.end = strlen(bytecodeFileContent);
    }
    else
    {
        mark2.end = strlen(bytecodeFileContent);
    }
}

void swapMarks()
{
    char mark1Content[100000] = "";
    char mark2Content[100000] = "";

    substring(bytecodeFileContent, mark1Content, mark1.start, mark1.end - mark1.start);
    substring(bytecodeFileContent, mark2Content, mark2.start, mark2.end - mark2.start);

    bytecodeFileContent[mark1.start] = '\0';

    strcat(bytecodeFileContent, mark2Content);
    strcat(bytecodeFileContent, mark1Content);
}

void scan_int()
{
    // char lastLoadCommand[100];
    // int lastIndexOfCommand = lastIndexOfCharInString('\n', bytecodeFileContent);
    // substring(bytecodeFileContent, lastLoadCommand, lastIndexOfCommand, strlen(bytecodeFileContent) - lastIndexOfCommand + 1);
    // bytecodeFileContent[lastIndexOfCommand] = '\0';

    // char lastLoadedId[10];
    // lastIndexOfCommand = lastIndexOfCharInString('_', lastLoadCommand);
    // substring(lastLoadCommand, lastLoadedId, lastIndexOfCommand, strlen(lastLoadCommand) - lastIndexOfCommand + 1);

    char intStr[12];
    int scannerId = getVariableId("scanner");
    sprintf(intStr, "%i", scannerId);

    strcat(bytecodeFileContent, "\naload_");
    strcat(bytecodeFileContent, intStr);
    strcat(bytecodeFileContent, "\ninvokevirtual java/util/Scanner/nextInt()I");
    // strcat(bytecodeFileContent, "\nistore");
    // strcat(bytecodeFileContent, lastLoadedId);
}