


////////////////////////////////////////////////////////
// PROGRAMACION II | PROYECTO FINAL
// LESLIE SARAHY CAZARES MENDOZA | MATRICULA:1673459
///////////////////////////////////////////////////////

// LIBRERIAS Y COSILLAS DIVERSAS
#include <windows.h>
#include <fstream>
#include <CommDlg.h>
#include "resource.h"
#include <ctime>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "string"
#include "cstring"
#include <iostream>
#pragma comment(lib, "winmm.lib")
using namespace std;



//Estructuras
struct arreglosousuarioso {
	arreglosousuarioso *ant;

	char nombre[MAX_PATH];
	char usuario[MAX_PATH];
	char contraseña[MAX_PATH];
	char foto01[MAX_PATH];
	arreglosousuarioso *sig;
};

struct arreglosoproductoso {
	arreglosoproductoso*ant;
	char usuario[MAX_PATH];
	char nombre[MAX_PATH];
	float precio;
	char categoria[MAX_PATH];
	char sonido[MAX_PATH];
	char foto01[MAX_PATH];
	char foto02[MAX_PATH];
	bool promocion = false;
	arreglosoproductoso *sig;
};

struct arreglosopromocioso {
	arreglosopromocioso*ant;
	char usuario[MAX_PATH];
	char producto[MAX_PATH];
	char nombrepromocion[MAX_PATH];
	float porcentajepromocion;
	char descripcion[50];
	char fechainicio[MAX_PATH];
	char fechafinal[MAX_PATH];
	char horainicio[MAX_PATH];
	char horafinal[MAX_PATH];
	char AMPM01[MAX_PATH];
	char AMPM02[MAX_PATH];
	char alarma[MAX_PATH];
	bool auxilio = false;
	int diapromocion;

	arreglosopromocioso *sig;
};

struct arreglosocarroso {
	arreglosocarroso*ant;
	char usuario[MAX_PATH];
	char producto[MAX_PATH];
	char productodelusuariosubido[MAX_PATH];
	float cantidaddeproductos;
	float porcentajepromocion;
	float precioinicial;
	float preciofinal;
	bool promocion = false;
	arreglosocarroso *sig;
};


// Punteros principales
arreglosousuarioso *inicioU, *finU, *auxU, *nuevoU;
arreglosoproductoso *inicioP, *finP, *auxP, *nuevoP;
arreglosopromocioso *inicioPR, *finPR, *auxPR, *nuevoPR;
arreglosocarroso *inicioC, *finC, *auxC, *nuevoC;


// VARIABLES IMPORTANTES O BASURA
bool banderoso = false;
bool existe = false;
bool iniciosesion = false;
bool programosofin = false;
char usuariosoqueiniciosesion[50];
HBITMAP imagenosha, imagenosho;
OPENFILENAME pancho;
OPENFILENAME panchis;
char ArchivosoCancionIntroducida[MAX_PATH] = "";
char ArchivosoImagenIntroducida01[MAX_PATH] = "";
char ArchivosoImagenIntroducida02[MAX_PATH] = "";
static HBITMAP BMP01, BMP02, BMP2000;
char mp3[MAX_PATH] = "", comando[MAX_PATH];
FILE *auxilioso = NULL;
int panto = -1;
int panta = -1;
int pantato = -1;
int i = 0;
int pantequillosho = 1;
char temporal[MAX_PATH];
char pancentavo[MAX_PATH];
char pantrequilo[MAX_PATH];
char pantequigocho[MAX_PATH];
char pantequillochocho[MAX_PATH];
bool fecha01 = false;
bool fecha02 = false;
bool hora01 = false;
bool hora02 = false;

char *dia, *mes, *año;
char *hora, *minutos, *segundos;
time_t ACTUALTIME;
char pantecarfecha[80];
char pantecarhora[80];
char nombre[MAX_PATH], alarma[MAX_PATH], descripcion[MAX_PATH], nombreCITA[MAX_PATH];
time_t timeAux;
struct tm *timeinfoAux;
struct tm *timeinfo;
UINT timmer = 0;
time_t actualtime;
string mesdelafecha;
#define ID_5SECONDS 100
UINT TIMERID1 = 0;
UINT TIMERID2 = 0;
char pan05[MAX_PATH] = "false";
bool banderra = false;
char nombredemipromocionvalida[MAX_PATH];
int diadehoy;
bool revivirtimer = true;
bool eliminarusuario = false;
bool cargar = true;


// VARIABLES HANDLE | INSTANCE
HWND hDlgLogin = 0, Loginoso = 0, AgregadochoUsuariocho = 0, Cambiocho = 0, Tiendocho = 0, Productuochos = 0, AgregadochoProductocho = 0,
AgregadochoPromosiocho = 0, Promociochos = 0, Carrocho = 0, Alarmocho = 0;
HINSTANCE panoso;

// PROTOTIPOS DE LAS FUNCIONES
void CargarArchivosoU();
void GuardarArchivosoU();
void CargarArchivosoP();
void GuardarArchivosoP();
void CargarArchivosoPR();
void GuardarArchivosoPR();
void CargarArchivosoC();
void GuardarArchivosoC();


