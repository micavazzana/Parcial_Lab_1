/*
 * inform.c
 *
 *  Created on: 12 oct. 2020
 *      Author: micavazzana
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inform.h"
#define LEN_RUBRO 1000

/**
 * \brief Prints a subMenu and lets the user to choose which inform wants
 * \param listPublication Publication* Pointer to array of publications
 * \param lenPublication int Array publications length
 * \param listClient Client* Pointer to array of clients
 * \param lenClient Array client length
 * \return Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int info_subMenu(Publication *listPublication, int lenPubli, Client* listClient, int lenClient)
{
	int result = ERROR;
	int option;
	int index;
	Rubro listRubro[LEN_RUBRO];
	int bufferRubro;
	int isListRubroCreated;
	int qtyAds;

	if (listClient != NULL && lenClient > 0 && listPublication != NULL && lenPubli > 0)
	{
		isListRubroCreated = rubro_generateList(listPublication, lenPubli, listRubro, LEN_RUBRO);
		do {
			if(utn_getNumber(&option,
				"\n\nIngrese una opcion: \n"
				"\n1. Cliente con más avisos"
				"\n2. Cantidad de avisos pausados"
				"\n3. Rubro con mas avisos"
				"\n4. Cliente con más avisos activos"
				"\n5. Cliente con más avisos pausados"
				"\n6. Volver al menu principal\n\n","\nError! elija una opcion valida",1,6,3)==SUCCESS)
		{
			switch(option)
			{
			case 1:
				if(info_findIndexClientWithMorePublications(listPublication,lenPubli,listClient,lenClient,&qtyAds)!=ERROR)
				{
					index = info_findIndexClientWithMorePublications(listPublication,lenPubli,listClient,lenClient,&qtyAds);
					if(index>=0)
					{
						printf("\nEl cliente con mas avisos es: \n\n%10s %15s %15s %35s\n", "ID CLIENTE", "NOMBRE", "APELLIDO","CUIT");
						cli_printOne(listClient[index]);
						printf("\nTiene %d avisos",qtyAds);
					} else if (index == -2) {
						printf("Hay mas de un cliente con la misma cantidad de avisos");
					} else {
						printf("Error");
					}
				}
				break;
			case 2:
				if(publi_qtyPublications(listPublication, lenPubli, &qtyAds,PAUSED) == SUCCESS && qtyAds > 0)
				{
					printf("\nLa cantidad de avisos pausados es: %d",qtyAds);
					publi_printPublicationsByState(listPublication, lenPubli,PAUSED);
				} else if(qtyAds == 0) {
					printf("\nNo hay avisos pausados");
				}
				break;
			case 3:
				if(isListRubroCreated != ERROR)
				{
					bufferRubro = info_rubroWithMorePublications(listPublication, lenPubli, listRubro, LEN_RUBRO);
					if(bufferRubro >=0)
					{
						printf("\nEl numero de rubro con mas publicaciones es: %d",bufferRubro);
					} else if (bufferRubro == -2) {
						printf("Hay mas de un rubro con la misma cantidad de avisos");
					}else {
						printf("Error");
					}
				}
				break;
			case 4:
				if(info_findIndexClientWithMorePublicationsActivesorPaused(listPublication,lenPubli,listClient,lenClient,&qtyAds,ACTIVE)!=ERROR)
				{
					index = info_findIndexClientWithMorePublicationsActivesorPaused(listPublication,lenPubli,listClient,lenClient,&qtyAds,ACTIVE);
					if(index>=0)
					{
						printf("\nEl cliente con mas avisos activos es: \n\n%10s %15s %15s %35s\n", "ID CLIENTE", "NOMBRE", "APELLIDO","CUIT");
						cli_printOne(listClient[index]);
						printf("\nTiene %d avisos",qtyAds);
					} else if (index == -2) { //imprimir aunque sea 1
						printf("Hay mas de un cliente con la misma cantidad de avisos activos");
					} else {
						printf("Error");
					}
				}
				break;
			case 5:
				if(info_findIndexClientWithMorePublicationsActivesorPaused(listPublication,lenPubli,listClient,lenClient,&qtyAds,PAUSED)!=ERROR)
				{
					index = info_findIndexClientWithMorePublicationsActivesorPaused(listPublication,lenPubli,listClient,lenClient,&qtyAds,PAUSED);
					if(index>=0)
					{
						printf("\nEl cliente con mas avisos pausados es: \n\n%10s %15s %15s %35s\n", "ID CLIENTE", "NOMBRE", "APELLIDO","CUIT");
						cli_printOne(listClient[index]);
						printf("\nTiene %d avisos",qtyAds);
					} else if (index == -2) {
						printf("Hay mas de un cliente con la misma cantidad de avisos pausados");
					} else {
						printf("Error");
					}
				}
				break;
			}
		}
		}while(option!=6);
		result=SUCCESS;
	}
	return result;
}

/**
 * \brief Finds the index from client that has more publications
 * \param listPublication Publication* Pointer to array of publications
 * \param lenPublication int Array publications length
 * \param listClient Client* Pointer to array of clients
 * \param lenClient Array client length
 * \param qtyAds int* Pointer to where it will leave the maximum number of publications found
 * \return Return (-1) if Error [Invalid length or NULL pointer] -
 * 				  or number of index in which the client with more publications is
 * 				  (-2) if it can't find a client with more publications than other
 */
