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
 * \brief Recibe el puntero al elemento y lo añade a la lista
 * \param list LinkedList* puntero a la lista
 * \param pElement void* puntero a elemento
 * \return int Return (-1) ERROR - Si el puntero a LikedList es NULL o si el puntero al elemento es NULL
 * 					  (0) EXITO
 */
int controller_add(LinkedList* list,void* pElement)
{
	int result = ERROR;

	if(list != NULL && pElement != NULL)
	{
		result = ll_add(list, pElement);
	}
	return result;
}

/**
 * \brief Muestra el listado que decide por parametro y realiza una baja
 * \param list LinkedList* puntero al array de empleados
 * \param pFuncRemove (*pFunc)- puntero a la funcion que hace un remove
 * \param pFuncHeader (*pFunc)- puntero a la funcion que imprime una cabecera
 * \param pFuncPrint (*pFunc)- puntero a la funcion que imprime un elemento
 * \return int Return (-1) ERROR - Si el puntero a LikedList es NULL o los punteros a las funciones son NULL
 *					  (0) EXITO
 */
int controller_remove(LinkedList* list, int (*pFuncRemove)(LinkedList*),void (*pFuncHeader)(void),int (*pFuncPrint)(void*))
{
	int result = ERROR;
	if(list != NULL && pFuncRemove != NULL && pFuncHeader != NULL && pFuncPrint != NULL)
	{
		controller_list(list,pFuncHeader,pFuncPrint);
		result = pFuncRemove(list);
	}
	return result;
}

/**
 * \brief Listar - Imprime los datos del listado que se decida mostrar
 * \param list LinkedList* puntero al listado
 * \param pFuncHeader (*pFunc)- puntero a la funcion que imprime una cabecera
 * \param pFuncPrint (*pFunc)- puntero a la funcion que imprime un elemento
 * \return int Return (-1) ERROR - Si el puntero a LikedList es NULL o el puntero a las funciones son NULL
 *					  (0) EXITO
 */
int controller_list(LinkedList* list, void (*pFuncHeader)(void),int (*pFuncPrint)(void*))
{
	int result = ERROR;
	if(list != NULL && pFuncHeader != NULL && pFuncPrint != NULL)
	{
		pFuncHeader();
		ll_map(list,pFuncPrint);
		result = SUCCESS;
	}
	return result;
}

/** \brief Ordenar - Permite al usuario elegir que criterio utilizar para ordenar
 * 					y si quiere realizarlo de manera ascendente o descendente
 * \param list LinkedList* puntero al listado
 * \param pFuncMenu (*pFunc)- puntero a la funcion que imprime un menu de opciones
 * \param pFuncSort (*pFunc)- puntero a la funcion que ordena segun el criterio elegido
 * \return int Return (-1) ERROR - Si el puntero a LikedList es NULL o no pudo realizar el ordenamiento
 *					  (0) EXITO
 */
int controller_sort(LinkedList* list, int (*pFuncMenu)(void),int (*pFuncSort)(LinkedList*,int, int))
{
	int result = ERROR;
	int order;
	int option;

	if (list != NULL && pFuncMenu != NULL && pFuncSort != NULL)
	{
		do
		{
			option = pFuncMenu();
			if (option != 4 &&
					utn_getNumber(&order,"\nIngrese el criterio con el que desea ordenar [1-ASCENDENTE/0-DESCEDENTE]: ",
						"\nError, debe ingresar o 0 o 1",0,1,3)==SUCCESS)
			{
				pFuncSort(list,option,order);
				result = SUCCESS;
			}
		} while (option != 4);
	}
	return result;
}