// PROTOTIPO DE LAS CALLBACK
BOOL CALLBACK Inicioso(HWND Loginoso, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Informacioso(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Registroso(HWND AgregadochoUsuariocho, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Cambioso(HWND Cambiocho, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Tiendoso(HWND Tiendocho, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Carritoso(HWND Carrocho, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Productuosos(HWND Productuochos, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AgregadosoProductoso(HWND AgregadochoProductocho, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Promocioso(HWND Promociochos, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AgregadosoPromocioso(HWND AgregadochoPromosiocho, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK PromocionosoExistententoso(HWND Alarmocho, UINT msg, WPARAM wParam, LPARAM lParam);


// FUNCIONES IMPORTANTES

//Guardar usuarios
void CargarArchivosoU() {

	fstream archivo("Archivo_Usuario.bin", ios::binary | ios::in);

	if (archivo.is_open()) {

		nuevoU = new arreglosousuarioso;
		archivo.read((char*)nuevoU, sizeof(arreglosousuarioso));
		while (archivo.eof() == false)
		{
			nuevoU->sig = NULL;
			nuevoU->ant = NULL;
			if (inicioU == NULL)
				inicioU = nuevoU;
			else
			{
				arreglosousuarioso*finalU = inicioU;
				while (finalU->sig != NULL)
				{
					finalU = finalU->sig;
				}


				arreglosousuarioso*ultimoU = finalU;
				ultimoU->sig = nuevoU;
				nuevoU->ant = ultimoU;
			}
			nuevoU = new arreglosousuarioso;
			archivo.read((char*)nuevoU, sizeof(arreglosousuarioso));
		}
		archivo.close();
	}


}
void GuardarArchivosoU() {

	fstream archivaldo("Archivo_Usuario.bin", ios::binary | ios::out | ios::trunc);

	if (inicioU != NULL) {  //Aqui se muestra la informacion nodo por nodo si la lista esta llena
		auxU = inicioU;

		if (archivaldo.is_open()) {


			auxU = inicioU;
			while (auxU != NULL)
			{
				archivaldo.write((char*)auxU, sizeof(arreglosousuarioso));
				auxU = auxU->sig;
			}

		}
	}
	else {
		MessageBox(0, "No se puede abrir el archivo", "", MB_ICONERROR);
	}
	archivaldo.close();

}
// Guardar Productos
void CargarArchivosoP() {

	fstream archivo("Archivo_Productos.bin", ios::binary | ios::in);

	if (archivo.is_open()) {

		nuevoP = new arreglosoproductoso;
		archivo.read((char*)nuevoP, sizeof(arreglosoproductoso));
		while (archivo.eof() == false)
		{
			nuevoP->sig = NULL;
			nuevoP->ant = NULL;
			if (inicioP == NULL)
				inicioP = nuevoP;
			else
			{
				arreglosoproductoso*finalP = inicioP;
				while (finalP->sig != NULL)
				{
					finalP = finalP->sig;
				}


				arreglosoproductoso*ultimoP = finalP;
				ultimoP->sig = nuevoP;
				nuevoP->ant = ultimoP;
			}
			nuevoP = new arreglosoproductoso;
			archivo.read((char*)nuevoP, sizeof(arreglosoproductoso));
		}
		archivo.close();
	}


}
void GuardarArchivosoP() {

	fstream archivaldo("Archivo_Productos.bin", ios::binary | ios::out | ios::trunc);

	if (inicioP != NULL) {  //Aqui se muestra la informacion nodo por nodo si la lista esta llena
		auxP = inicioP;

		if (archivaldo.is_open()) {


			auxP = inicioP;
			while (auxP != NULL)
			{
				archivaldo.write((char*)auxP, sizeof(arreglosoproductoso));
				auxP = auxP->sig;
			}

		}
	}
	else {
		MessageBox(0, "No se puede abrir el archivo", "", MB_ICONERROR);
	}
	archivaldo.close();

}
//Guardar Promociones
void CargarArchivosoPR() {

	fstream archivo("Archivo_Promocion.bin", ios::binary | ios::in);

	if (archivo.is_open()) {

		nuevoPR = new arreglosopromocioso;
		archivo.read((char*)nuevoPR, sizeof(arreglosopromocioso));
		while (archivo.eof() == false)
		{
			nuevoPR->sig = NULL;
			nuevoPR->ant = NULL;
			if (inicioPR == NULL)
				inicioPR = nuevoPR;
			else
			{
				arreglosopromocioso*finalPR = inicioPR;
				while (finalPR->sig != NULL)
				{
					finalPR = finalPR->sig;
				}


				arreglosopromocioso*ultimoPR = finalPR;
				ultimoPR->sig = nuevoPR;
				nuevoPR->ant = ultimoPR;
			}
			nuevoPR = new arreglosopromocioso;
			archivo.read((char*)nuevoPR, sizeof(arreglosopromocioso));
		}
		archivo.close();
	}


}
void GuardarArchivosoPR() {

	fstream archivaldo("Archivo_Promocion.bin", ios::binary | ios::out | ios::trunc);

	if (inicioPR != NULL) {  //Aqui se muestra la informacion nodo por nodo si la lista esta llena
		auxPR = inicioPR;

		if (archivaldo.is_open()) {


			auxPR = inicioPR;
			while (auxPR != NULL)
			{
				archivaldo.write((char*)auxPR, sizeof(arreglosopromocioso));
				auxPR = auxPR->sig;
			}

		}
	}
	else {
		MessageBox(0, "No se puede abrir el archivo", "", MB_ICONERROR);
	}
	archivaldo.close();

}
//Guardar Carrito
void CargarArchivosoC() {

	fstream archivo("Archivo_Carrito.bin", ios::binary | ios::in);

	if (archivo.is_open()) {

		nuevoC = new arreglosocarroso;
		archivo.read((char*)nuevoC, sizeof(arreglosocarroso));
		while (archivo.eof() == false)
		{
			nuevoC->sig = NULL;
			nuevoC->ant = NULL;
			if (inicioC == NULL)
				inicioC = nuevoC;
			else
			{
				arreglosocarroso*finalC = inicioC;
				while (finalC->sig != NULL)
				{
					finalC = finalC->sig;
				}


				arreglosocarroso*ultimoC = finalC;
				ultimoC->sig = nuevoC;
				nuevoC->ant = ultimoC;
			}
			nuevoC = new arreglosocarroso;
			archivo.read((char*)nuevoC, sizeof(arreglosocarroso));
		}
		archivo.close();
	}


}
void GuardarArchivosoC() {

	fstream archivaldo("Archivo_Carrito.bin", ios::binary | ios::out | ios::trunc);

	if (inicioC != NULL) {  //Aqui se muestra la informacion nodo por nodo si la lista esta llena
		auxC = inicioC;

		if (archivaldo.is_open()) {


			auxC = inicioC;
			while (auxC != NULL)
			{
				archivaldo.write((char*)auxC, sizeof(arreglosocarroso));
				auxC = auxC->sig;
			}

		}
	}
	else {
		MessageBox(0, "No se puede abrir el archivo", "", MB_ICONERROR);
	}
	archivaldo.close();

}

// WINAPI WINMAIN
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int showCmd)
{
	CargarArchivosoU();
	CargarArchivosoP();
	CargarArchivosoPR();
	CargarArchivosoC();
	panoso = hInstance;
	hDlgLogin = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_LOGIN), 0, Inicioso);
	ShowWindow(hDlgLogin, showCmd);

	MSG mensaje;
	ZeroMemory(&mensaje, sizeof(MSG));
	while (GetMessage(&mensaje, 0, 0, 0))
	{
		if (hDlgLogin == 0 || !IsDialogMessage(hDlgLogin, &mensaje))
		{
			TranslateMessage(&mensaje);
			DispatchMessage(&mensaje);
		}
	}
	return (int)mensaje.wParam;
}

// CALLBACKS


BOOL CALLBACK Inicioso(HWND Loginoso, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_INITDIALOG:
		imagenosha = (HBITMAP)LoadImage(NULL, "Logotipo_Rollei.bmp", IMAGE_BITMAP, 170, 170, LR_LOADFROMFILE);
		SendDlgItemMessage(Loginoso, IDC_PICTURE_LOGOLOGIN, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagenosha);
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_INFORMACION:
			DialogBox(panoso, MAKEINTRESOURCE(IDD_INFORMACION), Loginoso, Informacioso);
			return true;
		case ID_REGISTRARSE:
			DialogBox(panoso, MAKEINTRESOURCE(IDD_REGISTRO), Loginoso, Registroso);
			return true;
		case ID_CAMBIO:
			DialogBox(panoso, MAKEINTRESOURCE(IDD_CAMBIO), Loginoso, Cambioso);
			return true;
		case ID_INICIARSESION:
		{
			existe = false;
			char usuariochecar[50];
			SendDlgItemMessage(Loginoso, IDC_EDIT_UL, WM_GETTEXT, 50, (LPARAM)usuariochecar);

			char contraseñachecar[50];
			SendDlgItemMessage(Loginoso, IDC_EDIT_CL, WM_GETTEXT, 50, (LPARAM)contraseñachecar);

			auxU = inicioU;
			while (auxU != NULL) {
				if (strcmp(auxU->usuario, usuariochecar) == 0 && strcmp(auxU->contraseña, contraseñachecar) == 0) {
					existe = true;
					iniciosesion = true;
					strcpy_s(usuariosoqueiniciosesion, auxU->usuario);
					SendDlgItemMessage(Loginoso, IDC_EDIT_UL, WM_SETTEXT, 50, (LPARAM)"");
					SendDlgItemMessage(Loginoso, IDC_EDIT_CL, WM_SETTEXT, 50, (LPARAM)"");
					DialogBox(panoso, MAKEINTRESOURCE(IDD_TIENDA), Loginoso, Tiendoso);
					break;
				}
				auxU = auxU->sig;
			}
			if (existe != true) {
				MessageBox(Loginoso, "Usuario y/o contraseñas incorrectas", "ERROR", MB_OK);
			}
			return true;
		}
		case ID_SALIR:
			GuardarArchivosoU();
			GuardarArchivosoP();
			GuardarArchivosoPR();
			GuardarArchivosoC();
			DestroyWindow(Loginoso);
			return true;
		}
		return true;
	case WM_CLOSE:
		GuardarArchivosoU();
		GuardarArchivosoP();
		GuardarArchivosoPR();
		GuardarArchivosoC();
		DestroyWindow(Loginoso);
		return true;
	case WM_DESTROY:
		GuardarArchivosoU();
		GuardarArchivosoP();
		GuardarArchivosoPR();
		GuardarArchivosoC();
		PostQuitMessage(0);
		return true;
	}
	return false;
}

BOOL CALLBACK Informacioso(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg)
	{
	case WM_INITDIALOG:
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_OK:
			EndDialog(hDlg, 0);
			return true;
		}
		return true;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return true;
	case WM_DESTROY:
		EndDialog(hDlg, 0);
		return true;
	}
	return false;

}

BOOL CALLBACK Registroso(HWND AgregadochoUsuariocho, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg)
	{
	case WM_INITDIALOG:
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_COMPROBARNUR: {
			existe = false;
			char usuariochequeador[50];
			SendDlgItemMessage(AgregadochoUsuariocho, IDC_EDIT_NUR, WM_GETTEXT, 50, (LPARAM)usuariochequeador);

			auxU = inicioU;
			while (auxU != NULL) {
				if (strcmp(auxU->usuario, usuariochequeador) == 0) {
					existe = true;
					break;
				}
				auxU = auxU->sig;
			}
			if (existe == false) {
				MessageBox(AgregadochoUsuariocho, "Usuario Disponible.", "¡PERFECTO!", MB_OK);
				SendDlgItemMessage(AgregadochoUsuariocho, IDC_CHECK_UDR, BM_SETCHECK, BST_CHECKED, 0);

			}
			else {
				banderoso = false;
				MessageBox(0, "Usuario no disponible. Favor de ingresar otro.", "ERROR", MB_ICONERROR | MB_OK);
			}
			return true;
		}
		case ID_EXAMINARR: {
			ZeroMemory(&panchis, sizeof(panchis));
			panchis.lStructSize = sizeof(panchis);
			panchis.hwndOwner = AgregadochoUsuariocho;
			panchis.lpstrFilter = "BMP (*.bmp)\0*.bmp\0";
			panchis.lpstrFile = ArchivosoImagenIntroducida01;
			panchis.nMaxFile = MAX_PATH;
			panchis.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
			panchis.lpstrDefExt = ".bmp";
			if (GetSaveFileName(&panchis) == TRUE) {
				BMP01 = (HBITMAP)LoadImage(NULL, ArchivosoImagenIntroducida01, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
				SendDlgItemMessage(AgregadochoUsuariocho, IDC_PICTURE_FR, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP01);
				SendDlgItemMessage(AgregadochoUsuariocho, IDC_EDIT_URLFR, WM_SETTEXT, NULL, (LPARAM)ArchivosoImagenIntroducida01);
			}
			else {
				MessageBox(AgregadochoUsuariocho, "No se pudo cargar el archivo.", "Error", MB_ICONERROR | MB_OK);
			}
			return true;
		}
		case ID_ACEPTARR: {
			if (existe == false) {
				nuevoU = new arreglosousuarioso;
				nuevoU->ant = NULL;
				nuevoU->sig = NULL;

				//NOMBRE
				char pantequilla[50];
				SendDlgItemMessage(AgregadochoUsuariocho, IDC_EDIT_NR, WM_GETTEXT, 50, (LPARAM)pantequilla);
				for (int i = 0; pantequilla[i]; i++) {          // Aqui se esta acomodando de minusculas a  mayusculas usando la 
					pantequilla[i] = toupper(pantequilla[i]);   // funcion toupper
					banderoso = true;
				}
				strcpy_s(nuevoU->nombre, pantequilla);

				//USUARIO
				char pantequillar[50];
				SendDlgItemMessage(AgregadochoUsuariocho, IDC_EDIT_NUR, WM_GETTEXT, 50, (LPARAM)pantequillar);
				auxU = inicioU;
				while (auxU != NULL) {
					if (strcmp(auxU->usuario, pantequillar) == 0) {
						existe = true;
						banderoso = false;
						break;
					}
					auxU = auxU->sig;
				}

				if (existe != true) {
					banderoso = true;
				}

				strcpy_s(nuevoU->usuario, pantequillar);

				//CONTRASEÑA
				char pantequillolo[50];
				SendDlgItemMessage(AgregadochoUsuariocho, IDC_EDIT_CR, WM_GETTEXT, 50, (LPARAM)pantequillolo);

				strcpy_s(nuevoU->contraseña, pantequillolo);


				//IMAGEN
				char panteimagen01[MAX_PATH];
				SendDlgItemMessage(AgregadochoUsuariocho, IDC_EDIT_URLFR, WM_GETTEXT, MAX_PATH, (LPARAM)panteimagen01);
				strcpy_s(nuevoU->foto01, panteimagen01);

			}


			if (banderoso == true && existe == false) {

				if (inicioU == NULL) {
					inicioU = nuevoU;
				}
				else {
					auxU = inicioU;
					while (auxU->sig != NULL) {
						auxU = auxU->sig;
					}
					auxU->sig = nuevoU;
					nuevoU->ant = auxU;
				}

				MessageBox(AgregadochoUsuariocho, "Registro Exitoso.", "¡PERFECTO!", MB_OK);
				EndDialog(AgregadochoUsuariocho, 0);

			}
			else {
				if (existe == true) {
					MessageBox(0, "Usuario no disponible. Favor de ingresar otro.", "ERROR", MB_ICONERROR | MB_OK);
				}
				MessageBox(0, "Error con los datos ingresados. Favor de ingresar o corregir los datos.", "ERROR", MB_ICONERROR | MB_OK);
			}

			return true; }
		case ID_CANCELARR:
			EndDialog(AgregadochoUsuariocho, 0);
			return true;
		}
		return true;
	case WM_CLOSE:
		EndDialog(AgregadochoUsuariocho, 0);
		return true;
	case WM_DESTROY:
		EndDialog(AgregadochoUsuariocho, 0);
		return true;
	}
	return false;

}

BOOL CALLBACK Cambioso(HWND Cambiocho, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg)
	{
	case WM_INITDIALOG:

		eliminarusuario = false;
		if (iniciosesion == true) {

			auxU = inicioU;
			while (auxU != NULL) {
				if (strcmp(auxU->usuario, usuariosoqueiniciosesion) == 0) {
					existe = true;
					banderoso = false;
					break;
				}
				auxU = auxU->sig;
			}

			if (existe == true) {
				SendDlgItemMessage(Cambiocho, IDC_EDIT_NUCNCI, WM_SETTEXT, 50, (LPARAM)auxU->usuario);
				SendDlgItemMessage(Cambiocho, IDC_EDIT_NNCNCI, WM_SETTEXT, 50, (LPARAM)auxU->nombre);
				SendDlgItemMessage(Cambiocho, IDC_EDIT_CCNCI, WM_SETTEXT, 50, (LPARAM)auxU->contraseña);
				SendDlgItemMessage(Cambiocho, IDC_EDIT_URLFCNCI, WM_SETTEXT, 50, (LPARAM)auxU->foto01);

				BMP01 = (HBITMAP)LoadImage(NULL, auxU->foto01, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
				SendDlgItemMessage(Cambiocho, IDC_PICTURE_CNCI, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP01);
			}
		}
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_OK_UCNCI: {
			char buscarusuario[50];
			SendDlgItemMessage(Cambiocho, IDC_EDIT_NUCNCI, WM_GETTEXT, 50, (LPARAM)buscarusuario);

			auxU = inicioU;
			while (auxU != NULL) {
				if (strcmp(auxU->usuario, buscarusuario) == 0) {
					existe = true;
					banderoso = false;
					break;
				}
				auxU = auxU->sig;
			}

			if (existe == true) {
				SendDlgItemMessage(Cambiocho, IDC_EDIT_NNCNCI, WM_SETTEXT, 50, (LPARAM)auxU->nombre);
				SendDlgItemMessage(Cambiocho, IDC_EDIT_CCNCI, WM_SETTEXT, 50, (LPARAM)auxU->contraseña);
				SendDlgItemMessage(Cambiocho, IDC_EDIT_URLFCNCI, WM_SETTEXT, 50, (LPARAM)auxU->foto01);

				BMP01 = (HBITMAP)LoadImage(NULL, auxU->foto01, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
				SendDlgItemMessage(Cambiocho, IDC_PICTURE_CNCI, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP01);
			}
			else {
				banderoso = false;
				MessageBox(Cambiocho, "Usuario no encontrado.", "ERROR", MB_ICONERROR | MB_OK);
			}
			return true;
		}
		case ID_EXAMINAR_CNCI: {
			ZeroMemory(&panchis, sizeof(panchis));
			panchis.lStructSize = sizeof(panchis);
			panchis.hwndOwner = Cambiocho;
			panchis.lpstrFilter = "BMP (*.bmp)\0*.bmp\0";
			panchis.lpstrFile = ArchivosoImagenIntroducida01;
			panchis.nMaxFile = MAX_PATH;
			panchis.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
			panchis.lpstrDefExt = ".bmp";
			if (GetSaveFileName(&panchis) == TRUE) {
				BMP01 = (HBITMAP)LoadImage(NULL, ArchivosoImagenIntroducida01, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
				SendDlgItemMessage(Cambiocho, IDC_PICTURE_CNCI, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP01);
				SendDlgItemMessage(Cambiocho, IDC_EDIT_URLFCNCI, WM_SETTEXT, NULL, (LPARAM)ArchivosoImagenIntroducida01);
			}
			else {
				MessageBox(Cambiocho, "No se pudo cargar el archivo.", "Error", MB_ICONERROR | MB_OK);
			}
			return true;
		}
		case ID_ELIMINAR_CNCI: {
			auxU = inicioU;
			auxP = inicioP;
			auxPR = inicioPR;
			auxC = inicioC;
			arreglosocarroso *auxCC = inicioC;
			char eliminacion[MAX_PATH];
			SendDlgItemMessage(Cambiocho, IDC_EDIT_NUCNCI, WM_GETTEXT, MAX_PATH, (LPARAM)eliminacion);

			bool elimina = true;
			bool eliminaUsuario = false;
			bool eliminaProducto = false;
			bool eliminaPromocion = false;
			bool eliminaCarrito = false;

			if (elimina == true) {

				while (auxC != NULL) {
					if (strcmp(auxC->usuario, eliminacion) == 0) {
						arreglosocarroso *eliminarC = auxC;

						if (eliminarC->sig == NULL && eliminarC->ant == NULL) {
							eliminarC = inicioC;
							inicioC = NULL;
							auxC = NULL;
							delete eliminarC;
						}
						else if (eliminarC->ant == NULL) {
							auxC = auxC->sig;
							inicioC = eliminarC->sig;
							inicioC->sig = NULL;
							eliminarC->sig = NULL;
							delete eliminarC;


						}
						else if (eliminarC->sig == NULL) {
							auxC = eliminarC->ant;
							eliminarC->ant->sig = NULL;
							delete eliminarC;


						}
						else {
							auxC = eliminarC->ant;
							auxC->sig = eliminarC->ant;
							eliminarC->sig->ant = auxC;
							delete eliminarC;
						}

						eliminaCarrito = true;
						break;

					}
					auxC = auxC->sig;
				}

				
				while (auxCC != NULL) {
					if (strcmp(auxCC->productodelusuariosubido, eliminacion) == 0) {
						arreglosocarroso *eliminarCC = auxC;

						if (eliminarCC->sig == NULL && eliminarCC->ant == NULL) {
							eliminarCC = inicioC;
							inicioC = NULL;
							auxCC = NULL;
							delete eliminarCC;
						}
						else if (eliminarCC->ant == NULL) {
							auxCC = auxCC->sig;
							inicioC = eliminarCC->sig;
							inicioC->sig = NULL;
							eliminarCC->sig = NULL;
							delete eliminarCC;


						}
						else if (eliminarCC->sig == NULL) {
							auxCC = eliminarCC->ant;
							eliminarCC->ant->sig = NULL;
							delete eliminarCC;


						}
						else {
							auxCC = eliminarCC->ant;
							auxCC->sig = eliminarCC->ant;
							eliminarCC->sig->ant = auxCC;
							delete eliminarCC;
						}
						
					}
					auxCC = auxCC->sig;
				}


				while (auxPR != NULL) {
					if (strcmp(auxPR->usuario, eliminacion) == 0) {
						arreglosopromocioso *eliminarPR = auxPR;

						if (eliminarPR->sig == NULL && eliminarPR->ant == NULL) {
							eliminarPR = inicioPR;
							inicioPR = NULL;
							auxPR = NULL;
							delete eliminarPR;
						}
						else if (eliminarPR->ant == NULL) {
							auxPR = auxPR->sig;
							inicioPR = eliminarPR->sig;
							inicioPR->sig = NULL;
							eliminarPR->sig = NULL;
							delete eliminarPR;


						}
						else if (eliminarPR->sig == NULL) {
							auxPR = eliminarPR->ant;
							eliminarPR->ant->sig = NULL;
							delete eliminarPR;


						}
						else {
							auxPR = eliminarPR->ant;
							auxPR->sig = eliminarPR->ant;
							eliminarPR->sig->ant = auxPR;
							delete eliminarPR;
						}

						eliminaPromocion = true;
						continue;
					}
					auxPR = auxPR->sig;
				}

				while (auxP != NULL) {
					if (strcmp(auxP->usuario, eliminacion) == 0) {
						arreglosoproductoso *eliminarP = auxP;

						if (eliminarP->sig == NULL && eliminarP->ant == NULL) {
							eliminarP = inicioP;
							inicioP = NULL;
							auxP = NULL;
							delete eliminarP;
						}
						else if (eliminarP->ant == NULL) {
							auxP = auxP->sig;
							inicioP = eliminarP->sig;
							inicioP->sig = NULL;
							eliminarP->sig = NULL;
							delete eliminarP;


						}
						else if (eliminarP->sig == NULL) {
							auxP = eliminarP->ant;
							eliminarP->ant->sig = NULL;
							delete eliminarP;


						}
						else {
							auxP = eliminarP->ant;
							auxP->sig = eliminarP->ant;
							eliminarP->sig->ant = auxP;
							delete eliminarP;
						}

						eliminaProducto = true;
						continue;
					}
					auxP = auxP->sig;
				}

				while (auxU != NULL) {
					if (strcmp(auxU->usuario, eliminacion) == 0) {
						arreglosousuarioso *eliminarU = auxU;

						if (eliminarU->sig == NULL && eliminarU->ant == NULL) {
							eliminarU = inicioU;
							inicioU = NULL;
							auxU = NULL;
							delete eliminarU;
						}
						else if (eliminarU->ant == NULL) {
							auxU = auxU->sig;
							inicioU = eliminarU->sig;
							inicioU->sig = NULL;
							eliminarU->sig = NULL;
							delete eliminarU;


						}
						else if (eliminarU->sig == NULL) {
							auxU = eliminarU->ant;
							eliminarU->ant->sig = NULL;
							delete eliminarU;


						}
						else {
							auxU = eliminarU->ant;
							auxU->sig = eliminarU->ant;
							eliminarU->sig->ant = auxU;
							delete eliminarU;
						}

						eliminaUsuario = true;
						break;
					}
					auxU = auxU->sig;
				}


			}

			if (eliminaUsuario != true && eliminaProducto != true && eliminaPromocion != true) {
				MessageBox(Cambiocho, "La Eliminación Fallo.", "ERROR", MB_OK);
			}
			else {
				MessageBox(Cambiocho, "Eliminación Exitosa", "¡PERFECTO!", MB_OK);
				eliminarusuario = true;
				EndDialog(Cambiocho, 0);
			}
			return true;
		}
		case ID_ACEPTARNCI: {

			//NOMBRE
			char pantequilla[50];
			SendDlgItemMessage(Cambiocho, IDC_EDIT_NNCNCI, WM_GETTEXT, 50, (LPARAM)pantequilla);
			for (int i = 0; pantequilla[i]; i++) {          // Aqui se esta acomodando de minusculas a  mayusculas usando la 
				pantequilla[i] = toupper(pantequilla[i]);   // funcion toupper
				banderoso = true;
			}

			//CONTRASEÑA
			char pantequillolo[50];
			SendDlgItemMessage(Cambiocho, IDC_EDIT_CCNCI, WM_GETTEXT, 50, (LPARAM)pantequillolo);

			//IMAGEN
			char panteimagen01[MAX_PATH];
			SendDlgItemMessage(Cambiocho, IDC_EDIT_URLFCNCI, WM_GETTEXT, MAX_PATH, (LPARAM)panteimagen01);


			if (banderoso == true) {

				strcpy_s(auxU->nombre, pantequilla);
				strcpy_s(auxU->contraseña, pantequillolo);
				strcpy_s(auxU->foto01, panteimagen01);

				MessageBox(Cambiocho, "Cambio Exitoso.", "¡PERFECTO!", MB_OK);
				EndDialog(Cambiocho, 0);

			}
			else {
				MessageBox(Cambiocho, "Error con los datos ingresados. Favor de ingresar o corregir los datos.", "ERROR", MB_ICONERROR | MB_OK);
			}

			return true;
		}
		case ID_CANCELARNCI: {
			EndDialog(Cambiocho, 0);
			return true;
		}
		}
		return true;
	case WM_CLOSE:
		EndDialog(Cambiocho, 0);
		return true;
	case WM_DESTROY:
		EndDialog(Cambiocho, 0);
		return true;

	}
	return false;

}

BOOL CALLBACK Tiendoso(HWND Tiendocho, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg)
	{
	case WM_INITDIALOG: {

		if (revivirtimer == true) {
			TIMERID2 = SetTimer(Tiendocho, ID_5SECONDS, 10000, NULL);
		}

		if (cargar == true) {
			MessageBox(0, "Espere a que carguen completamente los datos. Una pantalla se desplegará cuando esto suceda.", "CARGANDO ...", MB_OK);
		}


		BMP01 = (HBITMAP)LoadImage(NULL, "Logotipo_Rollei.bmp", IMAGE_BITMAP, 125, 125, LR_LOADFROMFILE);
		SendDlgItemMessage(Tiendocho, IDC_PICTURELOGOGO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP01);

		BMP02 = (HBITMAP)LoadImage(NULL, "logotipo.bmp", IMAGE_BITMAP, 494, 80, LR_LOADFROMFILE);
		SendDlgItemMessage(Tiendocho, IDC_PICTUREGOGO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP02);


		auxU = inicioU;
		while (auxU != NULL) {
			if (strcmp(auxU->usuario, usuariosoqueiniciosesion) == 0) {
				SendDlgItemMessage(Tiendocho, IDC_EDIT_NUT, WM_SETTEXT, 50, (LPARAM)auxU->usuario);
				BMP2000 = (HBITMAP)LoadImage(NULL, auxU->foto01, IMAGE_BITMAP, 125, 125, LR_LOADFROMFILE);
				SendDlgItemMessage(Tiendocho, IDC_PICTURE_FUT, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP2000);
				break;
			}
			auxU = auxU->sig;
		}


		imagenosha = (HBITMAP)LoadImage(NULL, "Marca_Rollei.bmp", IMAGE_BITMAP, 170, 170, LR_LOADFROMFILE);
		SendDlgItemMessage(Loginoso, IDC_PICTURE_LOGOLOGIN, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagenosha);

		SendDlgItemMessage(Tiendocho, IDC_COMBO_CATEGORIAT, CB_ADDSTRING, 0, (LPARAM)"CD");
		SendDlgItemMessage(Tiendocho, IDC_COMBO_CATEGORIAT, CB_ADDSTRING, 0, (LPARAM)"DVD");
		SendDlgItemMessage(Tiendocho, IDC_COMBO_CATEGORIAT, CB_ADDSTRING, 0, (LPARAM)"BLU-RAY");
		SendDlgItemMessage(Tiendocho, IDC_COMBO_CATEGORIAT, CB_ADDSTRING, 0, (LPARAM)"GAMES");
		SendDlgItemMessage(Tiendocho, IDC_COMBO_CATEGORIAT, CB_ADDSTRING, 0, (LPARAM)"MERCANCÍA OFICIAL");
		SendDlgItemMessage(Tiendocho, IDC_COMBO_CATEGORIAT, CB_ADDSTRING, 0, (LPARAM)"INSTRUMENTOS MUSICALES");
		SendDlgItemMessage(Tiendocho, IDC_COMBO_CATEGORIAT, CB_ADDSTRING, 0, (LPARAM)"ELECTRÓNICA");

		SendDlgItemMessage(Tiendocho, IDC_COMBO_CANTIDADPRODUCTOST, WM_SETTEXT, 0, (LPARAM)"1");
		SendDlgItemMessage(Tiendocho, IDC_COMBO_CANTIDADPRODUCTOST, CB_INSERTSTRING, 0, (LPARAM)"1");
		SendDlgItemMessage(Tiendocho, IDC_COMBO_CANTIDADPRODUCTOST, CB_INSERTSTRING, 0, (LPARAM)"2");
		SendDlgItemMessage(Tiendocho, IDC_COMBO_CANTIDADPRODUCTOST, CB_INSERTSTRING, 0, (LPARAM)"3");
		SendDlgItemMessage(Tiendocho, IDC_COMBO_CANTIDADPRODUCTOST, CB_INSERTSTRING, 0, (LPARAM)"4");
		SendDlgItemMessage(Tiendocho, IDC_COMBO_CANTIDADPRODUCTOST, CB_INSERTSTRING, 0, (LPARAM)"5");
		SendDlgItemMessage(Tiendocho, IDC_COMBO_CANTIDADPRODUCTOST, CB_INSERTSTRING, 0, (LPARAM)"6");
		SendDlgItemMessage(Tiendocho, IDC_COMBO_CANTIDADPRODUCTOST, CB_INSERTSTRING, 0, (LPARAM)"7");
		SendDlgItemMessage(Tiendocho, IDC_COMBO_CANTIDADPRODUCTOST, CB_INSERTSTRING, 0, (LPARAM)"8");
		SendDlgItemMessage(Tiendocho, IDC_COMBO_CANTIDADPRODUCTOST, CB_INSERTSTRING, 0, (LPARAM)"9");
		SendDlgItemMessage(Tiendocho, IDC_COMBO_CANTIDADPRODUCTOST, CB_INSERTSTRING, 0, (LPARAM)"10");

		SendDlgItemMessage(Tiendocho, IDC_EDIT_DESCUENTOT, WM_SETTEXT, 0, (LPARAM)"0");
		SendDlgItemMessage(Tiendocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONT, WM_SETTEXT, 0, (LPARAM)"0");
		SendDlgItemMessage(Tiendocho, IDC_EDIT_PRECIOFINALCONPROMOCIONT, WM_SETTEXT, 0, (LPARAM)"0");

		SendDlgItemMessage(Tiendocho, IDC_COMBO_PRODUCTOSDISPONIBLEST, CB_RESETCONTENT, 0, 0);
		auxP = inicioP;

		while (auxP != NULL)
		{
			SendDlgItemMessage(Tiendocho, IDC_COMBO_PRODUCTOSDISPONIBLEST, CB_ADDSTRING, 0, (LPARAM)auxP->nombre);
			auxP = auxP->sig;
		}


		return true;
	}

	case WM_TIMER: {

		if (cargar == true) {
			MessageBox(0, "Se han cargado perfectamente los datos.", "¡PERFECTO!", MB_OK);
			cargar = false;
		}


		int DDACTUAL, MMACTUAL, AAAAACTUAL, HHACTUAL, MTACTUAL, SSACTUAL;
		int DDINICIOINT, MMINICIOINT, AAAAINICIOINT, HHINICIOINT, MTINICIOINT, SSINICIOINT;
		int DDFINALINT, MMFINALINT, AAAAFINALINT, HHFINALINT, MTFINALINT, SSFINALINT;
		int panMMDDINICIOINT, panHHMMSSINICIOINT, panMMDDFINALINT, panHHMMSSFINALINT, panMMDDACTUALINT, panHHMTSSACTUALINT;
		int DDMMAAAAINICIOINT, DDMMAAAAFINALINT, DDMMAAAAACTUALINT;
		int HHMTSSINICIOINT, HHMTSSFINALINT, HHMTSSACTUALINT;
	

		char DDACTUAL02[MAX_PATH];
		char MMACTUAL02[MAX_PATH];
		char HHACTUAL02[MAX_PATH];
		char MTACTUAL02[MAX_PATH];
		char SSACTUAL02[MAX_PATH];
		char DDMMAAAAACTUAL[MAX_PATH];
		char HHMTSSACTUAL[MAX_PATH];

		//timeinfo = localtime(&actualtime);
		//strftime(fechaactual, 80, "%d/%m/%Y", timeinfo);
		//strftime(horaactual, 80, "%I:%M:%S", timeinfo);

		time(&actualtime);
		timeinfo = localtime(&actualtime);
		DDACTUAL = timeinfo->tm_mday;
		MMACTUAL = timeinfo->tm_mon + 1;
		AAAAACTUAL = timeinfo->tm_year + 1900;
		HHACTUAL = timeinfo->tm_hour;
		MTACTUAL = timeinfo->tm_min;
		SSACTUAL = timeinfo->tm_sec;
		//char pan = timeinfo->tm_isdst;



		//strftime(DDMMAAAAACTUAL, 80, "%d/%m/%Y", timeinfo);
		//strftime(HHMTSSACTUAL, 80, "%I:%M:%S", timeinfo);

		strftime(DDMMAAAAACTUAL, 80, "%Y/%m/%d", timeinfo);
		strftime(HHMTSSACTUAL, 80, "%I:%M:%S", timeinfo);


		//itoa(DDMMAAAAACTUALINT, DDMMAAAAACTUAL, 10);
		//itoa(HHMTSSACTUALINT, HHMTSSACTUAL, 10);

		itoa(DDACTUAL, DDACTUAL02, 10);
		itoa(MMACTUAL, MMACTUAL02, 10);
		itoa(HHACTUAL, HHACTUAL02, 10);
		itoa(MTACTUAL, MTACTUAL02, 10);
		itoa(SSACTUAL, SSACTUAL02, 10);



		switch (DDACTUAL02[MAX_PATH]) {
		case '0':
			strcpy_s(SSACTUAL02, "00");
			break;
		case '1':
			strcpy_s(SSACTUAL02, "01");
			break;
		case '2':
			strcpy_s(SSACTUAL02, "02");
			break;
		case '3':
			strcpy_s(SSACTUAL02, "03");
			break;
		case '4':
			strcpy_s(SSACTUAL02, "04");
			break;
		case '5':
			strcpy_s(SSACTUAL02, "05");
			break;
		case '6':
			strcpy_s(SSACTUAL02, "06");
			break;
		case '7':
			strcpy_s(SSACTUAL02, "07");
			break;
		case '8':
			strcpy_s(SSACTUAL02, "08");
			break;
		case '9':
			strcpy_s(SSACTUAL02, "09");
			break;
		}
		switch (MMACTUAL02[MAX_PATH]) {
		case '0':
			strcpy_s(SSACTUAL02, "00");
			break;
		case '1':
			strcpy_s(SSACTUAL02, "01");
			break;
		case '2':
			strcpy_s(SSACTUAL02, "02");
			break;
		case '3':
			strcpy_s(SSACTUAL02, "03");
			break;
		case '4':
			strcpy_s(SSACTUAL02, "04");
			break;
		case '5':
			strcpy_s(SSACTUAL02, "05");
			break;
		case '6':
			strcpy_s(SSACTUAL02, "06");
			break;
		case '7':
			strcpy_s(SSACTUAL02, "07");
			break;
		case '8':
			strcpy_s(SSACTUAL02, "08");
			break;
		case '9':
			strcpy_s(SSACTUAL02, "09");
			break;
		}
		switch (HHACTUAL02[MAX_PATH]) {
		case '0':
			strcpy_s(SSACTUAL02, "00");
			break;
		case '1':
			strcpy_s(SSACTUAL02, "01");
			break;
		case '2':
			strcpy_s(SSACTUAL02, "02");
			break;
		case '3':
			strcpy_s(SSACTUAL02, "03");
			break;
		case '4':
			strcpy_s(SSACTUAL02, "04");
			break;
		case '5':
			strcpy_s(SSACTUAL02, "05");
			break;
		case '6':
			strcpy_s(SSACTUAL02, "06");
			break;
		case '7':
			strcpy_s(SSACTUAL02, "07");
			break;
		case '8':
			strcpy_s(SSACTUAL02, "08");
			break;
		case '9':
			strcpy_s(SSACTUAL02, "09");
			break;
		}
		switch (MTACTUAL02[MAX_PATH]) {
		case '0':
			strcpy_s(SSACTUAL02, "00");
			break;
		case '1':
			strcpy_s(SSACTUAL02, "01");
			break;
		case '2':
			strcpy_s(SSACTUAL02, "02");
			break;
		case '3':
			strcpy_s(SSACTUAL02, "03");
			break;
		case '4':
			strcpy_s(SSACTUAL02, "04");
			break;
		case '5':
			strcpy_s(SSACTUAL02, "05");
			break;
		case '6':
			strcpy_s(SSACTUAL02, "06");
			break;
		case '7':
			strcpy_s(SSACTUAL02, "07");
			break;
		case '8':
			strcpy_s(SSACTUAL02, "08");
			break;
		case '9':
			strcpy_s(SSACTUAL02, "09");
			break;
		}
		switch (SSACTUAL02[MAX_PATH]) {
		case '0':
			strcpy_s(SSACTUAL02, "00");
			break;
		case '1':
			strcpy_s(SSACTUAL02, "01");
			break;
		case '2':
			strcpy_s(SSACTUAL02, "02");
			break;
		case '3':
			strcpy_s(SSACTUAL02, "03");
			break;
		case '4':
			strcpy_s(SSACTUAL02, "04");
			break;
		case '5':
			strcpy_s(SSACTUAL02, "05");
			break;
		case '6':
			strcpy_s(SSACTUAL02, "06");
			break;
		case '7':
			strcpy_s(SSACTUAL02, "07");
			break;
		case '8':
			strcpy_s(SSACTUAL02, "08");
			break;
		case '9':
			strcpy_s(SSACTUAL02, "09");
			break;
		}



		string DDACTUAL01 = string(DDACTUAL02);
		string MMACTUAL01 = string(MMACTUAL02);
		string HHACTUAL01 = string(HHACTUAL02);
		string MTACTUAL01 = string(MTACTUAL02);
		string SSACTUAL01 = string(SSACTUAL02);

		string panMMDDACTUAL = MMACTUAL01 + DDACTUAL01;
		const char* panMMDDACTUAL01 = panMMDDACTUAL.c_str();
		panMMDDACTUALINT = atoi(panMMDDACTUAL01);
		diadehoy = panMMDDACTUALINT;

		string panHHMTSSACTUAL = HHACTUAL01 + MTACTUAL01 + SSACTUAL01;
		const char* panHHMTSSACTUAL01 = panHHMTSSACTUAL.c_str();
		panHHMTSSACTUALINT = atoi(panHHMTSSACTUAL01);


		bool pan = false;
		auxP = inicioP;
		auxPR = inicioPR;
		bool banderrochalista = false;

		if (auxPR != NULL) {

			while (auxP != NULL) {
				
				while (auxPR != NULL) {

					

					string fechainicio = string(auxPR->fechainicio);
					string fechafinal = string(auxPR->fechafinal);
					string horainicio = string(auxPR->horainicio);
					string horafinal = string(auxPR->horafinal);

					string DDINICIO = fechainicio.substr(0, 2);
					const char* DDINICIO01 = DDINICIO.c_str();
					DDINICIOINT = atoi(DDINICIO01);

					string MMINICIO = fechainicio.substr(3, 2);
					const char* MMINICIO01 = MMINICIO.c_str();
					MMINICIOINT = atoi(MMINICIO01);

					//////////////////////////////////////////////
					string panMMDDINICIO = MMINICIO + DDINICIO;
					const char* panMMDDINICIO01 = panMMDDINICIO.c_str();
					panMMDDINICIOINT = atoi(panMMDDINICIO01);
					//////////////////////////////////////////////

					string AAAAINICIO = fechainicio.substr(6, 9);
					const char* AAAAINICIO01 = AAAAINICIO.c_str();
					AAAAINICIOINT = atoi(AAAAINICIO01);


					//////////////////////////////////////////////////

					string stringAAAAMMDDINICIAL = AAAAINICIO + "/" + MMINICIO + "/" + DDINICIO;
					const char* AAAAMMDDINICIAL = stringAAAAMMDDINICIAL.c_str();

					////////////////////////////////////////////////////

					string HHINICIO = horainicio.substr(0, 2);
					const char* HHINICIO01 = HHINICIO.c_str();
					HHINICIOINT = atoi(HHINICIO01);

					string MTINICIO = horainicio.substr(3, 2);
					const char* MTINICIO01 = MTINICIO.c_str();
					MTINICIOINT = atoi(MTINICIO01);

					string SSINICIO = horainicio.substr(6, 7);
					const char* SSINICIO01 = SSINICIO.c_str();
					SSINICIOINT = atoi(SSINICIO01);

					////////////////////////////////////////////////////////
					string panHHMMSSINICIO = HHINICIO + MTINICIO + SSINICIO;
					const char* panHHMMSSINICIO01 = panHHMMSSINICIO.c_str();
					panHHMMSSINICIOINT = atoi(panHHMMSSINICIO01);
					////////////////////////////////////////////////////////

					////////////////////////////////////////////////////////////////////			
					string DDFINAL = fechafinal.substr(0, 2);
					const char* DDFINAL01 = DDFINAL.c_str();
					DDFINALINT = atoi(DDFINAL01);

					string MMFINAL = fechafinal.substr(3, 2);
					const char* MMFINAL01 = MMFINAL.c_str();
					MMFINALINT = atoi(MMFINAL01);

					/////////////////////////////////////////////////
					string panMMDDFINAL = MMFINAL + DDFINAL;
					const char* panMMDDFINAL01 = panMMDDFINAL.c_str();
					panMMDDFINALINT = atoi(panMMDDFINAL01);

					/////////////////////////////////////////////////

					string AAAAFINAL = fechafinal.substr(6, 9);
					const char* AAAAFINAL01 = AAAAFINAL.c_str();
					AAAAFINALINT = atoi(AAAAFINAL01);



					/////////////////////////////////////////////////

					string stringAAAAMMDDFINAL = AAAAFINAL + "/" + MMFINAL + "/" + DDFINAL;
					const char* AAAAMMDDFINAL = stringAAAAMMDDFINAL.c_str();


					////////////////////////////////////////////////

					string HHFINAL = horafinal.substr(0, 2);
					const char* HHFINAL01 = HHFINAL.c_str();
					HHFINALINT = atoi(HHFINAL01);

					string MTFINAL = horafinal.substr(3, 2);
					const char* MTFINAL01 = MTFINAL.c_str();
					MTFINALINT = atoi(MTFINAL01);

					string SSFINAL = horafinal.substr(6, 7);
					const char* SSFINAL01 = SSFINAL.c_str();
					SSFINALINT = atoi(SSFINAL01);

					////////////////////////////////////////////////////////
					string panHHMMSSFINAL = HHFINAL + MTFINAL + SSFINAL;
					const char* panHHMMSSFINAL01 = panHHMMSSFINAL.c_str();
					panHHMMSSFINALINT = atoi(panHHMMSSFINAL01);


					string stringHHMTSSFINALALREVEZ = HHFINAL + ":" + MTFINAL + ":" + SSFINAL;
					const char* HHMTSSFINALALREVEZ = stringHHMTSSFINALALREVEZ.c_str();
					////////////////////////////////////////////////////////
					

					bool promocionaunnocomienza = false;
					bool promocionyacaduco = false;

					if (diadehoy != auxPR->diapromocion) {


						if (strcmp(AAAAMMDDINICIAL, DDMMAAAAACTUAL) <= 0) {
							strcpy_s(nombredemipromocionvalida, auxPR->nombrepromocion);
							auxPR->auxilio = true;
							pan = true;
						}

						if (strcmp(AAAAMMDDFINAL, DDMMAAAAACTUAL) >= 0) {
							strcpy_s(nombredemipromocionvalida, auxPR->nombrepromocion);
							auxPR->auxilio = true;
							pan = true;
						}


						if (strcmp(auxPR->horainicio, HHMTSSACTUAL) <= 0 && strcmp(AAAAMMDDINICIAL, DDMMAAAAACTUAL) == 0) {
							
							strcpy_s(nombredemipromocionvalida, auxPR->nombrepromocion);
							auxPR->auxilio = true;
							pan = true;
						}

						if (strcmp(auxPR->horafinal, HHMTSSACTUAL) >= 0 && strcmp(AAAAMMDDFINAL, DDMMAAAAACTUAL) == 0) {
							strcpy_s(nombredemipromocionvalida, auxPR->nombrepromocion);
							auxPR->auxilio = true;
							pan = true;
						}

						if (strcmp(AAAAMMDDINICIAL, DDMMAAAAACTUAL) >= 0) {
							pan = false;
							auxPR->auxilio = false;
						}

						if (strcmp(auxPR->horainicio, HHMTSSACTUAL) >= 0 && strcmp(AAAAMMDDINICIAL, DDMMAAAAACTUAL) == 0) {

							pan = false;
							auxPR->auxilio = false;
						}


						if (strcmp(AAAAMMDDFINAL, DDMMAAAAACTUAL) <= 0) {
							pan = false;
							auxPR->auxilio = false;
						}

						if (strcmp(auxPR->horafinal, HHMTSSACTUAL) <= 0 && strcmp(AAAAMMDDFINAL, DDMMAAAAACTUAL) == 0) {

							pan = false;
							auxPR->auxilio = false;

						}

						/*
						if (AAAAACTUAL >= AAAAINICIOINT && AAAAACTUAL <= AAAAFINALINT) {

							

							
							if (panMMDDACTUALINT >= panMMDDINICIOINT && panMMDDACTUALINT <= panMMDDFINALINT) {

								if (panHHMTSSACTUALINT <= panHHMMSSINICIOINT && panMMDDACTUALINT == panMMDDINICIOINT
									&& strcmp(auxP->nombre, auxPR->producto) == 0) {
									promocionaunnocomienza = true;
									auxP->promocion = false;
									pan = false;
									continue;
								}

								if (panHHMTSSACTUALINT >= panHHMMSSFINALINT && panMMDDACTUALINT == panMMDDFINALINT
									&& strcmp(auxP->nombre, auxPR->producto) == 0) {
									promocionyacaduco = true;
									pan = false;
									auxP->promocion = false;
									continue;
								}

								if (auxP->promocion == true && auxPR->auxilio == true &&
									promocionaunnocomienza == false && promocionyacaduco == false && strcmp(auxP->nombre, auxPR->producto) == 0) {

								
								}
							}
							



						}
						*/
					}						
					else {
						pan = false;
					}

					if (pan == true) {
						KillTimer(Tiendocho, TIMERID2);
						revivirtimer = false;
						DialogBox(panoso, MAKEINTRESOURCE(IDD_PROMOCIONEXISTENTE), Tiendocho, PromocionosoExistententoso);

						if (revivirtimer == true) {
							TIMERID2 = SetTimer(Tiendocho, ID_5SECONDS, 10000, NULL);
						}
						continue;
					}
					
					auxPR = auxPR->sig;
				}

				auxP = auxP->sig;
			}

		}

		return true;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_ARCHIVO_GUARDAR:
			GuardarArchivosoU();
			GuardarArchivosoP();
			GuardarArchivosoPR();
			GuardarArchivosoC();
			MessageBox(Tiendocho, "Su información ha sido guardada.", "Información Guardada", MB_OK);
			return true;
		case ID_ARCHIVO_CERRARSESION:
			KillTimer(Tiendocho, TIMERID2);
			cargar = true;
			auxPR = inicioPR;
			while (auxPR != NULL)
			{
				if (auxPR->diapromocion == diadehoy) {
					auxPR->diapromocion = 0;
				}
				auxPR = auxPR->sig;
			}
			GuardarArchivosoU();
			GuardarArchivosoP();
			GuardarArchivosoPR();
			GuardarArchivosoC();

			iniciosesion = false;
			EndDialog(Tiendocho, 0);
			CreateDialog(panoso, MAKEINTRESOURCE(IDD_LOGIN), 0, Inicioso);
			ShowWindow(Tiendocho, 0);
			return true;
		case ID_ARCHIVO_SALIR:
			KillTimer(Tiendocho, TIMERID2);
			cargar = true;
			auxPR = inicioPR;
			while (auxPR != NULL)
			{
				if (auxPR->diapromocion == diadehoy) {
					auxPR->diapromocion = 0;
				}
				auxPR = auxPR->sig;
			}
			GuardarArchivosoU();
			GuardarArchivosoP();
			GuardarArchivosoPR();
			GuardarArchivosoC();

			DestroyWindow(Tiendocho);
			PostQuitMessage(0);
			return true;
		case ID_USUARIO_CAMBIODEDATOS:
			DialogBox(panoso, MAKEINTRESOURCE(IDD_CAMBIO), Tiendocho, Cambioso);

			if (eliminarusuario == true) {

				KillTimer(Tiendocho, TIMERID2);
				auxPR = inicioPR;
				while (auxPR != NULL)
				{
					if (auxPR->diapromocion == diadehoy) {
						auxPR->diapromocion = 0;
					}
					auxPR = auxPR->sig;
				}
				GuardarArchivosoU();
				GuardarArchivosoP();
				GuardarArchivosoPR();
				GuardarArchivosoC();

				iniciosesion = false;
				EndDialog(Tiendocho, 0);
				CreateDialog(panoso, MAKEINTRESOURCE(IDD_LOGIN), 0, Inicioso);
				ShowWindow(Tiendocho, 0);
				return true;



			}

			return true;
		case ID_CARRITO_ADMINISTRADORDELCARRITO:
			DialogBox(panoso, MAKEINTRESOURCE(IDD_CARRITO), Tiendocho, Carritoso);
			return true;
		case ID_OTRO_INFORMACION:
			DialogBox(panoso, MAKEINTRESOURCE(IDD_INFORMACION), Tiendocho, Informacioso);
			return true;
		case ID_VENTAS_ADMINISTRADORDEVENTAS:
			DialogBox(panoso, MAKEINTRESOURCE(IDD_ADMINISTRADORVENTAS), Tiendocho, Productuosos);
			return true;
		case ID_PROMOCIONEXISTENTE:
			DialogBox(panoso, MAKEINTRESOURCE(IDD_PROMOCIONEXISTENTE), Tiendocho, PromocionosoExistententoso);
			return true;
		case ID_ACTUALIZART: {
			SendDlgItemMessage(Tiendocho, IDC_COMBO_PRODUCTOSDISPONIBLEST, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(Tiendocho, IDC_EDIT_NOMBREPRODUCTOT, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Tiendocho, IDC_EDIT_SONIDOT, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Tiendocho, IDC_EDIT_DESCUENTOT, WM_SETTEXT, 0, (LPARAM)"0");
			SendDlgItemMessage(Tiendocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONT, WM_SETTEXT, 0, (LPARAM)"0");
			SendDlgItemMessage(Tiendocho, IDC_EDIT_PRECIOFINALCONPROMOCIONT, WM_SETTEXT, 0, (LPARAM)"0");
			SendDlgItemMessage(Tiendocho, IDC_EDIT_FINALPROMOCIONFECHAT, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Tiendocho, IDC_EDIT_FINALPROMOCIONHORAT, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Tiendocho, IDC_EDIT_FINALPROMOCIONAMPMT, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Tiendocho, IDC_EDIT_DESCRIPCIONPROMOCIONT, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Tiendocho, IDC_COMBO_CANTIDADPRODUCTOST, WM_SETTEXT, MAX_PATH, (LPARAM)"1");


			BMP01 = (HBITMAP)LoadImage(NULL, "", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
			SendDlgItemMessage(Tiendocho, IDC_PICTURE_PRODUCTOST, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)"");
			auxP = inicioP;

			while (auxP != NULL)
			{
				SendDlgItemMessage(Tiendocho, IDC_COMBO_PRODUCTOSDISPONIBLEST, CB_ADDSTRING, 0, (LPARAM)auxP->nombre);
				auxP = auxP->sig;
			}

			return true; }
		case ID_OKMOSTRART: {
			auxP = inicioP;
			char pantequimia[MAX_PATH];
			SendDlgItemMessage(Tiendocho, IDC_COMBO_PRODUCTOSDISPONIBLEST, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimia);
			while (auxP != NULL)
			{
				if (strcmp(auxP->nombre, pantequimia) == 0) {

					char panpan[MAX_PATH];
					SendDlgItemMessage(Tiendocho, IDC_EDIT_NOMBREPRODUCTOT, WM_SETTEXT, MAX_PATH, (LPARAM)auxP->nombre);
					itoa(auxP->precio, panpan, 10);
					SendDlgItemMessage(Tiendocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONT, WM_SETTEXT, MAX_PATH, (LPARAM)panpan);
					SendDlgItemMessage(Tiendocho, IDC_EDIT_SONIDOT, WM_SETTEXT, MAX_PATH, (LPARAM)auxP->sonido);
					BMP01 = (HBITMAP)LoadImage(NULL, auxP->foto01, IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
					SendDlgItemMessage(Tiendocho, IDC_PICTURE_PRODUCTOST, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP01);


					auxPR = inicioPR;

					while (auxPR != NULL) {
						if (strcmp(auxP->nombre, auxPR->producto) == 0 && auxPR->auxilio == true) {
							float porcentaje;
							float precioinicial;
							float preciofinal;

							char pantequimia[MAX_PATH];
							char pantequimiosho[MAX_PATH];
							char pantequiqui[MAX_PATH];
							char temporal[MAX_PATH];

							itoa(auxPR->porcentajepromocion, temporal, 10);
							SendDlgItemMessage(Tiendocho, IDC_EDIT_DESCUENTOT, WM_SETTEXT, MAX_PATH, (LPARAM)temporal);
							SendDlgItemMessage(Tiendocho, IDC_EDIT_DESCUENTOT, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimia);
							porcentaje = atoi(pantequimia); // Se modifican los valores char a int

							SendDlgItemMessage(Tiendocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONT, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimiosho);
							precioinicial = atoi(pantequimiosho); // Se modifican los valores char a int

							preciofinal = ((precioinicial*porcentaje) / 100);
							preciofinal = (precioinicial - preciofinal);

							itoa(preciofinal, pantequiqui, 10);
							SendDlgItemMessage(Tiendocho, IDC_EDIT_PRECIOFINALCONPROMOCIONT, WM_SETTEXT, MAX_PATH, (LPARAM)pantequiqui);
							SendDlgItemMessage(Tiendocho, IDC_EDIT_FINALPROMOCIONFECHAT, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->fechafinal);
							SendDlgItemMessage(Tiendocho, IDC_EDIT_FINALPROMOCIONHORAT, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->horafinal);
							SendDlgItemMessage(Tiendocho, IDC_EDIT_FINALPROMOCIONAMPMT, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->AMPM02);
							SendDlgItemMessage(Tiendocho, IDC_EDIT_DESCRIPCIONPROMOCIONT, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->descripcion);

							break;
						}
						auxPR = auxPR->sig;
					}


					break;
				}
				auxP = auxP->sig;
			}
			return true;
		}
		case ID_OKCATEGORIAT: {
			SendDlgItemMessage(Tiendocho, IDC_COMBO_PRODUCTOSDISPONIBLEST, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(Tiendocho, IDC_EDIT_NOMBREPRODUCTOT, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Tiendocho, IDC_EDIT_SONIDOT, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Tiendocho, IDC_EDIT_DESCUENTOT, WM_SETTEXT, 0, (LPARAM)"0");
			SendDlgItemMessage(Tiendocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONT, WM_SETTEXT, 0, (LPARAM)"0");
			SendDlgItemMessage(Tiendocho, IDC_EDIT_PRECIOFINALCONPROMOCIONT, WM_SETTEXT, 0, (LPARAM)"0");
			SendDlgItemMessage(Tiendocho, IDC_EDIT_FINALPROMOCIONFECHAT, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Tiendocho, IDC_EDIT_FINALPROMOCIONHORAT, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Tiendocho, IDC_EDIT_FINALPROMOCIONAMPMT, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Tiendocho, IDC_EDIT_DESCRIPCIONPROMOCIONT, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Tiendocho, IDC_COMBO_CANTIDADPRODUCTOST, WM_SETTEXT, MAX_PATH, (LPARAM)"1");


			BMP01 = (HBITMAP)LoadImage(NULL, "", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
			SendDlgItemMessage(Tiendocho, IDC_PICTURE_PRODUCTOST, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)"");
			auxP = inicioP;


			char pantequimio[MAX_PATH];
			SendDlgItemMessage(Tiendocho, IDC_COMBO_CATEGORIAT, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimio);

			while (auxP != NULL)
			{
				if (strcmp(auxP->categoria, pantequimio) == 0 && strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0) {
					SendDlgItemMessage(Tiendocho, IDC_COMBO_PRODUCTOSDISPONIBLEST, CB_ADDSTRING, 0, (LPARAM)auxP->nombre);
				}
				auxP = auxP->sig;
			}
			return true; }
		case ID_OKBUSCARPRODUCTOAV03: {
			auxP = inicioP;
			bool banderin = false;
			char pantequimi[MAX_PATH];
			SendDlgItemMessage(Tiendocho, IDC_EDIT_BUSCARPRODUCTOT, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimi);
			for (int i = 0; pantequimi[i]; i++) {          // Aqui se esta acomodando de minusculas a  mayusculas usando la 
				pantequimi[i] = toupper(pantequimi[i]);   // funcion toupper
			}

			while (auxP != NULL)
			{
				if (strcmp(auxP->nombre, pantequimi) == 0 && strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0) {

					char panpan[MAX_PATH];
					SendDlgItemMessage(Tiendocho, IDC_EDIT_NOMBREPRODUCTOT, WM_SETTEXT, MAX_PATH, (LPARAM)auxP->nombre);
					itoa(auxP->precio, panpan, 10);
					SendDlgItemMessage(Tiendocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONT, WM_SETTEXT, MAX_PATH, (LPARAM)panpan);
					SendDlgItemMessage(Tiendocho, IDC_EDIT_SONIDOT, WM_SETTEXT, MAX_PATH, (LPARAM)auxP->sonido);
					BMP01 = (HBITMAP)LoadImage(NULL, auxP->foto01, IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
					SendDlgItemMessage(Tiendocho, IDC_PICTURE_PRODUCTOST, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP01);


					auxPR = inicioPR;

					while (auxPR != NULL) {
						if (strcmp(auxP->nombre, auxPR->producto) == 0 && auxP->promocion == true) {
							float porcentaje;
							float precioinicial;
							float preciofinal;

							char pantequimia[MAX_PATH];
							char pantequimiosho[MAX_PATH];
							char pantequiqui[MAX_PATH];
							char temporal[MAX_PATH];

							itoa(auxPR->porcentajepromocion, temporal, 10);
							SendDlgItemMessage(Tiendocho, IDC_EDIT_DESCUENTOT, WM_SETTEXT, MAX_PATH, (LPARAM)temporal);
							SendDlgItemMessage(Tiendocho, IDC_EDIT_DESCUENTOT, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimia);
							porcentaje = atoi(pantequimia); // Se modifican los valores char a int

							SendDlgItemMessage(Tiendocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONT, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimiosho);
							precioinicial = atoi(pantequimiosho); // Se modifican los valores char a int

							preciofinal = ((precioinicial*porcentaje) / 100);
							preciofinal = (precioinicial - preciofinal);

							itoa(preciofinal, pantequiqui, 10);
							SendDlgItemMessage(Tiendocho, IDC_EDIT_PRECIOFINALCONPROMOCIONT, WM_SETTEXT, MAX_PATH, (LPARAM)pantequiqui);
							SendDlgItemMessage(Tiendocho, IDC_EDIT_FINALPROMOCIONFECHAT, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->fechafinal);
							SendDlgItemMessage(Tiendocho, IDC_EDIT_FINALPROMOCIONHORAT, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->horafinal);
							SendDlgItemMessage(Tiendocho, IDC_EDIT_FINALPROMOCIONAMPMT, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->AMPM02);
							SendDlgItemMessage(Tiendocho, IDC_EDIT_DESCRIPCIONPROMOCIONT, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->descripcion);
						}
						auxPR = auxPR->sig;
					}

					SendDlgItemMessage(Tiendocho, IDC_EDIT_BUSCARPRODUCTOT, WM_SETTEXT, MAX_PATH, (LPARAM)"");

					banderin = true;
					MessageBox(Tiendocho, "Búsqueda Exitosa", "¡PERFECTO!", MB_OK);

					break;
				}
				auxP = auxP->sig;
			}

			if (banderin == false) {

				MessageBox(0, "No se encontro la información.", "ERROR", MB_ICONEXCLAMATION | MB_OK);
			}
			return true; }
		case IDC_IMAGENDERECHAT: {
			auxP = inicioP;
			char pantequimia[MAX_PATH];
			SendDlgItemMessage(Tiendocho, IDC_COMBO_PRODUCTOSDISPONIBLEST, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimia);
			while (auxP != NULL)
			{
				if (strcmp(auxP->nombre, pantequimia) == 0) {
					BMP01 = (HBITMAP)LoadImage(NULL, auxP->foto02, IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
					SendDlgItemMessage(Tiendocho, IDC_PICTURE_PRODUCTOST, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP01);
					break;
				}
				auxP = auxP->sig;
			}
			return true;
		}
		case IDC_IMAGENIZQUIERDAT: {
			auxP = inicioP;
			char pantequimia[MAX_PATH];
			SendDlgItemMessage(Tiendocho, IDC_COMBO_PRODUCTOSDISPONIBLEST, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimia);
			while (auxP != NULL)
			{
				if (strcmp(auxP->nombre, pantequimia) == 0) {
					BMP01 = (HBITMAP)LoadImage(NULL, auxP->foto01, IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
					SendDlgItemMessage(Tiendocho, IDC_PICTURE_PRODUCTOST, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP01);
					break;
				}
				auxP = auxP->sig;
			}
			return true;
		}
		case ID_REPRODUCIRT: {
			SendDlgItemMessage(Tiendocho, IDC_EDIT_SONIDOT, WM_GETTEXT, MAX_PATH, (LPARAM)mp3);
			if (strcmp(mp3, "") != 0)
			{
				sprintf_s(comando, "open \"%s\" alias MP3", mp3);
				mciSendString(comando, NULL, 0, 0);
				mciSendString("play MP3", NULL, 0, 0);
			}
			return true; }
		case ID_PAUSAT:
			mciSendString("pause Mp3", NULL, 0, 0);
			return true;
		case ID_PARART:
			mciSendString("stop MP3", NULL, 0, 0);
			mciSendString("close MP3", NULL, 0, 0);
			return true;
		case ID_AGREGARCARRITO: {
			nuevoC = new arreglosocarroso;
			nuevoC->ant = NULL;
			nuevoC->sig = NULL;

			float temporal01;
			float temporal02;
			float temporal03;
			float temporal04;




			strcpy_s(nuevoC->usuario, usuariosoqueiniciosesion);

			//NOMBRE DEL PRODUCTO
			char pantequilla[50];
			SendDlgItemMessage(Tiendocho, IDC_EDIT_NOMBREPRODUCTOT, WM_GETTEXT, 50, (LPARAM)pantequilla);
			for (int i = 0; pantequilla[i]; i++) {          // Aqui se esta acomodando de minusculas a  mayusculas usando la 
				pantequilla[i] = toupper(pantequilla[i]);   // funcion toupper
				banderoso = true;
			}
			strcpy_s(nuevoC->producto, pantequilla);

			char panecito[MAX_PATH];
			auxP = inicioP;
			while (auxP != NULL) {

				if (strcmp(auxP->nombre, pantequilla) == 0) {

					strcpy(panecito, auxP->usuario);
				}
				auxP = auxP->sig;
			}
			
			strcpy_s(nuevoC->productodelusuariosubido, panecito);

			//CANTIDAD DE PRODUCTOS
			char pantequillocho[50];
			SendDlgItemMessage(Tiendocho, IDC_COMBO_CANTIDADPRODUCTOST, WM_GETTEXT, 50, (LPARAM)pantequillocho);
			temporal01 = atoi(pantequillocho);
			if (!temporal01)
			{
				banderoso = false;
			}
			else {
				nuevoC->cantidaddeproductos = temporal01;
			};

			//PORCENTAJE PROMOCIÓN
			char pantequilloso[50];
			SendDlgItemMessage(Tiendocho, IDC_EDIT_DESCUENTOT, WM_GETTEXT, 50, (LPARAM)pantequilloso);
			temporal02 = atoi(pantequilloso); // Se modifican los valores char a int

			nuevoC->porcentajepromocion = temporal02;


			//PRECIO INICIAL
			char panpon[50];
			SendDlgItemMessage(Tiendocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONT, WM_GETTEXT, 50, (LPARAM)panpon);
			temporal03 = atoi(panpon); // Se modifican los valores char a int

			nuevoC->precioinicial = temporal03;


			//PRECIO FINAL
			char panplan[50];
			SendDlgItemMessage(Tiendocho, IDC_EDIT_PRECIOFINALCONPROMOCIONT, WM_GETTEXT, 50, (LPARAM)panplan);
			temporal04 = atoi(panplan); // Se modifican los valores char a int

			nuevoC->preciofinal = temporal04;
			if (strcmp(pantequilloso, "0") != 0) {

				nuevoC->promocion = true;
			}

			auxC = inicioC;
			while (auxC != NULL) {

				char panteyoyo[50];
				SendDlgItemMessage(Tiendocho, IDC_EDIT_NOMBREPRODUCTOT, WM_GETTEXT, 50, (LPARAM)panteyoyo);

				if (strcmp(auxC->producto, panteyoyo) == 0 && strcmp(auxC->usuario, usuariosoqueiniciosesion) == 0) {
					banderoso = false;
					banderra = true;
					break;
				}
				auxC = auxC->sig;
			}

			if (banderoso == true) {
				if (inicioC == NULL) {
					inicioC = nuevoC;
				}
				else {
					auxC = inicioC;
					while (auxC->sig != NULL) {
						auxC = auxC->sig;
					}
					auxC->sig = nuevoC;
					nuevoC->ant = auxC;
				}

				mciSendString("stop MP3", NULL, 0, 0);
				mciSendString("close MP3", NULL, 0, 0);
				MessageBox(Tiendocho, "Añadido Al Carrito Exitoso", "¡PERFECTO!", MB_OK);

			}
			else {
				if (banderra == true) {
					MessageBox(0, "Este producto ya esta añadido a su carrito.", "ERROR", MB_ICONERROR | MB_OK);
				}
				MessageBox(0, "Error con los datos ingresados. Favor de ingresar o corregir los datos.", "ERROR", MB_ICONERROR | MB_OK);
			}

			return true;

		}
		}
		return true;
	case WM_CLOSE:
		KillTimer(Tiendocho, TIMERID2);
		cargar = true;
		auxPR = inicioPR;
		while (auxPR != NULL)
		{
			if (auxPR->diapromocion == diadehoy) {
				auxPR->diapromocion = 0;
			}
			auxPR = auxPR->sig;
		}
		GuardarArchivosoU();
		GuardarArchivosoP();
		GuardarArchivosoPR();
		GuardarArchivosoC();

		DestroyWindow(Tiendocho);
		PostQuitMessage(0);
		return true;
	case WM_DESTROY:
		EndDialog(Tiendocho, 0);
		return true;
	}

	return false;

}

BOOL CALLBACK Carritoso(HWND Carrocho, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg)
	{
	case WM_INITDIALOG:
		SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, WM_SETTEXT, MAX_PATH, (LPARAM)"1");
		SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, CB_INSERTSTRING, 0, (LPARAM)"1");
		SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, CB_INSERTSTRING, 0, (LPARAM)"2");
		SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, CB_INSERTSTRING, 0, (LPARAM)"3");
		SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, CB_INSERTSTRING, 0, (LPARAM)"4");
		SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, CB_INSERTSTRING, 0, (LPARAM)"5");
		SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, CB_INSERTSTRING, 0, (LPARAM)"6");
		SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, CB_INSERTSTRING, 0, (LPARAM)"7");
		SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, CB_INSERTSTRING, 0, (LPARAM)"8");
		SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, CB_INSERTSTRING, 0, (LPARAM)"9");
		SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, CB_INSERTSTRING, 0, (LPARAM)"10");

		SendDlgItemMessage(Carrocho, IDC_EDIT_DESCUENTOC, WM_SETTEXT, 0, (LPARAM)"0");
		SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONC, WM_SETTEXT, 0, (LPARAM)"0");
		SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOFINALCONPROMOCIONC, WM_SETTEXT, 0, (LPARAM)"0");
		SendDlgItemMessage(Carrocho, IDC_COMBO_TIPODEPAGOC, CB_ADDSTRING, 0, (LPARAM)"Tarjeta de crédito");
		SendDlgItemMessage(Carrocho, IDC_COMBO_TIPODEPAGOC, CB_ADDSTRING, 0, (LPARAM)"Efectivo");
		SendDlgItemMessage(Carrocho, IDC_COMBO_TIPODEPAGOC, CB_ADDSTRING, 0, (LPARAM)"Pay-Pal");
		SendDlgItemMessage(Carrocho, IDC_COMBO_TIPODEPAGOC, CB_ADDSTRING, 0, (LPARAM)"Riot Points");
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_ACTUALIZARC: {
			SendDlgItemMessage(Carrocho, IDC_COMBO_PRODUCTOSC, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(Carrocho, IDC_EDIT_DESCUENTOC, WM_SETTEXT, 0, (LPARAM)"0");
			SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONC, WM_SETTEXT, 0, (LPARAM)"0");
			SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOFINALCONPROMOCIONC, WM_SETTEXT, 0, (LPARAM)"0");
			SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOTOTALPORPRODUCTOSC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Carrocho, IDC_TOTALC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Carrocho, IDC_COMBO_TIPODEPAGOC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, WM_SETTEXT, MAX_PATH, (LPARAM)"1");

			auxC = inicioC;
			while (auxC != NULL)
			{
				if (strcmp(auxC->usuario, usuariosoqueiniciosesion) == 0) {
					SendDlgItemMessage(Carrocho, IDC_COMBO_PRODUCTOSC, CB_ADDSTRING, 0, (LPARAM)auxC->producto);
				}
				auxC = auxC->sig;
			}

			return true; }
		case ID_MOSTRARPRODUCTOSC: {
			auxC = inicioC;
			char pantequimia[MAX_PATH];
			float preciototal = 0;
			SendDlgItemMessage(Carrocho, IDC_COMBO_PRODUCTOSC, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimia);
			while (auxC != NULL)
			{
				if (strcmp(auxC->usuario, usuariosoqueiniciosesion) == 0 && strcmp(auxC->producto, pantequimia) == 0) {

					char panpan[MAX_PATH];
					char panfo[MAX_PATH];
					char panla[MAX_PATH];
					char panchon[MAX_PATH];
					char pantequimiosho[MAX_PATH];

					float precioporcantidad = 0;

					itoa(auxC->cantidaddeproductos, panchon, 10);
					SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, WM_SETTEXT, MAX_PATH, (LPARAM)panchon);

					itoa(auxC->porcentajepromocion, panpan, 10);
					SendDlgItemMessage(Carrocho, IDC_EDIT_DESCUENTOC, WM_SETTEXT, MAX_PATH, (LPARAM)panpan);
					itoa(auxC->precioinicial, panfo, 10);
					SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONC, WM_SETTEXT, MAX_PATH, (LPARAM)panfo);
					itoa(auxC->preciofinal, panla, 10);
					SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOFINALCONPROMOCIONC, WM_SETTEXT, MAX_PATH, (LPARAM)panla);


					arreglosocarroso*auxCC = inicioC;

					while (auxCC != NULL) {
						char panjo[MAX_PATH];
						SendDlgItemMessage(Carrocho, IDC_COMBO_PRODUCTOSC, WM_GETTEXT, MAX_PATH, (LPARAM)panjo);
						if (strcmp(auxCC->usuario, usuariosoqueiniciosesion) == 0 && strcmp(auxCC->producto, panjo) == 0) {

							precioporcantidad = (auxCC->preciofinal * auxCC->cantidaddeproductos);
							preciototal = (preciototal + precioporcantidad);

							itoa(precioporcantidad, pantequimiosho, 10);
							SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOTOTALPORPRODUCTOSC, WM_SETTEXT, MAX_PATH, (LPARAM)pantequimiosho);

							if (strcmp(panpan, "0") == 0 && strcmp(panla, "0") == 0) {


								precioporcantidad = (auxCC->precioinicial * auxCC->cantidaddeproductos);
								preciototal = (preciototal + precioporcantidad);

								itoa(precioporcantidad, pantequimia, 10);
								SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOTOTALPORPRODUCTOSC, WM_SETTEXT, MAX_PATH, (LPARAM)pantequimia);

							}

							break;
						}



						auxCC = auxCC->sig;
					}


					break;

				}
				auxC = auxC->sig;
			}
			return true;
		}
		case ID_MODIFICARC: {
			auxP = inicioP;
			auxC = inicioC;
			char pantequimico[MAX_PATH];
			float pan01;
			float pan02;
			float pan03;
			float pan04;
			SendDlgItemMessage(Carrocho, IDC_COMBO_PRODUCTOSC, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimico);

			panto = SendDlgItemMessage(Carrocho, IDC_COMBO_PRODUCTOSC, CB_GETCURSEL, 0, 0);

			if (panto != -1) {
				while (auxC != NULL)
				{

					if (strcmp(auxC->producto, pantequimico) == 0 && strcmp(auxC->usuario, usuariosoqueiniciosesion) == 0) {

						//NOMBRE DEL PRODUCTO
						strcpy_s(nuevoC->usuario, usuariosoqueiniciosesion);

						char pantequilla[50];
						SendDlgItemMessage(Carrocho, IDC_COMBO_PRODUCTOSC, WM_GETTEXT, 50, (LPARAM)pantequilla);
						for (int i = 0; pantequilla[i]; i++) {          // Aqui se esta acomodando de minusculas a  mayusculas usando la 
							pantequilla[i] = toupper(pantequilla[i]);   // funcion toupper
							banderoso = true;
						}

						//CANTIDAD DE PRODUCTOS
						panto = SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, CB_GETCURSEL, 0, 0);
						if (panto != -1) {
							char pantequillocho[50];
							SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, WM_GETTEXT, 50, (LPARAM)pantequillocho);
							pan01 = atoi(pantequillocho);
							if (!pan01)
							{
								banderoso = false;
							}


							//PORCENTAJE PROMOCIÓN
							char pantequilloso[50];
							SendDlgItemMessage(Carrocho, IDC_EDIT_DESCUENTOC, WM_GETTEXT, 50, (LPARAM)pantequilloso);
							pan02 = atoi(pantequilloso); // Se modifican los valores char a int


														 //PRECIO INICIAL
							char panpon[50];
							SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONC, WM_GETTEXT, 50, (LPARAM)panpon);
							pan03 = atoi(panpon); // Se modifican los valores char a int


														 //PRECIO FINAL
							char panplan[50];
							SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOFINALCONPROMOCIONC, WM_GETTEXT, 50, (LPARAM)panplan);
							pan04 = atoi(panplan); // Se modifican los valores char a int


						}

						if (banderoso == true) {

							strcpy_s(auxC->producto, pantequilla);
							auxC->cantidaddeproductos = pan01;
							auxC->porcentajepromocion = pan02;
							auxC->precioinicial = pan03;
							auxC->preciofinal = pan04;

							SendDlgItemMessage(Carrocho, IDC_COMBO_PRODUCTOSC, CB_RESETCONTENT, 0, 0);
							SendDlgItemMessage(Carrocho, IDC_EDIT_DESCUENTOC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOFINALCONPROMOCIONC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOTOTALPORPRODUCTOSC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Carrocho, IDC_TOTALC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Carrocho, IDC_COMBO_TIPODEPAGOC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, WM_SETTEXT, MAX_PATH, (LPARAM)"1");
							SendDlgItemMessage(Carrocho, IDC_COMBO_PRODUCTOSC, WM_SETTEXT, MAX_PATH, (LPARAM)"");

							MessageBox(Carrocho, "Cambio Exitoso.", "¡PERFECTO!", MB_OK);

						}
						else {
							MessageBox(Carrocho, "Error con los datos ingresados. Favor de ingresar o corregir los datos.", "ERROR", MB_ICONERROR | MB_OK);
						}
						break;
					}
					auxC = auxC->sig;
				}

			}
			else { MessageBox(Carrocho, "La Modifición Fallo.", "ERROR", MB_OK); };
			return true;
		}
		case ID_ELIMINARC: {
			auxC = inicioC;
			panto = SendDlgItemMessage(Carrocho, IDC_COMBO_PRODUCTOSC, CB_GETCURSEL, 0, 0);
			char eliminacion[MAX_PATH];
			SendDlgItemMessage(Carrocho, IDC_COMBO_PRODUCTOSC, WM_GETTEXT, MAX_PATH, (LPARAM)eliminacion);


			if (panto != -1) {

				while (auxC != NULL) {
					if (strcmp(auxC->producto, eliminacion) == 0) {
						arreglosocarroso *eliminarC = auxC;

						if (eliminarC->sig == NULL && eliminarC->ant == NULL) {
							eliminarC = inicioC;
							inicioC = NULL;
							auxC = NULL;
							delete eliminarC;



						}
						else if (eliminarC->ant == NULL) {
							auxC = auxC->sig;
							inicioC = eliminarC->sig;
							inicioC->sig = NULL;
							eliminarC->sig = NULL;
							delete eliminarC;


						}
						else if (eliminarC->sig == NULL) {
							auxC = eliminarC->ant;
							eliminarC->ant->sig = NULL;
							delete eliminarC;


						}
						else {
							auxC = eliminarC->ant;
							auxC->sig = eliminarC->ant;
							eliminarC->sig->ant = auxC;
							delete eliminarC;
						}

						SendDlgItemMessage(Carrocho, IDC_COMBO_PRODUCTOSC, CB_RESETCONTENT, 0, 0);
						SendDlgItemMessage(Carrocho, IDC_COMBO_PRODUCTOSC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Carrocho, IDC_EDIT_DESCUENTOC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOFINALCONPROMOCIONC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOTOTALPORPRODUCTOSC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Carrocho, IDC_TOTALC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Carrocho, IDC_COMBO_TIPODEPAGOC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, WM_SETTEXT, MAX_PATH, (LPARAM)"1");

						MessageBox(Carrocho, "Eliminación Exitosa", "¡PERFECTO!", MB_OK);
						break;

					}

					auxC = auxC->sig;
				};
			}
			else { MessageBox(Carrocho, "La Eliminación Fallo.", "ERROR", MB_OK); };
			return true;
		}
		case ID_COMPRARPRODUCTOS: {
			auxC = inicioC;
			panto = SendDlgItemMessage(Carrocho, IDC_COMBO_TIPODEPAGOC, CB_GETCURSEL, 0, 0);


			if (panto != -1) {

				while (auxC != NULL) {

					if (strcmp(auxC->usuario, usuariosoqueiniciosesion) == 0) {
						arreglosocarroso *eliminarC = auxC;

						if (eliminarC->sig == NULL && eliminarC->ant == NULL) {
							eliminarC = inicioC;
							inicioC = NULL;
							auxC = NULL;
							delete eliminarC;



						}
						else if (eliminarC->ant == NULL) {
							auxC = auxC->sig;
							inicioC = eliminarC->sig;
							inicioC->sig = NULL;
							eliminarC->sig = NULL;
							delete eliminarC;


						}
						else if (eliminarC->sig == NULL) {
							auxC = eliminarC->ant;
							eliminarC->ant->sig = NULL;
							delete eliminarC;


						}
						else {
							auxC = eliminarC->ant;
							auxC->sig = eliminarC->ant;
							eliminarC->sig->ant = auxC;
							delete eliminarC;
						}

						SendDlgItemMessage(Carrocho, IDC_COMBO_PRODUCTOSC, CB_RESETCONTENT, 0, 0);
						SendDlgItemMessage(Carrocho, IDC_COMBO_PRODUCTOSC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Carrocho, IDC_EDIT_DESCUENTOC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOFINALCONPROMOCIONC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOTOTALPORPRODUCTOSC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Carrocho, IDC_TOTALC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Carrocho, IDC_COMBO_TIPODEPAGOC, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, WM_SETTEXT, MAX_PATH, (LPARAM)"1");

						MessageBox(Carrocho, "Compra Exitosa", "¡PERFECTO!", MB_OK);
						break;

					}

					auxC = auxC->sig;
				};
			}
			else { MessageBox(Carrocho, "La Compra Fallo.", "ERROR", MB_OK); };
			return true;
		}
		case ID_OKCANTIDADTOTALPRODUCTOSC: {


									  panto = SendDlgItemMessage(Carrocho, IDC_COMBO_PRODUCTOSC, CB_GETCURSEL, 0, 0);
									  if (panto != -1) {

										  char panpan[MAX_PATH];
										  char pancho[MAX_PATH];
										  char pantequimiosho[MAX_PATH];
										  char pantequila[MAX_PATH];
										  char pantequeque[MAX_PATH];
										  char pantequimia[MAX_PATH];
										  int precioporcantidad;
										  int precioinicial;
										  int preciofinal;
										  int descuento;
										  int cantidad;

										  SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONC, WM_GETTEXT, MAX_PATH, (LPARAM)panpan);
										  precioinicial = atoi(panpan);
										  SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOFINALCONPROMOCIONC, WM_GETTEXT, MAX_PATH, (LPARAM)pancho);
										  preciofinal = atoi(pancho);
										  SendDlgItemMessage(Carrocho, IDC_EDIT_DESCUENTOC, WM_GETTEXT, MAX_PATH, (LPARAM)pantequila);
										  descuento = atoi(pantequila);
										  SendDlgItemMessage(Carrocho, IDC_COMBO_CANTIDADPRODUCTOSC, WM_GETTEXT, MAX_PATH, (LPARAM)pantequeque);
										  cantidad = atoi(pantequeque);


										  precioporcantidad = (preciofinal * cantidad);
										  
										
										  if (strcmp(panpan, "0") == 0 && strcmp(pantequila, "0") == 0) {


											  precioporcantidad = (precioinicial * cantidad);
											 
										  }

										  itoa(precioporcantidad, pantequimia, 10);
										  SendDlgItemMessage(Carrocho, IDC_EDIT_PRECIOTOTALPORPRODUCTOSC, WM_SETTEXT, MAX_PATH, (LPARAM)pantequimia);


									  return true;
								  }
								  }

	    case ID_OKCALCULAR:{

								  auxC = inicioC;
								  char pangala[MAX_PATH];
								  int preciotototal = 0;
								  int precioporporcantidad = 0;


								  while (auxC != NULL) {


									  if (strcmp(auxC->usuario, usuariosoqueiniciosesion) == 0) {

										  precioporporcantidad = (auxC->preciofinal * auxC->cantidaddeproductos);


										  if (auxC->porcentajepromocion == 0 && auxC->preciofinal == 0) {
											  precioporporcantidad = (auxC->precioinicial * auxC->cantidaddeproductos);
										  }

										  preciotototal = (preciotototal + precioporporcantidad);


									  }
									  auxC = auxC->sig;
								  }


								  char panjaja[MAX_PATH];
								  itoa(preciotototal, panjaja, 10);
								  SendDlgItemMessage(Carrocho, IDC_TOTALC, WM_SETTEXT, MAX_PATH, (LPARAM)panjaja);

								  return true;
							  }
		}

		return true;
	case WM_CLOSE:
		EndDialog(Carrocho, 0);
		return true;
	case WM_DESTROY:
		EndDialog(Carrocho, 0);
		return true;
	}
	return false;

}

