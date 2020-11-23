/*
 * Parser.c
 *
 *  Created on: 21 nov. 2020
 *      Author: micavazzana
 */
#include "Parser.h"

#define ERROR -1
#define SUCCESS 0

/** \brief Parsea los datos desde el archivo que recibe por parametro (modo texto).
 * \param pFile FILE* puntero al archivo a cargar
 * \param listClient LinkedList* puntero a la lista de clientes
 * \return int Return (-1) ERROR - Si el puntero a LikedList es NULL o si el puntero al archivo es NULL o si no pudo añadir el cliente a la lista
 * 					  (0) EXITO
 */
int parser_ClientFromText(FILE* pFile, LinkedList* listClient)
{
	int result = ERROR;
	char bufferId[150];
	char bufferName[150];
	char bufferLastName[150];
	char bufferCuit[150];
	Client* pClient;

	if(pFile != NULL && listClient != NULL)
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",bufferId,bufferName,bufferLastName,bufferCuit);
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",bufferId,bufferName,bufferLastName,bufferCuit) == 4)
			{
				pClient = cli_newParametros(bufferId,bufferName,bufferLastName,bufferCuit);
				if(pClient != NULL)
				{
					result = ll_add(listClient,pClient);
				}
			} else {
				result = ERROR;
				break;
			}
		}while(!feof(pFile));
	}
	return result;
}

/** \brief Parsea los datos desde el archivo que recibe por parametro (modo texto).
 * \param pFile FILE* puntero al archivo a cargar
 * \param listSale LinkedList* puntero a la lista de ventas
 * \return int Return (-1) ERROR - Si el puntero a LikedList es NULL o si el puntero al archivo es NULL o si no pudo añadir la venta a la lista
 * 					  (0) EXITO
 */
int parser_SaleFromText(FILE* pFile, LinkedList* listSale)
{
	int result = ERROR;
	char bufferId[150];
	char bufferIdClient[150];
	char posterQty[150];
	char fileName[150];
	char zone[150];
	char status[150];
	Sale* pSale;

	if(pFile != NULL && listSale != NULL)
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",bufferId,bufferIdClient,posterQty,fileName,zone,status);
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",bufferId,bufferIdClient,posterQty,fileName,zone,status) == 6)
			{
				pSale = sale_newParametros(bufferId,bufferIdClient,posterQty,fileName,zone,status);
				if(pSale != NULL)
				{
					result = ll_add(listSale,pSale);
				}
			} else {
				result = ERROR;
				break;
			}
		}while(!feof(pFile));
	}
	return result;
}

/**
 * \brief Escribe los datos de los clientes en el archivo que recibe por parametro(modo texto).
 * \param pFile FILE* puntero al archivo a cargar
 * \param listClient LinkedList* puntero a la lista de clientes
 * \return int Return (-1) ERROR - Si el puntero a LikedList es NULL o si el puntero al archivo es NULL o si no pudo escribir el cliente al archivo
 * 					  (0) EXITO
 */
int parser_ClientToText(FILE* pFile, LinkedList* listClient)
{
	int result = ERROR;
	Client* pClient;
	Client buffer;

	if(pFile != NULL && listClient != NULL)
	{
		fprintf(pFile,"ID,NOMBRE,APELLIDO,CUIT\n");
		for(int i = 0; i< ll_len(listClient);i++)
		{
			pClient = (Client*)ll_get(listClient,i);
			if(pClient != NULL
					&& cli_getId(pClient,&buffer.idClient) == SUCCESS
					&& cli_getName(pClient,buffer.name) == SUCCESS
					&& cli_getLastName(pClient,buffer.lastName) == SUCCESS
					&& cli_getCuit(pClient,buffer.cuit) == SUCCESS)
			{
				fprintf(pFile,"%d,%s,%s,%s\n",buffer.idClient,buffer.name,buffer.lastName,buffer.cuit);
			}
		}
		result = SUCCESS;
	}
	return result;
}

/**
 * \brief Escribe los datos de las ventas en el archivo que recibe por parametro(modo texto).
 * \param pFile FILE* puntero al archivo a cargar
 * \param listSale LinkedList* puntero lista de ventas
 * \return int Return (-1) ERROR - Si el puntero a LikedList es NULL o si el puntero al archivo es NULL o si no pudo escribir la venta al archivo
 * 					  (0) EXITO
 */
int parser_SaleToText(FILE* pFile, LinkedList* listSale)
{
	int result = ERROR;
	Sale* pSale;
	Sale buffer;

	if(pFile != NULL && listSale != NULL)
	{
		fprintf(pFile,"ID,ID CLIENTE,CANT AFICHES,NOMBRE ARCHIVO,ZONA,ESTADO\n");
		for(int i = 0; i< ll_len(listSale);i++)
		{
			pSale = (Sale*)ll_get(listSale,i);
			if(pSale != NULL
					&& sale_getId(pSale,&buffer.id) == SUCCESS
					&& sale_getIdClient(pSale,&buffer.idClient) == SUCCESS
					&& sale_getPosterQty(pSale,&buffer.posterQty) == SUCCESS
					&& sale_getFileName(pSale,buffer.fileName) == SUCCESS
					&& sale_getZone(pSale,&buffer.zone) == SUCCESS
					&& sale_getStatus(pSale,&buffer.status) == SUCCESS)
			{
				fprintf(pFile,"%d,%d,%d,%s,%d,%d\n",
						buffer.id,
						buffer.idClient,
						buffer.posterQty,
						buffer.fileName,
						buffer.zone,
						buffer.status);
			}
		}
		result = SUCCESS;
	}
	return result;
}

/**
 * \brief Escribe los datos de los clientes en el archivo que recibe por parametro(modo texto).
 * \param pFile FILE* puntero al archivo a cargar
 * \param listClient LinkedList* puntero a la lista de clientes
 * \return int Return (-1) ERROR - Si el puntero a LikedList es NULL o si el puntero al archivo es NULL o si no pudo escribir el cliente al archivo
 * 					  (0) EXITO
 */
int parser_qtySalesCharged(FILE* pFile, LinkedList* newList)
{
	int result = ERROR;
	Client* pClient;
	Client buffer;

	if(pFile != NULL && newList != NULL)
	{
		fprintf(pFile,"ID,NOMBRE,APELLIDO,CUIT,CANTIDAD VENTAS\n");
		for(int i = 0; i< ll_len(newList);i++)
		{
			pClient = (Client*)ll_get(newList,i);
			if(pClient != NULL
					&& cli_getId(pClient,&buffer.idClient) == SUCCESS
					&& cli_getName(pClient,buffer.name) == SUCCESS
					&& cli_getLastName(pClient,buffer.lastName) == SUCCESS
					&& cli_getCuit(pClient,buffer.cuit) == SUCCESS
					&& cli_getSalesByClient(pClient,&buffer.qtySalesByClient)==SUCCESS)
			{
				fprintf(pFile,"%d,%s,%s,%s,%d\n",buffer.idClient,buffer.name,buffer.lastName,buffer.cuit,buffer.qtySalesByClient);
			}
		}
		result = SUCCESS;
	}
	return result;
}
