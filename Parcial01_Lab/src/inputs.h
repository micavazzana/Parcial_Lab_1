/*
 * inputs.h
 *
 *  Created on: 18 sep. 2020
 *      Author: micavazzana
 */

#ifndef INPUTS_H_
#define INPUTS_H_

/**
 * \brief Requests the user to enter a number (integer)
 * \param int *pNumber, pointer to the space where the value obtained will be left
 * \param char *message, message to be shown to the user
 * \param char *errorMessage, message to be shown to the user
 * \param int min, minimum value allowed
 * \param int max, maximum value allowed
 * \param int retries, number of opportunities to enter the data
 * \return (-1) ERROR (0) SUCCESS
 */
int utn_getNumber(int* pNumber, char* message, char* errorMessage, int min, int max,int retries);

/**
 * \brief Requests the user to enter a number (decimal number)
 * \param float *pNumber, pointer to the space where the value obtained will be left
 * \param char *message, message to be shown to the user
 * \param char *errorMessage, message to be shown to the user
 * \param float min, minimum value allowed
 * \param float max, maximum value allowed
 * \param int retries, number of opportunities to enter the data
 * \return (-1) ERROR (0) SUCCESS
 */
int utn_getFloatNumber(float *pNumber, char *message, char *errorMessage, float min, float max, int retries);

/**
 * \brief Requests the user to enter a string (only letters)
 * \param char *name, pointer to the space where the value obtained will be left
 * \param int len, size of name
 * \param char *message, message to be shown to the user
 * \param char *errorMessage, message to be shown to the user
 * \param int retries, number of opportunities to enter the data
 * \return (-1) ERROR (0) SUCCESS
 */
int utn_getName(char* name, int len, char* message, char* errorMessage, int retries);

/**
 * \brief Requests the user to enter a string (letters or numbers)
 * \param char *name, pointer to the space where the value obtained will be left
 * \param int len, size of name
 * \param char *message, message to be shown to the user
 * \param char *errorMessage, message to be shown to the user
 * \param int retries, number of opportunities to enter the data
 * \return (-1) ERROR (0) SUCCESS
 */
int utn_getAlphanumeric(char* name, int len, char* message, char* errorMessage, int retries);

/**
 * \brief Requests the user to enter a e-mail domain
 * \param char *name, pointer to the space where the value obtained will be left
 * \param int len, size of name
 * \param char *message, message to be shown to the user
 * \param char *errorMessage, message to be shown to the user
 * \param int retries, number of opportunities to enter the data
 * \return (-1) ERROR (0) SUCCESS
 */
int utn_getMail(char *name, int len, char *message, char *errorMessage, int retries);

/**
 * \brief Requests the user to enter a id card number. It can be used for web domains as well.
 * \param char *name, pointer to the space where the value obtained will be left
 * \param int len, size of name
 * \param char *message, message to be shown to the user
 * \param char *errorMessage, message to be shown to the user
 * \param int retries, number of opportunities to enter the data
 * \return (-1) ERROR (0) SUCCESS
 */
int utn_getIdentityDocument(char *name, int len, char *message, char *errorMessage, int retries);


#endif /* INPUTS_H_ */