BOOL CALLBACK Productuosos(HWND Productuochos, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg)
	{
	case WM_INITDIALOG: {
		SendDlgItemMessage(Productuochos, IDC_COMBO_PRODUCTOSAV, CB_RESETCONTENT, 0, 0);
		auxP = inicioP;

		while (auxP != NULL)
		{
			if (strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0) {
				SendDlgItemMessage(Productuochos, IDC_COMBO_PRODUCTOSAV, CB_ADDSTRING, 0, (LPARAM)auxP->nombre);
			}
			auxP = auxP->sig;
		}

		SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAORDENARAV, CB_ADDSTRING, 0, (LPARAM)"CD");
		SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAORDENARAV, CB_ADDSTRING, 0, (LPARAM)"DVD");
		SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAORDENARAV, CB_ADDSTRING, 0, (LPARAM)"BLU-RAY");
		SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAORDENARAV, CB_ADDSTRING, 0, (LPARAM)"GAMES");
		SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAORDENARAV, CB_ADDSTRING, 0, (LPARAM)"MERCANCÍA OFICIAL");
		SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAORDENARAV, CB_ADDSTRING, 0, (LPARAM)"INSTRUMENTOS MUSICALES");
		SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAORDENARAV, CB_ADDSTRING, 0, (LPARAM)"ELECTRÓNICA");

		SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAPRODUCTOAV, CB_ADDSTRING, 0, (LPARAM)"CD");
		SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAPRODUCTOAV, CB_ADDSTRING, 0, (LPARAM)"DVD");
		SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAPRODUCTOAV, CB_ADDSTRING, 0, (LPARAM)"BLU-RAY");
		SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAPRODUCTOAV, CB_ADDSTRING, 0, (LPARAM)"GAMES");
		SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAPRODUCTOAV, CB_ADDSTRING, 0, (LPARAM)"MERCANCÍA OFICIAL");
		SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAPRODUCTOAV, CB_ADDSTRING, 0, (LPARAM)"INSTRUMENTOS MUSICALES");
		SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAPRODUCTOAV, CB_ADDSTRING, 0, (LPARAM)"ELECTRÓNICA");


		return true; }
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_ACTUALIZARAV: {
			SendDlgItemMessage(Productuochos, IDC_COMBO_PRODUCTOSAV, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(Productuochos, IDC_EDIT_NOMBREPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_EDIT_PRECIOPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_EDIT_URLSONIDOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_EDIT_URLFOTO01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_EDIT_URLFOTO02, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_EDIT_PORCENTAJEPROMOCIONAP, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_EDIT_PRECIOFINALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_CHECK_PROMOCION, BM_SETCHECK, BST_UNCHECKED, 0);

			BMP01 = (HBITMAP)LoadImage(NULL, "", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
			BMP02 = (HBITMAP)LoadImage(NULL, "", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
			SendDlgItemMessage(Productuochos, IDC_PICTURE_FOTO01, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_PICTURE_FOTO02, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)"");
			auxP = inicioP;

			while (auxP != NULL)
			{
				if (strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0) {
					SendDlgItemMessage(Productuochos, IDC_COMBO_PRODUCTOSAV, CB_ADDSTRING, 0, (LPARAM)auxP->nombre);
				}
				auxP = auxP->sig;
			}

			return true; }
		case ID_OK_MOSTRARPRODUCTOS: {
			auxP = inicioP;
			char pantequimia[MAX_PATH];
			SendDlgItemMessage(Productuochos, IDC_COMBO_PRODUCTOSAV, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimia);
			while (auxP != NULL)
			{
				if (strcmp(auxP->nombre, pantequimia) == 0 && strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0) {

					SendDlgItemMessage(Productuochos, IDC_EDIT_NOMBREPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)auxP->nombre);
					char temporal[MAX_PATH];
					itoa(auxP->precio, temporal, 10);
					SendDlgItemMessage(Productuochos, IDC_EDIT_PRECIOPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)temporal);
					SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)auxP->categoria);
					SendDlgItemMessage(Productuochos, IDC_EDIT_URLSONIDOAV, WM_SETTEXT, MAX_PATH, (LPARAM)auxP->sonido);
					SendDlgItemMessage(Productuochos, IDC_EDIT_URLFOTO01, WM_SETTEXT, MAX_PATH, (LPARAM)auxP->foto01);
					SendDlgItemMessage(Productuochos, IDC_EDIT_URLFOTO02, WM_SETTEXT, MAX_PATH, (LPARAM)auxP->foto02);

					BMP01 = (HBITMAP)LoadImage(NULL, auxP->foto01, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
					BMP02 = (HBITMAP)LoadImage(NULL, auxP->foto02, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
					SendDlgItemMessage(Productuochos, IDC_PICTURE_FOTO01, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP01);
					SendDlgItemMessage(Productuochos, IDC_PICTURE_FOTO02, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP02);

					auxPR = inicioPR;

					while (auxPR != NULL) {
						if (strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0 && strcmp(auxP->nombre, auxPR->producto) == 0 && auxP->promocion == true) {
							float porcentaje;
							float precioinicial;
							float preciofinal;

							char pantequimia[MAX_PATH];
							char pantequimiosho[MAX_PATH];
							char pantequiqui[MAX_PATH];
							char temporal[MAX_PATH];

							itoa(auxPR->porcentajepromocion, temporal, 10);
							SendDlgItemMessage(Productuochos, IDC_EDIT_PORCENTAJEPROMOCIONAP, WM_SETTEXT, MAX_PATH, (LPARAM)temporal);
							SendDlgItemMessage(Productuochos, IDC_EDIT_PORCENTAJEPROMOCIONAP, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimia);
							porcentaje = atoi(pantequimia); // Se modifican los valores char a int

							SendDlgItemMessage(Productuochos, IDC_EDIT_PRECIOPRODUCTOAV, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimiosho);
							precioinicial = atoi(pantequimiosho); // Se modifican los valores char a int

							preciofinal = ((precioinicial*porcentaje) / 100);
							preciofinal = (precioinicial - preciofinal);

							itoa(preciofinal, pantequiqui, 10);
							SendDlgItemMessage(Productuochos, IDC_EDIT_PRECIOFINALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)pantequiqui);
							SendDlgItemMessage(Productuochos, IDC_CHECK_PROMOCION, BM_SETCHECK, BST_CHECKED, 0);
							break;
						}
						auxPR = auxPR->sig;
					}


					break;
				}
				auxP = auxP->sig;
			}
			return true;
		}
		case ID_OKMOSTRARTODOAV01: {
			SendDlgItemMessage(Productuochos, IDC_COMBO_PRODUCTOSAV, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(Productuochos, IDC_EDIT_NOMBREPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_EDIT_PRECIOPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_EDIT_URLSONIDOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_EDIT_URLFOTO01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_EDIT_URLFOTO02, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_EDIT_PORCENTAJEPROMOCIONAP, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_EDIT_PRECIOFINALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_CHECK_PROMOCION, BM_SETCHECK, BST_UNCHECKED, 0);


			BMP01 = (HBITMAP)LoadImage(NULL, "", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
			BMP02 = (HBITMAP)LoadImage(NULL, "", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
			SendDlgItemMessage(Productuochos, IDC_PICTURE_FOTO01, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_PICTURE_FOTO02, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)"");
			auxP = inicioP;

			while (auxP != NULL)
			{
				if (strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0) {
					SendDlgItemMessage(Productuochos, IDC_COMBO_PRODUCTOSAV, CB_ADDSTRING, 0, (LPARAM)auxP->nombre);
				}
				auxP = auxP->sig;
			}
			return true; }
		case ID_OKCATEGORIAAV02: {
			SendDlgItemMessage(Productuochos, IDC_COMBO_PRODUCTOSAV, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(Productuochos, IDC_EDIT_NOMBREPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_EDIT_PRECIOPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_EDIT_URLSONIDOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_EDIT_URLFOTO01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_EDIT_URLFOTO02, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_EDIT_PORCENTAJEPROMOCIONAP, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_EDIT_PRECIOFINALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_CHECK_PROMOCION, BM_SETCHECK, BST_UNCHECKED, 0);

			BMP01 = (HBITMAP)LoadImage(NULL, "", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
			BMP02 = (HBITMAP)LoadImage(NULL, "", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
			SendDlgItemMessage(Productuochos, IDC_PICTURE_FOTO01, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)"");
			SendDlgItemMessage(Productuochos, IDC_PICTURE_FOTO02, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)"");
			auxP = inicioP;


			char pantequimio[MAX_PATH];
			SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAORDENARAV, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimio);

			while (auxP != NULL)
			{
				if (strcmp(auxP->categoria, pantequimio) == 0 && strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0) {
					SendDlgItemMessage(Productuochos, IDC_COMBO_PRODUCTOSAV, CB_ADDSTRING, 0, (LPARAM)auxP->nombre);
				}
				auxP = auxP->sig;
			}

			return true; }
		case ID_OKBUSCARPRODUCTOAV03: {
			auxP = inicioP;
			bool banderin = false;
			char pantequimi[MAX_PATH];
			SendDlgItemMessage(Productuochos, IDC_EDIT_BUSCARPRODUCTOS, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimi);
			for (int i = 0; pantequimi[i]; i++) {          // Aqui se esta acomodando de minusculas a  mayusculas usando la 
				pantequimi[i] = toupper(pantequimi[i]);   // funcion toupper
			}

			while (auxP != NULL)
			{
				if (strcmp(auxP->nombre, pantequimi) == 0 && strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0) {

					SendDlgItemMessage(Productuochos, IDC_EDIT_NOMBREPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)auxP->nombre);
					char temporal[MAX_PATH];
					itoa(auxP->precio, temporal, 10);
					SendDlgItemMessage(Productuochos, IDC_EDIT_PRECIOPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)temporal);
					SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)auxP->categoria);
					SendDlgItemMessage(Productuochos, IDC_EDIT_URLSONIDOAV, WM_SETTEXT, MAX_PATH, (LPARAM)auxP->sonido);
					SendDlgItemMessage(Productuochos, IDC_EDIT_URLFOTO01, WM_SETTEXT, MAX_PATH, (LPARAM)auxP->foto01);
					SendDlgItemMessage(Productuochos, IDC_EDIT_URLFOTO02, WM_SETTEXT, MAX_PATH, (LPARAM)auxP->foto02);

					BMP01 = (HBITMAP)LoadImage(NULL, auxP->foto01, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
					BMP02 = (HBITMAP)LoadImage(NULL, auxP->foto02, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
					SendDlgItemMessage(Productuochos, IDC_PICTURE_FOTO01, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP01);
					SendDlgItemMessage(Productuochos, IDC_PICTURE_FOTO02, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP02);

					SendDlgItemMessage(Productuochos, IDC_EDIT_BUSCARPRODUCTOS, WM_SETTEXT, MAX_PATH, (LPARAM)"");

					banderin = true;
					MessageBox(Productuochos, "Búsqueda Exitosa", "¡PERFECTO!", MB_OK);

					break;
				}

				auxP = auxP->sig;
			}

			if (banderin == false) {

				MessageBox(0, "No se encontro la información.", "ERROR", MB_ICONEXCLAMATION | MB_OK);
			}
			return true; }
		case IDC_OKPROMOCION: {

			auxP = inicioP;
			auxPR = inicioPR;

			while (auxP != NULL) {
				while (auxPR != NULL) {
					if (strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0 && strcmp(auxP->nombre, auxPR->producto) && auxP->promocion == true) {
						float porcentaje;
						float precioinicial;
						float preciofinal;

						char pantequimia[MAX_PATH];
						char pantequimiosho[MAX_PATH];
						char pantequiqui[MAX_PATH];

						SendDlgItemMessage(Productuochos, IDC_EDIT_PORCENTAJEPROMOCIONAP, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimia);
						porcentaje = atoi(pantequimia); // Se modifican los valores char a int

						SendDlgItemMessage(Productuochos, IDC_EDIT_PRECIOPRODUCTOAV, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimiosho);
						precioinicial = atoi(pantequimiosho); // Se modifican los valores char a int

						preciofinal = ((precioinicial*porcentaje) / 100);
						preciofinal = (precioinicial - preciofinal);

						itoa(preciofinal, pantequiqui, 10);
						SendDlgItemMessage(Productuochos, IDC_EDIT_PRECIOFINALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)pantequiqui);

					}
					auxPR = auxPR->sig;
				}
				auxP = auxP->sig;
			}

			return true; }
		case ID_MODIFICARPRODUCTO: {
			auxP = inicioP;
			char pantequimico[MAX_PATH];
			SendDlgItemMessage(Productuochos, IDC_COMBO_PRODUCTOSAV, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimico);

			panto = SendDlgItemMessage(Productuochos, IDC_COMBO_PRODUCTOSAV, CB_GETCURSEL, 0, 0);

			if (panto != -1) {
				while (auxP != NULL)
				{

					if (strcmp(auxP->nombre, pantequimico) == 0 && strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0) {
						//NOMBRE DEL PRODUCTO
						char pantequilla[50];
						SendDlgItemMessage(Productuochos, IDC_EDIT_NOMBREPRODUCTOAV, WM_GETTEXT, 50, (LPARAM)pantequilla);
						for (int i = 0; pantequilla[i]; i++) {          // Aqui se esta acomodando de minusculas a  mayusculas usando la 
							pantequilla[i] = toupper(pantequilla[i]);   // funcion toupper
							banderoso = true;
						}


						//PRECIO DEL PRODUCTO
						int temporal;
						char pantequilloso[50];
						SendDlgItemMessage(Productuochos, IDC_EDIT_PRECIOPRODUCTOAV, WM_GETTEXT, 50, (LPARAM)pantequilloso);
						temporal = atoi(pantequilloso); // Se modifican los valores char a int
						if (!temporal)
						{
							banderoso = false;
						}

						//CATEGORIA DEL PRODUCTO
						char pantequillocho[50];
						SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAPRODUCTOAV, WM_GETTEXT, 50, (LPARAM)pantequillocho);


						// SONIDO
						char pantimusica[MAX_PATH];
						SendDlgItemMessage(Productuochos, IDC_EDIT_URLSONIDOAV, WM_GETTEXT, MAX_PATH, (LPARAM)pantimusica);


						// FOTOS
						char pantimagen01[MAX_PATH];
						SendDlgItemMessage(Productuochos, IDC_EDIT_URLFOTO01, WM_GETTEXT, MAX_PATH, (LPARAM)pantimagen01);


						char pantimagen02[MAX_PATH];
						SendDlgItemMessage(Productuochos, IDC_EDIT_URLFOTO02, WM_GETTEXT, MAX_PATH, (LPARAM)pantimagen02);


						if (banderoso == true) {

							strcpy(nuevoP->nombre, pantequilla);
							nuevoP->precio = temporal;
							strcpy(nuevoP->categoria, pantequillocho);
							strcpy(nuevoP->sonido, pantimusica);
							strcpy(nuevoP->foto01, pantimagen01);
							strcpy(nuevoP->foto02, pantimagen02);

							SendDlgItemMessage(Productuochos, IDC_COMBO_PRODUCTOSAV, CB_RESETCONTENT, 0, 0);
							SendDlgItemMessage(Productuochos, IDC_COMBO_PRODUCTOSAV, CB_DELETESTRING, 0, (LPARAM)auxP->nombre);
							SendDlgItemMessage(Productuochos, IDC_EDIT_NOMBREPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Productuochos, IDC_EDIT_PRECIOPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Productuochos, IDC_EDIT_URLSONIDOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Productuochos, IDC_EDIT_URLFOTO01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Productuochos, IDC_EDIT_URLFOTO02, WM_SETTEXT, MAX_PATH, (LPARAM)"");

							BMP01 = (HBITMAP)LoadImage(NULL, "", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
							BMP02 = (HBITMAP)LoadImage(NULL, "", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
							SendDlgItemMessage(Productuochos, IDC_PICTURE_FOTO01, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)"");
							SendDlgItemMessage(Productuochos, IDC_PICTURE_FOTO02, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)"");


							MessageBox(Productuochos, "Cambio Exitoso.", "¡PERFECTO!", MB_OK);

						}
						else {
							MessageBox(Productuochos, "Error con los datos ingresados. Favor de ingresar o corregir los datos.", "ERROR", MB_ICONERROR | MB_OK);
						}
						break;
					}
					auxP = auxP->sig;
				}

			}
			else { MessageBox(Productuochos, "La Modifición Fallo.", "ERROR", MB_OK); };
			return true;
		}
		case ID_ELIMINARPRODUCTO: {
			auxP = inicioP;
			auxPR = inicioPR;
			panto = SendDlgItemMessage(Productuochos, IDC_COMBO_PRODUCTOSAV, CB_GETCURSEL, 0, 0);
			char eliminacion[MAX_PATH];
			SendDlgItemMessage(Productuochos, IDC_COMBO_PRODUCTOSAV, WM_GETTEXT, MAX_PATH, (LPARAM)eliminacion);


			if (panto != -1) {

				while (auxP != NULL) {

					while (auxPR != NULL) {
						if (strcmp(auxPR->producto, eliminacion) == 0 && strcmp(auxPR->usuario, usuariosoqueiniciosesion) == 0)
						{
							arreglosopromocioso *eliminarPR = auxPR;

							if (eliminarPR->sig == NULL && eliminarPR->ant == NULL) {
								eliminarPR = inicioPR;
								inicioPR = NULL;
								auxPR = NULL;
								delete eliminarPR;
							}
							else if (eliminarPR->ant == NULL) {
								auxPR = auxPR->sig;
								inicioPR = eliminarPR->sig;
								inicioPR->sig = NULL;
								eliminarPR->sig = NULL;
								delete eliminarPR;


							}
							else if (eliminarPR->sig == NULL) {
								auxPR = eliminarPR->ant;
								eliminarPR->ant->sig = NULL;
								delete eliminarPR;


							}
							else {
								auxPR = eliminarPR->ant;
								auxPR->sig = eliminarPR->ant;
								eliminarPR->sig->ant = auxPR;
								delete eliminarPR;
							}
							continue;
						}
						auxPR = auxPR->sig;
					}

					if (strcmp(auxP->nombre, eliminacion) == 0) {
						arreglosoproductoso *eliminarP = auxP;

						if (eliminarP->sig == NULL && eliminarP->ant == NULL) {
							eliminarP = inicioP;
							inicioP = NULL;
							auxP = NULL;
							delete eliminarP;



						}
						else if (eliminarP->ant == NULL) {
							auxP = auxP->sig;
							inicioP = eliminarP->sig;
							inicioP->sig = NULL;
							eliminarP->sig = NULL;
							delete eliminarP;


						}
						else if (eliminarP->sig == NULL) {
							auxP = eliminarP->ant;
							eliminarP->ant->sig = NULL;
							delete eliminarP;


						}
						else {
							auxP = eliminarP->ant;
							auxP->sig = eliminarP->ant;
							eliminarP->sig->ant = auxP;
							delete eliminarP;
						}
						SendDlgItemMessage(Productuochos, IDC_COMBO_PRODUCTOSAV, CB_RESETCONTENT, 0, 0);
						SendDlgItemMessage(Productuochos, IDC_EDIT_NOMBREPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Productuochos, IDC_EDIT_PRECIOPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Productuochos, IDC_COMBO_CATEGORIAPRODUCTOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Productuochos, IDC_EDIT_URLSONIDOAV, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Productuochos, IDC_EDIT_URLFOTO01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Productuochos, IDC_EDIT_URLFOTO02, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Productuochos, IDC_EDIT_PORCENTAJEPROMOCIONAP, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Productuochos, IDC_EDIT_PRECIOFINALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Productuochos, IDC_CHECK_PROMOCION, BM_SETCHECK, BST_UNCHECKED, 0);

						BMP01 = (HBITMAP)LoadImage(NULL, "", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
						BMP02 = (HBITMAP)LoadImage(NULL, "", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
						SendDlgItemMessage(Productuochos, IDC_PICTURE_FOTO01, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)"");
						SendDlgItemMessage(Productuochos, IDC_PICTURE_FOTO02, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)"");


						MessageBox(Productuochos, "Eliminación Exitosa", "¡PERFECTO!", MB_OK);
						break;

					}

					auxP = auxP->sig;
				};
			}
			else { MessageBox(Productuochos, "La Eliminación Fallo.", "ERROR", MB_OK); };
			return true;
		}
		case ID_EXAMINARAV01: {ZeroMemory(&panchis, sizeof(panchis));
			panchis.lStructSize = sizeof(panchis);
			panchis.hwndOwner = Productuochos;
			panchis.lpstrFilter = "MP3 (*.mp3)\0*.mp3\0";
			panchis.lpstrFile = ArchivosoCancionIntroducida;
			panchis.nMaxFile = MAX_PATH;
			panchis.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
			panchis.lpstrDefExt = ".mp3";
			if (GetSaveFileName(&panchis) == TRUE) {
				SendDlgItemMessage(Productuochos, IDC_EDIT_URLSONIDOAV, WM_SETTEXT, NULL, (LPARAM)ArchivosoCancionIntroducida);
			}
			else {
				MessageBox(Productuochos, "No se pudo cargar el archivo.", "Error", MB_ICONERROR | MB_OK);
			}
			return true;
		}
		case ID_EXAMINARAV02: {
			ZeroMemory(&panchis, sizeof(panchis));
			panchis.lStructSize = sizeof(panchis);
			panchis.hwndOwner = Productuochos;
			panchis.lpstrFilter = "BMP (*.bmp)\0*.bmp\0";
			panchis.lpstrFile = ArchivosoImagenIntroducida01;
			panchis.nMaxFile = MAX_PATH;
			panchis.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
			panchis.lpstrDefExt = ".bmp";
			if (GetSaveFileName(&panchis) == TRUE) {
				BMP01 = (HBITMAP)LoadImage(NULL, ArchivosoImagenIntroducida01, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
				SendDlgItemMessage(Productuochos, IDC_PICTURE_FOTO01, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP01);
				SendDlgItemMessage(Productuochos, IDC_EDIT_URLFOTO01, WM_SETTEXT, NULL, (LPARAM)ArchivosoImagenIntroducida01);
			}
			else {
				MessageBox(Productuochos, "No se pudo cargar el archivo.", "Error", MB_ICONERROR | MB_OK);
			}
			return true;
		}
		case ID_EXAMINARAV03: {
			ZeroMemory(&panchis, sizeof(panchis));
			panchis.lStructSize = sizeof(panchis);
			panchis.hwndOwner = Productuochos;
			panchis.lpstrFilter = "BMP (*.bmp)\0*.bmp\0";
			panchis.lpstrFile = ArchivosoImagenIntroducida02;
			panchis.nMaxFile = MAX_PATH;
			panchis.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
			panchis.lpstrDefExt = ".bmp";
			if (GetSaveFileName(&panchis) == TRUE) {
				BMP02 = (HBITMAP)LoadImage(NULL, ArchivosoImagenIntroducida02, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
				SendDlgItemMessage(Productuochos, IDC_PICTURE_FOTO02, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP02);
				SendDlgItemMessage(Productuochos, IDC_EDIT_URLFOTO02, WM_SETTEXT, NULL, (LPARAM)ArchivosoImagenIntroducida02);
			}
			else {
				MessageBox(Productuochos, "No se pudo cargar el archivo.", "Error", MB_ICONERROR | MB_OK);
			}
			return true;
		}
		case ID_REPRODUCIRAP: {
			SendDlgItemMessage(Productuochos, IDC_EDIT_URLSONIDOAP, WM_GETTEXT, MAX_PATH, (LPARAM)mp3);
			if (strcmp(mp3, "") != 0)
			{
				sprintf_s(comando, "open \"%s\" alias MP3", mp3);
				mciSendString(comando, NULL, 0, 0);
				mciSendString("play MP3", NULL, 0, 0);
			}
			return true; }
		case ID_PAUSAAP:
			mciSendString("pause Mp3", NULL, 0, 0);
			return true;
		case ID_PARARAP:
			mciSendString("stop MP3", NULL, 0, 0);
			mciSendString("close MP3", NULL, 0, 0);
			return true;
		case ID_Menu:
			mciSendString("stop MP3", NULL, 0, 0);
			mciSendString("close MP3", NULL, 0, 0);
			EndDialog(Productuochos, 0);
			return true;
		case ID_PRODUCTOS_AGREGARPRODUCTOS:
			mciSendString("stop MP3", NULL, 0, 0);
			mciSendString("close MP3", NULL, 0, 0);
			DialogBox(panoso, MAKEINTRESOURCE(IDD_AGREGARPRODUCTO), Productuochos, AgregadosoProductoso);
			return true;
		case ID_PROMOCIONES_ADMINISTRADORDEPROMOCIONES:
			mciSendString("stop MP3", NULL, 0, 0);
			mciSendString("close MP3", NULL, 0, 0);
			DialogBox(panoso, MAKEINTRESOURCE(IDD_PROMOCIONES), Productuochos, Promocioso);
			return true;

		}
		return true;
	case WM_CLOSE:
		mciSendString("stop MP3", NULL, 0, 0);
		mciSendString("close MP3", NULL, 0, 0);
		EndDialog(Productuochos, 0);
		return true;
	case WM_DESTROY:
		EndDialog(Productuochos, 0);
		return true;
	}
	return false;
}

