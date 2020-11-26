/*
 * Sale.h
 *
 *  Created on: 21 nov. 2020
 *      Author: micavazzana
 */

#ifndef SALE_H_
#define SALE_H_
#define FILENAME_LEN 31
#define TO_CHARGE 1
#define CHARGED 2
#define CABA 1
#define ZONA_SUR 2
#define ZONA_OESTE 3
#include "Client.h"

typedef struct {
	int id;
	int idClient;
	int posterQty;
	char fileName[FILENAME_LEN];
	int zone;
	int status;
}Sale;

Sale* sale_new(void);
Sale* sale_newParametros(char* idStr, char* idClientStr, char* posterQtyStr,char* fileNameStr, char* zoneStr, char* statusStr);
void sale_delete(Sale* this);

int sale_setId(Sale* this,int id);
int sale_getId(Sale* this,int* id);
int sale_setIdTxt(Sale* this, char* id);
int sale_getIdTxt(Sale* this, char* id);

int sale_setIdClient(Sale* this,int id);
int sale_getIdClient(Sale* this,int* id);
int sale_setIdClientTxt(Sale* this, char* id);
int sale_getIdClientTxt(Sale* this, char* id);

int sale_setPosterQty(Sale* this, int posterQty);
int sale_getPosterQty(Sale* this, int* posterQty);
int sale_setPosterQtyTxt(Sale* this, char* posterQty);
int sale_getPosterQtyTxt(Sale* this, char* posterQty);

int sale_setFileName(Sale* this, char* fileName);
int sale_getFileName(Sale* this, char* fileName);

int sale_setZone(Sale* this, int zone);
int sale_getZone(Sale* this, int* zone);
int sale_setZoneTxt(Sale* this, char* zone);
int sale_getZoneTxt(Sale* this, char* zone);

int sale_setStatus(Sale* this, int status);
int sale_getStatus(Sale* this, int* status);
int sale_setStatusTxt(Sale* this, char* status);
int sale_getStatusTxt(Sale* this, char* status);

int sale_printOne(void* this);
void headerSale(void);
void* findById(LinkedList* list, int id,int choiceList);
Sale* sale_loadAndAddData(LinkedList* listSale, LinkedList* listClient);
int sale_Edit(LinkedList* listSale, LinkedList* listClient, int (*pFunc)(Sale*,LinkedList*),char* msj, int status);
int sale_EditFields(Sale* pSale, LinkedList* listClient);
int sale_EditStatus(Sale* pSale, LinkedList* listClient);
int sale_compareByStatus(void* this, void* arg);
int sale_compareQtyPoster(void* pElement, void* arg);

/************************** AGREGADAS *****************************/

int sale_sort(LinkedList* list,int option, int order);
int sale_compareByPosterQty(void* first, void* second);
int sale_compareByFileName(void* first, void* second);
int sale_compareByZone(void* first, void* second);
int menuSortSale(void);
int sale_compareZoneAndPosterQty(void* first, void* second);
int sale_remove(LinkedList* listSale);

#endif /* SALE_H_ */
