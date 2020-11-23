/*
 ============================================================================
 Name        : Parcial02_Lab.c
 Author      : micavazzana
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "inputs.h"
#include "LinkedList.h"
#include "Controller.h"
#define ERROR -1
#define SUCCESS 0
#define TRUE 1
#define FALSE 0

int main(void) {

	int option;
	LinkedList* listClient = ll_newLinkedList();
	LinkedList* listSale = ll_newLinkedList();
	void* pElement;
	int bufferId;

	if(controller_loadOrSaveFromTxt(listClient,"client.txt","r",parser_ClientFromText)==SUCCESS && controller_loadOrSaveFromTxt(listSale,"sales.txt","r",parser_SaleFromText) == SUCCESS)
	{
		do
		{
			if(utn_getNumber(&option,"\nIngrese una opcion: "
					"\n1. Agregar cliente"
					"\n2. Vender afiches"
					"\n3. Modificar venta"
					"\n4. Cobrar venta"
					"\n5. Generar informe de cobros"
					"\n6. Generar informe de deudas"
					"\n7. Generar estadísticas"
					"\n8. SALIR\n\n",
					"\nError, elija una opcion valida!",1,8,5)==SUCCESS)
			{
				switch(option)
				{
				case 1:
					switch(cli_loadAndAddData(listClient))
					{
					case SUCCESS:
						printf("\nAlta realizada con exito!\n\nSu carga:\n");
						pElement = ll_get(listClient,ll_len(listClient)-1);
						headerClient();
						cli_printOne(pElement);
						if(controller_loadOrSaveFromTxt(listClient,"client.txt","w",parser_ClientToText) == SUCCESS)
						{
							printf("\nGuardado con exito!\n");
						}
						break;
					case ERROR:
						printf("\nSe ha producido un error, vuelva a intentarlo\n");
						break;
					case -2:
						printf("\nEl cuit ingresado ya existe, vuelva a intentarlo\n");
						break;
					}
					break;
				case 2:
					switch(sale_loadAndAddData(listSale,listClient,&bufferId))
					{
					case SUCCESS:
						printf("\nAlta realizada con exito!\n");
						printf("\nID ASIGNADO: %d\nSu carga:\n",bufferId);
						pElement = ll_get(listSale,ll_len(listSale)-1);
						headerSale();
						sale_printOne(pElement);
						if(controller_loadOrSaveFromTxt(listSale,"sales.txt","w",parser_SaleToText) == SUCCESS)
						{
							printf("\nGuardado con exito!\n");
						}
						break;
					case ERROR:
						printf("\nSe ha producido un error, vuelva a intentarlo\n");
						break;
					case -2:
						printf("\nEl id ingresado no existe o ha ingresado incorrectamente lo requerido, vuelva a intentarlo\n");
						break;
					}
					break;
				case 3:
					if(sale_edit(listSale, listClient,sale_EditFields,"\nIngrese el id de la venta a modificar: ") == SUCCESS
							&& controller_loadOrSaveFromTxt(listSale,"sales.txt","w",parser_SaleToText) == SUCCESS)
					{
						printf("\nCambios realizados con exito\n");
					} else {
						printf("\nNo se pudieron guardar los cambios\n");
					}
					break;
				case 4:
					if(sale_edit(listSale, listClient,sale_EditStatus,"\nIngrese el id de la venta que quiere cobrar: ") == SUCCESS
							&& controller_loadOrSaveFromTxt(listSale,"sales.txt","w",parser_SaleToText) == SUCCESS)
					{
						printf("\nCobrada con exito\n");
					} else {
						printf("\nNo se pudo realizar el cobro\n");
					}
					break;
				case 5:
					cli_qtySalesByClient(listSale, listClient,CHARGED);
					break;
				case 6:
					cli_qtySalesByClient(listSale, listClient,TO_CHARGE);
					break;
				case 7:
					/*
					1 - si estado es cobrada - cuento cantidad de afiches por cada idCliente / listadoVentas / maximo //MOSTRAR CLIENTE
					2 - si estado es cobrada - cuento cantidad de afiches por cada idCliente / listadoVentas / minimo // MOSTRAR CLIENTE
					3 - MOSTRAR VENTA (maxima cantidad de adiches)*/
					//headerClient();
					//ll_map(listClient,cli_printOne);
					headerSale();
					ll_map(listSale,sale_printOne);
					break;
				case 8:
					printf("Hasta luego!");
					break;
				}
			}
		}while(option != 8);
	}
	return EXIT_SUCCESS;
}
