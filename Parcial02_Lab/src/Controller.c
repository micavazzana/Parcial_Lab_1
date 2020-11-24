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
