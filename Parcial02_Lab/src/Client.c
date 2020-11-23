/*
 * Client.c
 *
 *  Created on: 21 nov. 2020
 *      Author: micavazzana
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Client.h"
#include "validations.h"
#define ERROR -1
#define SUCCESS 0
#define TRUE 1
#define FALSE 0

/*
 * \brief Pide memoria para un nuevo cliente
 * \param void
 * \return int Return puntero con espacio de memoria con tipo Client*
 */
Client* cli_new(void)
{
	return (Client*) malloc(sizeof(Client));
}

/*
 * \brief Pide memoria para un nuevo cliente y setea los campos en el espacio de memoria requerido
 * \param idStr char* id que va a setear
 * \param nameStr char* nombre que va a setear
 * \param lastNameStr char* apellido que va a setear
 * \param cuitStr char* cuit que va a setear
 * \return int Return puntero con espacio de memoria con tipo Client* con los campos ya seteados
 */
Client* cli_newParametros(char* idStr,char* nameStr,char* lastNameStr, char* cuitStr)
{
	Client* pClient = NULL;

	if (idStr != NULL && nameStr != NULL && lastNameStr != NULL && cuitStr != NULL)
	{
		pClient = cli_new();
		if (pClient != NULL)
		{
			cli_setIdTxt(pClient,idStr);
			cli_setName(pClient,nameStr);
			cli_setLastName(pClient,lastNameStr);
			cli_setCuit(pClient,cuitStr);
		}
	}
	return pClient;
}

/*
 * \brief Libera espacio de memoria de un cliente
 * \param this Client* puntero a cliente
 * \return void
 */
void cli_delete(Client* this)
{
	free(this);
}

/*
 * \brief Carga el id en el campo del cliente
 * \param this Client* puntero a cliente
 * \param id int id a cargar
 * \return int Return (-1) ERROR - Si el puntero a Client* es NULL o si el id no es valido
 * 					  (0) EXITO
 */
int cli_setId(Client* this,int id)
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
 * \param this Client* puntero a cliente
 * \param id int* puntero al espacio donde va a guardar el id obtenido
 * \return int Return (-1) ERROR - Si el puntero a Client* es NULL o si e puntero al id es NULL
 * 					  (0) EXITO
 */
int cli_getId(Client* this,int* id)
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
 * \brief Carga el id en el campo del cliente (tratado como texto) y valida que el dato sea correcto
 * \param this Client* puntero a cliente
 * \param id char* puntero al id que va a cargar
 * \return int Return (-1) ERROR - Si el puntero a Client* es NULL o si e puntero al id es NULL
 * 					  (0) EXITO
 */
int cli_setIdTxt(Client* this, char* id)
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
 * \param this Client* puntero a empleado
 * \param id char* puntero al espacio donde va a guardar el id obtenido
 * \return int Return (-1) ERROR - Si el puntero a Client* es NULL o si e puntero al id es NULL
 * 					  (0) EXITO
 */
int cli_getIdTxt(Client* this, char* id)
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
 * \brief Carga el nombre en el campo del cliente y valida que el dato sea correcto
 * \param this Client* puntero a cliente
 * \param name char* puntero al nombre que va a cargar
 * \return int Return (-1) ERROR - Si el puntero a Client* es NULL o si e puntero al nombre es NULL
 * 					  (0) EXITO
 */
