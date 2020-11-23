/*
 * Controller.h
 *
 *  Created on: 21 nov. 2020
 *      Author: micavazzana
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "Parser.h"
#define CLIENT 1
#define SALE 2

typedef int (*parserFunction)(FILE*, LinkedList*);
int controller_loadOrSaveFromTxt(LinkedList* this, char* path,char* opentype,parserFunction pFunc);
void* findById(LinkedList* list, int id,int entity);

int cli_loadAndAddData(LinkedList* listClient);
int cli_cuitIsInList(LinkedList* listClient, char* cuit);

int sale_loadAndAddData(LinkedList* listSale, LinkedList* listClient,int* asignedId);
int sale_edit(LinkedList* listSale, LinkedList* listClient, int (*pFunc)(Sale*,Client*),char* msj);
int sale_EditFields(Sale* pSale, Client* pClient);
int sale_EditStatus(Sale* pSale, Client* pClient);

int cli_qtySalesByClient(LinkedList* listSale, LinkedList* listClient, int choice);
int sale_qtySalesById(LinkedList* listSale, int* qty,int choice,int id);

#endif /* CONTROLLER_H_ */
