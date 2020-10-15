/*
 ============================================================================
 Name        : Parcial01_Lab.c
 Author      : micavazzana
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inform.h"
#define QTY_CLIENT 100
#define QTY_PUBLICATION 1000

int main(void) {

	int option;
	Client listClient[QTY_CLIENT];
	Publication listPublication[QTY_PUBLICATION];
	int resultFunc;
	int qtyAds;

	if(cli_initArray(listClient,QTY_CLIENT) == SUCCESS && publi_initArray(listPublication,QTY_PUBLICATION) == SUCCESS)
	{
		cli_hardCodeData(listClient);
		publi_hardCodeData(listPublication);
		do
		{
			if(utn_getNumber(&option,
					"\n\nIngrese una opcion: \n"
					"\n1. Alta cliente"
					"\n2. Modificar datos del cliente"
					"\n3. Baja de cliente y sus publicaciones"
					"\n4. Crear publicacion"
					"\n5. Pausar publicacion"
					"\n6. Reanudar publicacion"
					"\n7. Imprimir clientes"
					"\n8. Informar"
					"\n9. SALIR\n\n","\nError! elija una opcion valida",1,9,5)==SUCCESS)
			{
				switch(option)
				{
				case 1:
					resultFunc = cli_loadAndAddData(listClient, QTY_CLIENT);
					if (resultFunc >= 0) {
						printf("\nCarga realizada con exito! Su carga: \n\n%10s %15s %15s %35s\n", "ID CLIENTE", "NOMBRE", "APELLIDO","CUIT");
						cli_printOne(listClient[resultFunc]);
					} else if (resultFunc == ERROR) {
						printf("\nYa no hay lugar!\n");
					} else {
						printf("\nSe acabaron sus reintentos, vuelva a ingresar");
					}
					break;
				case 2:
					if (cli_isAnyData(listClient,QTY_CLIENT)) {
						switch (cli_modify(listClient, QTY_CLIENT)) {
						case SUCCESS:
							printf("\nModificacion realizada con exito\n");
							break;
						case ERROR:
							printf("\nNo existen clientes con ese ID, o no ha hecho modificaciones. Vuelva a intentarlo\n");
							break;
						case -2:
							printf("\nNo pudo realizar el cambio de nombre. Vuelva a intentarlo\n");
							break;
						case -3:
							printf("\nNo pudo realizar el cambio de apellido. Vuelva a intentarlo\n");
							break;
						case -4:
							printf("\nNo pudo realizar el cambio de cuit. Vuelva a intentarlo\n");
							break;
						}
					} else {
						printf("\nDebe cargar clientes primero\n");
					}
					break;
				case 3:
					if (cli_isAnyData(listClient, QTY_CLIENT) && client_removeClient(listClient, QTY_CLIENT,listPublication, QTY_PUBLICATION) == SUCCESS) {
						printf("\nBaja realizada con exito!\n");
					} else {
						printf("\nDebe cargar clientes primero, o ha ingresado un id invalido o no se ha procedido con la baja\n");
					}
					break;
				case 4:
					if (cli_isAnyData(listClient, QTY_CLIENT)) {
						resultFunc = publi_loadAndAddData(listPublication, QTY_PUBLICATION,listClient, QTY_CLIENT);
						if (resultFunc >=0) {
							printf("\nCarga realizada con exito! Su carga: \n\n%10s %15s %15s %35s %20s\n", "ID PUBLI", "RUBRO", "ID CLIENTE", "TEXTO AVISO", "ESTADO");
							publi_printOne(listPublication[resultFunc]);
						} else if (resultFunc == ERROR) {
							printf("\nYa no hay lugar!\n");
						} else {
							printf("\nSe acabaron sus reintentos, vuelva a ingresar");
						}
					} else {
						printf("\nDebe cargar clientes primero.\n");
					}
					break;
				case 5:
					if(publi_isAnyData(listPublication, QTY_PUBLICATION))
					{
						if(publi_qtyPublications(listPublication,QTY_PUBLICATION, &qtyAds,ACTIVE)==SUCCESS && qtyAds > 0
								&& publication_pause(listClient, QTY_CLIENT,listPublication, QTY_PUBLICATION) == SUCCESS)
						{
							printf("Publicacion pausada con exito");
						} else if (qtyAds == 0) {
							printf("No hay publicaciones activas para pausar");
						} else {
							printf("\nHa decidido no pausar la publicacion, o ha ingresado erroneamente el id, o la publicacion ya se encuentra pausada.\n");
						}
					} else {
						printf("\nDebe cargar publicaciones primero");
					}
					break;
				case 6:
					if(publi_isAnyData(listPublication, QTY_PUBLICATION))
					{
						if(publi_qtyPublications(listPublication,QTY_PUBLICATION, &qtyAds,PAUSED)==SUCCESS && qtyAds > 0
								&& publication_reactivate(listClient, QTY_CLIENT,listPublication, QTY_PUBLICATION) == SUCCESS)
						{
							printf("Publicacion activada con exito");
						} else if (qtyAds == 0) {
							printf("No hay publicaciones pausadas para reactivar");
						} else {
							printf("\nHa decidido no activar la publicacion, o ha ingresado erroneamente el id, o la publicacion ya se encuentra activa.\n");
						}
					} else {
						printf("\nDebe cargar publicaciones primero");
					}
					break;
				case 7:
					if(publi_isAnyData(listPublication, QTY_PUBLICATION) && cli_isAnyData(listClient, QTY_CLIENT)) {
						clientPublication_printClientAndPublications(listPublication, QTY_PUBLICATION,listClient, QTY_CLIENT);
					}  else {
					printf("\nDebe cargar datos primero");
					}
					break;
				case 8:
					if (publi_isAnyData(listPublication, QTY_PUBLICATION) && cli_isAnyData(listClient, QTY_CLIENT)) {
						info_subMenu(listPublication, QTY_PUBLICATION, listClient, QTY_CLIENT);
					} else {
						printf("\nDebe cargar datos primero");
					}
					break;
				case 9:
					printf("\nHasta luego!");
					break;
				}
			} else {
				printf("\nSe acabaron sus reintentos, vuelva a ingresar");
			}
		}while(option!=9);
	} else {
		printf("No se pudo iniciar el programa.");
	}
	return EXIT_SUCCESS;
}
