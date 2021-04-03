# include <stdio.h>
# include <stdbool.h>

// Conteúdo do arquivo de bytecode
char bytecodeFileContent[100000];
char variableMap[100][100];

void inicializarBytecodeFile();
void finalizarBytecodeFile();
void atribuiValorIntParaVariavel(int valorInt, char* nomeVariavel);
void printaInt(int valorInt);
void printaVariavel(char* nomeVariavel);
void bytecodeReturn();
void pushInt(int intValue);
void pushFloat(float floatValue);
void pushChar(char charValue);
void pushBool(bool boolValue);
void storeVariable(char* variableName);
void loadVariable(char* variableName);
void printHeadStack();