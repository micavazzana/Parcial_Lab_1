/*
 * allFunctions.h
 *
 *  Created on: 11 oct. 2020
 *      Author: micavazzana
 */

#ifndef CLIENTPUBLICATION_H_
#define CLIENTPUBLICATION_H_
#include "inputs.h"
#include "Publication.h"

int client_removeClient(Client* listClient,int lenClient, Publication* listPublication, int lenPubli);
int client_printClientInformation(Publication *listPublication, int lenPubli, Client* listClient, int lenClient, int id);
int publication_pause(Client* listClient,int lenClient, Publication* listPublication, int lenPubli);
int publication_reactivate(Client* listClient,int lenClient, Publication* listPublication, int lenPubli);

int clientPublication_printClientAndPublications(Publication *listPublication, int lenPubli, Client* listClient, int lenClient);
int clientPublication_printActivePublicationsById(Publication *listPublication, int lenPubli, int id, int* contador);

#endif /* CLIENTPUBLICATION_H_ */
