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
	int pausedPublication;
	Rubro listRubro[LEN_RUBRO];
	int bufferRubro;

	if (listClient != NULL && lenClient > 0 && listPublication != NULL && lenPubli > 0)
	{
		do {
			if(utn_getNumber(&option,
				"\n\nIngrese una opcion: \n"
				"\n1. Cliente con más avisos"
				"\n2. Cantidad de avisos pausados"
				"\n3. Rubro con mas avisos"
				"\n4. Volver al menu principal\n\n","\nError! elija una opcion valida",1,4,3)==SUCCESS)
		{
			switch(option)
			{
			case 1:
				if(info_findIndexClientWithMorePublications(listPublication,lenPubli,listClient,lenClient)!=ERROR)
				{
					index = info_findIndexClientWithMorePublications(listPublication,lenPubli,listClient,lenClient);
					if(index>=0)
					{
						printf("\nEl cliente con mas avisos es: \n\n%10s %15s %15s %35s\n", "ID CLIENTE", "NOMBRE", "APELLIDO","CUIT");
						cli_printOne(listClient[index]);
					} else if (index == -2) {
						printf("Hay mas de un cliente con la misma cantidad de avisos");
					}
				}
				break;
			case 2:
				pausedPublication = publi_qtyPausedPublications(listPublication, lenPubli);
				if(pausedPublication != ERROR)
				{
					printf("La cantidad de avisos pausados es: %d",pausedPublication);
				}
				break;
			case 3:
				if(rubro_generateList(listPublication, lenPubli, listRubro, LEN_RUBRO) != ERROR)
				{
					bufferRubro = info_RubroWithMorePublications(listPublication, lenPubli, listRubro, LEN_RUBRO);
					if(bufferRubro >=0)
					{
						printf("\nEl numero de rubro con mas publicaciones es: %d",bufferRubro);
					} else if (bufferRubro == -2) {
						printf("Hay mas de un rubro con la misma cantidad de avisos");
					}
				}
				break;
			}
		}
		}while(option!=4);
		result=SUCCESS;
	}
	return result;
}

/**
 * \brief Checks which client has more publications
 * \param listPublication Publication* Pointer to array of publications
 * \param lenPublication int Array publications length
 * \param listClient Client* Pointer to array of clients
 * \param lenClient Array client length
 * \return Return (-1) if Error [Invalid length or NULL pointer] -
 * 				  or number of index in which the client with more publications is
 */
int info_findIndexClientWithMorePublications(Publication *listPublication, int lenPubli, Client* listClient, int lenClient)
{
	int result = ERROR;
	int counter = 0;
	int i;
	int j;
	int max;

	if (listClient != NULL && lenClient > 0 && listPublication != NULL && lenPubli > 0)
	{
		for (i = 0; i < lenClient; i++)
		{
			if(listClient[i].isEmpty == FALSE)
			{
				for (j = 0; j < lenPubli; j++)
				{
					if(listClient[i].idClient == listPublication[j].idClient)
					{
						counter++;
					}
				}
				if (counter > max || i == 0)
				{
					max = counter;
					result = i;
				} else if (counter == max) {
					result = -2;
				}
				counter = 0;
			}
		}
	}
	return result;
}

/**
 * \brief Checks which rubro has more publications
 * \param listPublication Publication* Pointer to array of publications
 * \param lenPublication int Array publications length
 * \param listRubro Rubro* Pointer to array of rubros
 * \param lenRubro int Array rubros length
 * \return Return (-1) if Error [Invalid length or NULL pointer] -
 * 				  or number of rubro with more publications
 */
int info_RubroWithMorePublications(Publication *listPublication, int lenPubli, Rubro* listRubro, int lenRubro)
{
	int result = ERROR;
	int counter = 0;
	int i;
	int j;
	int max;

	if (listRubro != NULL && lenRubro > 0 && listPublication != NULL && lenPubli > 0)
	{
		for (i = 0; i < lenRubro; i++)
		{
			if(listRubro[i].isEmpty == FALSE)
			{
				for (j = 0; j < lenPubli; j++)
				{
					if(listPublication[j].rubro == listRubro[i].rubro)
					{
						counter++;
					}
				}
				if (counter > max || i == 0)
				{
					max = counter;
					result = listRubro[i].rubro;
				} else if (counter == max) {
					result = -2;
				}
				counter = 0;
			}
		}
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
			result = TRUE;
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
	int indexPubli;
	int indexRubro = 0;

	if (listRubro != NULL && lenRubro > 0 && listPublication != NULL && lenPublication > 0 && rubro_init(listRubro, lenRubro) == SUCCESS)
	{
		for (indexPubli = 0; indexPubli < lenRubro; indexPubli++)
		{
			if (listPublication[indexPubli].isEmpty == FALSE && rubroIsInList(listRubro, lenRubro, listPublication[indexPubli].rubro) == FALSE)
			{
				listRubro[indexRubro].rubro = listPublication[indexPubli].rubro;
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
