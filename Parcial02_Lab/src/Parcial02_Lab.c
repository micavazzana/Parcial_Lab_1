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
#include "inform.h"

int main(void) {

	int option;
	LinkedList* listClient = ll_newLinkedList();
	LinkedList* listSale = ll_newLinkedList();
	void* pElement;
	int bufferId;

	if(controller_loadOrSaveFromTxt(listClient,"client.txt","r",parser_ClientFromText)==SUCCESS
			&& controller_loadOrSaveFromTxt(listSale,"sales.txt","r",parser_SaleFromText) == SUCCESS)
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
					pElement = cli_loadAndAddData(listClient);
					if(controller_add(listClient, pElement)==SUCCESS)
					{
						printf("\nAlta realizada con exito!\nSu carga:\n");
						headerClient();
						cli_printOne(pElement);
						if(controller_loadOrSaveFromTxt(listClient,"client.txt","w",parser_ClientToText) == SUCCESS)
						{
							printf("\nGuardado con exito!\n");
						}
					} else {
						printf("\nSe ha producido un error, vuelva a intentarlo\n");
					}
					break;
				case 2:
					pElement = sale_loadAndAddData(listSale, listClient);
					if(controller_add(listSale, pElement)==SUCCESS)
					{
						printf("\nAlta realizada con exito!\n");
						sale_getId(pElement,&bufferId);
						printf("\nID ASIGNADO: %d\nSu carga:\n",bufferId);
						headerSale();
						sale_printOne(pElement);
						if(controller_loadOrSaveFromTxt(listSale,"sales.txt","w",parser_SaleToText) == SUCCESS)
						{
							printf("\nGuardado con exito!\n");
						}
					} else {
						printf("\nSe ha producido un error, vuelva a intentarlo\n");
					}
					break;
				case 3:
					if(sale_Edit(listSale, listClient,sale_EditFields,"\nIngrese el id de la venta a modificar: ",TO_CHARGE) == SUCCESS
							&& controller_loadOrSaveFromTxt(listSale,"sales.txt","w",parser_SaleToText) == SUCCESS)
					{
						printf("\nCambios realizados con exito\n");
					} else {
						printf("\nNo se pudieron guardar los cambios\n");
					}
					break;
				case 4:
					if(sale_Edit(listSale, listClient,sale_EditStatus,"\nIngrese el id de la venta que quiere cobrar: ",TO_CHARGE) == SUCCESS
							&& controller_loadOrSaveFromTxt(listSale,"sales.txt","w",parser_SaleToText) == SUCCESS)
					{
						printf("\nCobrada con exito\n");
					} else {
						printf("\nNo se pudo realizar el cobro\n");
					}
					break;
				case 5:
					if(info_qtySalesByClient(listSale, listClient,CHARGED,cli_setQtySalesCharged) == SUCCESS
							&& controller_loadOrSaveFromTxt(listClient,"cobradas.txt","w",parser_ClientQtySalesCharged) == SUCCESS)
					{
						printf("\nArchivo guardado con exito\n");
					} else {
						printf("\nNo se pudo guardar el archivo\n");
					}
					break;
				case 6:
					if(info_qtySalesByClient(listSale, listClient,TO_CHARGE,cli_setQtySalesToCharge) == SUCCESS
							&& controller_loadOrSaveFromTxt(listClient,"a cobrar.txt","w",parser_ClientQtySalesToCharge) == SUCCESS)
					{
						printf("\nArchivo guardado con exito\n");
					} else {
						printf("\nNo se pudo guardar el archivo\n");
					}
					break;
				case 7:
					info_generateEstadistics(listSale, listClient);
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
