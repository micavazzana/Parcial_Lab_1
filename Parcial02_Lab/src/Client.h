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

typedef struct {
	int idClient;
	char name[NAME_LEN];
	char lastName[NAME_LEN];
	char cuit[CUIT_LEN];
	int qtySalesByClient;
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

int cli_setSalesByClient(Client* this,int qty);
int cli_getSalesByClient(Client* this,int* qty);

int cli_printOne(void* this);
void headerClient(void);

#endif /* CLIENT_H_ */
