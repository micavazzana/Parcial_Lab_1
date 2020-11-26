/*
 * Sale.c
 *
 *  Created on: 21 nov. 2020
 *      Author: micavazzana
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sale.h"

static int generateNewIdSale(void);

/*
 * \brief Pide memoria para una nueva venta
 * \param void
 * \return int Return puntero con espacio de memoria con tipo Sale*
 */
Sale* sale_new(void)
{
	return (Sale*) malloc(sizeof(Sale));
}

/*
 * \brief Pide memoria para una nueva venta y setea los campos en el espacio de memoria requerido
 * \param idStr char* id que va a setear
 * \param idClientStr char* id de cliente que va a setear
 * \param posterQty char* cantidad de afiches que va a setear
 * \param fileName char* nombre de archivo que va a setear
 * \param zone char* zona que va a setear
 * \param status char* estado que va a setear
 * \return int Return puntero con espacio de memoria con tipo Sale* con los campos ya seteados
 */
Sale* sale_newParametros(char* idStr, char* idClientStr, char* posterQtyStr,char* fileNameStr, char* zoneStr, char* statusStr)
{
	Sale* pSale = NULL;

	if (idStr != NULL && idClientStr != NULL && posterQtyStr != NULL && fileNameStr != NULL && zoneStr != NULL && statusStr != NULL)
	{
		pSale = sale_new();
		if (pSale != NULL)
		{
			sale_setIdTxt(pSale,idStr);
			sale_setIdClientTxt(pSale,idClientStr);
			sale_setPosterQtyTxt(pSale,posterQtyStr);
			sale_setFileName(pSale,fileNameStr);
			sale_setZoneTxt(pSale,zoneStr);
			sale_setStatusTxt(pSale,statusStr);
		}
	}
	return pSale;
}

/*
 * \brief Libera espacio de memoria de una venta
 * \param this Sale* puntero a venta
 * \return void
 */
void sale_delete(Sale* this)
{
	free(this);
}

/*
 * \brief Carga el id en el campo de la venta
 * \param this Sale* puntero a venta
 * \param id int id a cargar
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si el id no es valido
 * 					  (0) EXITO
 */
