/*
 * Controller.h
 *
 *  Created on: 21 nov. 2020
 *      Author: micavazzana
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "Parser.h"


typedef int (*parserFunction)(FILE*, LinkedList*);

int controller_loadOrSaveFromTxt(LinkedList* this, char* path,char* opentype,parserFunction pFunc);
int controller_add(LinkedList* list,void* pElement);
int controller_list(LinkedList* list, void (*pFuncHeader)(void),int (*pFuncPrint)(void*));
int controller_remove(LinkedList* list, int (*pFunc)(LinkedList*),void (*pFuncHeader)(void),int (*pFuncPrint)(void*));
int controller_sort(LinkedList* list, int (*pFunc)(void),int (*pFuncSort)(LinkedList*,int, int));

#endif /* CONTROLLER_H_ */
