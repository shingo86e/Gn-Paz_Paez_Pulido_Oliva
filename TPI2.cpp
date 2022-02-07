#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
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
	int dia;
	int mes;
	int anio;
};

struct usuarios
{
	char Usuario[11];
	char Password[33];
	char ApeNom[50];
};

struct profesionales
{
	char ApeNom[50];
	int ID;
	int DNI;
	int Telefono;
};

struct cliente
{
	char ApeNom[50];
	char Domicilio[50];
	int DNI;
	fecha FecNacimiento;
	int edad;
	float Peso;
	int Telefono;
};

struct turnos
{
	int IDProfesional;
	fecha fecAtencion;
	int DNICliente;
	char DetalleAtencion[380];
	bool atendido;
};

struct cuentasProfe
{
	usuarios cuenta;
	profesionales datos;
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
void MenuEspacios(cuentasProfe cuenta);
void MenuRecepcion(usuarios cuenta);
void MenuAdministracion();
bool Login(int tipo, cuentasProfe& cP, usuarios& cR);
int ListarEspera(cuentasProfe pro, fecha actual, bool listar);
void RegistrarEvolucion(cuentasProfe pro, fecha actual, int& c);
void RegistrarCliente();
void RegistrarTurno();
void ListarAtenciones();
void RegistrarProfesional();
void RegistrarRecepcionista();
void AtencionesProfesionales();
void RankingAtenciones();

main()
{
	FILE *ArchClientes;
	FILE *ArchProfesionales;
	FILE *ArchTurnos;
	FILE *ArchRecepcionistas;
	int usuariosMenu;
	cuentasProfe cP;
	usuarios cR;
	
	//Creo o abro los archivos necesarios para la ejecucion
	ArchClientes = fopen("Clientes.dat", "ab");
	fclose(ArchClientes);
	
	ArchProfesionales = fopen("Profesionales.dat", "ab");
	fclose(ArchProfesionales);
	
	ArchTurnos = fopen("Turnos.dat", "ab");
	fclose(ArchTurnos);
	
	ArchRecepcionistas = fopen("Recepcionistas.dat", "ab");
	fclose(ArchRecepcionistas);
	
	//Menu Principal
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
				//Dirige al menu profesional
				if(Login(1, cP, cR))
				MenuEspacios(cP);
				break;
				
			case 2:
				//Dirige al menu recepcion
				if(Login(2, cP, cR))
				MenuRecepcion(cR);
				break;
				
			case 3:
				//Dirige al menu administracion
				MenuAdministracion();
				break;
				
			default:
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
			
	}while(usuariosMenu!=0);
	getch();
	system("cls");
}

bool Login(int tipo, cuentasProfe& cP, usuarios& cR)
{
	FILE *arch;
	char usuario[10];
	char contra[33];
	cuentasProfe auxP;
	usuarios auxR;
	int b = 0;
	
	if(tipo == 1)
	{
		arch = fopen("Profesionales.dat", "rb");
	}else
	{
		arch = fopen("Recepcionistas.dat", "rb");
	}
	
	gotoxy(6,0);
	printf("Iniciar Sesion");
	printf("\n==========================");
	printf("\nIngrese Nombre de Usuario: ");
	printf("\nIngrese Contrasenia: ");
	printf("\n==========================");
	gotoxy(27,2);
	_flushall();
	gets(usuario);
	gotoxy(21,3);
	_flushall();
	gets(contra);
	
	if(tipo == 1)
	{
		while(!feof(arch))
		{
			fread(&auxP, sizeof(cuentasProfe), 1, arch);
			if(strcmp(auxP.cuenta.Usuario, usuario) == 0 && strcmp(auxP.cuenta.Password, contra) == 0)
			{
				b = 1;
				cP = auxP;
				system("cls");
				fclose(arch);
				return true;
			}
		}
	}else
	{
		while(!feof(arch))
		{
			fread(&auxR, sizeof(usuarios), 1, arch);
			if(strcmp(auxR.Usuario, usuario) == 0 && strcmp(auxR.Password, contra) == 0)
			{
				b = 1;
				cR = auxR;
				system("cls");
				fclose(arch);
				return true;
			}
		}
	}
	
	if(b == 0)
	{
		printf("\n\nNo existe usuario o contrasenia!");
		getch();
		system("cls");
		fclose(arch);
		return false;
	}
}

