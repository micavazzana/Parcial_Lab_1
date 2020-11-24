/*
 * Controller.h
 *
 *  Created on: 21 nov. 2020
 *      Author: micavazzana
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "Parser.h"


typedef int (*parserFunction)(FILE*, LinkedList*);

int controller_loadOrSaveFromTxt(LinkedList* this, char* path,char* opentype,parserFunction pFunc);

#endif /* CONTROLLER_H_ */
