/*
 * inputs.c
 *
 *  Created on: 18 sep. 2020
 *      Author: micavazzana
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stdio_ext.h>
#include "validations.h"
#define SUCCESS 0
#define ERROR -1

static int getString(char* string, int len);
static int getInt(int* integer);
static int getFloat(float * decimalNumber);
static int getText(char* text, int len);
static int getAlphaNumeric(char* text, int len);
static int getMail(char* text, int len);
static int getAlphanumericDots(char* text, int len);

//////////////Functions designed to request data from a user////////////////

int utn_getNumber(int *pNumber, char *message, char *errorMessage, int min,	int max, int retries)
{
    int result = ERROR;
    int auxInt;

    if (pNumber != NULL && message != NULL && errorMessage != NULL && min < max && max > min && retries > 0)
    {
        while (retries > 0)
        {
            printf("%s", message);
            if (getInt(&auxInt) == ERROR || (auxInt < min || auxInt > max))
            {
                printf("%s", errorMessage);
                retries--;
            }
            else
            {
                *pNumber = auxInt;
                result = SUCCESS;
                break;
            }
        }
    }
    return result;
}

int utn_getFloatNumber(float *pNumber, char *message, char *errorMessage,float min, float max, int retries)
{
    int result = ERROR;
    float auxFloat;

    if (pNumber != NULL && message != NULL && errorMessage != NULL && min < max	&& max > min && retries > 0)
    {
        while (retries > 0)
        {
            printf("%s", message);
            if (getFloat(&auxFloat) == ERROR || (auxFloat < min || auxFloat > max))
            {
                printf("%s", errorMessage);
                retries--;
            }
            else
            {
                *pNumber = auxFloat;
                result = SUCCESS;
                break;
            }
        }
    }
    return result;
}

int utn_getName(char* name, int len, char* message, char* errorMessage, int retries)
{
    int result = ERROR;
    char auxName[4096];

    if(name!=NULL && message!=NULL && errorMessage!=NULL && retries>0)
    {
        while(retries>0)
        {
            printf("%s",message);
            if(getText(auxName,sizeof(auxName))==SUCCESS && strnlen(auxName,sizeof(auxName))<len)
            {
                result = SUCCESS;
                strncpy(name,auxName,len);
                break;
            }
            else
            {
                printf("%s",errorMessage);
                retries--;
            }
        }
    }
    return result;
}

int utn_getAlphanumeric(char *name, int len, char *message, char *errorMessage, int retries)
{
    int result = ERROR;
    char auxName[4096];

    if (name != NULL && message != NULL && errorMessage != NULL && retries > 0)
    {
        while (retries > 0)
        {
            printf("%s", message);
            if (getAlphaNumeric(auxName, sizeof(auxName)) == SUCCESS && strnlen(auxName, sizeof(auxName)) < len)
            {
                result = SUCCESS;
                strncpy(name, auxName, len);
                break;
            }
            else
            {
                printf("%s", errorMessage);
                retries--;
            }
        }
    }
    return result;
}


int utn_getMail(char *name, int len, char *message, char *errorMessage, int retries)
{
    int result = ERROR;
    char auxName[4096];

    if (name != NULL && message != NULL && errorMessage != NULL	&& retries > 0)
    {
        while (retries > 0)
        {
            printf("%s", message);
            if (getMail(auxName, sizeof(auxName)) == SUCCESS && strnlen(auxName, sizeof(auxName)) < len)
            {
                result = SUCCESS;
                strncpy(name, auxName, len);
                break;
            }
            else
            {
                printf("%s", errorMessage);
                retries--;
            }
        }
    }
    return result;
}

int utn_getIdentityDocument(char *name, int len, char *message, char *errorMessage, int retries)
{
    int result = ERROR;
    char auxName[4096];

    if (name != NULL && message != NULL && errorMessage != NULL	&& retries > 0)
    {
        while (retries > 0)
        {
            printf("%s", message);
            if (getAlphanumericDots(auxName, sizeof(auxName)) == SUCCESS && strnlen(auxName, sizeof(auxName)) < len)
            {
                result = SUCCESS;
                strncpy(name, auxName, len);
                break;
            }
            else
            {
                printf("%s", errorMessage);
                retries--;
            }
        }
    }
    return result;
}


//////////////Functions that obtain data and validates that data////////////////

/**
 * \brief Gets a string of characters
 * \param char* string, pointer to the string where it leaves the obtained
 * \param int len, size of the string that it receives
 * \return (-1) ERROR (0) SUCCESS
 */
