#include "lista.h"
#include <stdio.h>
#include <stdbool.h>

// Conteúdo do arquivo de bytecode
char bytecodeFileContent[100000];
char variableMap[100][100];
char variableTypes[100];
char lastUsedType;

void inicializarBytecodeFile();
void finalizarBytecodeFile();
void atribuiValorIntParaVariavel(int valorInt, char *nomeVariavel);
void printaInt(int valorInt);
void printaVariavel(char *nomeVariavel);
void bytecodeReturn();
void pushInt(int intValue);
void pushFloat(float floatValue);
void pushChar(char charValue);
void pushBool(bool boolValue);
void saveTypeToVariables(char variableType, lista_t *inics);
void storeVariable(char *variableName);
void loadVariable(char *variableName);
void printHeadStack(char printType);
void setLastUsedType(char type);
void bytecodeAdd();
void bytecodeSub();
void bytecodeMul();
void bytecodeDiv();
void bytecodeNeg();
void bytecodeRest();
void bytecodeAnd();
void bytecodeOr();