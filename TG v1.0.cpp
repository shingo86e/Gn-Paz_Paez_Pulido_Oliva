#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<conio.h>
#include<math.h>
#include <ctype.h>
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

struct fecha
{
	int dia,mes,anio;
};


struct NICKYPASSUSUARIOS //registro para la carga de datos del personal
{
	char Nombre[50],Apellido[50],profesion[50],usuario[50],contrasenia[50];
	fecha fechasIngreso;
	int tipo;//tipo usado para seleccionar entre recepcionista o profesional
};

struct registroClientes
{
	char nombre[50],apellido[50],domicilio[100];
	fecha fechaNac;
	int edad, DNI, numRegistro=0;
};

void gotoxy(int x,int y)//funcion usada para poder posicionar lo que se muestra en pantalla con x columnas e y filas
{
	HANDLE hcon;
	hcon=GetStdHandle (STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X=x;
	dwPos.Y=y;
	SetConsoleCursorPosition(hcon,dwPos);
}

void usuariosyClaves(char usuarioPrueba[10],char contraseniaPrueba[10],int tipo)//funcion para el ingreso de usuarios desde funcion Espacios Admin
{
	FILE *usuarios;
	NICKYPASSUSUARIOS datos; 
	char salir, ingresarNuevo, usuario[50];
	int opcion,contarCaracteres,contarMayusculas=0,contarMinusculas=0,contarDigit=0,contarPuntuacion=0,contarEspacios=0,comparar;
	bool banderaIngreso=false, validar=true;
	
	usuarios=fopen("usuarios.dat","r+b");//abre el archivo en lectura mas escritura
	if(usuarios==NULL)// si no existe lo abre en forma de escritura
	{
		fclose(usuarios);
		usuarios=fopen("usuarios.dat","w+b");
		if(usuarios==NULL)// si da error al abrir el archivo informa el error y cierra el programa
		{
			printf("Error no se pudo abrir/crear el archivo, saliendo del programa...");
			getch();
			exit (1);
		}
	}
		
	gotoxy(5,0);
	if(tipo==1)printf("Registro Profesional");
	gotoxy(5,0);
	if(tipo==2)printf("Registro Recepcionista");
	printf("\n==============================");
	datos.tipo=1;
	printf("\nNombre: ");
	_flushall();
	gets(datos.Nombre);
	printf("Apellido: ");
	gets(datos.Apellido);
	printf("Profesion: ");
	gets(datos.profesion);
	printf("Fecha de ingreso (dd/mm/aaa): ");
	printf("\nDia: ");
	scanf("%d",&datos.fechasIngreso.dia);
	printf("Mes: ");
	scanf("%d",&datos.fechasIngreso.mes);
	printf("Anio: ");
	scanf("%d",&datos.fechasIngreso.anio);
	system("cls");
	do
	{
		gotoxy(7,0);
		printf("Registro Usuario");
		printf("\n==============================");
		printf("\nDebera cumplir con los siguientes requisitos: ");
		printf("\n1-Tener entre 6 y 10 caracteres.");
		printf("\n2-Pueden ser letras, numeros y/o simbolos del conjunto {+,-,/,*,?,¿,!,¡}.");
		printf("\n3-Ser unico para cada usuario registrado.\n");
		printf("4-Comenzar con una letra minuscula.\n");
		printf("5-Tener al menos 2 letras mayusculas.");
		printf("\n6-Tener como maximo 3 digitos.");
		printf("\nEjemplos de nombres de usuario incorrectos: AbC123 (no cumple con 4),\npTS!1234 (no cumple con 6), g178Mci (no cumple con 5), mARtin123gomez\n(tiene mas de 10 caracteres).\nEjemplos de nombres de usuario correctos: mARtin12, jo97!AR.\n");
		
		/*Nombre de usuario: Cantidad mínima de 6 caracteres y máxima de 10,\nlos cuales podrán ser letras, números y/o símbolos del conjunto {+,-,/,*,?,¿,!,¡}. 
		Deberá cumplir con los siguientes requisitos:\n
		1. Ser único para cada usuario registrado.\n
		2. Comenzar con una letra minúscula.\n
		3. Tener al menos 2 letras mayúsculas.\n
		4. Tener como máximo 3 dígitos.\n
		Ejemplos de nombres de usuario incorrectos: AbC123 (no cumple con b),\npTS!1234 (no cumple con d), g178Mci (no cumple con c), mARtin123gomez\n(tiene más de 10 caracteres).\nEjemplos de nombres de usuario correctos: mARtin12, jo97!AR.\n
		*/
		printf("Usuario: ");
		_flushall();
		gets(usuario);
		rewind(usuarios);
		while(!feof(usuarios))//1. Ser único para cada usuario registrado.
		{
			fread(&datos.usuario,sizeof(NICKYPASSUSUARIOS),1,usuarios);
			comparar=strcmp(datos.usuario,usuario);
			if(comparar==0)validar=false;
		}
		contarCaracteres=strlen(usuario);
		if(contarCaracteres<6 || contarCaracteres>10)validar=false;//Cantidad mínima de 6 caracteres y máxima de 10
		for(int i=0;i<contarCaracteres;i++)//los cuales podrán ser letras, números y/o símbolos del conjunto {+,-,/,*,?,¿,!,¡}
		{
			if(isdigit(usuario[i])||isalpha(usuario[i])||ispunct(usuario[i]))	
			{
				validar=true;
			}
			else
			{
				validar=false;
			}
		}
		if(isupper(usuario[0]))validar=false;//Comenzar con una letra minúscula.
		for(int i=0;i<contarCaracteres;i++)//Tener al menos 2 letras mayúsculas.
		{
			if(isupper(usuario[i]))contarMayusculas++;
		}
		if(contarMayusculas<2)validar=false;
		for(int i=0;i<contarCaracteres;i++)//Tener como máximo 3 dígitos.
		{
			if(isdigit(usuario[i]))contarDigit++;
		}
		if(contarDigit>3)validar=false;
		if(validar==false)
		{
			printf("\nERROR! El nombre de usuario no cumple con los requisitos");
			printf("\n\nIngresar Nuevo nombre de usuario? S/N");
			printf("\nOpcion: ");
			salir=getch();
			if(salir<='z' && salir >='a')salir=salir-'a'+'A';
			system("cls");					
		}
		else
		{
			strcpy(datos.usuario,usuario);
			printf("\nRegistro de Usuario Exitoso!");
			getch();
			system("cls");
		}		
	}while(validar==false && salir=='S');
	if(validar==true)
	{
		do
		{
			gotoxy(6,0);
			printf("Registre Contrasenia");
			printf("\n==============================");
			printf("\nDebera cumplir con los siguientes requisitos: ");
			printf("\n1. Debera contener al menos una letra mayuscula, una letra minuscula y un numero.");
			printf("\n2. No podra contener ningun caracter de puntuacion, ni acentos, ni espacios.Solo caracteres alfanumericos.");
			printf("\n3. Debera tener entre 6 y 32 caracteres.");
			printf("\n4. No debe tener mas de 3 caracteres numericos consecutivos.");
			printf("\n5. No debe tener 2 caracteres consecutivos que refieran a letras alfabeticamente consecutivas (ascendentemente).");
			printf("\nEjemplos de contrasenias mal formadas: \nAch32 (no cumple con 3), \ndorit1234 (no cumple la regla 1 ni la 4), \nsA;gotAP.10 (no cumple con 2), \naBuel123 (no cumple con 5).");
			printf("\nEjemplo de contrasenias bien formadas: Achus32, 125Af89, aLejo123, DORItO45,4aC2sa.");
			_flushall();
			printf("\n\nContrasenia: ");
			gets(datos.contrasenia);
			contarCaracteres=strlen(datos.contrasenia);
			for(int i=0;i<contarCaracteres;i++)//Deberá contener al menos una letra mayúscula, una letra minúscula y un número.
			{
				if(isalpha(datos.contrasenia[i]))
				{
					if(isupper(datos.contrasenia[i]))contarMayusculas++;
					if(islower(datos.contrasenia[i]))contarMinusculas++;
					if(isalpha(datos.contrasenia[i]))
					{
						if(isalpha(datos.contrasenia[i+1]))
						{
							if(datos.contrasenia[i]==datos.contrasenia[i+1]--)validar=false;//validar que no sean letras consecutivas
						}
					}
				}
				
				if(isdigit(datos.contrasenia[i]))
				{
					contarDigit++;//contar cantidad de numeros
					if(isdigit(datos.contrasenia[i+1]))
					{
						if(isdigit(datos.contrasenia[i+2]))
						{
							if(datos.contrasenia[i]==datos.contrasenia[i+1]-- && datos.contrasenia[i+1]==datos.contrasenia[i+2]--)validar=false;//validar que no hayan 3 numeros consecutivos
						}
					}
				}
				
				if(ispunct(datos.contrasenia[i]))contarPuntuacion++;//contar signos de puntuacion
				if(isspace(datos.contrasenia[i]))contarEspacios++;//contar espacios
				
			
			}
			if(contarMayusculas<1)validar=false;
			if(contarMinusculas<1)validar=false;
			if(contarDigit<1)validar=false;
			if(contarPuntuacion>0)validar=false;
			if(contarEspacios>0)validar=false;
			if(contarCaracteres<3 || contarCaracteres>32)validar=false;
			if(validar==false)
			{
				printf("\nERROR! La contrasenia no cumple con los requisitos");
				printf("\n\nIngresar Nueva contrasenia? S/N");
				printf("\nOpcion: ");
				salir=getch();
				if(salir<='z' && salir >='a')salir=salir-'a'+'A';
				system("cls");					
			}
			else
			{
				printf("\nRegistro de contrasenia Exitosa!");
				getch();
				system("cls");
			}
		}while(validar==false && salir=='S');
		
		
		/*Contraseña: Su conformación no podrá darse al azar, sino que deberá respetar lo siguiente:
		1. Deberá contener al menos una letra mayúscula, una letra minúscula y un número.
		2. No podrá contener ningún carácter de puntuación, ni acentos, ni espacios. Sólo caracteres
		alfanuméricos.
		3. Deberá tener entre 6 y 32 caracteres.
		4. No debe tener más de 3 caracteres numéricos consecutivos.
		5. No debe tener 2 caracteres consecutivos que refieran a letras alfabéticamente consecutivas
		(ascendentemente). Este criterio es válido tanto para letras mayúsculas, minúsculas o combinación de
		ambas.
		Ejemplos de contraseñas mal formadas: Ach32 (no cumple con c), dorit1234
		(no cumple la regla a ni la d), sA;gotAP.10 (no cumple con b), aBuel123 (no
		cumple con e).
		Ejemplo de contraseñas bien formadas: Achus32, 125Af89, aLejo123, DORItO45,
		4aC2sa.
		*/
	}
	if(validar==true)
	{
		fwrite(&datos,sizeof(NICKYPASSUSUARIOS),1,usuarios);
	}
	system("cls");	
}

void registrarClientes(registroClientes datosClientes)
{
	char salir;
	FILE *CLI;
	int numRegistro;
	CLI=fopen("clientes.dat","r+b");//abre el archivo en lectura mas escritura
	if(CLI==NULL)// si no existe lo abre en forma de escritura
	{
		fclose(CLI);
		CLI=fopen("clientes.dat","w+b");
		if(CLI==NULL)// si da error al abrir el archivo informa el error y cierra el programa
		{
			printf("Error no se pudo abrir/crear el archivo, saliendo del programa...");
			getch();
			exit (1);
		}
	}
	do
	{
		gotoxy(10,0);
		printf("Registro de clientes");
		printf("\n========================================");
		printf("Nombre: ");
		printf("Apellido: ");
		printf("Domicilio: ");
		printf("Fecha de nacimiento: ");
		printf("Edad: ");
		printf("\n========================================");
		
		_flushall();
		gotoxy(8,2);
		gets(datosClientes.nombre);
		gotoxy(10,3);
		gets(datosClientes.apellido);
		gotoxy(11,4);
		gets(datosClientes.domicilio);
		gotoxy(21,5);
		scanf("%d",&datosClientes.fechaNac);
		gotoxy(6,6);
		scanf("%d",&datosClientes.edad);
		while(!feof(CLI))//busca en la base de datos de clientes y le suma 1 mas al numero de registro.
		{
			fread(&datosClientes.numRegistro,sizeof(registroClientes),1,CLI);
			if(!feof(CLI))
			{
				numRegistro=datosClientes.numRegistro;
			}
		}
		datosClientes.numRegistro++;
		printf("\nNumero de Registro: %06d",datosClientes.numRegistro);
		fseek(CLI,-sizeof(registroClientes),2);
		fwrite(&datosClientes.numRegistro,sizeof(registroClientes),1,CLI);
		
	}while(salir=='N');	
		
	
	fclose(CLI);
	system("cls");
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
	registroClientes datosClientes;	
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
		system("cls");
		switch(option)
		{
			case 1:
				{
					registrarClientes(datosClientes);
					break;
					
				}
			case 2:
				{
					
					break;
				}
			case 3:
				{
					
					break;
				}
			default:
				{
					if(option!=0)
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
	}while(option!=0);	
	if(option==0)
	{
		printf("\nSaliendo del programa...");
		exit (1);
	}
	getch();
	system("cls");
}

void menuAdministracion(char usuarioPrueba[10])//recepcion en funcion de usuario ficticio, posteriormente debe recibir us y pass que coincida con una BD.
{
	const int prof=1,recep=2;//constantes para enviar a la creacion de usuario al seleccionar en el menu recep o prof.
	int option;
	char usuario[10],contraseniaPrueba[10];//contrasenia ficticia, aun hay que hacer la base de datos de admin
	
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
		system("cls");
		switch(option)
		{
			case 1:
				{
					usuariosyClaves(usuario,contraseniaPrueba,prof);
					break;
					
				}
			case 2:
				{
					usuariosyClaves(usuario,contraseniaPrueba,recep);
					break;
				}
			case 3:
				{
					
					break;
				}
			default:
				{
					if(option!=0)
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
	char usuarioPrueba[10], contraseniaPrueba[10];//usuarios y contrasenias ficticias a modo de ir creando el programa, posteriormente seran incluidas en una base de datos para los usuarios de administracion.
	bool b=false;
	
	//::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000); //mostrar en pantalla completa
	system("color 1A");	//color del programa
	
	do
	{
		gotoxy(60,1); // logo de la UTN
		printf("* *   * *   * *");
		gotoxy(60,2);
		printf("* *   * *   * *");
		gotoxy(60,3);
		printf("  * * * * * *");
		gotoxy(60,4);
		printf("* * * * * * * *");
		gotoxy(60,5);
		printf("* * * * * * * *");
		gotoxy(60,6);
		printf("  * * * * * *");
		gotoxy(60,7);
		printf("* *   * *   * *");
		gotoxy(60,8);
		printf("* *   * *   * *");
		gotoxy(0,0);
		printf("========================================");//0
		gotoxy(11,1);
		printf("CENTRO DE ESTETICA");//1
		printf("\n========================================");//2
		gotoxy(7,3);
		printf("Seleccione tipo de Modulo");//3
		printf("\n========================================");//4
		printf("\n 1- Modulo Espacios");//5
		printf("\n 2- Modulo Recepcion");//6
		printf("\n 3- Modulo Administracion");//7
		printf("\n Salir del sistema 0");//8
		printf("\n Opcion: ");//9
		gotoxy(0,9);
		printf("\n========================================");
		gotoxy(9,9);
		scanf("%d",&usuariosMenu);
		system("cls");
		
		switch(usuariosMenu)
		{
			case 1:
				{
					//Modulo Espacios
					do
					{
						gotoxy(6,0);
						printf("Modulo Espacios");
						printf("\n==========================");
						printf("\nIngrese Nombre de Usuario: ");
						printf("\nIngrese Contrasenia: ");
						printf("\n==========================");
						_flushall();
						gotoxy(27,2);
						gets(usuarioPrueba);
						gotoxy(21,3);
						gets(contraseniaPrueba);
						b=true; //esta bandera posteriormente validará que el usuario y contrasenia sea la correcta.
												
					}
					while(b==false);
					system("cls");
					menuEspacios(usuarioPrueba);
					break;
				}
			case 2:
				{
					//Modulo Recepcion
					do
					{
						gotoxy(5,0);
						printf("Modulo Recepcion");
						printf("\n==========================");
						printf("\nIngrese Nombre de Usuario: ");
						printf("\nIngrese Contrasenia: ");
						printf("\n==========================");
						_flushall();
						gotoxy(27,2);
						gets(usuarioPrueba);
						gotoxy(21,3);
						gets(contraseniaPrueba);
						b=true; //esta bandera posteriormente validará que el usuario y contrasenia sea la correcta.
												
					}
					while(b==false);
					system("cls");
					menuRecepcion(usuarioPrueba);
					break;
				}
			case 3:
				{
					//Modulo Administracion
					do
					{
						gotoxy(1,0);
						printf("Modulo Administracion");
						printf("\n==========================");
						printf("\nIngrese Nombre de Usuario: ");
						printf("\nIngrese Contrasenia: ");
						printf("\n==========================");
						_flushall();
						gotoxy(27,2);
						gets(usuarioPrueba);
						gotoxy(21,3);
						gets(contraseniaPrueba);
						b=true;//esta bandera posteriormente validará que el usuario y contrasenia sea la correcta.
												
					}
					while(b==false);
					
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
