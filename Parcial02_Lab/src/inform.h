/*
 * inform.h
 *
 *  Created on: 24 nov. 2020
 *      Author: micavazzana
 */

#ifndef INFORM_H_
#define INFORM_H_
#include "Controller.h"
#define MAX 0
#define MIN 1

int info_qtySalesByClient(LinkedList* listSale, LinkedList* listClient, int choice,int (*pFuncSet)(Client*,int));
int info_qtySalesById(LinkedList* listSale, int* qty,int choice,int id);
int info_generateEstadistics(LinkedList* listSale, LinkedList* listClient);
Sale* info_qtyPostersBySale(LinkedList* listSale, int choice, int* qtyPoster, int status);
Client* info_qtyPostersByClient(LinkedList* listSale,LinkedList* listClient, int choice, int* qtyPoster,int status);

#endif /* INFORM_H_ */
