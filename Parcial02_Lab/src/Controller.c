/*
 * Controller.c
 *
 *  Created on: 21 nov. 2020
 *      Author: micavazzana
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Controller.h"
#define ERROR -1
#define SUCCESS 0
#define TRUE 1
#define FALSE 0
#define MAX 0
#define MIN 1

/**
 * \brief Carga los datos desde el archivo que recibe como parametro (modo texto).
 * \param path char* ruta del archivo a cargar
 * \param this LinkedList* puntero a la lista
 * \return int Return (-1) ERROR - Si el puntero a LikedList es NULL, la ruta es invalida o no pudo abrir el archivo
 * 					  (0) EXITO
 */
int controller_loadOrSaveFromTxt(LinkedList* this, char* path,char* opentype,parserFunction pFunc)
{
	int result = ERROR;
	FILE* pFile;

	if(this != NULL && path != NULL)
	{
		pFile = fopen(path, opentype);
		if(pFile != NULL)
		{
			pFunc(pFile,this);
			result = SUCCESS;
			fclose(pFile);
		}
	}
	return result;
}

int info_qtySalesByClient(LinkedList* listSale, LinkedList* listClient, int choice)
{
	int result = ERROR;
	int i;
	int qty = 0;
	Client* pClient;
	int bufferIdClient;
	LinkedList* newList = NULL;
	char status[15];

	if(listSale != NULL && listClient != NULL)
	{
		newList = ll_newLinkedList();
		for (i = 0; i < ll_len(listClient); i++)
		{
			pClient = (Client*) ll_get(listClient,i);
			if(pClient != NULL)
			{
				cli_getId(pClient,&bufferIdClient);
				if (info_qtySalesById(listSale,&qty,choice,bufferIdClient) == SUCCESS && qty >= 0)
				{
					cli_setQtySalesByStatus(pClient,qty);
					result = ll_add(newList,pClient);
				}
			}
		}
		if(choice == TO_CHARGE)
		{
			sprintf(status,"a cobrar.txt");
		} else {
			sprintf(status,"cobradas.txt");
		}
		controller_loadOrSaveFromTxt(newList,status,"w",parser_ClientQtySalesCharged);
	}
	return result;
}

int info_qtySalesById(LinkedList* listSale, int* qty,int choice,int id)
{
	int result = ERROR;
	int i;
	int counter = 0;
	Sale* pSale;
	int status;
	int bufferIdClient;

	if (listSale != NULL && qty != NULL && (choice == TO_CHARGE || choice == CHARGED) && id > 0)
	{
		for (i = 0; i < ll_len(listSale); i++)
		{
			pSale = (Sale*) ll_get(listSale,i);
			if(pSale != NULL)
			{
				sale_getStatus(pSale,&status);
				sale_getIdClient(pSale,&bufferIdClient);
				if(status == choice && bufferIdClient == id)
				{
					counter++;
				}
			}
		}
		*qty = counter;
		result = SUCCESS;
	}
	return result;
}

int info_generateEstadistics(LinkedList* listSale, LinkedList* listClient)
{
	int result = ERROR;
	int option;
	Client* pClient;
	Sale* pSale;
	int qty;

	if(listSale != NULL && listClient != NULL)
	{
		do
		{
			if(utn_getNumber(&option,"\nIngrese una opcion: "
								"\n1. Cliente al que se le vendió mas afiches"
								"\n2. Cliente al que se le vendió menos afiches"
								"\n3. Venta con mas afiches vendidos"
								"\n4. Volver al menu principal\n\n",
								"\nError, elija una opcion valida!",1,4,5)==SUCCESS)
			{
				switch(option)
				{
				case 1:
					pClient = countPosters(listSale,listClient,MAX,CHARGED,CLIENT,&qty);
					headerClient();
					cli_printOne(pClient);
					printf("\nCantidad de afiches: %d\n",qty);
					break;
				case 2:
					pClient = countPosters(listSale,listClient,MIN,CHARGED,CLIENT,&qty);
					headerClient();
					cli_printOne(pClient);
					printf("\nCantidad de afiches: %d\n",qty);
					break;
				case 3:
					pSale = countPosters(listSale,listClient,MAX,CHARGED,SALE,&qty);
					headerSale();
					sale_printOne(pSale);
					printf("\nCantidad de afiches: %d\n",qty);
					break;
				}
			}
		}while(option != 4);
	}
	return result;
}

void* countPosters(LinkedList* listSale,LinkedList* listClient, int choice, int status, int type, int* qty)
{
	void* returnAux = NULL;
	Client* pClient;
	Sale* pSale;
	int qtyPoster;
	int bufferId;
	int max;
	int min;
	int indexMax;
	int indexMin;

	if(listSale != NULL)
	{
		for(int i = 0; i< ll_len(listSale);i++)
		{
			pSale = ll_get(listSale,i);
			sale_getPosterQty(pSale,&qtyPoster);
			if((i==0 || qtyPoster > max) && status == CHARGED && choice == MAX)
			{
				max = qtyPoster;
				indexMax = i;
			} else if((i== 0 || qtyPoster < min) && status == CHARGED && choice == MIN){
				min = qtyPoster;
				indexMin = i;
			}
		}
		if(choice  ==  MAX)
		{
			pSale = ll_get(listSale, indexMax);
			*qty = max;
		} else {
			pSale = ll_get(listSale, indexMin);
			*qty = min;
		}
		sale_getIdClient(pSale,&bufferId);
		pClient = findById(listClient,bufferId,CLIENT);
		if(type == CLIENT)
		{
			returnAux = pClient;
		} else if(type == SALE) {
			returnAux = pSale;
		}
	}
	return returnAux;
}