static int getString(char *string, int len)
{

    int result = ERROR;
    char aux[4096];

    if (string != NULL && len > 0)
    {
        //fflush(stdin); //WINDOWS
        //__fpurge(stdin); //LINUX
        fpurge(stdin); //MACOS
        fgets(aux, sizeof(aux), stdin);
        if(aux[strnlen(aux, sizeof(aux)) - 1] == '\n')
        {
            aux[strnlen(aux, sizeof(aux)) - 1] = '\0';
        }

        if(aux[0] == '\0')
        {
            result = ERROR;
        }
        else if(strnlen(aux, sizeof(aux)) <= len)
        {
            strncpy(string, aux, len);
            result = SUCCESS;
        }
    }
    return result;
}

/**
 * \brief Gets an integer and validates it
 * \param int* integer, pointer to the space where it leaves the obtained
 * \return (-1) ERROR (0) SUCCESS
 */
static int getInt(int* integer)
{
    int result = ERROR;
    char aux[4096];

    if(integer!=NULL)
    {
        if(getString(aux,sizeof(aux))== SUCCESS && isValidNumber(aux,sizeof(aux)))
        {
            *integer = atoi(aux);
            result = SUCCESS;
        }
    }
    return result;
}

/**
 * \brief Gets a decimal number and validates it
 * \param float* decimalNumber, pointer to the space where it leaves the obtained
 * \return (-1) ERROR (0) SUCCESS
 */
static int getFloat(float * decimalNumber)
{
    int result = ERROR;
    char aux[4096];

    if(decimalNumber!= NULL)
    {
        if(getString(aux,sizeof(aux))== SUCCESS && isValidNumberFloat(aux,sizeof(aux)))
        {
            *decimalNumber = atof(aux);
            result = SUCCESS;
        }
    }
    return result;
}

/**
 * \brief Gets a text of only letters and validates it
 * \param char* text, pointer to the space where it leaves the obtained
 * \return (-1) ERROR (0) SUCCESS
 */
static int getText(char* text, int len)
{
    int result = ERROR;
    char aux[4096];

    if(text!= NULL && len>0)
    {
        if(getString(aux,sizeof(aux))== SUCCESS && isValidLetters(aux,sizeof(aux)) && (strnlen(aux,sizeof(aux))<len))
        {
            strncpy(text,aux,len);
            result = SUCCESS;
        }
    }
    return result;
}

/**
 * \brief Gets a text of letters and numbers and validates it
 * \param char* text, pointer to the space where it leaves the obtained
 * \return (-1) ERROR (0) SUCCESS
 */
static int getAlphaNumeric(char* text, int len)
{
    int result = ERROR;
    char aux[4096];

    if(text!= NULL && len>0)
    {
        if(getString(aux,sizeof(aux))== SUCCESS && isValidAlphaNumeric(aux,sizeof(aux)) && (strnlen(aux,sizeof(aux))<len))
        {
            strncpy(text,aux,len);
            result = SUCCESS;
        }
    }
    return result;
}

/**
 * \brief Gets a text and validates it to match a valid e-mail
 * \param char* text, pointer to the space where it leaves the obtained
 * \return (-1) ERROR (0) SUCCESS
 */
static int getMail(char* text, int len)
{
    int result = ERROR;
    char aux[4096];

    if(text!= NULL && len>0)
    {
        if(getString(aux,sizeof(aux))== SUCCESS && isValidMail(aux,sizeof(aux)) && (strnlen(aux,sizeof(aux))<len))
        {
            strncpy(text,aux,len);
            result = SUCCESS;
        }
    }
    return result;
}

/**
 * \brief Gets a text and validates it to allow letters, numbers, dots and hyphens
 * \param char* text, pointer to the space where it leaves the obtained
 * \return (-1) ERROR (0) SUCCESS
 */
static int getAlphanumericDots(char* text, int len)
{
    int result = ERROR;
    char aux[4096];

    if(text!= NULL && len>0)
    {
        if(getString(aux,sizeof(aux))== SUCCESS && isValidDocumentNumber(aux,sizeof(aux)) && (strnlen(aux,sizeof(aux))<len))
        {
            strncpy(text,aux,len);
            result = SUCCESS;
        }
    }
    return result;
}
