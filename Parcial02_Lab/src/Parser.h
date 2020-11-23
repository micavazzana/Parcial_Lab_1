/*
 * Parser.h
 *
 *  Created on: 21 nov. 2020
 *      Author: micavazzana
 */

#ifndef PARSER_H_
#define PARSER_H_
#include "Sale.h"
#include <stdio.h>

int parser_ClientFromText(FILE* pFile, LinkedList* listClient);
int parser_SaleFromText(FILE* pFile, LinkedList* listSale);
int parser_ClientToText(FILE* pFile, LinkedList* listClient);
int parser_SaleToText(FILE* pFile, LinkedList* listSale);
int parser_ClientQtySalesCharged(FILE* pFile, LinkedList* newList);

#endif /* PARSER_H_ */
