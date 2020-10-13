/*
 * inform.h
 *
 *  Created on: 12 oct. 2020
 *      Author: micavazzana
 */

#ifndef INFORM_H_
#define INFORM_H_
#include "ClientPublication.h"

typedef struct {
	int rubro;
	int isEmpty;
}Rubro;

int info_subMenu(Publication *listPublication, int lenPubli, Client* listClient, int lenClient);
int info_findIndexClientWithMorePublications(Publication *listPublication, int lenPubli, Client* listClient, int lenClient);
int info_RubroWithMorePublications(Publication *listPublication, int lenPubli, Rubro* listRubro, int lenRubro);

int rubro_init(Rubro *listRubro, int lenRubro);
int rubro_generateList(Publication *listPublication, int lenPublication,Rubro *listRubro, int lenRubro);
int rubro_printOne(Rubro list);
int rubro_printList(Rubro *list, int len);

#endif /* INFORM_H_ */
