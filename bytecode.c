#include "bytecode.h"
#include <string.h>
#include <stdbool.h>

void inicializarBytecodeFile(){

    strcpy(bytecodeFileContent, ".class public java_class\n.super java/lang/Object\n\n.method public <init>()V\naload_0\ninvokenonvirtual java/lang/Object/<init>()V\nreturn\n.end method\n\n.method public static main([Ljava/lang/String;)V\n.limit locals 100\n.limit stack 100\n.line 1\n");
    
    for(int i = 0; i < 100; i++){
        strcpy(variableMap[i], "");
        variableTypes[i] = ' ';
    }

}

void finalizarBytecodeFile(){
    
    strcat(bytecodeFileContent, "\n.end method");
    
    FILE *bytecodeFile = fopen("java_bytecode.j", "w");
    
    fputs(bytecodeFileContent, bytecodeFile);

    fclose(bytecodeFile);
}

int getVariableId(char* variableName){

    for(int i = 0; i < 100; i++){
        
        if(strlen(variableMap[i]) == 0 || strcmp(variableMap[i], variableName) == 0){
            
            strcpy(variableMap[i], variableName);
            return i + 1;

        }

    }

    return -1;

}

void atribuiValorIntParaVariavel(int valorInt, char* nomeVariavel){

    char intStr[12];

    strcat(bytecodeFileContent, "\nbipush ");
    sprintf(intStr, "%i", valorInt);
    strcat(bytecodeFileContent, intStr);


    strcat(bytecodeFileContent, "\nistore ");
    int idVariavel = getVariableId(nomeVariavel);
    sprintf(intStr, "%i", idVariavel);
    strcat(bytecodeFileContent, intStr);

}

void printaInt(int valorInt){

    char intStr[12];

    strcat(bytecodeFileContent, "\ngetstatic java/lang/System/out Ljava/io/PrintStream;");

    strcat(bytecodeFileContent, "\nbipush ");
    sprintf(intStr, "%i", valorInt);
    strcat(bytecodeFileContent, intStr);

    strcat(bytecodeFileContent, "\ninvokevirtual java/io/PrintStream/println(I)V");

}

void printaVariavel(char* nomeVariavel){

    char intStr[12];

    strcat(bytecodeFileContent, "\ngetstatic java/lang/System/out Ljava/io/PrintStream;");

    strcat(bytecodeFileContent, "\niload ");
    int idVariavel = getVariableId(nomeVariavel);
    sprintf(intStr, "%i", idVariavel);
    strcat(bytecodeFileContent, intStr);

    strcat(bytecodeFileContent, "\ninvokevirtual java/io/PrintStream/println(I)V");

}

void bytecodeReturn(){
    strcat(bytecodeFileContent, "\nreturn");
}

void pushInt(int intValue){
    
    char intStr[12];
    strcat(bytecodeFileContent, "\nbipush ");
    sprintf(intStr, "%i", intValue);
    strcat(bytecodeFileContent, intStr);

}

void pushFloat(float floatValue){
    
    char floatStr[12];
    strcat(bytecodeFileContent, "\nldc ");
    sprintf(floatStr, "%f", floatValue);
    strcat(bytecodeFileContent, floatStr);

}

void pushChar(char charValue){

    char stringValue[4];
    stringValue[0] = '\"';
    stringValue[1] = charValue;
    stringValue[2] = '\"';
    stringValue[3] = '\0';
    
    strcat(bytecodeFileContent, "\nldc ");
    strcat(bytecodeFileContent, stringValue);

}

void pushBool(bool boolValue){
    
    char boolStr[12];
    strcat(bytecodeFileContent, "\nbipush ");
    sprintf(boolStr, "%i", boolValue);
    strcat(bytecodeFileContent, boolStr);

}

void saveTypeToVariables(char variableType, lista_t *inics){

    for (size_t i = 0; i < lista_tamanho (inics, NULL); i++)
	{
		/* Obtencao do proximo identificador da lista. */
		char *variableName;
		lista_buscar (inics, i, &variableName);
        int variableId = getVariableId(variableName);
        variableTypes[variableId] = variableType;
    }


}

char getVariableType(int variableId){

    if(variableTypes[variableId] == ' '){
        return lastTypeUsed;
    }else{
        return variableTypes[variableId];
    }

}

void storeVariable(char* variableName){
    
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

void loadVariable(char* variableName){

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

int lastIndexOfCharInString(char searched, char* string){

    int size = strlen(string);

    for(int i = size - 1; i >= 0; i--){
        if(string[i] == searched){
            return i;
        }
    }

    return -1;

}

void substring(char s[], char sub[], int p, int l) {
   
   int c = 0;
   
   while (c < l) {
      sub[c] = s[p+c];
      c++;
   }
   sub[c] = '\0';

}

void printHeadStack(char printType){

    if(printType != 'C' && printType != 'F'){
        printType = 'I';
    }

    char printTypeStr[100] = "\0";
    printTypeStr[0] = printType;

    if(printType == 'C'){
        strcpy(printTypeStr, "Ljava/lang/String;");
    }

    char lastLoadCommand[100];
    int lastIndexOfCommand = lastIndexOfCharInString('\n', bytecodeFileContent);
    substring(bytecodeFileContent, lastLoadCommand, lastIndexOfCommand, strlen(bytecodeFileContent) - lastIndexOfCommand + 1);

    strcat(bytecodeFileContent, "\ngetstatic java/lang/System/out Ljava/io/PrintStream;");
    strcat(bytecodeFileContent, lastLoadCommand);
    strcat(bytecodeFileContent, "\ninvokevirtual java/io/PrintStream/println(");
    strcat(bytecodeFileContent, printTypeStr);
    strcat(bytecodeFileContent, ")V");

}

void setLastTypeUsed(char type){
    lastTypeUsed = type;
}