BOOL CALLBACK AgregadosoProductoso(HWND AgregadochoProductocho, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg)
	{
	case WM_INITDIALOG:


		SendDlgItemMessage(AgregadochoProductocho, IDC_COMBO_CATEGORIAP, CB_ADDSTRING, 0, (LPARAM)"CD");
		SendDlgItemMessage(AgregadochoProductocho, IDC_COMBO_CATEGORIAP, CB_ADDSTRING, 0, (LPARAM)"DVD");
		SendDlgItemMessage(AgregadochoProductocho, IDC_COMBO_CATEGORIAP, CB_ADDSTRING, 0, (LPARAM)"BLU-RAY");
		SendDlgItemMessage(AgregadochoProductocho, IDC_COMBO_CATEGORIAP, CB_ADDSTRING, 0, (LPARAM)"GAMES");
		SendDlgItemMessage(AgregadochoProductocho, IDC_COMBO_CATEGORIAP, CB_ADDSTRING, 0, (LPARAM)"MERCANCÍA OFICIAL");
		SendDlgItemMessage(AgregadochoProductocho, IDC_COMBO_CATEGORIAP, CB_ADDSTRING, 0, (LPARAM)"INSTRUMENTOS MUSICALES");
		SendDlgItemMessage(AgregadochoProductocho, IDC_COMBO_CATEGORIAP, CB_ADDSTRING, 0, (LPARAM)"ELECTRÓNICA");

		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_EXAMINARAP: {ZeroMemory(&panchis, sizeof(panchis));
			panchis.lStructSize = sizeof(panchis);
			panchis.hwndOwner = AgregadochoProductocho;
			panchis.lpstrFilter = "MP3 (*.mp3)\0*.mp3\0";
			panchis.lpstrFile = ArchivosoCancionIntroducida;
			panchis.nMaxFile = MAX_PATH;
			panchis.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
			panchis.lpstrDefExt = ".mp3";
			if (GetSaveFileName(&panchis) == TRUE) {
				SendDlgItemMessage(AgregadochoProductocho, IDC_EDIT_URLSONIDOAP, WM_SETTEXT, NULL, (LPARAM)ArchivosoCancionIntroducida);
			}
			else {
				MessageBox(AgregadochoProductocho, "No se pudo cargar el archivo.", "Error", MB_ICONERROR | MB_OK);
			}

			return true;
		}
		case ID_EXAMINARFAP01: {
			ZeroMemory(&panchis, sizeof(panchis));
			panchis.lStructSize = sizeof(panchis);
			panchis.hwndOwner = AgregadochoProductocho;
			panchis.lpstrFilter = "BMP (*.bmp)\0*.bmp\0";
			panchis.lpstrFile = ArchivosoImagenIntroducida01;
			panchis.nMaxFile = MAX_PATH;
			panchis.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
			panchis.lpstrDefExt = ".bmp";
			if (GetSaveFileName(&panchis) == TRUE) {
				BMP01 = (HBITMAP)LoadImage(NULL, ArchivosoImagenIntroducida01, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
				SendDlgItemMessage(AgregadochoProductocho, IDC_PICTURE_FOTOAP01, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP01);
				SendDlgItemMessage(AgregadochoProductocho, IDC_EDIT_IMAGENAP01, WM_SETTEXT, NULL, (LPARAM)ArchivosoImagenIntroducida01);
			}
			else {
				MessageBox(AgregadochoProductocho, "No se pudo cargar el archivo.", "Error", MB_ICONERROR | MB_OK);
			}
			return true;
		}
		case ID_EXAMINARFAP02: {
			ZeroMemory(&panchis, sizeof(panchis));
			panchis.lStructSize = sizeof(panchis);
			panchis.hwndOwner = AgregadochoProductocho;
			panchis.lpstrFilter = "BMP (*.bmp)\0*.bmp\0";
			panchis.lpstrFile = ArchivosoImagenIntroducida02;
			panchis.nMaxFile = MAX_PATH;
			panchis.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
			panchis.lpstrDefExt = ".bmp";
			if (GetSaveFileName(&panchis) == TRUE) {
				BMP02 = (HBITMAP)LoadImage(NULL, ArchivosoImagenIntroducida02, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
				SendDlgItemMessage(AgregadochoProductocho, IDC_PICTURE_FOTOAP02, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP02);
				SendDlgItemMessage(AgregadochoProductocho, IDC_EDIT_IMAGENAP02, WM_SETTEXT, NULL, (LPARAM)ArchivosoImagenIntroducida02);
			}
			else {
				MessageBox(AgregadochoProductocho, "No se pudo cargar el archivo.", "Error", MB_ICONERROR | MB_OK);
			}
			return true;
		}
		case ID_REPRODUCIRAP: {
			SendDlgItemMessage(AgregadochoProductocho, IDC_EDIT_URLSONIDOAP, WM_GETTEXT, MAX_PATH, (LPARAM)mp3);
			if (strcmp(mp3, "") != 0)
			{
				sprintf_s(comando, "open \"%s\" alias MP3", mp3);
				mciSendString(comando, NULL, 0, 0);
				mciSendString("play MP3", NULL, 0, 0);
			}
			return true; }
		case ID_PAUSAAP:
			mciSendString("pause Mp3", NULL, 0, 0);
			return true;
		case ID_PARARAP:
			mciSendString("stop MP3", NULL, 0, 0);
			mciSendString("close MP3", NULL, 0, 0);
			return true;
		case ID_ACEPTARAP: {nuevoP = new arreglosoproductoso;
			nuevoP->ant = NULL;
			nuevoP->sig = NULL;

			int temporal;

			//NOMBRE DEL PRODUCTO
			strcpy_s(nuevoP->usuario, usuariosoqueiniciosesion);

			char pantequilla[50];
			SendDlgItemMessage(AgregadochoProductocho, IDC_EDIT_NOMBREAP, WM_GETTEXT, 50, (LPARAM)pantequilla);
			for (int i = 0; pantequilla[i]; i++) {          // Aqui se esta acomodando de minusculas a  mayusculas usando la 
				pantequilla[i] = toupper(pantequilla[i]);   // funcion toupper
				banderoso = true;
			}
			strcpy_s(nuevoP->nombre, pantequilla);

			//PRECIO DEL PRODUCTO
			char pantequilloso[50];
			SendDlgItemMessage(AgregadochoProductocho, IDC_EDIT_PRECIOAP, WM_GETTEXT, 50, (LPARAM)pantequilloso);
			temporal = atoi(pantequilloso); // Se modifican los valores char a int
			if (!temporal)
			{
				banderoso = false;
			}
			else {
				nuevoP->precio = temporal;
			};

			//CATEGORIA DEL PRODUCTO
			panto = SendDlgItemMessage(AgregadochoProductocho, IDC_COMBO_CATEGORIAP, CB_GETCURSEL, 0, 0);
			if (panto != -1) {
				char pantequillocho[50];
				SendDlgItemMessage(AgregadochoProductocho, IDC_COMBO_CATEGORIAP, WM_GETTEXT, 50, (LPARAM)pantequillocho);
				strcpy_s(nuevoP->categoria, pantequillocho);
			}
			else(banderoso = false);

			// SONIDO
			char pantimusica[MAX_PATH];
			SendDlgItemMessage(AgregadochoProductocho, IDC_EDIT_URLSONIDOAP, WM_GETTEXT, MAX_PATH, (LPARAM)pantimusica);
			strcpy_s(nuevoP->sonido, pantimusica);

			// FOTOS
			char pantimagen01[MAX_PATH];
			SendDlgItemMessage(AgregadochoProductocho, IDC_EDIT_IMAGENAP01, WM_GETTEXT, MAX_PATH, (LPARAM)pantimagen01);
			strcpy_s(nuevoP->foto01, pantimagen01);

			char pantimagen02[MAX_PATH];
			SendDlgItemMessage(AgregadochoProductocho, IDC_EDIT_IMAGENAP02, WM_GETTEXT, MAX_PATH, (LPARAM)pantimagen02);
			strcpy_s(nuevoP->foto02, pantimagen02);


			auxP = inicioP;
			while (auxP != NULL) {

				char panteyoyo[50];
				SendDlgItemMessage(AgregadochoProductocho, IDC_EDIT_NOMBREAP, WM_GETTEXT, 50, (LPARAM)panteyoyo);

				if (strcmp(auxP->nombre, panteyoyo) == 0) {
					banderoso = false;
					banderra = true;
					break;
				}
				auxP = auxP->sig;
			}


			if (banderoso == true) {
				if (inicioP == NULL) {
					inicioP = nuevoP;
				}
				else {
					auxP = inicioP;
					while (auxP->sig != NULL) {
						auxP = auxP->sig;
					}
					auxP->sig = nuevoP;
					nuevoP->ant = auxP;
				}

				mciSendString("stop MP3", NULL, 0, 0);
				mciSendString("close MP3", NULL, 0, 0);
				MessageBox(AgregadochoProductocho, "Registro Exitoso", "¡PERFECTO!", MB_OK);
				EndDialog(AgregadochoProductocho, 0);

			}
			else {

				if (banderra == true) {
					MessageBox(0, "Error con el nombre del producto. Favor de ingresarlo con diferente nombre.", "ERROR", MB_ICONERROR | MB_OK);

				}
				MessageBox(0, "Error con los datos ingresados. Favor de ingresar o corregir los datos.", "ERROR", MB_ICONERROR | MB_OK);
			}

			return true; }
		case ID_CANCELARAP:
			EndDialog(AgregadochoProductocho, 0);
			return true;
		}
		return true;
	case WM_CLOSE:
		EndDialog(AgregadochoProductocho, 0);
		mciSendString("stop MP3", NULL, 0, 0);
		mciSendString("close MP3", NULL, 0, 0);
		return true;
	case WM_DESTROY:
		EndDialog(AgregadochoProductocho, 0);
		return true;
	}
	return false;

}