int cli_setName(Client* this, char* name)
{
	int result = ERROR;
	if (this != NULL && name != NULL && isValidCompoundName(name, NAME_LEN))
	{
		strncpy(this->name, name, NAME_LEN);
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Obtiene el nombre del cliente
 * \param this Client* puntero a cliente
 * \param name char* puntero al espacio donde va a guardar el nombre obtenido
 * \return int Return (-1) ERROR - Si el puntero a Client* es NULL o si e puntero al nombre es NULL
 * 					  (0) EXITO
 */
int cli_getName(Client* this, char* name)
{
	int result = ERROR;
	if (this != NULL && name != NULL)
	{
		strncpy(name, this->name, NAME_LEN);
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Carga el apellido en el campo del cliente y valida que el dato sea correcto
 * \param this Client* puntero a cliente
 * \param lastName char* puntero al apellido que va a cargar
 * \return int Return (-1) ERROR - Si el puntero a Client* es NULL o si e puntero al apellido es NULL
 * 					  (0) EXITO
 */
int cli_setLastName(Client* this, char* lastName)
{
	int result = ERROR;
	if (this != NULL && lastName != NULL && isValidCompoundName(lastName, NAME_LEN))
	{
		strncpy(this->lastName, lastName, NAME_LEN);
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Obtiene el apellido del cliente
 * \param this Client* puntero a cliente
 * \param lastName char* puntero al espacio donde va a guardar el apellido obtenido
 * \return int Return (-1) ERROR - Si el puntero a Client* es NULL o si e puntero al apellido es NULL
 * 					  (0) EXITO
 */
int cli_getLastName(Client* this, char* lastName)
{
	int result = ERROR;
	if (this != NULL && lastName != NULL)
	{
		strncpy(lastName, this->lastName, NAME_LEN);
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Carga el cuit en el campo del cliente y valida que el dato sea correcto
 * \param this Client* puntero a cliente
 * \param cuit char* puntero al cuit que va a cargar
 * \return int Return (-1) ERROR - Si el puntero a Client* es NULL o si e puntero al cuit es NULL
 * 					  (0) EXITO
 */
int cli_setCuit(Client* this, char* cuit)
{
	int result = ERROR;
	if (this != NULL && cuit != NULL && isValidDocumentNumber(cuit, NAME_LEN))
	{
		strncpy(this->cuit, cuit, CUIT_LEN);
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Obtiene el cuit del cliente
 * \param this Client* puntero a cliente
 * \param cuit char* puntero al espacio donde va a guardar el cuit obtenido
 * \return int Return (-1) ERROR - Si el puntero a Client* es NULL o si e puntero al cuit es NULL
 * 					  (0) EXITO
 */
int cli_getCuit(Client* this, char* cuit)
{
	int result = ERROR;
	if (this != NULL && cuit != NULL)
	{
		strncpy(cuit, this->cuit, CUIT_LEN);
		result = SUCCESS;
	}
	return result;
}

int cli_setSalesByClient(Client* this,int qty)
{
	int result = ERROR;
	if (this != NULL && qty >= 0)
	{
		this->qtySalesByClient = qty;
		result = SUCCESS;
	}
	return result;
}

/*
 * \brief Obtiene el id del cliente
 * \param this Client* puntero a cliente
 * \param id int* puntero al espacio donde va a guardar el id obtenido
 * \return int Return (-1) ERROR - Si el puntero a Client* es NULL o si e puntero al id es NULL
 * 					  (0) EXITO
 */
int cli_getSalesByClient(Client* this,int* qty)
{
	int result = ERROR;
	if (this != NULL && qty != NULL)
	{
		*qty = this->qtySalesByClient;
		result = SUCCESS;
	}
	return result;
}

/**
 * \brief Imprime los datos de un cliente
 * \param this void* puntero a void
 * \return int Return (-1) ERROR - Si el puntero a void es NULL
 *					  (0) EXITO
 */
int cli_printOne(void* this)
{
	int result = ERROR;
	Client* oneClient;
	Client buffer;

	if(this != NULL)
	{
		oneClient = (Client*)this;
		cli_getId(oneClient,&buffer.idClient);
		cli_getName(oneClient,buffer.name);
		cli_getLastName(oneClient,buffer.lastName);
		cli_getCuit(oneClient,buffer.cuit);
		printf("\n%10d %15s %15s %15s\n",buffer.idClient,buffer.name,buffer.lastName,buffer.cuit);
		result = SUCCESS;
	}
	return result;
}

/**
 * \brief Imprime una cabecera
 * \param void*
 * \return void Return
 */
void headerClient(void)
{
	printf("\n%10s %15s %15s %15s\n","ID","NOMBRE","APELLIDO","CUIT");
}
