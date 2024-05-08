//Creado por Rocio Guisell Lopez espinoza 9959-23-740
#include "secciones.h"

#include <fstream>
#include <iostream>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<iomanip>

using namespace std;
// Definición de la función CrudSeccion de la clase SeccionesCrud
void SeccionesCrud::CrudSeccion()
{
    // Declaración de la variable 'opcion' que almacenará la opción del usuario
    int opcion;

    // Bucle do-while que se ejecutará hasta que el usuario elija la opción 5 (Regresar al menú anterior)
    do{

    // Limpia la consola
	system("cls");
	// Imprime el menú de opciones en la consola
	cout<<"\t\t\t--------------------------------------------"<<endl;
	cout<<"\t\t\t|     SISTEMA DE GESTION UMG - Secciones       |"<<endl;
	cout<<"\t\t\t--------------------------------------------"<<endl;
	cout<<"\t\t\t 1. Ingresar Seccion"<<endl;
	cout<<"\t\t\t 2. Modificar Seccion"<<endl;
	cout<<"\t\t\t 3. Borrar Seccion"<<endl;
	cout<<"\t\t\t 4. Desplegar Seccion"<<endl;
	cout<<"\t\t\t 5. Regresar Menu Anterior"<<endl;
    cout<<"\t\t\t --------------------------------------------"<<endl;
	cout<<"\t\t\t |   Opcion a escoger:[1|2|3|4|5|]           |"<<endl;
	cout<<"\t\t\t --------------------------------------------"<<endl;
	cout<<"\t\t\tIngresa tu Opcion: ";
    // Lee la opción del usuario desde la consola
    cin>>opcion;

    // Estructura switch que ejecuta una acción dependiendo de la opción elegida por el usuario
    switch (opcion)
    {
    case 1:
        // Si la opción es 1, llama a la función IngresarSeccion
        IngresarSeccion();
        break;
    case 2:
        // Si la opción es 2, llama a la función ModificarSeccion
        ModificarSeccion();
        break;
    case 3:
        // Si la opción es 3, llama a la función BorrarSeccion
        BorrarSeccion();
        break;
    case 4:
        // Si la opción es 4, llama a la función DesplegarSeccion
        DesplegarSeccion();
        break;
    case 5:
        // Si la opción es 5, sale del bucle
        break;
    default:
        // Si la opción no es ninguna de las anteriores, imprime un mensaje de error y espera una entrada del usuario
        cout<<"\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
		cin.get();
    }
    // El bucle se ejecuta mientras la opción no sea 5
    }while(opcion!= 5);
}

// Definición de la función IngresarSeccion de la clase SeccionesCrud
void SeccionesCrud::IngresarSeccion()
{
    // Limpia la consola
    system("cls");
    // Imprime el título de la sección en la consola
    cout<<"\n------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"\n-------------------------------------------------Agregar Seccion--------------------------------------------"<<endl;
    // Crea un objeto 'seccion' de la clase 'secciones'
    secciones seccion;
    // Solicita al usuario que ingrese el código de la sección
    cout << "Ingrese el codigo del Seccion: ";
    cin >> seccion.codigo;
    cin.ignore();

    // Solicita al usuario que ingrese el nombre de la sección
    cout << "Ingrese el nombre del Seccion: ";
    cin.getline(seccion.nombre, 50);

    // Solicita al usuario que ingrese el estatus de la sección
    cout << "Ingrese la estatus de la Seccion: ";
    cin.getline(seccion.estatus, 50);

    // Abre el archivo 'seccion.dat' en modo binario y de escritura al final del archivo
    ofstream archivo("seccion.dat", ios::binary | ios::app);
    // Escribe el objeto 'seccion' en el archivo
    archivo.write(reinterpret_cast<const char*>(&seccion), sizeof(secciones));
    // Cierra el archivo
    archivo.close();

    // Imprime un mensaje de éxito en la consola
    cout << "Seccion agregada exitosamente!" << endl;

}