BOOL CALLBACK Promocioso(HWND Promociochos, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg)
	{
	case WM_INITDIALOG: {
		SendDlgItemMessage(Promociochos, IDC_COMBO_PROMOCIONESAPR, CB_RESETCONTENT, 0, 0);
		auxPR = inicioPR;

		while (auxPR != NULL)
		{
			SendDlgItemMessage(Promociochos, IDC_COMBO_PROMOCIONESAPR, CB_ADDSTRING, 0, (LPARAM)auxPR->nombrepromocion);
			auxPR = auxPR->sig;
		}


		//PORCENTAJE DE PROMOCION

		SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)"1");
		SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)"2");
		SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)"3");
		SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)"4");
		SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)"5");
		SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)"6");
		SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)"7");
		SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)"8");
		SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)"9");

		pantequillosho = 10;

		for (i = 0; i <= 90; i++) {
			itoa(pantequillosho, temporal, 10);
			SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)temporal);
			pantequillosho++;
		}

		// FECHA DD

		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)"09");

		pantequillosho = 10;

		for (i = 0; i <= 21; i++) {
			itoa(pantequillosho, temporal, 10);
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)temporal);
			pantequillosho++;
		}

		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)"09");

		pantequillosho = 10;

		for (i = 0; i <= 21; i++) {
			itoa(pantequillosho, temporal, 10);
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)temporal);
			pantequillosho++;
		}

		// FECHA MM

		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"09");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"10");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"11");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"12");

		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"09");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"10");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"11");
		SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"12");

		//FECHA AAAA

		pantequillosho = 2017;

		for (i = 0; i <= 27; i++) {
			itoa(pantequillosho, temporal, 10);
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAAAAAAPR_01, CB_ADDSTRING, 0, (LPARAM)temporal);
			pantequillosho++;
		}

		pantequillosho = 2017;

		for (i = 0; i <= 27; i++) {
			itoa(pantequillosho, temporal, 10);
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAAAAAAPR_2, CB_ADDSTRING, 0, (LPARAM)temporal);
			pantequillosho++;
		}

		//HORA HH
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"09");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"10");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"11");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"12");

		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"09");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"10");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"11");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"12");

		//HORA MM

		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"00");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"09");

		pantequillosho = 10;

		for (i = 0; i <= 49; i++) {
			itoa(pantequillosho, temporal, 10);
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)temporal);
			pantequillosho++;
		}

		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"00");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"09");

		pantequillosho = 10;

		for (i = 0; i <= 49; i++) {
			itoa(pantequillosho, temporal, 10);
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)temporal);
			pantequillosho++;
		}

		//HORA SS

		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR3, CB_ADDSTRING, 0, (LPARAM)"00");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR3, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR3, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR3, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR3, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR3, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR3, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR3, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR3, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR3, CB_ADDSTRING, 0, (LPARAM)"09");

		pantequillosho = 10;

		for (i = 0; i <= 49; i++) {
			itoa(pantequillosho, temporal, 10);
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR3, CB_ADDSTRING, 0, (LPARAM)temporal);
			pantequillosho++;
		}

		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"00");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"09");

		pantequillosho = 10;

		for (i = 0; i <= 49; i++) {
			itoa(pantequillosho, temporal, 10);
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)temporal);
			pantequillosho++;
		}

		//AM y PM
		SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM01, CB_ADDSTRING, 0, (LPARAM)"AM");
		SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM01, CB_ADDSTRING, 0, (LPARAM)"PM");
		SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM2, CB_ADDSTRING, 0, (LPARAM)"AM");
		SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM2, CB_ADDSTRING, 0, (LPARAM)"PM");

		//ALARMA
		SendDlgItemMessage(Promociochos, IDC_COMBO_SONIDOALARMA, CB_ADDSTRING, 0, (LPARAM)"Nituninadie.mp3");
		SendDlgItemMessage(Promociochos, IDC_COMBO_SONIDOALARMA, CB_ADDSTRING, 0, (LPARAM)"Jigglypuff.mp3");
		SendDlgItemMessage(Promociochos, IDC_COMBO_SONIDOALARMA, CB_ADDSTRING, 0, (LPARAM)"Sometimes.mp3");




		return true;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_ACTUALIZARAPR: {
			SendDlgItemMessage(Promociochos, IDC_COMBO_PROMOCIONESAPR, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(Promociochos, IDC_EDIT_NOMBREPRODUCTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_NOMBREPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOINICIALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOFINALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_DESCRIPCIONPRODUCTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAAAAAAPR_01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR3, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAAAAAAPR_2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_SONIDOPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA02, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA02, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM02, WM_SETTEXT, MAX_PATH, (LPARAM)"");


			auxPR = inicioPR;

			while (auxPR != NULL)
			{
				if (strcmp(auxPR->usuario, usuariosoqueiniciosesion) == 0) {
					SendDlgItemMessage(Promociochos, IDC_COMBO_PROMOCIONESAPR, CB_ADDSTRING, 0, (LPARAM)auxPR->nombrepromocion);
				}
				auxPR = auxPR->sig;
			}

			return true; }
		case ID_OK_MOSTRARPROMOCIONES: {
			auxPR = inicioPR;
			char pantequimia[MAX_PATH];
			SendDlgItemMessage(Promociochos, IDC_COMBO_PROMOCIONESAPR, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimia);
			while (auxPR != NULL)
			{
				if (strcmp(auxPR->nombrepromocion, pantequimia) == 0 && strcmp(auxPR->usuario, usuariosoqueiniciosesion) == 0) {

					SendDlgItemMessage(Promociochos, IDC_EDIT_NOMBREPRODUCTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->producto);
					SendDlgItemMessage(Promociochos, IDC_EDIT_NOMBREPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->nombrepromocion);
					SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->nombrepromocion);

					char temporal[MAX_PATH];
					itoa(auxPR->porcentajepromocion, temporal, 10);
					SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)temporal);


					SendDlgItemMessage(Promociochos, IDC_DESCRIPCIONPRODUCTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->descripcion);
					SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->fechainicio);
					SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA02, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->fechafinal);
					SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->horainicio);
					SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA02, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->horafinal);
					SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->AMPM01);
					SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM02, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->AMPM02);
					SendDlgItemMessage(Promociochos, IDC_COMBO_SONIDOPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->alarma);

					float porcentaje;
					float precioinicial;
					float preciofinal;


					char pantequimiosho[MAX_PATH];
					char pantequiqui[MAX_PATH];

					porcentaje = auxPR->porcentajepromocion;

					auxP = inicioP;
					while (auxP != NULL)
					{
						if (strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0 && strcmp(auxP->nombre, auxPR->producto) == 0) {

							char pantequilloco[MAX_PATH];
							itoa(auxP->precio, pantequilloco, 10);
							SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOINICIALCONPROMOCIONAPR, WM_SETTEXT, 0, (LPARAM)pantequilloco);
						}
						auxP = auxP->sig;
					}

					SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOINICIALCONPROMOCIONAPR, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimiosho);
					precioinicial = atoi(pantequimiosho); // Se modifican los valores char a int

					preciofinal = ((precioinicial*porcentaje) / 100);
					preciofinal = (precioinicial - preciofinal);

					itoa(preciofinal, pantequiqui, 10);
					SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOFINALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)pantequiqui);

					break;
				}
				auxPR = auxPR->sig;
			}

			return true;
		}
		case ID_OKTODASPROMOCIONESAPR: {
			SendDlgItemMessage(Promociochos, IDC_COMBO_PROMOCIONESAPR, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(Promociochos, IDC_EDIT_NOMBREPRODUCTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_NOMBREPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOINICIALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOFINALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_DESCRIPCIONPRODUCTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAAAAAAPR_01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR3, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAAAAAAPR_2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_SONIDOPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA02, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA02, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM02, WM_SETTEXT, MAX_PATH, (LPARAM)"");

			auxPR = inicioPR;

			while (auxPR != NULL)
			{
				if (strcmp(auxPR->usuario, usuariosoqueiniciosesion) == 0) {
					SendDlgItemMessage(Promociochos, IDC_COMBO_PROMOCIONESAPR, CB_ADDSTRING, 0, (LPARAM)auxPR->nombrepromocion);
				}
				auxPR = auxPR->sig;
			}

			return true;
		}
		case ID_OKNOMBREDELAPROMOCIONAPR: {
			SendDlgItemMessage(Promociochos, IDC_COMBO_PROMOCIONESAPR, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(Promociochos, IDC_EDIT_NOMBREPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOINICIALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOFINALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_DESCRIPCIONPRODUCTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAAAAAAPR_01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR3, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAAAAAAPR_2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_COMBO_SONIDOPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA02, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA02, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM02, WM_SETTEXT, MAX_PATH, (LPARAM)"");

			auxPR = inicioPR;

			while (auxPR != NULL)
			{
				if (strcmp(auxPR->usuario, usuariosoqueiniciosesion) == 0) {
					SendDlgItemMessage(Promociochos, IDC_COMBO_PROMOCIONESAPR, CB_ADDSTRING, 0, (LPARAM)auxPR->nombrepromocion);
				}
				auxPR = auxPR->sig;
			}

			return true;
		}
		case ID_OKBUSCARNOMBREPROMOCIONAPR: {
			auxPR = inicioPR;
			bool banderin = false;
			char pantequimi[MAX_PATH];
			SendDlgItemMessage(Productuochos, IDC_EDIT_BUSCARPRODUCTOS, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimi);
			for (int i = 0; pantequimi[i]; i++) {          // Aqui se esta acomodando de minusculas a  mayusculas usando la 
				pantequimi[i] = toupper(pantequimi[i]);   // funcion toupper
			}

			while (auxPR != NULL)
			{
				if (strcmp(auxPR->nombrepromocion, pantequimi) == 0 && strcmp(auxPR->usuario, usuariosoqueiniciosesion) == 0) {

					SendDlgItemMessage(Promociochos, IDC_EDIT_NOMBREPRODUCTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->producto);
					SendDlgItemMessage(Promociochos, IDC_EDIT_NOMBREPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->nombrepromocion);
					SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->nombrepromocion);

					char temporal[MAX_PATH];
					itoa(auxPR->porcentajepromocion, temporal, 10);
					SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)temporal);


					SendDlgItemMessage(Promociochos, IDC_DESCRIPCIONPRODUCTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->descripcion);
					SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->fechainicio);
					SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA02, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->fechafinal);
					SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->horainicio);
					SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA02, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->horafinal);
					SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->AMPM01);
					SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM02, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->AMPM02);
					SendDlgItemMessage(Promociochos, IDC_COMBO_SONIDOPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->alarma);

					float porcentaje;
					float precioinicial;
					float preciofinal;


					char pantequimiosho[MAX_PATH];
					char pantequiqui[MAX_PATH];

					porcentaje = auxPR->porcentajepromocion;

					auxP = inicioP;
					while (auxP != NULL)
					{
						if (strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0 && strcmp(auxP->nombre, auxPR->producto) == 0) {

							char pantequilloco[MAX_PATH];
							itoa(auxP->precio, pantequilloco, 10);
							SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOINICIALCONPROMOCIONAPR, WM_SETTEXT, 0, (LPARAM)pantequilloco);
						}
						auxP = auxP->sig;
					}

					SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOINICIALCONPROMOCIONAPR, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimiosho);
					precioinicial = atoi(pantequimiosho); // Se modifican los valores char a int

					preciofinal = ((precioinicial*porcentaje) / 100);
					preciofinal = (precioinicial - preciofinal);

					itoa(preciofinal, pantequiqui, 10);
					SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOFINALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)pantequiqui);

					SendDlgItemMessage(Promociochos, IDC_EDIT_BUSCARPRODUCTOS, WM_SETTEXT, MAX_PATH, (LPARAM)"");


					banderin = true;
					MessageBox(Promociochos, "Búsqueda Exitosa", "¡PERFECTO!", MB_OK);

					break;
				}

				auxP = auxP->sig;
			}

			if (banderin == false) {

				MessageBox(0, "No se encontro la información.", "ERROR", MB_ICONEXCLAMATION | MB_OK);
			}
			return true; }
		case ID_OKBUSCARNOMBREDELPRODUCTOAPR: {
			auxPR = inicioPR;
			bool banderin = false;
			char pantequimi[MAX_PATH];
			SendDlgItemMessage(Promociochos, IDC_EDIT_BUSCARPRODUCTOS, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimi);
			for (int i = 0; pantequimi[i]; i++) {          // Aqui se esta acomodando de minusculas a  mayusculas usando la 
				pantequimi[i] = toupper(pantequimi[i]);   // funcion toupper
			}

			while (auxPR != NULL)
			{
				if (strcmp(auxPR->producto, pantequimi) == 0 && strcmp(auxPR->usuario, usuariosoqueiniciosesion) == 0) {


					SendDlgItemMessage(Promociochos, IDC_EDIT_NOMBREPRODUCTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->producto);
					SendDlgItemMessage(Promociochos, IDC_EDIT_NOMBREPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->nombrepromocion);
					SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->nombrepromocion);

					char temporal[MAX_PATH];
					itoa(auxPR->porcentajepromocion, temporal, 10);
					SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)temporal);


					SendDlgItemMessage(Promociochos, IDC_DESCRIPCIONPRODUCTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->descripcion);
					SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->fechainicio);
					SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA02, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->fechafinal);
					SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->horainicio);
					SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA02, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->horafinal);
					SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->AMPM01);
					SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM02, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->AMPM02);
					SendDlgItemMessage(Promociochos, IDC_COMBO_SONIDOPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)auxPR->alarma);

					float porcentaje;
					float precioinicial;
					float preciofinal;

					char pantequimiosho[MAX_PATH];
					char pantequiqui[MAX_PATH];

					porcentaje = auxPR->porcentajepromocion;

					auxP = inicioP;
					while (auxP != NULL)
					{
						if (strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0 && strcmp(auxP->nombre, auxPR->producto) == 0) {

							char pantequilloco[MAX_PATH];
							itoa(auxP->precio, pantequilloco, 10);
							SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOINICIALCONPROMOCIONAPR, WM_SETTEXT, 0, (LPARAM)pantequilloco);
						}
						auxP = auxP->sig;
					}

					SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOINICIALCONPROMOCIONAPR, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimiosho);
					precioinicial = atoi(pantequimiosho); // Se modifican los valores char a int

					preciofinal = ((precioinicial*porcentaje) / 100);
					preciofinal = (precioinicial - preciofinal);

					itoa(preciofinal, pantequiqui, 10);
					SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOFINALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)pantequiqui);

					SendDlgItemMessage(Promociochos, IDC_EDIT_BUSCARPRODUCTOS, WM_SETTEXT, MAX_PATH, (LPARAM)"");

					banderin = true;
					MessageBox(Promociochos, "Búsqueda Exitosa", "¡PERFECTO!", MB_OK);

					break;
				}

				auxP = auxP->sig;
			}

			if (banderin == false) {

				MessageBox(0, "No se encontro la información.", "ERROR", MB_ICONEXCLAMATION | MB_OK);
			}
			return true; }
		case ID_OKAPR2: {
			float porcentaje;
			float precioinicial;
			float preciofinal;

			char pantequimia[MAX_PATH];
			char pantequimiosho[MAX_PATH];
			char pantequiqui[MAX_PATH];

			SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimia);
			porcentaje = atoi(pantequimia); // Se modifican los valores char a int

			SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOINICIALCONPROMOCIONAPR, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimiosho);
			precioinicial = atoi(pantequimiosho); // Se modifican los valores char a int

			preciofinal = ((precioinicial*porcentaje) / 100);
			preciofinal = (precioinicial - preciofinal);

			itoa(preciofinal, pantequiqui, 10);
			SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOFINALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)pantequiqui);

			return true; }
		case ID_REPRODUCIRAPR: {
			SendDlgItemMessage(Promociochos, IDC_COMBO_SONIDOPROMOCIONAPR, WM_GETTEXT, MAX_PATH, (LPARAM)mp3);
			if (strcmp(mp3, "") != 0)
			{
				sprintf_s(comando, "open \"%s\" alias MP3", mp3);
				mciSendString(comando, NULL, 0, 0);
				mciSendString("play MP3", NULL, 0, 0);
			}
			return true; }
		case ID_PAUSAAPR:
			mciSendString("pause Mp3", NULL, 0, 0);
			return true;
		case ID_PARARAPR:
			mciSendString("stop MP3", NULL, 0, 0);
			mciSendString("close MP3", NULL, 0, 0);
			return true;
		case ID_OKAPR3: {

			char pantedia[MAX_PATH];
			char pantemes[MAX_PATH];
			char panteaño[MAX_PATH];

			SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			panto = SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_01, CB_GETCURSEL, 0, 0);
			panta = SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, CB_GETCURSEL, 0, 0);
			pantato = SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAAAAAAPR_01, CB_GETCURSEL, 0, 0);


			if (panto != -1 && panta != -1 && pantato != -1) {
				fecha01 = true;

				SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_01, WM_GETTEXT, MAX_PATH, (LPARAM)pantedia);
				SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, WM_GETTEXT, MAX_PATH, (LPARAM)pantemes);
				SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAAAAAAPR_01, WM_GETTEXT, MAX_PATH, (LPARAM)panteaño);

				
					if (strcmp(pantemes, "02") == 0 && strcmp(pantedia, "31") == 0 || strcmp(pantedia, "30") == 0 || strcmp(pantedia, "29") == 0) {
						strcpy_s(pantedia, "28");
					}

					if (strcmp(pantemes, "04") == 0 && strcmp(pantedia, "31") == 0) {
						strcpy_s(pantedia, "30");
					}
					
					if (strcmp(pantemes, "06") == 0 && strcmp(pantedia, "31") == 0) {
						strcpy_s(pantedia, "30");
					}
			
					if (strcmp(pantemes, "09") == 0 && strcmp(pantedia, "31") == 0) {
						strcpy_s(pantedia, "30");
					}
					
					if (strcmp(pantemes, "11") == 0 && strcmp(pantedia, "31") == 0) {
						strcpy_s(pantedia, "30");
					}

				string dia = string(pantedia);
				string mes = string(pantemes);
				string año = string(panteaño);

				string panfecha = dia + "/" + mes + "/" + año;
				const char* panfechainicio = panfecha.c_str();

				SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA, WM_SETTEXT, MAX_PATH, (LPARAM)panfechainicio);

			}
			else(banderoso = false);
			return true; }
		case ID_OKAPR4: {

			char pantedia02[MAX_PATH];
			char pantemes02[MAX_PATH];
			char panteaño02[MAX_PATH];

			SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA02, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			panto = SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_2, CB_GETCURSEL, 0, 0);
			panta = SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, CB_GETCURSEL, 0, 0);
			pantato = SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAAAAAAPR_2, CB_GETCURSEL, 0, 0);


			if (panto != -1 && panta != -1 && pantato != -1) {
				fecha02 = true;

				SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_2, WM_GETTEXT, MAX_PATH, (LPARAM)pantedia02);
				SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, WM_GETTEXT, MAX_PATH, (LPARAM)pantemes02);
				SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAAAAAAPR_2, WM_GETTEXT, MAX_PATH, (LPARAM)panteaño02);

				if (strcmp(pantemes02, "02") == 0 && strcmp(pantedia02, "31") == 0 || strcmp(pantedia02, "30") == 0 || strcmp(pantedia02, "29") == 0) {
					strcpy_s(pantedia02, "28");
				}

				if (strcmp(pantemes02, "04") == 0 && strcmp(pantedia02, "31") == 0) {
					strcpy_s(pantedia02, "30");
				}

				if (strcmp(pantemes02, "06") == 0 && strcmp(pantedia02, "31") == 0) {
					strcpy_s(pantedia02, "30");
				}

				if (strcmp(pantemes02, "09") == 0 && strcmp(pantedia02, "31") == 0) {
					strcpy_s(pantedia02, "30");
				}

				if (strcmp(pantemes02, "11") == 0 && strcmp(pantedia02, "31") == 0) {
					strcpy_s(pantedia02, "30");
				}

				string dia02 = string(pantedia02);
				string mes02 = string(pantemes02);
				string año02 = string(panteaño02);

				string panfecha02 = dia02 + "/" + mes02 + "/" + año02;
				const char* panfechafinal02 = panfecha02.c_str();

				SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA02, WM_SETTEXT, MAX_PATH, (LPARAM)panfechafinal02);


			}
			else(banderoso = false);
			return true;
		}
		case ID_OKAPR5: {

			char pantehora[MAX_PATH];
			char panteminuto[MAX_PATH];
			char pantesegundo[MAX_PATH];
			SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			panto = SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, CB_GETCURSEL, 0, 0);
			panta = SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, CB_GETCURSEL, 0, 0);
			pantato = SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR01, CB_GETCURSEL, 0, 0);

			if (panto != -1 && panta != -1 && pantato != -1) {
				hora01 = true;

				SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, WM_GETTEXT, MAX_PATH, (LPARAM)pantehora);
				SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, WM_GETTEXT, MAX_PATH, (LPARAM)panteminuto);
				SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR3, WM_GETTEXT, MAX_PATH, (LPARAM)pantesegundo);

				int pantehoraint;
				int horapm;
				char ampmjumm[MAX_PATH];
				SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM01, WM_GETTEXT, MAX_PATH, (LPARAM)ampmjumm);
				if (strcmp(ampmjumm, "PM") == 0) {
					pantehoraint = atoi(pantehora);

					horapm = (12 - pantehoraint);
					horapm = (24 - horapm);
					itoa(horapm, pantehora, 10);
				}



				string hora = string(pantehora);
				string minuto = string(panteminuto);
				string segundo = string(pantesegundo);

				string panhora = hora + ":" + minuto + ":" + segundo;
				const char* panhorainicio = panhora.c_str();

				SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA, WM_SETTEXT, MAX_PATH, (LPARAM)panhorainicio);

				char panpan[MAX_PATH];
				SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM01, WM_GETTEXT, MAX_PATH, (LPARAM)panpan);
				SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)panpan);


			}
			else(banderoso = false);

			return true;
		}
		case ID_OKAPR6: {
			char pantehora02[MAX_PATH];
			char panteminuto02[MAX_PATH];
			char pantesegundo02[MAX_PATH];

			SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA02, WM_SETTEXT, MAX_PATH, (LPARAM)"");
			panto = SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, CB_GETCURSEL, 0, 0);
			panta = SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, CB_GETCURSEL, 0, 0);
			pantato = SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR01, CB_GETCURSEL, 0, 0);

			if (panto != -1 && panta != -1 && pantato != -1) {
				hora02 = true;

				SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, WM_GETTEXT, MAX_PATH, (LPARAM)pantehora02);
				SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, WM_GETTEXT, MAX_PATH, (LPARAM)panteminuto02);
				SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR2, WM_GETTEXT, MAX_PATH, (LPARAM)pantesegundo02);

				int pantehoraint;
				int horapm;
				char ampmjumm[MAX_PATH];
				SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM2, WM_GETTEXT, MAX_PATH, (LPARAM)ampmjumm);
				if (strcmp(ampmjumm, "PM") == 0) {
					pantehoraint = atoi(pantehora02);

					horapm = (12 - pantehoraint);
					horapm = (24 - horapm);
					itoa(horapm, pantehora02, 10);
				}



				string hora02 = string(pantehora02);
				string minuto02 = string(panteminuto02);
				string segundo02 = string(pantesegundo02);


				string panhora02 = hora02 + ":" + minuto02 + ":" + segundo02;
				const char* panhorafinal02 = panhora02.c_str();

				SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA02, WM_SETTEXT, MAX_PATH, (LPARAM)panhorafinal02);
				char panpan[MAX_PATH];
				SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM2, WM_GETTEXT, MAX_PATH, (LPARAM)panpan);
				SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM02, WM_SETTEXT, MAX_PATH, (LPARAM)panpan);

			}
			else(banderoso = false);


			return true;
		}
		case ID_MODIFICARPROMOCION: {
			auxPR = inicioPR;
			char pantequimico[MAX_PATH];
			SendDlgItemMessage(Promociochos, IDC_COMBO_PROMOCIONESAPR, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimico);

			panto = SendDlgItemMessage(Promociochos, IDC_COMBO_PRODUCTOSAV, CB_GETCURSEL, 0, 0);

			if (panto != -1) {
				while (auxPR != NULL)
				{

					if (strcmp(auxPR->nombrepromocion, pantequimico) == 0 && strcmp(auxPR->usuario, usuariosoqueiniciosesion) == 0) {



						// VERIFICACION DE PROMOCION EN EL DIA
						auxPR->diapromocion = 0;
						nuevoPR->auxilio = true;


						//NOMBRE DE LA PROMOCION
						char pantequilla[50];
						SendDlgItemMessage(Promociochos, IDC_EDIT_NOMBREPROMOCIONAPR, WM_GETTEXT, 50, (LPARAM)pantequilla);
						for (int i = 0; pantequilla[i]; i++) {          // Aqui se esta acomodando de minusculas a  mayusculas usando la 
							pantequilla[i] = toupper(pantequilla[i]);   // funcion toupper
							banderoso = true;
						}


						//PORCENTAJE DE LA PROMOCION DEL PRODUCTO
						char pantequilloso[50];
						float temporal;
						SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, WM_GETTEXT, 50, (LPARAM)pantequilloso);
						temporal = atoi(pantequilloso); // Se modifican los valores char a int
						if (!temporal)
						{
							banderoso = false;
						}


						//DESCRIPCION DE LA PROMOCION
						char pantequico[MAX_PATH];
						SendDlgItemMessage(Promociochos, IDC_DESCRIPCIONPRODUCTOAPR, WM_GETTEXT, MAX_PATH, (LPARAM)pantequico);
						for (int i = 0; pantequico[i]; i++) {          // Aqui se esta acomodando de minusculas a  mayusculas usando la 
							pantequico[i] = toupper(pantequico[i]);   // funcion toupper
							banderoso = true;
						}


						//FECHA INICIO DE LA PROMOCION
						panto = SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_01, CB_GETCURSEL, 0, 0);
						panta = SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, CB_GETCURSEL, 0, 0);
						pantato = SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAAAAAAPR_01, CB_GETCURSEL, 0, 0);

						if (fecha01 == true) {
							if (panto != -1 && panta != -1 && pantato != -1 || fecha01 == true) {

								SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA, WM_GETTEXT, MAX_PATH, (LPARAM)pancentavo);

							}
							else(banderoso = false);
						}
						else(strcpy_s(pancentavo, auxPR->fechainicio));

						//FECHA FINAL DE LA PROMOCION

						panto = SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_2, CB_GETCURSEL, 0, 0);
						panta = SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, CB_GETCURSEL, 0, 0);
						pantato = SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAAAAAAPR_2, CB_GETCURSEL, 0, 0);

						if (fecha02 == true) {
							if (panto != -1 && panta != -1 && pantato != -1) {
								SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA02, WM_GETTEXT, MAX_PATH, (LPARAM)pantrequilo);
							}
							else(banderoso = false);
						}
						else(strcpy_s(pantrequilo, auxPR->fechafinal));


						//HORA INICIO DE LA PROMOCION
						panto = SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, CB_GETCURSEL, 0, 0);
						panta = SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, CB_GETCURSEL, 0, 0);
						pantato = SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR3, CB_GETCURSEL, 0, 0);

						if (hora01 == true) {
							if (panto != -1 && panta != -1 && pantato != -1 || hora01 == true) {

								SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA, WM_GETTEXT, MAX_PATH, (LPARAM)pantequigocho);
							}
							else(banderoso = false);
						}
						else(strcpy_s(pantequigocho, auxPR->horainicio));

						//HORA FINAL DE LA PROMOCION
						panto = SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, CB_GETCURSEL, 0, 0);
						panta = SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, CB_GETCURSEL, 0, 0);
						pantato = SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR01, CB_GETCURSEL, 0, 0);

						if (hora01 == true) {
							if (panto != -1 && panta != -1 && pantato != -1 || hora02 == true) {

								SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA02, WM_GETTEXT, MAX_PATH, (LPARAM)pantequillochocho);

							}
							else(banderoso = false);
						}
						else(strcpy_s(pantequillochocho, auxPR->horafinal));


						// AM Y PM
						char pantiAMPM01[MAX_PATH];
						SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM01, WM_GETTEXT, MAX_PATH, (LPARAM)pantiAMPM01);


						char pantiAMPM02[MAX_PATH];
						SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM02, WM_GETTEXT, MAX_PATH, (LPARAM)pantiAMPM02);


						//SONIDO
						char pantisonido01[MAX_PATH];
						SendDlgItemMessage(Promociochos, IDC_COMBO_SONIDOPROMOCIONAPR, WM_GETTEXT, MAX_PATH, (LPARAM)pantisonido01);



						if (banderoso == true) {

							strcpy_s(auxPR->nombrepromocion, pantequilla);
							auxPR->porcentajepromocion = temporal;
							strcpy_s(auxPR->descripcion, pantequico);
							strcpy_s(auxPR->fechainicio, pancentavo);
							strcpy_s(auxPR->fechafinal, pantrequilo);
							strcpy_s(auxPR->horainicio, pantequigocho);
							strcpy_s(auxPR->horafinal, pantequillochocho);
							strcpy_s(auxPR->AMPM01, pantiAMPM01);
							strcpy_s(auxPR->AMPM02, pantiAMPM02);
							strcpy_s(auxPR->alarma, pantisonido01);

							SendDlgItemMessage(Promociochos, IDC_COMBO_PROMOCIONESAPR, CB_RESETCONTENT, 0, 0);
							SendDlgItemMessage(Promociochos, IDC_EDIT_NOMBREPRODUCTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_EDIT_NOMBREPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOINICIALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOFINALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_DESCRIPCIONPRODUCTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAAAAAAPR_01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR3, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAAAAAAPR_2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_COMBO_SONIDOPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA02, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA02, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
							SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM02, WM_SETTEXT, MAX_PATH, (LPARAM)"");

							fecha01 = false;
							fecha02 = false;
							hora01 = false;
							hora02 = false;


							MessageBox(Promociochos, "Cambio Exitoso.", "¡PERFECTO!", MB_OK);
							break;

						}
						else {
							MessageBox(Promociochos, "Error con los datos ingresados. Favor de ingresar o corregir los datos.", "ERROR", MB_ICONERROR | MB_OK);
							break;

						}

						break;
					}

					auxPR = auxPR->sig;
				}

			}
			else { MessageBox(Promociochos, "La Modifición Fallo.", "ERROR", MB_OK); };
			return true;
		}
		case IDCELIMINARPROMOCION: {
			auxPR = inicioPR;
			panto = SendDlgItemMessage(Promociochos, IDC_COMBO_PROMOCIONESAPR, CB_GETCURSEL, 0, 0);
			char eliminacion[MAX_PATH];
			SendDlgItemMessage(Promociochos, IDC_COMBO_PROMOCIONESAPR, WM_GETTEXT, MAX_PATH, (LPARAM)eliminacion);


			if (panto != -1) {

				while (auxPR != NULL) {
					if (strcmp(auxPR->nombrepromocion, eliminacion) == 0) {
						arreglosopromocioso *eliminarPR = auxPR;


						auxP = inicioP;

						while (auxP != NULL)
						{

							if (strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0 && strcmp(auxP->nombre, auxPR->producto) == 0) {
								auxP->promocion = false;
							}
							auxP = auxP->sig;
						}

						if (eliminarPR->sig == NULL && eliminarPR->ant == NULL) {
							eliminarPR = inicioPR;
							inicioPR = NULL;
							auxPR = NULL;
							delete eliminarPR;



						}
						else if (eliminarPR->ant == NULL) {
							auxPR = auxPR->sig;
							inicioPR = eliminarPR->sig;
							inicioPR->sig = NULL;
							eliminarPR->sig = NULL;
							delete eliminarPR;


						}
						else if (eliminarPR->sig == NULL) {
							auxPR = eliminarPR->ant;
							eliminarPR->ant->sig = NULL;
							delete eliminarPR;


						}
						else {
							auxPR = eliminarPR->ant;
							auxPR->sig = eliminarPR->ant;
							eliminarPR->sig->ant = auxPR;
							delete eliminarPR;
						}

						SendDlgItemMessage(Promociochos, IDC_COMBO_PROMOCIONESAPR, CB_RESETCONTENT, 0, 0);
						SendDlgItemMessage(Promociochos, IDC_EDIT_NOMBREPRODUCTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_EDIT_NOMBREPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_COMBO_DESCUENTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOINICIALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_EDIT_PRECIOFINALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_DESCRIPCIONPRODUCTOAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAAAAAAPR_01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR3, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_COMBO_FECHADDAPR_2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAMMAPR_2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_COMBO_FECHAAAAAAPR_2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_COMBO_HORAHHAPR2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_COMBO_HORAMMAPR2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_COMBO_HORASSAPR2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_COMBO_AMPM2, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_COMBO_SONIDOPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONFECHA02, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_EDIT_INICIOPROMOCIONHORA02, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM01, WM_SETTEXT, MAX_PATH, (LPARAM)"");
						SendDlgItemMessage(Promociochos, IDC_EDIT_AMPM02, WM_SETTEXT, MAX_PATH, (LPARAM)"");



						MessageBox(Promociochos, "Eliminación Exitosa", "¡PERFECTO!", MB_OK);
						break;

					}

					auxPR = auxPR->sig;
				};
			}
			else { MessageBox(Promociochos, "La Eliminación Fallo.", "ERROR", MB_OK); };
			return true;
		}

		case ID_ARCHIVO_REGRESARALMENU:
			EndDialog(Promociochos, 0);
			return true;
		case ID_PROMOCIONES_AGREGARPROMOCIONES:
			DialogBox(panoso, MAKEINTRESOURCE(IDD_AGREGARPROMOCIONES), hDlgLogin, AgregadosoPromocioso);
			return true;
		}
		return true;
	case WM_CLOSE:
		mciSendString("stop MP3", NULL, 0, 0);
		mciSendString("close MP3", NULL, 0, 0);
		EndDialog(Promociochos, 0);
		return true;
	case WM_DESTROY:
		EndDialog(Promociochos, 0);
		return true;
	}
	return false;

}

