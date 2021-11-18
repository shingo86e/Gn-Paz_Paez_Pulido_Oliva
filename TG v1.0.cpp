#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<conio.h>
#include <windows.h> 

/*
integrantes 
-----------
*Páez, Micaela Agustina 
correo: Micaela.Paez@alu.frt.utn.edu.ar
Legajo: 53374
*Oliva, Solange Marianella
correo: Solange.Oliva@alu.frt.utn.edu.ar
Legajo: 53365
* Paz, Exequiel Victor Roberto
correo: exequiel.Paz@alu.frt.utn.edu.ar
Legajo: 53382
*Pulido, Luciano Nicolas
correo:Luciano.Pulido@alu.frt.utn.edu.ar
Legajo: 53397
*/

void gotoxy(int x,int y)
{
	HANDLE hcon;
	hcon=GetStdHandle (STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X=x;
	dwPos.Y=y;
	SetConsoleCursorPosition(hcon,dwPos);
}
void menuEspacios(char usuarioPrueba[10])
{
	int option;
	
	do
	{
		gotoxy(7,0);
		printf("Modulo Espacios");
		printf("\n=========================");
		printf("\n Bienvenido %s",usuarioPrueba);
		printf("\n 1.- Visualizar Lista de Espera de Turnos (informe)");
		printf("\n 2.- Registrar Evolucion del tratamiento");
		printf("\n 0.- Cerrar la aplicacion");
		printf("\n Ingrese una opcion: ");
		gotoxy(0,7);
		printf("=========================");
		gotoxy(21,6);
		scanf("%d",&option);
	
	}while(option!=0);
	if(option==0)
	{
		printf("\nSaliendo del programa...");
		exit (1);
	}
	getch();
	system("cls");	
}

void menuRecepcion(char usuarioPrueba[10])
{
	int option;
	
	do
	{
		gotoxy(1,0);
		printf("Modulo del recepcionista");
		printf("\n==========================");
		printf("\n Bienvenido %s",usuarioPrueba);
		printf("\n 1.- Registrar Cliente");
		printf("\n 2.- Registrar Turno");
		printf("\n 3.- Listado de Atenciones por Profesional y Fecha");
		printf("\n 0.- Cerrar la aplicacion.");
		printf("\n Ingrese una opcion: ");
		gotoxy(0,8);
		printf("==========================");
		gotoxy(21,7);
		scanf("%d",&option);
	
	}while(option!=0);
	if(option==0)
	{
		printf("\nSaliendo del programa...");
		exit (1);
	}
	getch();
	system("cls");
}

void menuAdministracion(char usuarioPrueba[10])
{
	int option;
	
	do
	{
		gotoxy(1,0);
		printf("Modulo Administracion");
		printf("\n==========================");
		printf("\n Bienvenido %s",usuarioPrueba);
		printf("\n 1.- Registrar Profesional");
		printf("\n 2.- Registrar Usuario Recepcionista");
		printf("\n 3.- Atenciones por Profesional");
		printf("\n 4.- Ranking de Profesionales por Atenciones");
		printf("\n 0.- Cerrar la aplicacion.");
		printf("\n Ingrese una opcion: ");
		gotoxy(0,9);
		printf("==========================");
		gotoxy(21,8);
		scanf("%d",&option);
	
	}while(option!=0);
	if(option==0)
	{
		printf("\nSaliendo del programa...");
		exit (1);
	}
	getch();
	system("cls");
}

main()
{
	//seleccion de menu de usuarios
	int usuariosMenu;
	char usuarioPrueba[10];
	do
	{
		gotoxy(7,0);
		printf("Seleccione tipo de Modulo");
		printf("\n========================================");
		printf("\n 1- Modulo Espacios");
		printf("\n 2- Modulo Recepcion");
		printf("\n 3- Modulo Administracion");
		printf("\n Salir del sistema 0");
		printf("\n Opcion: ");
		gotoxy(0,6);
		printf("\n========================================");
		gotoxy(9,6);
		scanf("%d",&usuariosMenu);
		system("cls");
		switch(usuariosMenu)
		{
			case 1:
				{
					//Modulo Espacios
					printf("\nIngrese Nombre de Usuario: ");
					_flushall();
					gets(usuarioPrueba);
					system("cls");
					menuEspacios(usuarioPrueba);
					break;
				}
			case 2:
				{
					//Modulo Recepcion
					printf("\nIngrese Nombre de Usuario: ");
					_flushall();
					gets(usuarioPrueba);
					system("cls");
					menuRecepcion(usuarioPrueba);
					break;
				}
			case 3:
				{
					//Modulo Administracion
					printf("\nIngrese Nombre de Usuario: ");
					_flushall();
					gets(usuarioPrueba);
					system("cls");
					menuAdministracion(usuarioPrueba);
					break;
				}
			default:
				{
					if(usuariosMenu!=0)
					{
						printf("\nOpcion no valida");
					}
					else
					{
						printf("\nSaliendo del programa...");
					}
					getch();
					system("cls");
				}	
		}
			
	}while(usuariosMenu!=0);
	getch();
	system("cls");
}
