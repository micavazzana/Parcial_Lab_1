/*
 * Client.h
 *
 *  Created on: 21 nov. 2020
 *      Author: micavazzana
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#define NAME_LEN 51
#define CUIT_LEN 20
#define ERROR -1
#define SUCCESS 0
#define TRUE 1
#define FALSE 0
#define CLIENT 1
#define SALE 2
#include "LinkedList.h"
#include "inputs.h"

typedef struct {
	int idClient;
	char name[NAME_LEN];
	char lastName[NAME_LEN];
	char cuit[CUIT_LEN];
	int qtySalesCharged;
	int qtySalesToCharge;
}Client;

Client* cli_new(void);
Client* cli_newParametros(char* idStr,char* nameStr,char* lastNameStr, char* cuitStr);
void cli_delete(Client* this);

int cli_setId(Client* this,int id);
int cli_getId(Client* this,int* id);
int cli_setIdTxt(Client* this, char* id);
int cli_getIdTxt(Client* this, char* id);

int cli_setName(Client* this, char* name);
int cli_getName(Client* this, char* name);

int cli_setLastName(Client* this, char* lastName);
int cli_getLastName(Client* this, char* lastName);

int cli_setCuit(Client* this, char* cuit);
int cli_getCuit(Client* this, char* cuit);

int cli_setQtySalesCharged(Client* this,int qty);
int cli_getQtySalesCharged(Client* this,int* qty);
int cli_setQtySalesToCharge(Client* this,int qty);
int cli_getQtySalesToCharge(Client* this,int* qty);

int cli_printOne(void* this);
void headerClient(void);
Client* cli_loadAndAddData(LinkedList* listClient);
int cli_cuitIsInList(LinkedList* listClient, char* cuit);


/************************** AGREGADAS *****************************/

int cli_sort(LinkedList* list,int option, int order);
int cli_compareByName(void* first, void* second);
int cli_compareByLastName(void* first, void* second);
int cli_compareByCuit(void* first, void* second);
int menuSortClient(void);

#endif /* CLIENT_H_ */
