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
#define SUCCESS 0
#define ERROR -1

static int getString(char* string, int len);
static int getInt(int* integer);
static int getFloat(float * decimalNumber);
static int getText(char* text, int len);
static int getAlphaNumeric(char* text, int len);
static int getMail(char* text, int len);
static int getAlphanumericDots(char* text, int len);
static int validationInt(char* num);
static int validationFloat(char* num);
static int validationOnlyLetter(char* string);
static int validationAlphaNumeric(char* string);
static int validationMail(char* string);
static int validationAlphanumericDots(char* string);


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
			} else {
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
			} else {
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
			} else {
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
			} else {
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
			} else {
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
static int getString(char *string, int len) {

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
        if(getString(aux,sizeof(aux))== SUCCESS && validationInt(aux) == SUCCESS)
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
        if(getString(aux,sizeof(aux))== SUCCESS && validationFloat(aux) == SUCCESS)
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
        if(getString(aux,sizeof(aux))== SUCCESS && validationOnlyLetter(aux) == SUCCESS && (strnlen(aux,sizeof(aux))<len))
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
        if(getString(aux,sizeof(aux))== SUCCESS && validationAlphaNumeric(aux) == SUCCESS && (strnlen(aux,sizeof(aux))<len))
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
        if(getString(aux,sizeof(aux))== SUCCESS && validationMail(aux) == SUCCESS && (strnlen(aux,sizeof(aux))<len))
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
        if(getString(aux,sizeof(aux))== SUCCESS && validationAlphanumericDots(aux) == SUCCESS && (strnlen(aux,sizeof(aux))<len))
        {
            strncpy(text,aux,len);
            result = SUCCESS;
        }
    }
    return result;
 }


//////////////Functions that validates data////////////////

/**
 * \brief Validates that what it receives is a number.
 * 		  Contemplates both negatives and positives.
 * \param char *num, pointer to the string to be validated
 * \return (-1) ERROR (0) SUCCESS
 */
static int validationInt(char* num)
{
    int result = SUCCESS;
    int i = 0;

    if(num!= NULL)
    {
        if(num[0] == '-' || num[0] == '+')
        {
            i = 1;
        }
        for( ; num[i]!= '\0'; i++)
        {
            if(num[i] < '0' || num[i] > '9')
            {
            	result = ERROR;
                break;
            }
        }
    }
    return result;
}

/**
 * \brief Validates that what it receives is a number.
 * 		  Contemplates both negative and positive and decimal.
 * \param char *num, pointer to the string to be validated
 * \return (-1) ERROR (0) SUCCESS
 */
static int validationFloat(char* num)
{
    int result = SUCCESS;
    int i = 0;
    int counterDot = 0;

    if(num!= NULL)
    {
        if(num[0] == '-' || num[0] == '+')
        {
            i = 1;
        }
        for( ; num[i]!= '\0'; i++)
        {
            if(num[i] < '0' || num[i] > '9')
            {
                if(num[i] == '.')
                {
                	counterDot++;
                    if(counterDot>1)
                    {
                    	result = ERROR;
                        break;
                    }
                }
                else
                {
                	result = ERROR;
                    break;
                }
            }
        }
    }
    return result;
}

/**
 * \brief Valida que lo recibe sea una letra.
 * 		  Contempla espacios.
 * 		  Validates that what you receive it is a letter.
 * 		  Contemplates spaces.
 * \param char *string, puntero a la cadena que se busca validar // pointer to the string to be validated
 * \return (-1) ERROR (0) EXITO // (-1) ERROR (0) SUCCESS
 */
static int validationOnlyLetter(char* string)
{
    int i ;
    int result = SUCCESS;

    if(string!= NULL)
    {
    	for(i=0; string[i]!= '\0'; i++)
		{
			if((string[i] < 'a' || string [i] > 'z') && (string[i] < 'A' || string[i] > 'Z') && (string[i] != ' '))
			{
				result = ERROR;
				break;
			}
		}
    }
    return result;
}

/**
 * \brief Validates that what you receive it is a letter or a number.
 * 		  Contemplates spaces.
 * \param char *string, pointer to the string to be validated
 * \return (-1) ERROR (0) SUCCESS
 */
static int validationAlphaNumeric(char* string)
{
    int i ;
    int result = SUCCESS;

    if(string!= NULL)
    {
    	for(i=0; string[i]!= '\0'; i++)
		{
			if((string[i] < 'a' || string [i] > 'z') && (string[i] < 'A' || string[i] > 'Z') && (string[i] != ' ') && (string[i] < '0' || string[i] > '9'))
			{
				result = ERROR;
				break;
			}
		}
    }
    return result;
}

/**
 * \brief Validates that what you receive it is a valid mail.
 * \param char *string, pointer to the string to be validated
 * \return (-1) ERROR (0) SUCCESS
 */
static int validationMail(char* string)
{
    int i ;
    int result = SUCCESS;
    int counterAt=0;

    if(string!= NULL)
    {
    	for(i=0; string[i]!= '\0'; i++)
		{
    		if((string[i] < 'a' || string [i] > 'z') && (string[i] < 'A' || string[i] > 'Z')  && (string[i] < '0' || string[i] > '9')
    							&& (string[i] != '.' || string[0] == '.') && (string[i] != '-' || string[0] == '-') && (string[i] != '_' || string[0] == '_'))
			{
    			if(string[i] == '@')
				{
					counterAt++;
					if(counterAt>1 || string[0] == '@')
					{
						result = ERROR;
						break;
					}
				}
				else
				{
					result = ERROR;
					break;
				}
			}
		}
    }
    return result;
}

/**
 * \brief Validates that what you receive it is valid to a letter, number, dot or hyphen.
 * \param char *string, pointer to the string to be validated
 * \return (-1) ERROR (0) SUCCESS
 */
static int validationAlphanumericDots(char* string)
{
    int i ;
    int result = SUCCESS;

    if(string!= NULL)
    {
    	for(i=0; string[i]!= '\0'; i++)
		{
			if((string[i] < 'a' || string [i] > 'z') && (string[i] < 'A' || string[i] > 'Z')  && (string[i] < '0' || string[i] > '9')
					&& (string[i] != '.' || string[0] == '.') && (string[i] != '-' || string[0] == '-'))
			{
				result = ERROR;
				break;
			}
		}
    }
    return result;
}