// Definición de la función ModificarSeccion de la clase SeccionesCrud
void SeccionesCrud::ModificarSeccion()
{
    // Declaración de la variable 'codigo' que almacenará el código de la sección a modificar
    int codigo;
    // Solicita al usuario que ingrese el código de la sección a modificar
    cout << "Ingrese el codigo de la Seccion a modificar: ";
    cin >> codigo;

    // Abre el archivo 'seccion.dat' en modo binario para lectura y escritura
    fstream archivo("seccion.dat", ios::binary | ios::in | ios::out);
    // Si el archivo no se pudo abrir, imprime un mensaje de error y termina la función
    if (!archivo) {
        cout << "No hay Seccion registradas." << endl;
        return;
    }

    // Crea un objeto 'seccion' de la clase 'secciones'
    secciones seccion;
    // Declaración de la variable booleana 'encontrada' que indicará si se encontró la sección a modificar
    bool encontrada = false;
    // Mientras se pueda leer un objeto 'seccion' del archivo...
    while (archivo.read(reinterpret_cast<char*>(&seccion), sizeof(secciones))) {
        // Si el código de la sección leída es igual al código ingresado por el usuario...
        if (seccion.codigo == codigo) {
            // Solicita al usuario que ingrese el nuevo nombre de la sección
            cout << "Ingrese el nuevo nombre de la Seccion: ";
            cin.ignore();
            cin.getline(seccion.nombre, 50);

            // Solicita al usuario que ingrese el nuevo estatus de la sección
            cout << "Ingrese el nuevo estatus de la Seccion: ";
            cin.getline(seccion.estatus, 50);

            // Mueve el puntero de escritura del archivo a la posición de la sección a modificar
            archivo.seekp(-static_cast<int>(sizeof(seccion)), ios::cur);
            // Escribe el objeto 'seccion' modificado en el archivo
            archivo.write(reinterpret_cast<const char*>(&seccion), sizeof(secciones));

            // Cambia el valor de 'encontrada' a true
            encontrada = true;
            // Termina el bucle
            break;
        }
    }


    archivo.close();

     // Si 'encontrada' es false, es decir, si no se encontró la sección a modificar...
    if (!encontrada) {
        // Imprime un mensaje de error en la consola
        cout << "No se encontró la Seccion con el codigo ingresado." << endl;
    } else {
        // Si 'encontrada' es true, es decir, si se encontró y modificó la sección...
        // Imprime un mensaje de éxito en la consola
        cout << "Seccion modificada exitosamente!" << endl;
    }
}




void SeccionesCrud::BorrarSeccion()
{
    // Declaración de la variable 'codigo' que almacenará el código de la sección a eliminar
    int codigo;
    // Solicita al usuario que ingrese el código de la sección a eliminar
    cout << "Ingrese el codigo de la Seccion a eliminar: ";
    cin >> codigo;

    // Abre el archivo 'seccion.dat' en modo binario para lectura
    ifstream archivo("seccion.dat", ios::binary);
    // Si el archivo no se pudo abrir, imprime un mensaje de error y termina la función
    if (!archivo) {
        cout << "No hay seccion registradas." << endl;
    }



     // Crea un archivo temporal 'seccion_tmp.dat' en modo binario para escritura
    ofstream archivoTmp("seccion_tmp.dat", ios::binary);
    // Crea un objeto 'seccion' de la clase 'secciones'
    secciones seccion;
    // Declaración de la variable booleana 'eliminada' que indicará si se eliminó la sección
    bool eliminada = false;
    // Mientras se pueda leer un objeto 'seccion' del archivo...
    while (archivo.read(reinterpret_cast<char*>(&seccion), sizeof(secciones))) {
        // Si el código de la sección leída es diferente al código ingresado por el usuario...
        if (seccion.codigo != codigo) {
            // Escribe el objeto 'seccion' en el archivo temporal
            archivoTmp.write(reinterpret_cast<const char*>(&seccion), sizeof(secciones));
        } else {
            // Si el código de la sección leída es igual al código ingresado por el usuario, cambia el valor de 'eliminada' a true
            eliminada = true;
        }
    }

    // Cierra los archivos
    archivo.close();
    archivoTmp.close();
    // Aquí debería continuar el código para eliminar el archivo original y renombrar el archivo temporal



       // Elimina el archivo original 'seccion.dat'
    remove("seccion.dat");
    // Renombra el archivo temporal 'seccion_tmp.dat' a 'seccion.dat'
    rename("seccion_tmp.dat", "seccion.dat");

    // Si 'eliminada' es true, es decir, si se encontró y eliminó la sección...
    if (eliminada) {
        // Imprime un mensaje de éxito en la consola
        cout << "seccion eliminada exitosamente!" << endl;
    } else {
        // Si 'eliminada' es false, es decir, si no se encontró la sección a eliminar, imprime un mensaje de error en la consola
        cout << "No se encontró la seccion con el codigo ingresado." << endl;
    }


}
// Definición de la función DesplegarSeccion de la clase SeccionesCrud
void SeccionesCrud::DesplegarSeccion()
{
    // Limpia la consola
    system("cls");
    // Imprime el título de la sección en la consola
    cout<<"-----------------Despliegue de seccion registradas---------------------"<<endl;
    // Abre el archivo 'seccion.dat' en modo binario para lectura
    ifstream archivo("seccion.dat", ios::binary);
    // Si el archivo no se pudo abrir, imprime un mensaje de error y termina la función
    if (!archivo) {
        cout << "No hay seccion registradas." << endl;
        return;
    }

      // Crea un objeto 'seccion' de la clase 'secciones'
    secciones seccion;
    // Mientras se pueda leer un objeto 'seccion' del archivo...
    while (archivo.read(reinterpret_cast<char*>(&seccion), sizeof(secciones))) {
        // Imprime los datos de la sección en la consola
        cout << "Codigo: " << seccion.codigo << endl;
        cout << "Nombre: " << seccion.nombre << endl;
        cout << "Estatus: " << seccion.estatus << endl;
        cout << "-----------------------------" << endl;
    }

    // Cierra el archivo
    archivo.close();

    // Imprime un mensaje indicando al usuario que presione Enter para continuar
    cout << "Presione Enter para continuar...";
    // Ignora el siguiente carácter de entrada (generalmente el salto de línea después de la última entrada)
    cin.ignore();
    // Espera a que el usuario presione Enter
    cin.get();

}

