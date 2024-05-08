// Incluyendo las bibliotecas necesarias
#include "aulas.h"
#include <fstream> // Para operaciones de archivo
#include <iostream>
#include <cstdlib> // Para el uso de system("cls") y funciones de C
#include <iomanip> // Para manipulación de la salida
using namespace std;

// Definición de la clase y sus métodos
void AulasCRUD::CrudAula() {
    int opcion;
    do {
        system("cls"); // Limpia la pantalla
        // Menú de opciones
        cout << "\t\t\t--------------------------------------------" << endl;
        cout << "\t\t\t|     SISTEMA DE GESTION UMG - Aulas       |" << endl;
        cout << "\t\t\t--------------------------------------------" << endl;
        cout << "\t\t\t 1. Ingresar Aula" << endl;
        cout << "\t\t\t 2. Modificar Aula" << endl;
        cout << "\t\t\t 3. Borrar Aula" << endl;
        cout << "\t\t\t 4. Desplegar Aula" << endl;
        cout << "\t\t\t 5. Regresar Menu Anterior" << endl;
        cout << "\t\t\t --------------------------------------------" << endl;
        cout << "\t\t\t |   Opcion a escoger:[1|2|3|4|5|]           |" << endl;
        cout << "\t\t\t --------------------------------------------" << endl;
        cout << "\t\t\tIngresa tu Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                IngresarAula();
                break;
            case 2:
                ModificarAula();
                break;
            case 3:
                BorrarAula();
                break;
            case 4:
                DesplegarAula();
                break;
            case 5:
                break;
            default:
                cout << "\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
                cin.get();
        }
    } while (opcion != 5);
}

// Método para ingresar un aula
void AulasCRUD::IngresarAula() {
    system("cls");
    cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n-------------------------------------------------Agregar Aula--------------------------------------------" << endl;
    aulas aula;
    cout << "Ingrese el codigo del aula: ";
    cin >> aula.codigo;
    cin.ignore();

    cout << "Ingrese el nombre del aula: ";
    cin.getline(aula.nombre, 50);

    cout << "Ingrese la estatus de la aula: ";
    cin.getline(aula.estatus, 50);

    // Abre el archivo para escritura binaria en modo de agregar al final
    ofstream archivo("aulas.dat", ios::binary | ios::app);
    // Escribe la estructura 'aula' en el archivo
    archivo.write(reinterpret_cast<const char*>(&aula), sizeof(aulas));
    archivo.close(); // Cierra el archivo

    cout << "aula agregada exitosamente!" << endl;
}

// Método para modificar un aula
void AulasCRUD::ModificarAula() {
    int codigo;
    cout << "Ingrese el codigo de la aula a modificar: ";
    cin >> codigo;

    // Abre el archivo para lectura/escritura binaria
    fstream archivo("aulas.dat", ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "No hay aulas registradas." << endl;
        return;
    }

    aulas aula;
    bool encontrada = false;
    while (archivo.read(reinterpret_cast<char*>(&aula), sizeof(aulas))) {
        if (aula.codigo == codigo) {
            cout << "Ingrese el nuevo nombre de la aula: ";
            cin.ignore();
            cin.getline(aula.nombre, 50);

            cout << "Ingrese el nuevo estatus de la aula: ";
            cin.getline(aula.estatus, 50);

            archivo.seekp(-static_cast<int>(sizeof(aulas)), ios::cur);
            archivo.write(reinterpret_cast<const char*>(&aula), sizeof(aulas));

            encontrada = true;
            break;
        }
    }

    archivo.close();

    if (!encontrada) {
        cout << "No se encontró la aula con el codigo ingresado." << endl;
    } else {
        cout << "aula modificada exitosamente!" << endl;
    }
}

// Método para eliminar un aula
void AulasCRUD::BorrarAula() {
    int codigo;
    cout << "Ingrese el codigo de la aula a eliminar: ";
    cin >> codigo;

    // Abre el archivo para lectura binaria
    ifstream archivo("aulas.dat", ios::binary);
    if (!archivo) {
        cout << "No hay aulas registradas." << endl;
        return;
    }

    // Abre un archivo temporal para escritura binaria
    ofstream archivoTmp("aulas_tmp.dat", ios::binary);
    aulas aula;
    bool eliminada = false;
    while (archivo.read(reinterpret_cast<char*>(&aula), sizeof(aulas))) {
        if (aula.codigo != codigo) {
            archivoTmp.write(reinterpret_cast<const char*>(&aula), sizeof(aulas));
        } else {
            eliminada = true;
        }
    }

    archivo.close(); // Cierra el archivo original
    archivoTmp.close(); // Cierra el archivo temporal

    remove("aulas.dat"); // Elimina el archivo original
    rename("aulas_tmp.dat", "aulas.dat"); // Renombra el archivo temporal al original

    if (eliminada) {
        cout << "aula eliminada exitosamente!" << endl;
    } else {
        cout << "No se encontró la aula con el codigo ingresado." << endl;
    }
}

// Método para desplegar todas las aulas
void AulasCRUD::DesplegarAula() {
    system("cls");
    cout << "-----------------Despliegue de aulas registradas---------------------" << endl;
    // Abre el archivo para lectura binaria
    ifstream archivo("aulas.dat", ios::binary);
    if (!archivo) {
        cout << "No hay aulas registradas." << endl;
        return;
    }

    aulas aula;
    // Lee cada aula del archivo e imprime sus datos
    while (archivo.read(reinterpret_cast<char*>(&aula), sizeof(aulas))) {
        cout << "Codigo: " << aula.codigo << endl;
        cout << "Nombre: " << aula.nombre << endl;
        cout << "Estatus: " << aula.estatus << endl;
        cout << "-----------------------------" << endl;
    }

    archivo.close(); // Cierra el archivo

    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}



