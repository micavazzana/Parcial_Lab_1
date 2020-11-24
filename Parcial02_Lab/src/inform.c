/*
 * inform.c
 *
 *  Created on: 24 nov. 2020
 *      Author: micavazzana
 */
#include "inform.h"

/**
 * \brief Setea la cantidad de ventas por cliente y lo guarda en un archivo (cobradas o a cobrar segun se elija)
 * \param listSale LinkedList* puntero a la lista de ventas
 * \param listClient LinkedList* puntero a la lista de clientes
 * \param choice int valor cobrada o a cobrar a elegir
 * \return Return (-1)- ERROR
 * 				  (0) - EXITO
 */
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

/**
 * \brief Cuenta la cantidad de ventas que tiene un cliente (cobradas o a cobrar segun se elija)
 * \param listSale LinkedList* puntero a la lista de ventas
 * \param choice int valor cobrada o a cobrar a elegir
 * \param qty int* puntero al lugar donde va a guardar la cantidad de ventas
 * \param id int id
 * \return Return (-1)- ERROR
 * 				  (0) - EXITO
 */
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

/**
 * \brief Imprime un submenu que permite al usuario elegir que informe quiere ver
 * \param listSale LinkedList* puntero a la lista de ventas
 * \param listClient LinkedList* puntero a la lista de clientes
 * \return Return (-1) ERROR - Si el puntero a las LikedList es NULL, si eligio no ver los informes
 * 				  (0) EXITO
 *
 */
int info_generateEstadistics(LinkedList* listSale, LinkedList* listClient)
{
	int result = ERROR;
	int option;
	Client* pClient;
	Sale* pSale;
	int qty;
	int bufferId;
	int bufferIdClient;
	char bufferCuit[CUIT_LEN];

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
					pClient = info_qtyPostersByClient(listSale,listClient,MAX,&qty,CHARGED);
					if(pClient != NULL) {
						headerClient();
						cli_printOne(pClient);
						printf("\nCantidad de afiches: %d\n",qty);
						result = SUCCESS;
					}
					break;
				case 2:
					pClient = info_qtyPostersByClient(listSale,listClient,MIN,&qty,CHARGED);
					if(pClient != NULL) {
					headerClient();
					cli_printOne(pClient);
					printf("\nCantidad de afiches: %d\n",qty);
					result = SUCCESS;
					}
					break;
				case 3:
					pSale = info_qtyPostersBySale(listSale,MAX,&qty,CHARGED);
					if(pSale != NULL)
					{
						sale_getIdClient(pSale,&bufferIdClient);
						sale_getId(pSale,&bufferId);
						pClient = findById(listClient,bufferIdClient,CLIENT);
						if(pClient != NULL)
						{
							cli_getCuit(pClient,bufferCuit);
							printf("\nId venta: %d \nCUIT cliente: %s\n",bufferId,bufferCuit);
							printf("\nCantidad de afiches: %d\n",qty);
							result = SUCCESS;
						}
					}
					break;
				}
			}
		}while(option != 4);
	}
	return result;
}

/**
 * \brief Busca la cantidad de afiches por venta (min o maximo segun se elija - cobradas o a cobrar segun se elija)
 * \param listSale LinkedList* puntero a la lista de ventas
 * \param choice int valor maximo o minimo a elegir
 * \param qtyPoster int* puntero al lugar donde va a guardar la cantidad de afiches
 * \param status int valor cobrada o a cobrar a elegir
 * \return Return Sale* puntero a la venta
 * 				  NULL - Error
 */
Sale* info_qtyPostersBySale(LinkedList* listSale, int choice, int* qtyPoster, int status)
{
	void* returnAux = NULL;
	Sale* pSale;
	int qty;
	int max;
	int min;
	int i;
	int stat;

	if(listSale != NULL && (choice == MAX || choice == MIN) && qtyPoster != NULL && (status == TO_CHARGE || status == CHARGED))
	{
		for(i = 0; i< ll_len(listSale);i++)
		{
			pSale = ll_get(listSale,i);
			if(pSale != NULL)
			{
				sale_getPosterQty(pSale,&qty);
				sale_getStatus(pSale,&stat);
				if((i==0 || qty > max) && choice == MAX && stat == status)
				{
					max = qty;
					returnAux = pSale;
					*qtyPoster = qty;
				} else if((i== 0 || qty < min) && choice == MIN && stat == status) {
					min = qty;
					returnAux = pSale;
					*qtyPoster = qty;
				}
			}
		}
	}
	return returnAux;
}

/**
 * \brief Busca la cantidad de afiches por cliente (min o maximo segun se elija - cobradas o a cobrar segun se elija)
 * \param listSale LinkedList* puntero a la lista de ventas
 *  param listClient LinkedList* puntero a la lista de clientes
 * \param choice int valor maximo o minimo a elegir
 * \param qtyPoster int* puntero al lugar donde va a guardar la cantidad de afiches
 * \param status int valor cobrada o a cobrar a elegir
 * \return Return Sale* puntero a la venta
 * 				  NULL - Error
 */
Client* info_qtyPostersByClient(LinkedList* listSale,LinkedList* listClient, int choice, int* qtyPoster,int status)
{
	void* returnAux = NULL;
	LinkedList* clonedList = ll_newLinkedList();
	int max;
	int min;
	int i;
	Client* pClient;
	int bufferId;
	int acum;

	if(listSale != NULL && listClient != NULL && clonedList != NULL &&
				(choice == MAX || choice == MIN) && qtyPoster != NULL && (status == TO_CHARGE || status == CHARGED))
	{
		clonedList = ll_clone(listSale);
		if (clonedList != NULL)
		{
			if(ll_filter2(clonedList,sale_compareByStatus,&status) == SUCCESS)
			{
				for(i = 0; i < ll_len(listClient);i++)
				{
					acum = 0;
					pClient = ll_get(listClient,i);
					cli_getId(pClient,&bufferId);
					acum = ll_reduceInt2(clonedList,sale_compareQtyPoster,&bufferId);
					if((i == 0 || acum > max) && choice == MAX)
					{
						max = acum;
						returnAux = pClient;
						*qtyPoster = max;
					} else if ((i == 0 || acum < min) && choice == MIN)	{
						min = acum;
						returnAux = pClient;
						*qtyPoster = min;
					}
				}
			}
		}
	}
	return returnAux;
}
