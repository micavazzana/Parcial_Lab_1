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
#include "inputs.h"
#define ERROR -1
#define SUCCESS 0
#define TRUE 1
#define FALSE 0

static int generateNewIdClient(void);
static int generateNewIdSale(void);

void* findById(LinkedList* list, int id,int entityList)
{
	void* result = NULL;
	void* pElement;
	int i;
	int bufferId;

	if(list != NULL && id > 0)
	{
		for (i = 0; i < ll_len(list); i++)
		{
			if(entityList == CLIENT)
			{
				pElement = (Client*)ll_get(list,i);
				cli_getId(pElement,&bufferId);
			} else {
				pElement = (Sale*)ll_get(list,i);
				sale_getId(pElement,&bufferId);
			}
			if(bufferId == id)
			{
				result = pElement;
				break;
			}
		}
	}
	return result;
}

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

/**
 * \brief Alta de clientes - Solicita los datos de los campos al usuario y lo añade al listado
 * \param listClient LinkedList* puntero a lista clientes
 * \return int Return (-1) ERROR - Si el puntero a LikedList es NULL, si no hay espacio en memoria para un cliente
 * 								   o si el usuario completa erroneamente lo requerido o no lo puede agregar a la lista
 * 					  (-2) ERROR - Si el cuit ingresado ya existe
 * 					  (0) EXITO
 */
int cli_loadAndAddData(LinkedList* listClient)
{
	int result = ERROR;
	Client* pClient;
	Client buffer;

	if (listClient != NULL)
	{
		pClient = cli_new();
		if (pClient != NULL
				&& utn_getName(buffer.name, NAME_LEN, "\nIngrese nombre: ", "\nError!", 3) == SUCCESS
				&& utn_getName(buffer.lastName, NAME_LEN, "\nIngrese apellido: ", "\nError!", 3) == SUCCESS
				&& utn_getIdentityDocument(buffer.cuit, CUIT_LEN, "\nIngrese cuit: ", "\nError!", 3) == SUCCESS)
		{
			if(cli_cuitIsInList(listClient,buffer.cuit) == FALSE)
			{
				buffer.idClient = generateNewIdClient();
				if(cli_setName(pClient, buffer.name) == SUCCESS
						&& cli_setLastName(pClient, buffer.lastName) == SUCCESS
						&& cli_setCuit(pClient, buffer.cuit) == SUCCESS
						&& cli_setId(pClient, buffer.idClient) == SUCCESS)
				{
					result = ll_add(listClient,pClient);//pClient
				}
			} else {
				result = -2;
			}
		}
	}
	return result;
}

/**
 * \brief Verifica si existe un cuit dado en la lista de clientes
 * \param listClient LinkedList* puntero al listado de clientes
 * \param cuit char* cuit a buscar si ya existe
 * \return Return (0) FALSE si no existe (1) TRUE si lo encontro
 */
int cli_cuitIsInList(LinkedList* listClient, char* cuit)
{
	int result = FALSE;
	int i;
	char bufferCuit[CUIT_LEN];
	Client* pClient;

	if(listClient !=  NULL && cuit != NULL)
	{
		for (i = 0; i < ll_len(listClient); i++)
		{
			pClient = (Client*)ll_get(listClient,i);
			cli_getCuit(pClient,bufferCuit);
			if (strncmp(bufferCuit,cuit,CUIT_LEN)==0)
			{
				result = TRUE;
				break;
			}
		}
	}
	return result;
}

/**
 * \brief Genera un nuevo id para un nuevo cliente
 * \param void
 * \return int Return value of the new id
 */
static int generateNewIdClient(void)
{
    int id = ERROR;
    FILE* pFile;
    char bufferId[500];

	pFile = fopen("idClient.txt", "r");
	if(pFile != NULL)
	{
		if(fscanf(pFile,"%s",bufferId)==1)
		{
			id = atoi(bufferId);
			id++;
		}
		fclose(pFile);
	}
	pFile = fopen("idClient.txt", "w");
	if(pFile != NULL)
	{
		fprintf(pFile,"%d",id);
		fclose(pFile);
	}
    return id;
}

