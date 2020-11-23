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

int info_qtySalesByClient(LinkedList* listSale, LinkedList* listClient, int choice);
int info_qtySalesById(LinkedList* listSale, int* qty,int choice,int id);
int info_generateEstadistics(LinkedList* listSale, LinkedList* listClient);
void* countPosters(LinkedList* listSale,LinkedList* listClient, int choice, int status, int type, int* qty);

#endif /* CONTROLLER_H_ */
