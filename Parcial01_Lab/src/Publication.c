/*
 * Publication.c
 *
 *  Created on: 10 oct. 2020
 *      Author: micavazzana
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inputs.h"
#include "Publication.h"
#define ACTIVE 1
#define PAUSED 0

/**
 * \brief To indicate that all position in the array are empty,
 * 		  this function put the flag (isEmpty) in TRUE in all position of the array
 * \param list Publication* Pointer to array of publications
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 */
int publi_initArray(Publication *list, int len)
{
	int result = ERROR;
	int i;

	if (list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			list[i].isEmpty = TRUE;
		}
		result = SUCCESS;
	}
	return result;
}

/**
 * \brief Searches for an empty index in the array,
 * 		  this function checks if the flag(isEmpty) is TRUE and saves the first index found.
 * \param list Publication* Pointer to array of publications
 * \param len int Array length
 * \return int Return value of the first empty index found -
 * 			   or (-1) if Error [Invalid length, NULL pointer or if there isn't more avaible space]
 */
int publi_findEmptyIndex(Publication *list, int len)
{
	int result = ERROR;
	int i;

	if (list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			if (list[i].isEmpty)
			{
				result = i;
				break;
			}
		}
	}
	return result;
}

/**
 * \brief Generates a new id for a new publication,
 * \param void
 * \return int Return value of the new id
 */
static int generateNewId(void)
{
	static int id = 0;
	id++;
	return id;
}

/**
 * \brief Requests the user to complete the data asked and adds that data to the array.
 * \param listPubli Publication* Pointer to array of publications
 * \param lenPubli int Array length of publications
 * \param listClient Client* Pointer to array of clients
 * \param lenClient int Array length of clients
 * \return Return (-1) if Error - Invalid length or NULL pointer of the arguments or no avaible space (in publications array)
 * 				  (-2) if Error - wrong entry of the fields
 * 				  or publication index position where it was charged
 */
int publi_loadAndAddData(Publication *listPubli, int lenPubli, Client *listClient, int lenClient)
{
	int result = ERROR;
	Publication bufferPubli;
	int index;

	if (listPubli != NULL && lenPubli > 0 && listClient != NULL && lenClient > 0 && publi_findEmptyIndex(listPubli, lenPubli) != ERROR)
	{
		index = publi_findEmptyIndex(listPubli, lenPubli);
		if (cli_printList(listClient, lenClient) == SUCCESS
				&& utn_getNumber(&bufferPubli.idClient, "\nIngrese el id del cliente para realizar la publicacion: ", "\nError", 0, 99999, 3) == SUCCESS
				&& cli_findById(listClient, lenClient, bufferPubli.idClient)!=ERROR
				&& utn_getNumber(&bufferPubli.rubro,"\nIngrese numero de rubro: ","\nError",0,9999,3) == SUCCESS
				&& utn_getAlphanumeric(bufferPubli.advertisementText,ADV_LEN,"\nIngrese el texto del aviso: \n","\nError!",3) == SUCCESS)
		{
			bufferPubli.isEmpty = FALSE;
			bufferPubli.state = ACTIVE;
			bufferPubli.idPublication = generateNewId();
			listPubli[index] = bufferPubli;
			result = index;//SUCCESS;
		} else {
			result = -2;
		}
	}
	return result;
}
/**
 * \brief Searches the position in which is the client id
 * \param list Publication* Pointer to array of publications
 * \param len int Array length
 * \param id int, id searched
 * \return Return publication index position or (-1) if [Invalid length or NULL pointer received or client not found]
 */
int publi_findByIdClient(Publication *list, int len, int id)
{
	int result = ERROR;
	int i;

	if (list != NULL && len > 0 && id > 0)
	{
		for (i = 0; i < len; i++)
		{
			if (list[i].isEmpty == FALSE && list[i].idClient == id)
			{
				result = i;
				break;
			}
		}
	}
	return result;
}

/**
 * \brief Searches a Publication by Id
 * \param list Publication* Pointer to array of publications
 * \param len int Array length
 * \param id int, id searched
 * \return Return publication index position or (-1) if [Invalid length or NULL pointer received or publication not found]
 */
int publi_findById(Publication *list, int len, int id)
{
	int result = ERROR;
	int i;

	if (list != NULL && len > 0 && id > 0)
	{
		for (i = 0; i < len; i++)
		{
			if (list[i].isEmpty == FALSE && list[i].idPublication == id)
			{
				result = i;
				break;
			}
		}
	}
	return result;
}

/**
 * \brief Remove a publication searched by Id (put isEmpty Flag in 1)
 * \param list Publication* Pointer to array of publications
 * \param len int Array publications length
 * \param listClient Client* Pointer to array of clients
 * \param lenClient Array client length
 * \param id int, id searched
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't find a publication with that client id] - (0) if Ok
 */
int publi_remove(Publication *list, int len, Client* listClient, int lenClient, int id)
{
	int result = ERROR;
	int i;

	if (list != NULL && len > 0 && listClient != NULL && lenClient > 0 && id > 0 && cli_findById(listClient,lenClient,id) != ERROR && publi_findByIdClient(list,len,id) != ERROR)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == FALSE && list[i].idClient == id)
			{
				list[i].isEmpty = TRUE;
				result = SUCCESS;
			}
		}
	}
	return result;
}

/**
 * \brief Prints the data of only one publication
 * \param list Publication list
 * \return Return (-1) if Error [flag isEmpty is TRUE] - (0) if Ok
 */