/**
 * \brief Alta de ventas - Solicita los datos de los campos al usuario y lo añade a la lista
 * \param listSale LinkedList* puntero a lista ventas
 * \param listClient LinkedList* puntero a lista clientes
 * \return int Return (-1) ERROR - Si el puntero a LikedList es NULL, si no hay espacio en memoria para una venta o no puede agregar la carga
 * 					  (-2) ERROR - Si el id ingresado no existe o el usuario completa incorrectamente los campos
 * 					  (0) EXITO
 */
int sale_loadAndAddData(LinkedList* listSale, LinkedList* listClient, int* asignedId)
{
	int result = ERROR;
	Sale* pSale;
	Sale buffer;

	if (listSale != NULL)
	{
		pSale = sale_new();
		if (pSale != NULL)
		{
			headerClient();
			ll_map(listClient,cli_printOne);
			if(utn_getNumber(&buffer.idClient, "\nIngrese el id del cliente: ", "\nError", 0, 999999, 3) == SUCCESS
					&& findById(listClient,buffer.idClient,CLIENT)!= NULL
					&& utn_getNumber(&buffer.posterQty, "\nIngrese la cantidad de afiches: ", "\nError", 0, 999999, 3) == SUCCESS
					&& utn_getIdentityDocument(buffer.fileName, FILENAME_LEN, "\nIngrese nombre de archivo: ", "\nError!", 3) == SUCCESS
					&& utn_getNumber(&buffer.zone, "\nIngrese la zona [1-CABA / 2-ZONA SUR / 3-ZONA OESTE]: ", "\nError", 1, 3, 3) == SUCCESS)
			{
				buffer.id = generateNewIdSale();
				if(sale_setId(pSale,buffer.id) == SUCCESS
						&& sale_setIdClient(pSale,buffer.idClient) == SUCCESS
						&& sale_setPosterQty(pSale,buffer.posterQty) == SUCCESS
						&& sale_setFileName(pSale,buffer.fileName) == SUCCESS
						&& sale_setZone(pSale,buffer.zone) == SUCCESS
						&& sale_setStatus(pSale,TO_CHARGE) == SUCCESS)
				{
					result = ll_add(listSale,pSale);
					*asignedId = buffer.id;
				}
			} else {
				result = -2;
			}
		}
	}
	return result;
}

/**
 * \brief Genera un nuevo id para una nueva venta
 * \param void
 * \return int Return value of the new id
 */
static int generateNewIdSale(void)
{
    int id = ERROR;
    FILE* pFile;
    char bufferId[500];

	pFile = fopen("idSale.txt", "r");
	if(pFile != NULL)
	{
		if(fscanf(pFile,"%s",bufferId)==1)
		{
			id = atoi(bufferId);
			id++;
		}
		fclose(pFile);
	}
	pFile = fopen("idSale.txt", "w");
	if(pFile != NULL)
	{
		fprintf(pFile,"%d",id);
		fclose(pFile);
	}
    return id;
}

/**
 * \brief Modificar datos de la venta - Permite al usuario elegir que campo cambiar
 * \param listSale LinkedList* puntero a la lista de venta
 * \return Return (-1) Error - Si el puntero a LikedList es NULL o venta no encontrada
 * 				  (0) EXITO
 */