int info_findIndexClientWithMorePublications(Publication *listPublication, int lenPubli, Client* listClient, int lenClient, int* qtyAds)
{
	int result = ERROR;
	int qty;
	int i;
	int max;

	if (listClient != NULL && lenClient > 0 && listPublication != NULL && lenPubli > 0 && qtyAds != NULL)
	{
		for (i = 0; i < lenClient; i++)
		{
			if(listClient[i].isEmpty == FALSE)
			{
				qty = info_countPublicationsByClient(listPublication, lenPubli, listClient[i].idClient);
				if (qty > max || i == 0)
				{
					max = qty;
					result = i;
				} else if (qty == max) {
					result = -2;
				}
			}
		}
		*qtyAds = max;
	}
	return result;
}

/**
 * \brief Counts the quantity of publications of one client (it controls it by the id received)
 * \param listPublication Publication* Pointer to array of publications
 * \param lenPublication int Array publications length
 * \param id int id of the client searched
 * \return Return (-1) if Error [Invalid length or NULL pointer] -
 * 				  or number of publications counted
 */
int info_countPublicationsByClient(Publication *listPublication, int lenPubli, int id)
{
	int result = ERROR;
	int counter = 0;
	int i;

	if (listPublication != NULL && lenPubli > 0 && id >=0)
	{
		for (i = 0; i < lenPubli; i++)
		{
			if(listPublication[i].isEmpty == FALSE && listPublication[i].idClient == id)
			{
				counter++;
			}
		}
		result = counter;
	}
	return result;
}

/**
 * \brief Finds rubro number with more publications
 * \param listPublication Publication* Pointer to array of publications
 * \param lenPublication int Array publications length
 * \param listRubro Rubro* Pointer to array of rubros
 * \param lenRubro int Array rubros length
 * \return Return (-1) if Error [Invalid length or NULL pointer] -
 * 				  or number of rubro with more publications
 * 				  (-2) if it can't find a rubro with more publications than other
 */
int info_rubroWithMorePublications(Publication *listPublication, int lenPubli, Rubro* listRubro, int lenRubro)
{
	int result = ERROR;
	int qty;
	int i;
	int max;

	if (listRubro != NULL && lenRubro > 0 && listPublication != NULL && lenPubli > 0)
	{
		for (i = 0; i < lenRubro; i++)
		{
			if(listRubro[i].isEmpty == FALSE)
			{
				qty = info_countPublicationsWithSameRubroNumber(listPublication, lenPubli,listRubro[i].rubro);
				if (qty > max || i == 0)
				{
					max = qty;
					result = listRubro[i].rubro;
				} else if (qty == max) {
					result = -2;
				}
			}
		}
	}
	return result;
}

/**
 * \brief Counts the quantity of publications with the same rubro number (it controls it by the id received)
 * \param listPublication Publication* Pointer to array of publications
 * \param lenPublication int Array publications length
 * \param idRubro int id of the rubro searched
 * \return Return (-1) if Error [Invalid length or NULL pointer] -
 * 				  or number of publications with same rubro number counted
 */
int info_countPublicationsWithSameRubroNumber(Publication *listPublication, int lenPubli,int idRubro)
{
	int result = ERROR;
	int counter = 0;
	int i;

	if (listPublication != NULL && lenPubli > 0 && idRubro >=0)
	{
		for (i = 0; i < lenPubli; i++)
		{
			if(listPublication[i].isEmpty == FALSE && listPublication[i].rubro == idRubro)
			{
				counter++;
			}
		}
		result = counter;
	}
	return result;
}




/////////////////Rubros functions////////////////////////

/**
 * \brief To indicate that all position in the array are empty,
 * 		  this function put the flag (isEmpty) in TRUE in all position of the array
 * \param listRubro Rubro* Pointer to array of rubros
 * \param lenRubro int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 */
