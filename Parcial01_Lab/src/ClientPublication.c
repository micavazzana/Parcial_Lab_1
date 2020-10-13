/*
 * allFunctions.c
 *
 *  Created on: 11 oct. 2020
 *      Author: micavazzana
 */
#include "ClientPublication.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define ACTIVE 1
#define PAUSED 0

/**
 * \brief Remove a client and its publications
 * \param list Client* Pointer to array of clients
 * \param lenClient int Array clients length
 * \param list Publication* Pointer to array of publications
 * \param lenPubli int Array publications length
 * \return int Return (-1) if Error - Invalid length or NULL pointer (from both arrays) or if can't find a client id or if user chooses not to delete
 * 					  (0) if Ok
 */
int client_removeClient(Client* listClient,int lenClient, Publication* listPublication, int lenPubli)
{
	int result = ERROR;
	int bufferId;
	char bufferAnswer[10];

	if (listClient != NULL && lenClient > 0 && listPublication != NULL && lenPubli > 0)
	{
		if (cli_printList(listClient, lenClient) == SUCCESS
				&& utn_getNumber(&bufferId, "\n\nIngrese el id del cliente que quiere eliminar: ", "\nError", 0, INT_MAX, 3) == SUCCESS
				&& cli_findById(listClient, lenClient, bufferId) != ERROR)
		{
			if (publi_printListById(listPublication, lenPubli, bufferId) == SUCCESS
					&& utn_getName(bufferAnswer, 10, "\n\nSe eliminaran los avisos aqui mostrados ademas del cliente. "
							"Debe ingresar 'Si' para proceder con la baja: ", "\nError,ingrese una respuesta valida.", 3) == SUCCESS
					&& strncasecmp(bufferAnswer, "si", 10) == 0
					&& publi_remove(listPublication, lenPubli, listClient, lenClient, bufferId) == SUCCESS
					&& cli_remove(listClient, lenClient, bufferId) == SUCCESS)
			{
				result = SUCCESS;
			}
		}
	}
	return result;
}

/**
 * \brief Requests the user to choose what publication wants to pause, then asks for confirmation and pauses it.
 * \param list Client* Pointer to array of clients
 * \param lenClient int Array clients length
 * \param list Publication* Pointer to array of publications
 * \param lenPubli int Array publications length
 * \return int Return (-1) if Error - Invalid length or NULL pointer (from both arrays) or if can't find a publication or if user chooses not to pause
 * 					  (0) if Ok
 */
int publication_pause(Client* listClient,int lenClient, Publication* listPublication, int lenPubli)
{
	int result = ERROR;
	int bufferId;
	char bufferAnswer[10];

	if (listClient != NULL && lenClient > 0 && listPublication != NULL && lenPubli > 0)
	{
		if( publi_printList(listPublication, lenPubli) == SUCCESS
				&& utn_getNumber(&bufferId, "\n\nIngrese el id de la publicacion que quiere pausar: ", "\nError", 0, INT_MAX, 3) == SUCCESS
				&& publi_isActive(listPublication,lenPubli,bufferId)
				&& client_printClientInformation(listPublication,lenPubli,listClient,lenClient,bufferId) == SUCCESS
				&& utn_getName(bufferAnswer,10,"\n\nEsta seguro de que quiere pausar esta publicacion? Debe ingresar 'Si' para proceder: ", "\nError,ingrese una respuesta valida.",3) == SUCCESS
				&& strncasecmp(bufferAnswer,"si",10)==0
				&& publi_pausePublication(listPublication, lenPubli,bufferId) == SUCCESS)
		{
			result = SUCCESS;
		}
	}
	return result;
}

/**
 * \brief Requests the user to choose what publication wants to activate, then asks for confirmation and activates it.
 * \param list Client* Pointer to array of clients
 * \param lenClient int Array clients length
 * \param list Publication* Pointer to array of publications
 * \param lenPubli int Array publications length
 * \return int Return (-1) if Error - Invalid length or NULL pointer (from both arrays) or if can't find a publication or if user chooses not to activate
 * 					  (0) if Ok
 */