int publi_printOne(Publication listPubli)
{
	int result = ERROR;
	char state[8];

	if (listPubli.isEmpty == FALSE)
	{
		if(listPubli.state == PAUSED)
		{
			sprintf(state,"PAUSADO");
		}else if(listPubli.state == ACTIVE)
		{
			sprintf(state,"ACTIVO");
		}
		printf("\n%10d %15d %15d %35s %20s\n",
				listPubli.idPublication,
				listPubli.rubro,
				listPubli.idClient,
				listPubli.advertisementText,
				state);
		result = SUCCESS;
	}
	return result;
}

/**
 * \brief Print the content of publications array
 * \param list Publication* Pointer to array of publications
 * \param length int  Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 */
int publi_printList(Publication *list, int len)
{
	int result = ERROR;
	int i;

	if (list != NULL && len > 0)
	{
		printf("\n%10s %15s %15s %35s %20s\n", "ID PUBLI", "RUBRO", "ID CLIENTE", "TEXTO AVISO", "ESTADO");
		for (i = 0; i < len; i++)
		{
			publi_printOne(list[i]);
		}
		result = SUCCESS;
	}
	return result;
}

/**
 * \brief Print the content of publications array of the id received
 * \param list Publication* Pointer to array of publications
 * \param length int  Array length
 * \param id int, id received
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 */
int publi_printListById(Publication *list, int len,int id)
{
	int result = ERROR;
	int i;

	if (list != NULL && len > 0 && id > 0)
	{
		printf("\n%10s %15s %15s %35s %20s\n", "ID PUBLI", "RUBRO", "ID CLIENTE", "TEXTO AVISO", "ESTADO");
		for (i = 0; i < len; i++)
		{
			if (list[i].idClient == id)
			{
				publi_printOne(list[i]);
			}
		}
		result = SUCCESS;
	}
	return result;
}

/**
 * \brief Checks if there is any data in the array
 * 			this function checks the flag (isEmpty). If it is false, there is data.
 * \param list Publication* Pointer to array of publications
 * \param len int Array length
 * \return int Returns TRUE(1) if there is data, if not, returns FALSE(0)
 */
int publi_isAnyData(Publication *list, int len)
{
	int i;
	int result = FALSE;

	if (list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == FALSE) //if there is data
			{
				result = TRUE;
				break;
			}
		}
	}
	return result;
}

/**
 * \brief Forces data into the array of publications
 * \param list Publication* Pointer to array of publications
 * \return Return (-1) if Error [NULL pointer] - (0) if Ok
 */
int publi_hardCodeData(Publication* list)
{
	int result = ERROR;
	int idClient[] = {1,2,3,4,8,3,7,10,5,3,9,6,11};
	int rubro[] = {11,11,22,11,22,33,55,33,44,44,55,66,77};
	char advertisementText[][ADV_LEN] = {"Telefonos baratos","Eliminacion de monstruos","Se busca radio con antena",
			"Carpas de Will, la mejor proteccion","Buenas vibras spa","La buena rula","Comida casera","Jardineria, corto su pasto",
			"Compra luces de todos los colores","Nos comunicamos con el otro lado","Foto pro, la mejor foto de tu boda","Defensa de su hogar","Cuidado de niños"};
	int i;

	if (list != NULL)
	{
		for (i = 0; i < 13; i++)
		{
			list[i].idClient = idClient[i];
			list[i].rubro = rubro[i];
			strncpy(list[i].advertisementText,advertisementText[i],ADV_LEN);
			list[i].idPublication = generateNewId();
			list[i].isEmpty = FALSE;
			list[i].state = ACTIVE;
		}
		result=SUCCESS;
	}
	return result;
}

/**
 * \brief Checks if the publication is alredy in active state
 * \param list Publication* Pointer to array of publications
 * \param len int Array length
 * \param id int, id searched
 * \return int Returns TRUE(1) if is active, if not, returns FALSE(0)
 */
int publi_isActive(Publication *list, int len, int id)
{
	int i;
	int result = FALSE;

	if (list != NULL && len > 0 && id > 0)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].state == ACTIVE && id == list[i].idPublication) //if it's active
			{
				result = TRUE;
				break;
			}
		}
	}
	return result;
}

/**
 * \brief Pause a publication searched by Id (put state Flag in 0)
 * \param list Publication* Pointer to array of publications
 * \param len int Array length
 * \param id int, id searched
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't find a publication] - (0) if Ok
 */
int publi_pausePublication(Publication *list, int len, int idPubli)
{
	int result = ERROR;
	int index;

	if (list != NULL && len > 0 && idPubli > 0 && publi_findById(list,len,idPubli) != ERROR)
	{
		index = publi_findById(list,len,idPubli);
		if(list[index].isEmpty == FALSE && list[index].state == ACTIVE)
		{
			list[index].state = PAUSED;
			result = SUCCESS;
		}
	}
	return result;
}

/**
 * \brief Restart a publication searched by Id (put state Flag in 1)
 * \param list Publication* Pointer to array of publications
 * \param len int Array length
 * \param id int, id searched
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't find a publication] - (0) if Ok
 */
int publi_restartPublication(Publication *list, int len, int idPubli)
{
	int result = ERROR;
	int index;

	if (list != NULL && len > 0 && idPubli > 0 && publi_findById(list,len,idPubli) != ERROR)
	{
		index = publi_findById(list,len,idPubli);
		if(list[index].isEmpty == FALSE)
		{
			list[index].state = ACTIVE;
			result = SUCCESS;
		}
	}
	return result;
}

/**
 * \brief It counts the quantity of paused publications
 * \param list Publication* Pointer to array of publications
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] -
 * 					   or quantity of paused publications
 */
int publi_qtyPausedPublications(Publication *list, int len)
{
	int result = ERROR;
	int i;
	int counter=0;

	if (list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == FALSE && list[i].state == PAUSED)
			{
				counter++;
			}
		}
		result = counter;
	}
	return result;
}