int sale_setId(Sale* this,int id)
{
	int result = ERROR;
	if (this != NULL && id >= 0)
	{
		this->id = id;
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Obtiene el id de la venta
 * \param this Sale* puntero a vemta
 * \param id int* puntero al espacio donde va a guardar el id obtenido
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si e puntero al id es NULL
 * 					  (0) EXITO
 */
int sale_getId(Sale* this,int* id)
{
	int result = ERROR;
	if (this != NULL && id != NULL)
	{
		*id = this->id;
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Carga el id en el campo de la venta (tratado como texto) y valida que el dato sea correcto
 * \param this Sale* puntero a venta
 * \param id char* puntero al id que va a cargar
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si e puntero al id es NULL
 * 					  (0) EXITO
 */
int sale_setIdTxt(Sale* this, char* id)
{
	int result = ERROR;
	if (this != NULL && id != NULL && isValidNumber(id, sizeof(id)))
	{
		this->id = atoi(id);
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Obtiene el id de la venta (tratado como texto)
 * \param this Sale* puntero a venta
 * \param id char* puntero al espacio donde va a guardar el id obtenido
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si e puntero al id es NULL
 * 					  (0) EXITO
 */
int sale_getIdTxt(Sale* this, char* id)
{
	int result = ERROR;
	if (this != NULL && id != NULL)
	{
		sprintf(id, "%d", this->id);
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Carga el id del cliente en el campo de la venta
 * \param this Sale* puntero a venta
 * \param id int id a cargar
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si el id no es valido
 * 					  (0) EXITO
 */
int sale_setIdClient(Sale* this,int id)
{
	int result = ERROR;
	if (this != NULL && id >= 0)
	{
		this->idClient = id;
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Obtiene el id del cliente
 * \param this Sale* puntero a venta
 * \param id int* puntero al espacio donde va a guardar el id obtenido
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si e puntero al id es NULL
 * 					  (0) EXITO
 */
int sale_getIdClient(Sale* this,int* id)
{
	int result = ERROR;
	if (this != NULL && id != NULL)
	{
		*id = this->idClient;
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Carga el id del cliente en el campo de la venta (tratado como texto) y valida que el dato sea correcto
 * \param this Sale* puntero a venta
 * \param id char* puntero al id que va a cargar
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si e puntero al id es NULL
 * 					  (0) EXITO
 */
int sale_setIdClientTxt(Sale* this, char* id)
{
	int result = ERROR;
	if (this != NULL && id != NULL && isValidNumber(id, sizeof(id)))
	{
		this->idClient = atoi(id);
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Obtiene el id del cliente (tratado como texto)
 * \param this Sale* puntero a venta
 * \param id char* puntero al espacio donde va a guardar el id obtenido
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si e puntero al id es NULL
 * 					  (0) EXITO
 */
int sale_getIdClientTxt(Sale* this, char* id)
{
	int result = ERROR;
	if (this != NULL && id != NULL)
	{
		sprintf(id, "%d", this->idClient);
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Carga la cantidad de afiches en el campo de la venta
 * \param this Sale* puntero a venta
 * \param posterQty int cantidad de afiches
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si el valor no es valido
 * 					  (0) EXITO
 */
int sale_setPosterQty(Sale* this, int posterQty)
{
	int result = ERROR;
	if(this != NULL && posterQty > 0)
	{
		this->posterQty = posterQty;
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Obtiene la cantidad de afiches de la venta
 * \param this Sale* puntero a venta
 * \param posterQty int* puntero al espacio donde va a guardar la cantidad de afiches obtenido
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si el puntero al entero es NULL
 * 					  (0) EXITO
 */
int sale_getPosterQty(Sale* this, int* posterQty)
{
    int result = ERROR;
    if (this != NULL && posterQty != NULL)
    {
        *posterQty = this->posterQty;
        result = SUCCESS;
    }
    return result;
}

/*
 * \brief Carga la cantidad de afiches en el campo de la venta (tratado como texto) y valida que el dato sea correcto
 * \param this Sale* puntero a venta
 * \param posterQty char* puntero a la cantidad de afiches que va a cargar
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o puntero a la cantidad de afiches es NULL
 * 					  (0) EXITO
 */
int sale_setPosterQtyTxt(Sale* this, char* posterQty)
{
    int result = ERROR;
    if (this != NULL && posterQty != NULL && isValidNumber(posterQty, sizeof(posterQty)))
    {
        this->posterQty = atoi(posterQty);
        result = SUCCESS;
    }
    return result;
}

/*
 * \brief Obtiene la cantidad de afiches (tratado como texto)
 * \param this Sale* puntero a venta
 * \param posterQty char* puntero al espacio donde va a guardar la cantidad de afiches obtenido
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si e puntero a la cantidad de afiches es NULL
 * 					  (0) EXITO
 */
int sale_getPosterQtyTxt(Sale* this, char* posterQty)
{
    int result = ERROR;
    if (this != NULL && posterQty != NULL)
    {
        sprintf(posterQty, "%d", this->posterQty);
        result = SUCCESS;
    }
    return result;
}

/*
 * \brief Carga el nombre de archivo en el campo de la venta y valida que el dato sea correcto
 * \param this Sale* puntero a venta
 * \param fileName char* puntero al nombre de  archivo que va a cargar
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si e puntero al nombre de archivo es NULL
 * 					  (0) EXITO
 */
int sale_setFileName(Sale* this, char* fileName)
{
	int result = ERROR;
	if (this != NULL && fileName != NULL && isValidDocumentNumber(fileName, FILENAME_LEN))
	{
		strncpy(this->fileName, fileName, FILENAME_LEN);
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Obtiene el nombre de archivo de la venta
 * \param this Sale* puntero a venta
 * \param fileName char* puntero al espacio donde va a guardar el nombre de archivo obtenido
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si e puntero al nombre de archivo es NULL
 * 					  (0) EXITO
 */
int sale_getFileName(Sale* this, char* fileName)
{
	int result = ERROR;
	if (this != NULL && fileName != NULL)
	{
		strncpy(fileName, this->fileName, FILENAME_LEN);
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Carga la zona en el campo de la venta
 * \param this Sale* puntero a venta
 * \param zone int zona
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si el valor no es valido
 * 					  (0) EXITO
 */
int sale_setZone(Sale* this, int zone)
{
	int result = ERROR;
	if(this != NULL && (zone == 1 || zone == 2 || zone ==3))
	{
		this->zone = zone;
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Obtiene la zona de la venta
 * \param this Sale* puntero a venta
 * \param zone int* puntero al espacio donde va a guardar la zona obtenida
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si el puntero a la zona es NULL
 * 					  (0) EXITO
 */
int sale_getZone(Sale* this, int* zone)
{
    int result = ERROR;
    if (this != NULL && zone != NULL)
    {
        *zone = this->zone;
        result = SUCCESS;
    }
    return result;
}

/*
 * \brief Carga la zona en el campo de la venta (tratado como texto) y valida que el dato sea correcto
 * \param this Sale* puntero a venta
 * \param zone char* puntero a la zona que va a cargar
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o puntero a la zona es NULL
 * 					  (0) EXITO
 */
int sale_setZoneTxt(Sale* this, char* zone)
{
    int result = ERROR;
    if (this != NULL && zone != NULL && isValidNumber(zone, sizeof(zone)))
    {
        this->zone = atoi(zone);
        result = SUCCESS;
    }
    return result;
}

/*
 * \brief Obtiene la zona (tratado como texto)
 * \param this Sale* puntero a venta
 * \param zone char* puntero al espacio donde va a guardar la zona obtenida
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si e puntero a la zona es NULL
 * 					  (0) EXITO
 */
int sale_getZoneTxt(Sale* this, char* zone)
{
    int result = ERROR;
    if (this != NULL && zone != NULL)
    {
        sprintf(zone, "%d", this->zone);
        result = SUCCESS;
    }
    return result;
}

/*
 * \brief Carga el estado en el campo de la venta
 * \param this Sale* puntero a venta
 * \param status int estado
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si el valor no es valido
 * 					  (0) EXITO
 */
int sale_setStatus(Sale* this, int status)
{
	int result = ERROR;
	if(this != NULL && (status == 1 || status == 2))
	{
		this->status = status;
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Obtiene el estado de la venta
 * \param this Sale* puntero a venta
 * \param status int* puntero al espacio donde va a guardar el estado obtenido
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si el puntero al estado es NULL
 * 					  (0) EXITO
 */
int sale_getStatus(Sale* this, int* status)
{
    int result = ERROR;
    if (this != NULL && status != NULL)
    {
        *status = this->status;
        result = SUCCESS;
    }
    return result;
}

/*
 * \brief Carga el estado en el campo de la venta (tratado como texto) y valida que el dato sea correcto
 * \param this Sale* puntero a venta
 * \param status char* puntero al estado que va a cargar
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o puntero al estado es NULL
 * 					  (0) EXITO
 */
int sale_setStatusTxt(Sale* this, char* status)
{
    int result = ERROR;
    if (this != NULL && status != NULL && isValidNumber(status, sizeof(status)))
    {
        this->status = atoi(status);
        result = SUCCESS;
    }
    return result;
}

/*
 * \brief Obtiene el estado (tratado como texto)
 * \param this Sale* puntero a venta
 * \param status char* puntero al espacio donde va a guardar el estado obtenido
 * \return int Return (-1) ERROR - Si el puntero a Sale* es NULL o si e puntero al estado es NULL
 * 					  (0) EXITO
 */
int sale_getStatusTxt(Sale* this, char* status)
{
    int result = ERROR;
    if (this != NULL && status != NULL)
    {
        sprintf(status, "%d", this->status);
        result = SUCCESS;
    }
    return result;
}


/****************** FUNCIONES *****************/

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
 * \brief Imprime los datos de una venta
 * \param this void* puntero a void
 * \return int Return (-1) ERROR - Si el puntero a void es NULL
 *					  (0) EXITO
 */
int sale_printOne(void* this)
{
	int result = ERROR;
	Sale* oneSale;
	Sale buffer;
	char zone[15];
	char status[15];

	if(this != NULL)
	{
		oneSale = (Sale*)this;
		if(sale_getId(oneSale,&buffer.id) == SUCCESS
				&& sale_getIdClient(oneSale,&buffer.idClient) == SUCCESS
				&& sale_getPosterQty(oneSale,&buffer.posterQty) == SUCCESS
				&& sale_getFileName(oneSale,buffer.fileName) == SUCCESS
				&& sale_getZone(oneSale,&buffer.zone) == SUCCESS
				&& sale_getStatus(oneSale,&buffer.status) == SUCCESS)
		{
			if(buffer.zone == CABA)
			{
				sprintf(zone,"CABA");
			} else if (buffer.zone == ZONA_SUR)
			{
				sprintf(zone,"ZONA SUR");
			} else {
				sprintf(zone,"ZONA OESTE");
			}
			if(buffer.status == TO_CHARGE)
			{
				sprintf(status,"A COBRAR");
			} else {
				sprintf(status,"COBRADA");
			}
			printf("\n%10d %15d %15d %15s %18s %30s\n",buffer.id,buffer.idClient,buffer.posterQty,zone,status,buffer.fileName);
			result = SUCCESS;
		}
	}
	return result;
}

/**
 * \brief Imprime una cabecera
 * \param void*
 * \return void Return
 */
void headerSale(void)
{
	printf("\n%10s %15s %15s %15s %18s %30s\n","ID","ID CLIENTE","CANT AFICHES","ZONA","ESTADO","NOMBRE ARCHIVO");
}

/**
 * \brief Busca un id del listado que se elija por parametro
 * \param list LinkedList* puntero al listado
 * \param id int id buscado
 * \param choiceList int eleccion del listado
 * \return void* Return puntero al elemento buscado
 * 					   NULL - Si el puntero a LikedList es NULL,o id invalido o id no encontrado
 */
void* findById(LinkedList* list, int id,int choiceList)
{
	void* result = NULL;
	void* pElement;
	int i;
	int bufferId;
	int resultAux;

	if(list != NULL && id > 0 && (choiceList == 1 || choiceList == 2))
	{
		for (i = 0; i < ll_len(list); i++)
		{
			if(choiceList == CLIENT)
			{
				pElement = (Client*)ll_get(list,i);
				resultAux = cli_getId(pElement,&bufferId);
			} else {
				pElement = (Sale*)ll_get(list,i);
				resultAux = sale_getId(pElement,&bufferId);
			}
			if(resultAux != ERROR && bufferId == id)
			{
				result = pElement;
				break;
			}
		}
	}
	return result;
}

/**
 * \brief Alta de ventas - Solicita los datos de los campos al usuario y lo añade a la lista
 * \param listSale LinkedList* puntero a lista ventas
 * \param listClient LinkedList* puntero a lista clientes
 * \return int Return   Sale* pSale - Puntero al elemento donde almaceno esa venta
 * 						NULL - ERROR - Si el puntero a LikedList es NULL, si no hay espacio en memoria para una venta
 * 								   o si el usuario completa erroneamente lo requerido o no lo puede agregar a la lista
 * 					               Si el id ingresado no existe
 */
Sale* sale_loadAndAddData(LinkedList* listSale, LinkedList* listClient)
{
	Sale* result = NULL;
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
					result = pSale;
				} else {
					sale_delete(pSale);
				}
			} else {
				sale_delete(pSale);
				printf("\nEl id ingresado no existe o ha ingresado incorrectamente lo requerido, vuelva a intentarlo\n");
			}
		}
	}
	return result;
}

/**
 * \brief Filtra la lista por estado y muestra las ventas.
 *		  Pide al usuario un id de venta y muestra el cliente a quien le pertenece
 *		  Llama a la funcion que permite elegir que modificar
 * \param listSale LinkedList* puntero a la lista de ventas
 * \param listClient LinkedList* puntero a la lista de clientes
 * \param pFunc (*pFunc) puntero a funcion que permite elegir que modificar
 * \param msj char* mensaje a mostrar para pedirle al usuario que es lo que debe ingresar
 * \param status int estado para filtrar la lista: a_cobrar o cobrada
 * \return Return (-1) Error - Si el puntero a LikedList es NULL o venta no encontrada
 * 				  (0) EXITO
 */
int sale_Edit(LinkedList* listSale, LinkedList* listClient, int (*pFunc)(Sale*,LinkedList*),char* msj,int status)
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
			if(ll_filter2(newList,sale_compareByStatus,&status) == SUCCESS
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
					if(pFunc(pSale,listClient)==SUCCESS)
					{
						result = SUCCESS;
					}
				}
			}
			ll_deleteLinkedList(newList);
		}
	}
	return result;
}

/**
 * \brief Modificar datos de la venta - Permite al usuario elegir que campo cambiar
 * \param listClient LinkedList* puntero a la lista de cliente
 * \param pSale Sale* puntero al elemento (venta a modificar)
 * \return Return (-1) Error - Si el puntero a LikedList es NULL o puntero a la venta es NULL
 * 				  (-2) Error - Si no pudo cambiar el id del cliente
 * 				  (-3) Error - Si no pudo cambiar la cantidad de afiches
 * 				  (-4) Error - Si no pudo cambiar el nombre de archivo
 * 				  (-5) Error - Si no pudo cambiar la zona
 * 				  (0) EXITO
 */
int sale_EditFields(Sale* pSale, LinkedList* listClient)
{
	int result = ERROR;
	int option;
	Sale buffer;

	if(pSale != NULL && listClient != NULL)
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
					if (utn_getNumber(&buffer.idClient, "\nIngrese el nuevo id del cliente: ", "\nError", 0, 999999, 3) == SUCCESS
							&& findById(listClient,buffer.idClient,CLIENT)!= NULL)
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
				}
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

/**
 * \brief Modificar el estado de la venta - Cambia el estado "COBRADA"
 * \param listClient LinkedList* puntero a la lista de cliente
 * \param pSale Sale* puntero al elemento (venta a modificar)
 * \return Return (-1) Error - Si el puntero a LikedList es NULL o puntero a la venta es NULL o si decidio no cobrar la venta
 * 				  (0) EXITO
 */
int sale_EditStatus(Sale* pSale, LinkedList* listClient)
{
	int result = ERROR;
	char bufferAnswer[10];

	if(pSale != NULL && listClient != NULL)
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

/*
 * \brief Compara un estado
 * \param this void* puntero a elemento
 * \return int Return (-1) ERROR - Si el puntero a void* es NULL
 * 					  (1) TRUE - si el estado es igual a "a cobrar"
 * 					  (0) FALSE - si el estado es igual a "cobrada"
 */
int sale_compareByStatus(void* this, void* arg)
{
	int returnAux = ERROR;
	Sale* status = (Sale*)this;
	int bufferStatus;
	int* statusToCompare = (int*)arg;

	if(this != NULL)
	{
		sale_getStatus(status,&bufferStatus);
		if(bufferStatus == (*statusToCompare))
		{
			returnAux = TRUE;
		} else {
			returnAux = FALSE;
		}
	}
	return returnAux;
}

/*
 * \brief Compara el id de un cliente con el id que recibe por argumento
 * \param this void* puntero a elemento
 * \return int Return La cantidad de afiches que tiene ese cliente
 */
int sale_compareQtyPoster(void* pElement, void* arg)
{
	Sale* pSale = (Sale*)pElement;
	int* idClient = (int*)arg;
	int bufferId;
	int qty = 0;

	sale_getIdClient(pSale, &bufferId);
	if((*idClient) == bufferId)
	{
		sale_getPosterQty(pSale, &qty);
	}
	return qty;
}

/************************** AGREGADAS *****************************/

int sale_sort(LinkedList* list,int option, int order)
{
	int result = ERROR;

	if((option == 1 || option == 2 || option == 3) && (order == 1 || order == 0))
	{
		switch (option)
		{
		case 1:
			result = ll_sort(list, sale_compareByPosterQty,order);
			break;
		case 2:
			result = ll_sort(list, sale_compareByFileName,order);
			break;
		case 3:
			result = ll_sort(list, sale_compareByZone,order);
			break;
		}
	}
	return result;
}

int sale_compareByPosterQty(void* first, void* second)
{
	int result = -2;
	int bufferFirstSale;
	int bufferSecondSale;

	if(first != NULL && second != NULL)
	{
		sale_getPosterQty((Sale*)first,&bufferFirstSale);
		sale_getPosterQty((Sale*)second,&bufferSecondSale);
		if(bufferFirstSale > bufferSecondSale)
		{
			result = 1;
		} else if (bufferFirstSale < bufferSecondSale) {
			result = -1;
		} else {
			result = 0;
		}
	}
	return result;
}

int sale_compareByFileName(void* first, void* second)
{
	int result = -2;
	char bufferFirstSale[NAME_LEN];
	char bufferSecondSale[NAME_LEN];
	int strCompare;

	if(first != NULL && second != NULL)
	{
		sale_getFileName((Sale*)first,bufferFirstSale);
		sale_getFileName((Sale*)second,bufferSecondSale);
		strCompare = strncasecmp(bufferFirstSale, bufferSecondSale, FILENAME_LEN);
		if(strCompare > 0)
		{
			result = 1;
		} else if (strCompare < 0) {
			result = -1;
		} else {
			result = 0;
		}
	}
	return result;
}

int sale_compareByZone(void* first, void* second)
{
	int result = -2;
	int bufferFirstSale;
	int bufferSecondSale;

	if(first != NULL && second != NULL)
	{
		sale_getZone((Sale*)first,&bufferFirstSale);
		sale_getZone((Sale*)second,&bufferSecondSale);
		if(bufferFirstSale > bufferSecondSale)
		{
			result = 1;
		} else if (bufferFirstSale < bufferSecondSale) {
			result = -1;
		} else {
			result = 0;
		}
	}
	return result;
}

int menuSortSale(void)
{
	int result = ERROR;
	int option;
	if (utn_getNumber(&option, "\n\nIngrese una opcion: "
						"\n1.Ordenar por Cantidad de afiches "
						"\n2.Ordenar por Nombre de archivo "
						"\n3.Ordenar por Zona "
						"\n4.Volver al menu principal\n",
						"Error, elija una opcion valida\n", 1, 4, 3) == SUCCESS)
	{
		result = option;
	}
	return result;
}

int sale_compareZoneAndPosterQty(void* first, void* second)
{
	int result = -2;
	int bufferFirstZone;
	int bufferSecondZone;
	int bufferFirstPosterQty;
	int bufferSecondPosterQty;
	if(first != NULL && second != NULL)
	{
		sale_getZone((Sale*)first,&bufferFirstZone);
		sale_getZone((Sale*)second,&bufferSecondZone);
		sale_getPosterQty((Sale*)first,&bufferFirstPosterQty);
		sale_getPosterQty((Sale*)second,&bufferSecondPosterQty);
		if(bufferFirstZone > bufferSecondZone
				|| (bufferFirstZone == bufferSecondZone && bufferFirstPosterQty > bufferSecondPosterQty))
		{
			result = -1;
		} else if (bufferFirstZone < bufferSecondZone
				|| (bufferFirstZone == bufferSecondZone && bufferFirstPosterQty < bufferSecondPosterQty))
		{
			result = 1;
		} else {
			result = 0;
		}
	}
	return result;
}

int sale_remove(LinkedList* listSale)
{
	int result = ERROR;
	int bufferId;
	Sale* pSale;
	char bufferAnswer[10];
	int index;

	if (listSale != NULL)
	{
		if (utn_getNumber(&bufferId , "\nIngrese el id de la venta que quiere eliminar: ", "\nError!", 0, 999999, 5) == SUCCESS)
		{
			pSale = findById(listSale,bufferId,SALE);
			if(pSale != NULL
					&& utn_getName(bufferAnswer, 10, "\n\nDesea borrar? Debe ingresar 'Si' para proceder con la baja: ",
					"\nError,ingrese una respuesta valida.", 3) == SUCCESS
					&& strncasecmp(bufferAnswer, "si", 10) == 0)
			{
					sale_delete(pSale);
					index = ll_indexOf(listSale,pSale);
					result = ll_remove(listSale,index);
			}
		}
	}
	return result;
}