int publication_reactivate(Client* listClient,int lenClient, Publication* listPublication, int lenPubli)
{
	int result = ERROR;
	int bufferId;
	char bufferAnswer[10];

	if (listClient != NULL && lenClient > 0 && listPublication != NULL && lenPubli > 0)
	{
		if( publi_printList(listPublication, lenPubli) == SUCCESS
				&& utn_getNumber(&bufferId, "\n\nIngrese el id de la publicacion que quiere activar: ", "\nError", 0, INT_MAX, 3) == SUCCESS
				&& publi_isActive(listPublication,lenPubli,bufferId) == FALSE
				&& client_printClientInformation(listPublication,lenPubli,listClient,lenClient,bufferId) == SUCCESS
				&& utn_getName(bufferAnswer,10,"\n\nEsta seguro de que quiere activar esta publicacion? Debe ingresar 'Si' para proceder: ", "\nError,ingrese una respuesta valida.",3) == SUCCESS
				&& strncasecmp(bufferAnswer,"si",10)==0
				&& publi_restartPublication(listPublication, lenPubli,bufferId) == SUCCESS)
		{
			result = SUCCESS;
		}
	}
	return result;
}

/**
 * \brief Prints the information of the client requested
 * \param list Client* Pointer to array of clients
 * \param lenClient int Array clients length
 * \param list Publication* Pointer to array of publications
 * \param lenPubli int Array publications length
 * \param id int id needed for finding the index of publications
 * \return int Return (-1) if Error - Invalid length or NULL pointer (from both arrays) or if can't find a publication or if user chooses not to activate
 * 					  (0) if Ok
 */
int client_printClientInformation(Publication *listPublication, int lenPubli, Client* listClient, int lenClient, int id)
{
	int result = ERROR;
	int index;

	if (listClient != NULL && lenClient > 0 && listPublication != NULL && lenPubli > 0)
	{
		printf("\nInformacion del cliente: \n");
		printf("\n%10s %15s %15s %35s\n", "ID CLIENTE", "NOMBRE", "APELLIDO","CUIT");
		for(int i=0;i<lenClient;i++)
		{
			index = publi_findById(listPublication,lenPubli,id);
			if(listPublication[index].idClient == listClient[i].idClient)
			{
				cli_printOne(listClient[i]);
			}
		}
		result = SUCCESS;
	}
	return result;
}

/**
 * \brief Prints the information of all the clients and its publications
 * \param list Client* Pointer to array of clients
 * \param lenClient int Array clients length
 * \param list Publication* Pointer to array of publications
 * \param lenPubli int Array publications length
 * \param id int id needed for finding the index of publications
 * \return int Return (-1) if Error - Invalid length or NULL pointer (from both arrays)
 * 					  (0) if Ok
 */
int clientPublication_printClientAndPublications(Publication *listPublication, int lenPubli, Client* listClient, int lenClient)
{
	int result = ERROR;
	int i;
	int j;
	int flagIsPublication;

	if (listClient != NULL && lenClient > 0 && listPublication != NULL && lenPubli > 0)
	{
		for(i=0;i<lenClient;i++)
		{
			if(listClient[i].isEmpty == FALSE)
			{
				printf("\n\n%10s %15s %15s %35s\n", "ID CLIENTE", "NOMBRE", "APELLIDO","CUIT");
				cli_printOne(listClient[i]);
				printf("\n\n%10s %15s %15s %35s %20s\n", "ID PUBLI", "RUBRO", "ID CLIENTE", "TEXTO AVISO", "ESTADO");
				flagIsPublication = FALSE;
				for(j=0;j<lenPubli;j++)
				{
					if(listPublication[j].isEmpty == FALSE && listPublication[j].state == ACTIVE && listPublication[j].idClient == listClient[i].idClient)
					{
						flagIsPublication = TRUE;
						publi_printOne(listPublication[j]);
					}
				}
				if(flagIsPublication==FALSE)
				{
					printf("No tiene publicaciones");
				}
			}
		}
		result=SUCCESS;
	}
	return result;
}