BOOL CALLBACK AgregadosoPromocioso(HWND AgregadochoPromosiocho, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg)
	{

	case WM_INITDIALOG: {

		auxP = inicioP;

		while (auxP != NULL) {
			if (strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0) {
				SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_PRODUCTOAPR, CB_ADDSTRING, MAX_PATH, (LPARAM)auxP->nombre);
			}
			auxP = auxP->sig;
		}

		//PORCENTAJE DE PROMOCION

		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)"1");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)"2");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)"3");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)"4");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)"5");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)"6");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)"7");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)"8");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)"9");

		pantequillosho = 10;

		for (i = 0; i <= 90; i++) {
			itoa(pantequillosho, temporal, 10);
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_DESCUENTOAPR, CB_INSERTSTRING, 0, (LPARAM)temporal);
			pantequillosho++;
		}

		// FECHA DD

		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)"09");

		pantequillosho = 10;

		for (i = 0; i <= 21; i++) {
			itoa(pantequillosho, temporal, 10);
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_01, CB_ADDSTRING, 0, (LPARAM)temporal);
			pantequillosho++;
		}

		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)"09");

		pantequillosho = 10;

		for (i = 0; i <= 21; i++) {
			itoa(pantequillosho, temporal, 10);
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_2, CB_ADDSTRING, 0, (LPARAM)temporal);
			pantequillosho++;
		}

		// FECHA MM

		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"09");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"10");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"11");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_01, CB_ADDSTRING, 0, (LPARAM)"12");

		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"09");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"10");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"11");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_2, CB_ADDSTRING, 0, (LPARAM)"12");

		//FECHA AAAA

		pantequillosho = 2017;

		for (i = 0; i <= 27; i++) {
			itoa(pantequillosho, temporal, 10);
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAAAAAAPR_01, CB_ADDSTRING, 0, (LPARAM)temporal);
			pantequillosho++;
		}

		pantequillosho = 2017;

		for (i = 0; i <= 27; i++) {
			itoa(pantequillosho, temporal, 10);
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAAAAAAPR_2, CB_ADDSTRING, 0, (LPARAM)temporal);
			pantequillosho++;
		}

		//HORA HH
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"09");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"10");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"11");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR01, CB_ADDSTRING, 0, (LPARAM)"12");

		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"09");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"10");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"11");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR2, CB_ADDSTRING, 0, (LPARAM)"12");

		//HORA MM

		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"00");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)"09");

		pantequillosho = 10;

		for (i = 0; i <= 49; i++) {
			itoa(pantequillosho, temporal, 10);
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR01, CB_ADDSTRING, 0, (LPARAM)temporal);
			pantequillosho++;
		}

		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"00");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)"09");

		pantequillosho = 10;

		for (i = 0; i <= 49; i++) {
			itoa(pantequillosho, temporal, 10);
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR2, CB_ADDSTRING, 0, (LPARAM)temporal);
			pantequillosho++;
		}

		//HORA SS

		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR01, CB_ADDSTRING, 0, (LPARAM)"00");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR01, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR01, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR01, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR01, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR01, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR01, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR01, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR01, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR01, CB_ADDSTRING, 0, (LPARAM)"09");

		pantequillosho = 10;

		for (i = 0; i <= 49; i++) {
			itoa(pantequillosho, temporal, 10);
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR01, CB_ADDSTRING, 0, (LPARAM)temporal);
			pantequillosho++;
		}

		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"00");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"01");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"02");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"03");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"04");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"05");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"06");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"07");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"08");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)"09");

		pantequillosho = 10;

		for (i = 0; i <= 49; i++) {
			itoa(pantequillosho, temporal, 10);
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR2, CB_ADDSTRING, 0, (LPARAM)temporal);
			pantequillosho++;
		}

		//AM y PM
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_AMPM01, CB_ADDSTRING, 0, (LPARAM)"AM");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_AMPM01, CB_ADDSTRING, 0, (LPARAM)"PM");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_AMPM2, CB_ADDSTRING, 0, (LPARAM)"AM");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_AMPM2, CB_ADDSTRING, 0, (LPARAM)"PM");

		//ALARMA
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_SONIDOALARMA, CB_ADDSTRING, 0, (LPARAM)"Nituninadie.mp3");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_SONIDOALARMA, CB_ADDSTRING, 0, (LPARAM)"Jigglypuff.mp3");
		SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_SONIDOALARMA, CB_ADDSTRING, 0, (LPARAM)"Sometimes.mp3");

		return true;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case ID_OKAPR: {

			auxP = inicioP;
			char pantequimia[MAX_PATH];
			banderoso = true;
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_PRODUCTOAPR, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimia);

			while (auxP != NULL)
			{
				if (strcmp(auxP->nombre, pantequimia) == 0 && auxP->promocion == true && strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0) {

					MessageBox(0, "Error, no se puede ingresar diferentes promociones a un mismo producto. Favor corregir los datos.", "ERROR", MB_ICONERROR | MB_OK);
					banderoso = false;
					break;
				}
				auxP = auxP->sig;
			}

			if (banderoso == true) {
				auxP = inicioP;
				char pantequimia[MAX_PATH];
				SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_PRODUCTOAPR, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimia);
				while (auxP != NULL)
				{
					if (strcmp(auxP->nombre, pantequimia) == 0 && strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0) {
						itoa(auxP->precio, temporal, 10);
						SendDlgItemMessage(AgregadochoPromosiocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)temporal);
						break;
					}
					auxP = auxP->sig;
				}
			}
			return true;
		}
		case ID_OKAPR2: {
			float porcentaje;
			float precioinicial;
			float preciofinal;

			char pantequimia[MAX_PATH];
			char pantequimiosho[MAX_PATH];
			char pantequiqui[MAX_PATH];

			SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_DESCUENTOAPR, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimia);
			porcentaje = atoi(pantequimia); // Se modifican los valores char a int

			SendDlgItemMessage(AgregadochoPromosiocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONAPR, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimiosho);
			precioinicial = atoi(pantequimiosho); // Se modifican los valores char a int

			preciofinal = ((precioinicial*porcentaje) / 100);
			preciofinal = (precioinicial - preciofinal);

			itoa(preciofinal, pantequiqui, 10);
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_EDIT_PRECIOFINALCONPROMOCIONAPR, WM_SETTEXT, MAX_PATH, (LPARAM)pantequiqui);

			return true; }
		case ID_REPRODUCIRAPR:
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_SONIDOALARMA, WM_GETTEXT, MAX_PATH, (LPARAM)mp3);
			if (strcmp(mp3, "") != 0)
			{
				sprintf_s(comando, "open \"%s\" alias MP3", mp3);
				mciSendString(comando, NULL, 0, 0);
				mciSendString("play MP3", NULL, 0, 0);
			}
			return true;
		case ID_PAUSAAPR:
			mciSendString("pause Mp3", NULL, 0, 0);
			return true;
		case ID_PARARAPR:
			mciSendString("stop MP3", NULL, 0, 0);
			mciSendString("close MP3", NULL, 0, 0);
			return true;
		case ID_ACEPTARAPP: {
			nuevoPR = new arreglosopromocioso;
			nuevoPR->ant = NULL;
			nuevoPR->sig = NULL;

			int temporal;

			//USUARIO
			strcpy_s(nuevoPR->usuario, usuariosoqueiniciosesion);

			// VERIFICACION DE PROMOCION EN EL DIA
			nuevoPR->diapromocion = 0;
			nuevoPR->auxilio = true;

			//NOMBRE DEL PRODUCTO
			char pantequillalla[50];
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_PRODUCTOAPR, WM_GETTEXT, 50, (LPARAM)pantequillalla);
			for (int i = 0; pantequillalla[i]; i++) {          // Aqui se esta acomodando de minusculas a  mayusculas usando la 
				pantequillalla[i] = toupper(pantequillalla[i]);   // funcion toupper
				banderoso = true;
			}
			strcpy_s(nuevoPR->producto, pantequillalla);

			//NOMBRE DE LA PROMOCION
			char pantequilla[50];
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_EDIT_NOMBREAPR, WM_GETTEXT, 50, (LPARAM)pantequilla);
			for (int i = 0; pantequilla[i]; i++) {          // Aqui se esta acomodando de minusculas a  mayusculas usando la 
				pantequilla[i] = toupper(pantequilla[i]);   // funcion toupper
				banderoso = true;
			}
			strcpy_s(nuevoPR->nombrepromocion, pantequilla);

			//PORCENTAJE DE LA PROMOCION DEL PRODUCTO
			char pantequilloso[50];
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_DESCUENTOAPR, WM_GETTEXT, 50, (LPARAM)pantequilloso);
			temporal = atoi(pantequilloso); // Se modifican los valores char a int
			if (!temporal)
			{
				banderoso = false;
			}
			else {
				nuevoPR->porcentajepromocion = temporal;
			};

			//DESCRIPCION DE LA PROMOCION
			char pantequico[MAX_PATH];
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_EDIT_NOMBREAPR, WM_GETTEXT, MAX_PATH, (LPARAM)pantequico);
			for (int i = 0; pantequico[i]; i++) {          // Aqui se esta acomodando de minusculas a  mayusculas usando la 
				pantequico[i] = toupper(pantequico[i]);   // funcion toupper
				banderoso = true;
			}
			strcpy_s(nuevoPR->descripcion, pantequico);

			//FECHA INICIO DE LA PROMOCION
			panto = SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_01, CB_GETCURSEL, 0, 0);
			panta = SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_01, CB_GETCURSEL, 0, 0);
			pantato = SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAAAAAAPR_01, CB_GETCURSEL, 0, 0);

			if (panto != -1 && panta != -1 && pantato != -1) {
				char pantedia[MAX_PATH];
				char pantemes[MAX_PATH];
				char panteaño[MAX_PATH];

				SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_01, WM_GETTEXT, MAX_PATH, (LPARAM)pantedia);
				SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_01, WM_GETTEXT, MAX_PATH, (LPARAM)pantemes);
				SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAAAAAAPR_01, WM_GETTEXT, MAX_PATH, (LPARAM)panteaño);


				if (strcmp(pantemes, "02") == 0 && strcmp(pantedia, "31") == 0 || strcmp(pantedia, "30") == 0 || strcmp(pantedia, "29") == 0) {
					strcpy_s(pantedia, "28");
				}

				if (strcmp(pantemes, "04") == 0 && strcmp(pantedia, "31") == 0) {
					strcpy_s(pantedia, "30");
				}

				if (strcmp(pantemes, "06") == 0 && strcmp(pantedia, "31") == 0) {
					strcpy_s(pantedia, "30");
				}

				if (strcmp(pantemes, "09") == 0 && strcmp(pantedia, "31") == 0) {
					strcpy_s(pantedia, "30");
				}

				if (strcmp(pantemes, "11") == 0 && strcmp(pantedia, "31") == 0) {
					strcpy_s(pantedia, "30");
				}

				string dia = string(pantedia);
				string mes = string(pantemes);
				string año = string(panteaño);

				string panfecha = dia + "/" + mes + "/" + año;
				const char* panfechainicio = panfecha.c_str();
				strcpy_s(nuevoPR->fechainicio, panfechainicio);
			}
			else(banderoso = false);

			//FECHA FINAL DE LA PROMOCION
			char pantedia02[MAX_PATH];
			char pantemes02[MAX_PATH];
			char panteaño02[MAX_PATH];

			panto = SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_2, CB_GETCURSEL, 0, 0);
			panta = SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_2, CB_GETCURSEL, 0, 0);
			pantato = SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAAAAAAPR_2, CB_GETCURSEL, 0, 0);

			if (panto != -1 && panta != -1 && pantato != -1) {
				SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHADDAPR_2, WM_GETTEXT, MAX_PATH, (LPARAM)pantedia02);
				SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAMMAPR_2, WM_GETTEXT, MAX_PATH, (LPARAM)pantemes02);
				SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_FECHAAAAAAPR_2, WM_GETTEXT, MAX_PATH, (LPARAM)panteaño02);

				if (strcmp(pantemes02, "02") == 0 && strcmp(pantedia02, "31") == 0 || strcmp(pantedia02, "30") == 0 || strcmp(pantedia02, "29") == 0) {
					strcpy_s(pantedia02, "28");
				}

				if (strcmp(pantemes02, "04") == 0 && strcmp(pantedia02, "31") == 0) {
					strcpy_s(pantedia02, "30");
				}

				if (strcmp(pantemes02, "06") == 0 && strcmp(pantedia02, "31") == 0) {
					strcpy_s(pantedia02, "30");
				}

				if (strcmp(pantemes02, "09") == 0 && strcmp(pantedia02, "31") == 0) {
					strcpy_s(pantedia02, "30");
				}

				if (strcmp(pantemes02, "11") == 0 && strcmp(pantedia02, "31") == 0) {
					strcpy_s(pantedia02, "30");
				}



				string dia02 = string(pantedia02);
				string mes02 = string(pantemes02);
				string año02 = string(panteaño02);

				string panfecha02 = dia02 + "/" + mes02 + "/" + año02;
				const char* panfechafinal02 = panfecha02.c_str();
				strcpy_s(nuevoPR->fechafinal, panfechafinal02);
			}
			else(banderoso = false);

			//HORA INICIO DE LA PROMOCION
			char pantehora[MAX_PATH];
			char panteminuto[MAX_PATH];
			char pantesegundo[MAX_PATH];



			panto = SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR01, CB_GETCURSEL, 0, 0);
			panta = SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR01, CB_GETCURSEL, 0, 0);
			pantato = SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR01, CB_GETCURSEL, 0, 0);

			if (panto != -1 && panta != -1 && pantato != -1) {
				SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR01, WM_GETTEXT, MAX_PATH, (LPARAM)pantehora);
				SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR01, WM_GETTEXT, MAX_PATH, (LPARAM)panteminuto);
				SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR01, WM_GETTEXT, MAX_PATH, (LPARAM)pantesegundo);

				int pantehoraint;
				int horapm;
				char ampmjumm[MAX_PATH];
				SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_AMPM01, WM_GETTEXT, MAX_PATH, (LPARAM)ampmjumm);
				if (strcmp(ampmjumm, "PM") == 0) {
					pantehoraint = atoi(pantehora);

					horapm = (12 - pantehoraint);
					horapm = (24 - horapm);
					itoa(horapm, pantehora, 10);
				}



				string hora = string(pantehora);
				string minuto = string(panteminuto);
				string segundo = string(pantesegundo);

				string panhora = hora + ":" + minuto + ":" + segundo;
				const char* panhorainicio = panhora.c_str();
				strcpy_s(nuevoPR->horainicio, panhorainicio);
			}
			else(banderoso = false);

			//HORA FINAL DE LA PROMOCION
			char pantehora02[MAX_PATH];
			char panteminuto02[MAX_PATH];
			char pantesegundo02[MAX_PATH];

			panto = SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR2, CB_GETCURSEL, 0, 0);
			panta = SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR2, CB_GETCURSEL, 0, 0);
			pantato = SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR01, CB_GETCURSEL, 0, 0);

			if (panto != -1 && panta != -1 && pantato != -1) {
				SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAHHAPR2, WM_GETTEXT, MAX_PATH, (LPARAM)pantehora02);
				SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORAMMAPR2, WM_GETTEXT, MAX_PATH, (LPARAM)panteminuto02);
				SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_HORASSAPR2, WM_GETTEXT, MAX_PATH, (LPARAM)pantesegundo02);



				int pantehoraint;
				int horapm;
				char ampmjumm[MAX_PATH];
				SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_AMPM2, WM_GETTEXT, MAX_PATH, (LPARAM)ampmjumm);
				if (strcmp(ampmjumm, "PM") == 0) {
					pantehoraint = atoi(pantehora);

					horapm = (12 - pantehoraint);
					horapm = (24 - horapm);
					itoa(horapm, pantehora02, 10);
				}



				string hora02 = string(pantehora02);
				string minuto02 = string(panteminuto02);
				string segundo02 = string(pantesegundo02);

				string panhora02 = hora02 + ":" + minuto02 + ":" + segundo02;
				const char* panhorafinal02 = panhora02.c_str();
				strcpy_s(nuevoPR->horafinal, panhorafinal02);
			}
			else(banderoso = false);



			// AM Y PM
			char pantiAMPM01[MAX_PATH];
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_AMPM01, WM_GETTEXT, MAX_PATH, (LPARAM)pantiAMPM01);
			strcpy_s(nuevoPR->AMPM01, pantiAMPM01);

			char pantiAMPM02[MAX_PATH];
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_AMPM2, WM_GETTEXT, MAX_PATH, (LPARAM)pantiAMPM02);
			strcpy_s(nuevoPR->AMPM02, pantiAMPM02);

			//SONIDO
			char pantisonido01[MAX_PATH];
			SendDlgItemMessage(AgregadochoPromosiocho, IDC_COMBO_SONIDOALARMA, WM_GETTEXT, MAX_PATH, (LPARAM)pantisonido01);
			strcpy_s(nuevoPR->alarma, pantisonido01);


			if (banderoso == true) {
				if (inicioPR == NULL) {
					inicioPR = nuevoPR;
				}
				else {
					auxPR = inicioPR;
					while (auxPR->sig != NULL) {
						auxPR = auxPR->sig;
					}
					auxPR->sig = nuevoPR;
					nuevoPR->ant = auxPR;
				}


				auxP = inicioP;

				while (auxP != NULL)
				{
					if (strcmp(auxP->nombre, pantequillalla) == 0 && strcmp(auxP->usuario, usuariosoqueiniciosesion) == 0 && auxP->promocion == false) {
						auxP->promocion = true;
						break;
					}

					auxP = auxP->sig;
				}

				mciSendString("stop MP3", NULL, 0, 0);
				mciSendString("close MP3", NULL, 0, 0);
				MessageBox(AgregadochoPromosiocho, "Registro De Promoción Exitoso", "¡PERFECTO!", MB_OK);
				EndDialog(AgregadochoPromosiocho, 0);

			}
			else {
				MessageBox(0, "Error con los datos ingresados. Favor de ingresar o corregir los datos.", "ERROR", MB_ICONERROR | MB_OK);
			}

			return true; }
							return true;
		case ID_CANCELARAPP:
			EndDialog(AgregadochoPromosiocho, 0);
			return true;
		}
		return true;
	case WM_CLOSE:
		mciSendString("stop MP3", NULL, 0, 0);
		mciSendString("close MP3", NULL, 0, 0);
		EndDialog(AgregadochoPromosiocho, 0);
		return true;
	case WM_DESTROY:
		mciSendString("stop MP3", NULL, 0, 0);
		mciSendString("close MP3", NULL, 0, 0);
		EndDialog(AgregadochoPromosiocho, 0);
		return true;
	}
	return false;

}

