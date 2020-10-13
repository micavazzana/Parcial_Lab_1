/*
 * Publication.h
 *
 *  Created on: 10 oct. 2020
 *      Author: micavazzana
 */

#ifndef PUBLICATION_H_
#define PUBLICATION_H_
#define ADV_LEN 64
#include "Client.h"

typedef struct {
	int idClient;
	int rubro;
	char advertisementText[ADV_LEN];
	int idPublication;
	int isEmpty;
	int state;
}Publication;

int publi_initArray(Publication *list, int len);
int publi_findEmptyIndex(Publication *list, int len);
int publi_loadAndAddData(Publication *listPubli, int lenPubli, Client *listClient, int lenClient);
int publi_findByIdClient(Publication *list, int len, int id);
int publi_findById(Publication *list, int len, int id);
int publi_remove(Publication *list, int len, Client* listClient, int lenClient, int id);
int publi_printOne(Publication listPubli);
int publi_printList(Publication *list, int len);
int publi_printListById(Publication *list, int len,int id);
int publi_isAnyData(Publication *list, int len);
int publi_hardCodeData(Publication* list);
int publi_isActive(Publication *list, int len, int id);
int publi_pausePublication(Publication *list, int len, int idPubli);
int publi_restartPublication(Publication *list, int len, int idPubli);
int publi_qtyPausedPublications(Publication *list, int len);

//modificar
//ordenar

#endif /* PUBLICATION_H_ */
