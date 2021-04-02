#include "bytecode.h"
#include <string.h>

void inicializarBytecodeFile(){

    strcpy(bytecodeFileContent, ".class public java_class\n.super java/lang/Object\n\n.method public <init>()V\naload_0\ninvokenonvirtual java/lang/Object/<init>()V\nreturn\n.end method\n\n.method public static main([Ljava/lang/String;)V\n.limit locals 100\n.limit stack 100\n.line 1\n");
    
    for(int i = 0; i < 100; i++){
        strcpy(variableMap[i], "");
    }

}

void finalizarBytecodeFile(){
    
    strcat(bytecodeFileContent, "\n.end method");
    
    FILE *bytecodeFile = fopen("java_bytecode.j", "w");
    
    fputs(bytecodeFileContent, bytecodeFile);

    fclose(bytecodeFile);
}

int getIdVariavel(char* nomeVariavel){

    for(int i = 0; i < 100; i++){
        
        if(strlen(variableMap[i]) == 0 || strcmp(variableMap[i], nomeVariavel) == 0){
            
            strcpy(variableMap[i], nomeVariavel);
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
    int idVariavel = getIdVariavel(nomeVariavel);
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
    int idVariavel = getIdVariavel(nomeVariavel);
    sprintf(intStr, "%i", idVariavel);
    strcat(bytecodeFileContent, intStr);

    strcat(bytecodeFileContent, "\ninvokevirtual java/io/PrintStream/println(I)V");

}

void printaRetorno(){
    strcat(bytecodeFileContent, "\nreturn");
}