BOOL CALLBACK PromocionosoExistententoso(HWND Alarmocho, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg)
	{
	case WM_INITDIALOG: {


		arreglosopromocioso* auxlioshoPR = inicioPR;
		arreglosoproductoso* auxlioshoP = inicioP;
		bool banderraproducto = false;
		bool informacionlista = false;

		if (inicioPR != NULL) {

		
				while (auxlioshoPR != NULL) {
					
					if (strcmp(auxlioshoPR->nombrepromocion, nombredemipromocionvalida) == 0) {

						while (auxlioshoP != NULL) {

							if (strcmp(auxlioshoPR->producto, auxlioshoP->nombre) == 0) {
								char mp3[MAX_PATH];
								strcpy(alarma, auxlioshoPR->alarma);
								strcpy(mp3, alarma);

								sprintf_s(comando, "open \"%s\" alias MP3", mp3);
								mciSendString(comando, NULL, 0, 0);
								mciSendString("play MP3", NULL, 0, 0);

								SendDlgItemMessage(Alarmocho, IDC_EDIT_NOMBREDELPRODUCTO, WM_SETTEXT, MAX_PATH, (LPARAM)auxlioshoPR->producto);
								SendDlgItemMessage(Alarmocho, IDC_EDIT_NOMBREDELAPROMOCION, WM_SETTEXT, MAX_PATH, (LPARAM)auxlioshoPR->nombrepromocion);
								SendDlgItemMessage(Alarmocho, IDC_EDIT_DESCRIPCION, WM_SETTEXT, MAX_PATH, (LPARAM)auxlioshoPR->descripcion);
								SendDlgItemMessage(Alarmocho, IDC_EDIT_FECHAFINAL, WM_SETTEXT, MAX_PATH, (LPARAM)auxlioshoPR->fechafinal);
								SendDlgItemMessage(Alarmocho, IDC_EDIT_HORAFINAL, WM_SETTEXT, MAX_PATH, (LPARAM)auxlioshoPR->horafinal);


								BMP01 = (HBITMAP)LoadImage(NULL, auxlioshoP->foto01, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
								SendDlgItemMessage(Alarmocho, IDC_PICTURE01, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP01);


								BMP02 = (HBITMAP)LoadImage(NULL, auxlioshoP->foto02, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
								SendDlgItemMessage(Alarmocho, IDC_PICTURE02, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BMP02);




								float porcentaje;
								float precioinicial;
								float preciofinal;

								char pantequimia[MAX_PATH];
								char pantequimiosho[MAX_PATH];
								char pantequiqui[MAX_PATH];
								char temporal[MAX_PATH];

								itoa(auxlioshoPR->porcentajepromocion, temporal, 10);
								SendDlgItemMessage(Alarmocho, IDC_EDIT_DESCUENTOC, WM_SETTEXT, MAX_PATH, (LPARAM)temporal);
								SendDlgItemMessage(Alarmocho, IDC_EDIT_DESCUENTOC, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimia);
								porcentaje = atoi(pantequimia); // Se modifican los valores char a int

								itoa(auxlioshoP->precio, temporal, 10);
								SendDlgItemMessage(Alarmocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONC, WM_SETTEXT, MAX_PATH, (LPARAM)temporal);
								SendDlgItemMessage(Alarmocho, IDC_EDIT_PRECIOINICIALCONPROMOCIONC, WM_GETTEXT, MAX_PATH, (LPARAM)pantequimiosho);
								precioinicial = atoi(pantequimiosho); // Se modifican los valores char a int

								preciofinal = ((precioinicial*porcentaje) / 100);
								preciofinal = (precioinicial - preciofinal);

								itoa(preciofinal, pantequiqui, 10);
								SendDlgItemMessage(Alarmocho, IDC_EDIT_PRECIOFINALCONPROMOCIONC, WM_SETTEXT, MAX_PATH, (LPARAM)pantequiqui);

								auxlioshoPR->diapromocion = diadehoy;

								informacionlista = true;
								break;
							}
							auxlioshoP = auxlioshoP->sig;
						}

					
				}

				if (informacionlista == true) {
					break;
				}
		
				auxlioshoPR = auxlioshoPR->sig;
			}

		}



		return true; }
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_ACEPTARPE:
			mciSendString("stop MP3", NULL, 0, 0);
			mciSendString("close MP3", NULL, 0, 0);
			revivirtimer = true;
			EndDialog(Alarmocho, 0);
			return true;
		}
		return true;
	case WM_CLOSE:
		mciSendString("stop MP3", NULL, 0, 0);
		mciSendString("close MP3", NULL, 0, 0);
		revivirtimer = true;
		EndDialog(Alarmocho, 0);
		return true;
	case WM_DESTROY:
		EndDialog(Alarmocho, 0);
		return true;
	}
	return false;

}