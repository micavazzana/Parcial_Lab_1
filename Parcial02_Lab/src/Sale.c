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
#include "validations.h"
#define ERROR -1
#define SUCCESS 0
#define TRUE 1
#define FALSE 0

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
		sale_getId(oneSale,&buffer.id);
		sale_getIdClient(oneSale,&buffer.idClient);
		sale_getPosterQty(oneSale,&buffer.posterQty);
		sale_getFileName(oneSale,buffer.fileName);
		sale_getZone(oneSale,&buffer.zone);
		sale_getStatus(oneSale,&buffer.status);
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

int sale_compareByStatus(void* this)
{
	int returnAux = ERROR;
	Sale* status = (Sale*)this;
	int buffer;

	if(this != NULL)
	{
		sale_getStatus(status,&buffer);
		if(buffer == TO_CHARGE)//a cobrar
		{
			returnAux = TRUE;
		} else {
			returnAux = FALSE;
		}
	}
	return returnAux;
}