int sale_edit(LinkedList* listSale, LinkedList* listClient, int (*pFunc)(Sale*,Client*),char* msj)
{
	int result = ERROR;
	LinkedList* newList = NULL;
	Sale buffer;
	Client* pClient;
	Sale* pSale;

	if(listSale != NULL && listClient != NULL)
	{
		newList = ll_clone(listSale);
		if(newList != NULL)
		{
			if(ll_filter(newList,sale_compareByStatus) == SUCCESS
					&& ll_map(newList,sale_printOne) == SUCCESS
					&& utn_getNumber(&buffer.id, msj, "\nError", 0, 999999, 3) == SUCCESS)
			{
				pSale = findById(newList,buffer.id,SALE);
				if(pSale != NULL)
				{
					sale_getIdClient(pSale,&buffer.idClient);
					pClient = findById(listClient,buffer.idClient,CLIENT);
					printf("\nLa venta le pertenece al cliente: \n");
					headerClient();
					cli_printOne(pClient);
					pFunc(pSale,pClient);
					result = SUCCESS;
				}
			}
		}
	}
	return result;
}

int sale_EditFields(Sale* pSale, Client* pClient)
{
	int result = ERROR;
	int option;
	Sale buffer;

	if(pSale != NULL && pClient != NULL)
	{
		do
		{
			if (utn_getNumber(&option, "\n\nIngrese una opcion: "
					"\n1.Modificar cliente al que le pertenece la venta (idCliente)"
					"\n2.Modificar cantidad de afiches "
					"\n3.Modificar nombre de archivo"
					"\n4.Modificar zona"
					"\n5.Volver al menu principal\n",
					"Error, elija una opcion valida\n", 1, 5, 3) == SUCCESS)
			{
				switch (option)
				{
				case 1:
					if (utn_getNumber(&buffer.idClient, "\nIngrese el nuevo id del cliente: ", "\nError", 0, 999999, 3) == SUCCESS)
							//&& findById(listClient,buffer.idClient,CLIENT)!= NULL)
					{
						sale_setIdClient(pSale,buffer.idClient);
						result = SUCCESS;
					} else {
						result = -2;
					}
					break;
				case 2:
					if (utn_getNumber(&buffer.posterQty, "\nIngrese la nueva cantidad de afiches: ", "\nError", 0, 999999, 3) == SUCCESS)
					{
						sale_setPosterQty(pSale,buffer.posterQty);
						result = SUCCESS;
					} else {
						result = -3;
					}
					break;
				case 3:
					if (utn_getIdentityDocument(buffer.fileName, FILENAME_LEN, "\nIngrese el nuevo nombre de archivo: ", "\nError!", 3) == SUCCESS)
					{
						sale_setFileName(pSale,buffer.fileName);
						result = SUCCESS;
					} else {
						result = -4;
					}
					break;
				case 4:
					if (utn_getNumber(&buffer.zone, "\nIngrese la nueva zona [1-CABA / 2-ZONA SUR / 3-ZONA OESTE]: ", "\nError", 1, 3, 3) == SUCCESS)
					{
						sale_setZone(pSale,buffer.zone);
						result = SUCCESS;
					} else {
						result = -5;
					}
					break;
				} //fin switch
			} else {
				printf("Se acabaron sus reintentos, vuelva a ingresar");
			}
			if (result < 0) {
				break;
			}
		} while(option != 5);
	}
	return result;
}

int sale_EditStatus(Sale* pSale, Client* pClient)
{
	int result = ERROR;
	char bufferAnswer[10];

	if (pSale != NULL && pClient != NULL)
	{
		if (utn_getName(bufferAnswer, 10, "\n\nSeguro que quiere cobrarla? Debe ingresar 'Si' para proceder: ", "\nError,ingrese una respuesta valida.", 3) == SUCCESS
							&& strncasecmp(bufferAnswer, "si", 10) == 0)
		{
			sale_setStatus(pSale,CHARGED);
			result = SUCCESS;
		}
	}
	return result;
}

int cli_qtySalesByClient(LinkedList* listSale, LinkedList* listClient, int choice)//a cobrar
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
				if (sale_qtySalesById(listSale,&qty,choice,bufferIdClient) == SUCCESS && qty >= 0)
				{
					cli_setSalesByClient(pClient,qty);
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
		controller_loadOrSaveFromTxt(newList,status,"w",parser_qtySalesCharged);
	}
	return result;
}

int sale_qtySalesById(LinkedList* listSale, int* qty,int choice,int id)
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