int rubro_init(Rubro *listRubro, int lenRubro)
{
	int result = ERROR;
	int i;

	if (listRubro != NULL && lenRubro > 0)
	{
		for (i = 0; i < lenRubro; i++)
		{
			listRubro[i].isEmpty = TRUE;
		}
		result = SUCCESS;
	}
	return result;
}

/**
 * \brief Checks if alredy exists a rubro in the list
 * \param listRubro Rubro* Pointer to array of rubros
 * \param lenRubro int Array rubros length
 * \param rubro int rubro to check if exists
 * \return Return (-1) if Error [flag isEmpty is TRUE] - (0) if Ok
 */
static int rubroIsInList(Rubro *listRubro, int lenRubro, int rubro)
{
	int result = FALSE;
	int i;

	for (i = 0; i < lenRubro; i++)
	{
		if (listRubro[i].isEmpty == FALSE && listRubro[i].rubro == rubro)
		{
			result = TRUE; //alredy exists
			break;
		}
	}
	return result;
}

/**
 * \brief Generates a list of rubro
 * \param listPublication Publication* Pointer to array of publications
 * \param lenPublication int Array publications length
 * \param listRubro Rubro* Pointer to array of rubros
 * \param lenRubro int Array rubros length
 * \return Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 */
int rubro_generateList(Publication *listPublication, int lenPublication,Rubro *listRubro, int lenRubro)
{
	int result = ERROR;
	int i;
	int indexRubro = 0;

	if (listRubro != NULL && lenRubro > 0 && listPublication != NULL && lenPublication > 0 && rubro_init(listRubro, lenRubro) == SUCCESS)
	{
		for (i = 0; i < lenPublication; i++)
		{
			if (listPublication[i].isEmpty == FALSE && rubroIsInList(listRubro, lenRubro, listPublication[i].rubro) == FALSE)
			{
				listRubro[indexRubro].rubro = listPublication[i].rubro;
				listRubro[indexRubro].isEmpty = FALSE;
				indexRubro++;
			}
		}
		result = SUCCESS;
	}
	return result;
}

/**
 * \brief Prints the data of only one rubro
 * \param list Rubro
 * \return Return (-1) if Error [flag isEmpty is TRUE] - (0) if Ok
 */
int rubro_printOne(Rubro list)
{
	int result = ERROR;

	if (list.isEmpty == FALSE)
	{
		printf("\n%10d\n", list.rubro);
		result = SUCCESS;
	}
	return result;
}

/**
 * \brief Print the content of rubro array
 * \param list Rubro* Pointer to array of rubro
 * \param length int  Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 */
int rubro_printList(Rubro *list, int len)
{
	int result = ERROR;
	int i;

	if (list != NULL && len > 0)
	{
		printf("%10s\n", "RUBRO");
		for (i = 0; i < len; i++)
		{
			rubro_printOne(list[i]);
		}
		result = SUCCESS;
	}
	return result;
}





////////////DESARROLLADAS EN PARCIAL//////////////////////


/**
 * \brief Finds the index from client that has more publications
 * \param listPublication Publication* Pointer to array of publications
 * \param lenPublication int Array publications length
 * \param listClient Client* Pointer to array of clients
 * \param lenClient Array client length
 * \param qtyAds int* Pointer to where it will leave the maximum number of publications found
 * \return Return (-1) if Error [Invalid length or NULL pointer] -
 * 				  or number of index in which the client with more publications is
 * 				  (-2) if it can't find a client with more publications than other
 */
int info_findIndexClientWithMorePublicationsActivesorPaused(Publication *listPublication, int lenPubli, Client* listClient, int lenClient, int* qtyAds, int choice)
{
	int result = ERROR;
	int qty;
	int i;
	int max;

	if (listClient != NULL && lenClient > 0 && listPublication != NULL && lenPubli > 0 && qtyAds != NULL && (choice == PAUSED || choice == ACTIVE))
	{
		for (i = 0; i < lenClient; i++)
		{
			if(listClient[i].isEmpty == FALSE)
			{
				publi_qtyPublicationsById(listPublication, lenPubli, &qty, choice, listClient[i].idClient);
				if (qty > max || i == 0)
				{
					max = qty;
					result = i;
				} else if (qty == max) {
					result = -2;
				}
			}
		}
		*qtyAds = max;
	}
	return result;
}

int publi_qtyPublicationsById(Publication *list, int len, int* qtyAds,int choice,int id)
{
	int result = ERROR;
	int i;
	int counter = 0;

	if (list != NULL && len > 0 && qtyAds != NULL && (choice == PAUSED || choice == ACTIVE))
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == FALSE && list[i].state == choice && list[i].idClient == id)
			{
				counter++;
			}
		}
		*qtyAds = counter;

		result = SUCCESS;
	}
	return result;
}