void MenuEspacios(cuentasProfe cuenta)
{
	int option;
	fecha actual;
	int CantTurnos;
	
	printf("Indique la fecha\n");
	printf("Dia: ");
	scanf("%d", &actual.dia);
	printf("Mes: ");
	scanf("%d", &actual.mes);
	printf("Anio: ");
	scanf("%d", &actual.anio);
	
	system("cls");
	
	do
	{
		CantTurnos = ListarEspera(cuenta, actual, false);
		gotoxy(7,0);
		printf("Modulo Espacios");
		printf("\n=========================");
		printf("\n Bienvenido %s", cuenta.datos.ApeNom);
		printf("\n 1.- Visualizar Lista de Espera de Turnos (informe)");
		printf("\n 2.- Registrar Evolucion del tratamiento");
		printf("\n 0.- Cerrar la aplicacion");
		printf("\n Ingrese una opcion: ");
		gotoxy(0,7);
		printf("=========================");
		gotoxy(21,6);
		scanf("%d",&option);
		
		switch(option)
		{
			case 1:
				system("cls");
				CantTurnos = ListarEspera(cuenta, actual, true);
				break;
				
			case 2:
				RegistrarEvolucion(cuenta, actual, CantTurnos);
				break;
				
			default:
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
	}while(option!=0);
	if(option==0)
	{
		printf("\nSaliendo del programa...");
	}
	getch();
	system("cls");
}

int ListarEspera(cuentasProfe pro, fecha actual, bool listar)
{
	FILE *Turnos;
	FILE *Clientes;
	turnos reg;
	cliente cli;
	int b = 0;
	int i = 0;
	
	system("cls");
	
	Turnos = fopen("Turnos.dat", "rb");
	Clientes = fopen("Clientes.dat", "rb");
	
	rewind(Turnos);
	
	fread(&reg, sizeof(turnos), 1, Turnos);
	
	while(!feof(Turnos))
	{
		if((actual.dia == reg.fecAtencion.dia) && (actual.mes == reg.fecAtencion.mes) && (actual.anio == reg.fecAtencion.anio) && (reg.IDProfesional == pro.datos.ID) && !reg.atendido)
		{
			rewind(Clientes);
			
			while(!feof(Clientes) && b != 1)
			{
				fread(&cli, sizeof(cliente), 1, Clientes);
				
				if(reg.DNICliente == cli.DNI)
				{
					b = 1;
					i++;
					if(listar)
					printf("[Turno %d] Nombre del Paciente: %s; DNI: %d\n", i,cli.ApeNom, cli.DNI);
				}
			}
		}
		b = 0;
		fread(&reg, sizeof(turnos), 1, Turnos);
	}
	
	fclose(Turnos);
	fclose(Clientes);

	if(listar)
	getch();
	system("cls");
	
	return i;
}

void RegistrarEvolucion(cuentasProfe pro, fecha actual, int& c)
{
	int turno;
	FILE *Turnos;
	FILE *Clientes;
	turnos reg;
	cliente cli;
	int i = 0;
	int b = 0;
	int a = 0;
	float volver;
	long pos;
	
	system("cls");
	
	printf("Turno a atender (Del 1 al %d): ", c);
	do
	{
		if(b != 0)
		{
			printf("Ingrese un turno valido\n");
			printf("Turno a atender (Del 1 al %d): ", c);
		}
		scanf("%d", &turno);
		b = 1;
	}while(turno < 1 || turno > c);
	
	b = 0;
	system("cls");
	
	Turnos = fopen("Turnos.dat", "r+b");
	Clientes = fopen("Clientes.dat", "rb");
	
	rewind(Turnos);
	
	pos = ftell(Turnos);
	fread(&reg, sizeof(turnos), 1, Turnos);
	
	while(!feof(Turnos) && a == 0)
	{
		if((actual.dia == reg.fecAtencion.dia) && (actual.mes == reg.fecAtencion.mes) && (actual.anio == reg.fecAtencion.anio) && (reg.IDProfesional == pro.datos.ID) && !reg.atendido)
		{
			rewind(Clientes);
			
			while(!feof(Clientes) && b != 1)
			{
				fread(&cli, sizeof(cliente), 1, Clientes);
				
				if(reg.DNICliente == cli.DNI)
				{
					b = 1;
					i++;
					if(i == turno)
					a++;
				}
			}
		}
		b = 0;
		//pos = ftell(Turnos);
		
		if(a == 0)
		{
			pos = ftell(Turnos);
			fread(&reg, sizeof(turnos), 1, Turnos);
		}
		
	}
	
	printf("====Datos para la atencion====\n");
	printf("Nombre: %s\n", cli.ApeNom);
	printf("DNI: %d\n", cli.DNI);
	printf("Domicilio %s\n", cli.Domicilio);
	printf("Edad: %d\n", cli.edad);
	printf("Peso: %.2f\n\n", cli.Peso);
	printf("Evolucion: ");
	_flushall();
	gets(reg.DetalleAtencion);
	
	reg.atendido = true;
	
	fseek(Turnos, pos, SEEK_SET);
	fwrite(&reg, sizeof(turnos), 1, Turnos);
	
	fclose(Turnos);
	fclose(Clientes);
	
	getch();
	system("cls");
}

void MenuRecepcion(usuarios cuenta)
{
	int option;
	
	do
	{
		gotoxy(1,0);
		printf("Modulo del recepcionista");
		printf("\n==========================");
		printf("\n Bienvenido %s", cuenta.ApeNom);
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
				RegistrarCliente();
				break;
				
			case 2:
				RegistrarTurno();
				break;
				
			case 3:
				ListarAtenciones();
				break;
				
			default:
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
	}while(option!=0);
	if(option==0)
	{
		printf("\nSaliendo del programa...");
	}
	getch();
	system("cls");
}

void RegistrarCliente()
{
	FILE *arch;
	cliente reg;
	int b = 0;
	
	arch = fopen("Clientes.dat", "a+b");
	
	printf("====Registrar Cliente====\n");
	printf("Apellido y Nombre: ");
	_flushall();
	gets(reg.ApeNom);
	
	printf("Domicilio: ");
	_flushall();
	gets(reg.Domicilio);
	
	printf("DNI: ");
	scanf("%d", &reg.DNI);
	
	printf("Fecha de Nacimiento\n");
	printf("Dia: ");
	do
	{
		if(b != 0)
		{
			printf("Error! El dia debe ser entre 1 y 31\n");
			printf("Dia: ");
		}
		scanf("%d", &reg.FecNacimiento.dia);
		b = 1;
	}while(reg.FecNacimiento.dia < 1 || reg.FecNacimiento.dia > 31);
	
	b = 0;
	
	printf("Mes: ");
	do
	{
		if(b != 0)
		{
			printf("Error! El mes debe ser entre 1 y 12\n");
			printf("Mes: ");
		}
		scanf("%d", &reg.FecNacimiento.mes);
		b = 1;
	}while(reg.FecNacimiento.mes < 1 || reg.FecNacimiento.mes > 12);
	
	b = 0;
	
	printf("Anio: ");
	do
	{
		if(b != 0)
		{
			printf("Error! El anio debe ser mayor que 0\n");
			printf("Anio: ");
		}
		scanf("%d", &reg.FecNacimiento.anio);
		b = 1;
	}while(reg.FecNacimiento.anio < 1);
	
	b = 0;
	
	printf("Peso: ");
	do
	{
		if(b != 0)
		{
			printf("Error! El peso debe ser mayor que 0\n");
			printf("Peso: ");
		}
		scanf("%f", &reg.Peso);
		b = 1;
	}while(reg.Peso < 1);
	
	b = 0;
	
	printf("Telefono: ");
	do
	{
		if(b != 0)
		{
			printf("Error! El Telefono debe ser mayor que 0\n");
			printf("Anio: ");
		}
		scanf("%d", &reg.Telefono);
		b = 1;
	}while(reg.Telefono < 1);
	
	b = 0;
	
	reg.edad = 2021 - reg.FecNacimiento.anio;
	if(reg.FecNacimiento.mes < 12)
	{
		if(reg.FecNacimiento.dia < 12)
		{
			reg.edad--;
		}
	}
	
	fwrite(&reg, sizeof(cliente), 1, arch);
	fclose(arch);
	
	getch();
	system("cls");
}

void RegistrarTurno()
{
	FILE *Turnos;
	FILE *Pro;
	FILE *Clientes;
	cuentasProfe profesionales[100];
	cliente clientes[100];
	turnos reg;
	int iP = 0;
	int iC = 0;
	int b = 0;
	bool existe = false;
	int salir;
	
	Pro = fopen("Profesionales.dat", "rb");
	Clientes = fopen("Clientes.dat", "rb");
	Turnos = fopen("Turnos.dat", "a+b");
	
	while(!feof(Pro))
	{
		fread(&profesionales[iP], sizeof(cuentasProfe), 1, Pro);
		iP++;
	}
	
	while(!feof(Clientes))
	{
		fread(&clientes[iC], sizeof(cliente), 1, Clientes);
		iC++;
	}
	
	printf("====Registrar Turno====\n");
	
	do
	{
		printf("ID del profesional: ");
		scanf("%d", &reg.IDProfesional);
		
		for(int j = 0; j < iP; j++)
		{
			if(profesionales[j].datos.ID == reg.IDProfesional)
			{
				existe = true;
			}
		}
		
		if(!existe)
		{
			printf("Ingrese una ID valida!");
		}
	}while(!existe);
	
	existe = false;
	
	printf("Fecha de atencion\n");
	printf("Dia: ");
	do
	{
		if(b != 0)
		{
			printf("Error! El dia debe ser entre 1 y 31\n");
			printf("Dia: ");
		}
		scanf("%d", &reg.fecAtencion.dia);
		b = 1;
	}while(reg.fecAtencion.dia < 1 || reg.fecAtencion.dia > 31);
	
	b = 0;
	
	printf("Mes: ");
	do
	{
		if(b != 0)
		{
			printf("Error! El mes debe ser entre 1 y 12\n");
			printf("Mes: ");
		}
		scanf("%d", &reg.fecAtencion.mes);
		b = 1;
	}while(reg.fecAtencion.mes < 1 || reg.fecAtencion.mes > 12);
	
	b = 0;
	
	printf("Anio: ");
	do
	{
		if(b != 0)
		{
			printf("Error! El anio debe ser mayor que 0\n");
			printf("Anio: ");
		}
		scanf("%d", &reg.fecAtencion.anio);
		b = 1;
	}while(reg.fecAtencion.anio < 1);
	
	b = 0;
	
	do
	{
		printf("DNI del cliente: ");
		scanf("%d", &reg.DNICliente);
		
		for(int j = 0; j < iC; j++)
		{
			if(clientes[j].DNI == reg.DNICliente)
			{
				existe = true;
			}
		}
		
		if(!existe)
		{
			printf("Ingrese un DNI valido! Debe registrar al cliente antes de darle un turno.");
			printf("\nDesea salir de esta funcion? 1-No 2-Si: ");
			scanf("%d", &salir);
		}
		
		if(salir == 2)
		{
			fclose(Turnos);
			fclose(Pro);
			fclose(Clientes);
			system("cls");
			return;
		}
	}while(!existe);
	
	fwrite(&reg, sizeof(turnos), 1, Turnos);
	
	fclose(Turnos);
	fclose(Pro);
	fclose(Clientes);
	
	system("cls");
}

void ListarAtenciones()
{
	
}

void MenuAdministracion()
{
	int option,comparar,compararP;
	char usuario[15],pass[33];
	
	gotoxy(1,0);
	printf("Modulo Administracion");
	printf("\n==========================");
	printf("\nUsuario: ");
	printf("\nContrasenia: ");
	printf("\n==========================");
	gotoxy(9,2);
	_flushall();
	gets(usuario);
	gotoxy(13,3);
	gets(pass);
	comparar=strcmp(usuario,"PulidoLuciano");
	comparar=strcmp(usuario,"micaapaez");
	comparar=strcmp(usuario,"shingo86e");
	compararP=strcmp(pass,"elMejorGrupo2021");
	if (comparar==0 &&compararP==0)
	{
	
	do
	{
		gotoxy(1,0);
		printf("Modulo Administracion");
		printf("\n==========================");
		printf("\n Bienvenido");
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
				RegistrarProfesional();
				break;
				
			case 2:
				RegistrarRecepcionista();
				break;
				
			case 3:
				AtencionesProfesionales();
				break;
				
			case 4:
				RankingAtenciones();
				break;
				
			default:
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
	}while(option!=0);
}
else 
printf ("\nUsuario o contraseña no validas");
	getch();
	system("cls");
}

void RegistrarProfesional()
{
	FILE *arch;
	cuentasProfe reg;
	cuentasProfe aux;
	char salir, ingresarNuevo, usuario[50];
	int opcion,contarCaracteres,contarMayusculas=0,contarMinusculas=0,contarDigit=0,contarPuntuacion=0,contarEspacios=0,comparar, b=0;
	bool banderaIngreso=false, validar=true;
	
	arch = fopen("Profesionales.dat", "a+b");
	
	printf("====Registro del profesional====\n");
	printf("Nombre y apellido: ");
	_flushall();
	gets(reg.datos.ApeNom);
	printf("ID del profesional: ");
	do
	{
		if(b != 0)
		{
			printf("Error! La ID debe ser un numero mayor que cero\n");
			printf("ID del profesional: ");
		}
		scanf("%d", &reg.datos.ID);
		b = 1;
	}while(reg.datos.ID < 1);
	
	b = 0;
	
	printf("DNI: ");
	do
	{
		if(b != 0)
		{
			printf("Error! La DNI debe ser un numero mayor que cero\n");
			printf("DNI: ");
		}
		scanf("%d", &reg.datos.DNI);
		b = 1;
	}while(reg.datos.DNI < 1);
	
	b = 0;
	
	printf("Telefono: ");
	do
	{
		if(b != 0)
		{
			printf("Error! El Telefono debe ser un numero mayor que cero\n");
			printf("Telefono: ");
		}
		scanf("%d", &reg.datos.Telefono);
		b = 1;
	}while(reg.datos.Telefono < 1);
	
	system("cls");
	
	do
	{
		contarCaracteres = 0;
		contarMayusculas=0;
		contarMinusculas=0;
		contarDigit=0;
		contarPuntuacion=0;
		contarEspacios=0;
		comparar = 0;
		validar = true;
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
		gets(reg.cuenta.Usuario);
		rewind(arch);
		while(!feof(arch))//1. Ser único para cada usuario registrado.
		{
			fread(&aux,sizeof(cuentasProfe),1,arch);
			if(strcmp(reg.cuenta.Usuario, aux.cuenta.Usuario) == 0)validar=false;
		}
		contarCaracteres=strlen(reg.cuenta.Usuario);
		if(contarCaracteres<6 || contarCaracteres>10)validar=false;//Cantidad mínima de 6 caracteres y máxima de 10
		for(int i=0;i<contarCaracteres;i++)//los cuales podrán ser letras, números y/o símbolos del conjunto {+,-,/,*,?,¿,!,¡}
		{
			if(isdigit(reg.cuenta.Usuario[i])||isalpha(reg.cuenta.Usuario[i])||ispunct(reg.cuenta.Usuario[i]))	
			{
				//validar=true; Esta linea hace inutiles a las anteriores validaciones? REVISAR
			}
			else
			{
				validar=false;
			}
		}
		if(isupper(reg.cuenta.Usuario[0]))validar=false;//Comenzar con una letra minúscula.
		for(int i=0;i<contarCaracteres;i++)//Tener al menos 2 letras mayúsculas.
		{
			if(isupper(reg.cuenta.Usuario[i]))contarMayusculas++;
		}
		if(contarMayusculas<2)validar=false;
		for(int i=0;i<contarCaracteres;i++)//Tener como máximo 3 dígitos.
		{
			if(isdigit(reg.cuenta.Usuario[i]))contarDigit++;
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
			printf("\nRegistro de Usuario Exitoso!");
			getch();
			system("cls");
		}		
	}while(validar==false && salir=='S');
	
	if(validar==true)
	{
		do
		{
			contarCaracteres = 0;
			contarMayusculas=0;
			contarMinusculas=0;
			contarDigit=0;
			contarPuntuacion=0;
			contarEspacios=0;
			comparar = 0;
			validar = true;
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
			gets(reg.cuenta.Password);
			contarCaracteres=strlen(reg.cuenta.Password);
			for(int i=0;i<contarCaracteres;i++)//Deberá contener al menos una letra mayúscula, una letra minúscula y un número.
			{
				if(isalpha(reg.cuenta.Password[i]))
				{
					if(isupper(reg.cuenta.Password[i]))contarMayusculas++;
					if(islower(reg.cuenta.Password[i]))contarMinusculas++;
					if(isalpha(reg.cuenta.Password[i]))
					{
						if(isalpha(reg.cuenta.Password[i+1]))
						{
							if(reg.cuenta.Password[i]==(reg.cuenta.Password[i+1]-1))validar=false;//validar que no sean letras consecutivas
						}
					}
				}
				
				if(isdigit(reg.cuenta.Password[i]))
				{
					contarDigit++;//contar cantidad de numeros
					if(isdigit(reg.cuenta.Password[i+1]))
					{
						if(isdigit(reg.cuenta.Password[i+2]))
						{
							if(reg.cuenta.Password[i]==(reg.cuenta.Password[i+1]-1) && reg.cuenta.Password[i+1]==(reg.cuenta.Password[i+2]-1))validar=false;//validar que no hayan 3 numeros consecutivos
						}
					}
				}
				
				if(ispunct(reg.cuenta.Password[i]))contarPuntuacion++;//contar signos de puntuacion
				if(isspace(reg.cuenta.Password[i]))contarEspacios++;//contar espacios
				
			
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
		fwrite(&reg,sizeof(cuentasProfe),1,arch);
	}
	
	fclose(arch);
	system("cls");	
}

void RegistrarRecepcionista()
{
	FILE *arch;
	usuarios reg;
	usuarios aux;
	char salir, ingresarNuevo, usuario[50];
	int opcion,contarCaracteres,contarMayusculas=0,contarMinusculas=0,contarDigit=0,contarPuntuacion=0,contarEspacios=0,comparar, b=0;
	bool banderaIngreso=false, validar=true;
	
	arch = fopen("Recepcionistas.dat", "a+b");
	
	printf("====Registrar Recepcionista====\n");
	
	printf("Apellido y nombre: ");
	_flushall();
	gets(reg.ApeNom);
	
	system("cls");
	
	do
	{
		contarCaracteres = 0;
		contarMayusculas=0;
		contarMinusculas=0;
		contarDigit=0;
		contarPuntuacion=0;
		contarEspacios=0;
		comparar = 0;
		validar = true;
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
		gets(reg.Usuario);
		rewind(arch);
		while(!feof(arch))//1. Ser único para cada usuario registrado.
		{
			fread(&aux,sizeof(usuarios),1,arch);
			if(strcmp(reg.Usuario,aux.Usuario)==0)validar=false;
		}
		contarCaracteres=strlen(reg.Usuario);
		if(contarCaracteres<6 || contarCaracteres>10)validar=false;//Cantidad mínima de 6 caracteres y máxima de 10
		for(int i=0;i<contarCaracteres;i++)//los cuales podrán ser letras, números y/o símbolos del conjunto {+,-,/,*,?,¿,!,¡}
		{
			if(isdigit(reg.Usuario[i])||isalpha(reg.Usuario[i])||ispunct(reg.Usuario[i]))	
			{
			//	validar=true;
			}
			else
			{
				validar=false;
			}
		}
		if(isupper(reg.Usuario[0]))validar=false;//Comenzar con una letra minúscula.
		for(int i=0;i<contarCaracteres;i++)//Tener al menos 2 letras mayúsculas.
		{
			if(isupper(reg.Usuario[i]))contarMayusculas++;
		}
		if(contarMayusculas<2)validar=false;
		for(int i=0;i<contarCaracteres;i++)//Tener como máximo 3 dígitos.
		{
			if(isdigit(reg.Usuario[i]))contarDigit++;
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
			printf("\nRegistro de Usuario Exitoso!");
			getch();
			system("cls");
		}		
	}while(validar==false && salir=='S');
	if(validar==true)
	{
		do
		{
			contarCaracteres = 0;
			contarMayusculas=0;
			contarMinusculas=0;
			contarDigit=0;
			contarPuntuacion=0;
			contarEspacios=0;
			comparar = 0;
			validar = true;
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
			_flushall();
			gets(reg.Password);
			contarCaracteres=strlen(reg.Password);
			for(int i=0;i<contarCaracteres;i++)//Deberá contener al menos una letra mayúscula, una letra minúscula y un número.
			{
				if(isalpha(reg.Password[i]))
				{
					if(isupper(reg.Password[i]))contarMayusculas++;
					if(islower(reg.Password[i]))contarMinusculas++;
					if(isalpha(reg.Password[i]))
					{
						if(isalpha(reg.Password[i+1]))
						{
							if(reg.Password[i]==(reg.Password[i+1]-1))validar=false;//validar que no sean letras consecutivas
						}
					}
				}
				
				if(isdigit(reg.Password[i]))
				{
					contarDigit++;//contar cantidad de numeros
					if(isdigit(reg.Password[i+1]))
					{
						if(isdigit(reg.Password[i+2]))
						{
							if(reg.Password[i]==(reg.Password[i+1]-1) && reg.Password[i+1]==(reg.Password[i+2]-1))validar=false;//validar que no hayan 3 numeros consecutivos
						}
					}
				}
				
				if(ispunct(reg.Password[i]))contarPuntuacion++;//contar signos de puntuacion
				if(isspace(reg.Password[i]))contarEspacios++;//contar espacios
				
			
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
		fwrite(&reg,sizeof(usuarios),1,arch);
	}
	
	fclose(arch);
	system("cls");
}

void ConteoRegistroAdmin(int *pe)
{
    *pe=*pe+1;
}
void ConteoRegistroRecep(int *per)
{
    *per=*per+1;
}


void AtencionesProfesionales()
{
	
	
}

void RankingAtenciones()
{
	
}
