//Creado por Diana Mishel Loeiza Ram�rez 9959-23-3457//proceso nota//
#include "notas.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <conio.h>

using namespace std;

class Nota {
public:
    int codigoEstudiante;
    string nombreEstudiante;
    string nombreCurso;
    float nota;
};

void NotaCrud::CrudNota() {
    int opcion;

    do {
        system("cls");
        cout << "\t\t\t--------------------------------------------" << endl;
        cout << "\t\t\t|     SISTEMA DE GESTION UMG - Notas       |" << endl;
        cout << "\t\t\t--------------------------------------------" << endl;
        cout << "\t\t\t 1. Ingresar Nota" << endl;
        cout << "\t\t\t 2. Modificar Nota" << endl;
        cout << "\t\t\t 3. Borrar Nota" << endl;
        cout << "\t\t\t 4. Desplegar Notas" << endl;
        cout << "\t\t\t 5. Regresar al Men� Anterior" << endl;
        cout << "\t\t\t --------------------------------------------" << endl;
        cout << "\t\t\t |   Opci�n a escoger:[1|2|3|4|5|]           |" << endl;
        cout << "\t\t\t --------------------------------------------" << endl;
        cout << "\t\t\tIngrese tu Opci�n: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                IngresarNota();
                break;
            case 2:
                ModificarNota();
                break;
            case 3:
                BorrarNota();
                break;
            case 4:
                DesplegarNotas();
                break;
            case 5:
                break;
            default:
                cout << "\n\t\t\tOpci�n inv�lida. Por favor, prueba otra vez." << endl;
                cin.ignore();
                cin.get();
        }
    } while (opcion != 5);
}

void NotaCrud::IngresarNota() {
    system("cls");
    cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n-------------------------------------------------Agregar Nota--------------------------------------------" << endl;
    Nota nota;
    cout << "Ingrese el c�digo del estudiante: ";
    cin >> nota.codigoEstudiante;
    cin.ignore();

    cout << "Ingrese el nombre del estudiante: ";
    getline(cin, nota.nombreEstudiante);

    cout << "Ingrese el nombre del curso: ";
    getline(cin, nota.nombreCurso);

    cout << "Ingrese la nota: ";
    cin >> nota.nota;

    ofstream archivo("notas.dat", ios::binary | ios::app);
    archivo.write(reinterpret_cast<const char*>(&nota), sizeof(Nota));
    archivo.close();

    cout << "Nota agregada exitosamente!" << endl;
}

void NotaCrud::ModificarNota() {
    int codigo;
    cout << "Ingrese el c�digo del estudiante cuya nota desea modificar: ";
    cin >> codigo;

    fstream archivo("notas.dat", ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "No hay notas registradas." << endl;
        return;
    }

    Nota nota;
    bool encontrada = false;
    while (archivo.read(reinterpret_cast<char*>(&nota), sizeof(Nota))) {
        if (nota.codigoEstudiante == codigo) {
            cout << "Ingrese la nueva nota para el estudiante: ";
            cin >> nota.nota;

            archivo.seekp(-static_cast<int>(sizeof(Nota)), ios::cur);
            archivo.write(reinterpret_cast<const char*>(&nota), sizeof(Nota));

            encontrada = true;
            break;
        }
    }

    archivo.close();

    if (!encontrada) {
        cout << "No se encontr� la nota del estudiante con el c�digo ingresado." << endl;
    } else {
        cout << "Nota modificada exitosamente!" << endl;
    }
}

void NotaCrud::BorrarNota() {
    int codigo;
    cout << "Ingrese el c�digo del estudiante cuya nota desea eliminar: ";
    cin >> codigo;

    ifstream archivo("notas.dat", ios::binary);
    if (!archivo) {
        cout << "No hay notas registradas." << endl;
        return;
    }

    ofstream archivoTmp("notas_tmp.dat", ios::binary);
    Nota nota;
    bool eliminada = false;
    while (archivo.read(reinterpret_cast<char*>(&nota), sizeof(Nota))) {
        if (nota.codigoEstudiante != codigo) {
            archivoTmp.write(reinterpret_cast<const char*>(&nota), sizeof(Nota));
        } else {
            eliminada = true;
        }
    }

    archivo.close();
    archivoTmp.close();

    remove("notas.dat");
    rename("notas_tmp.dat", "notas.dat");

    if (eliminada) {
        cout << "Nota eliminada exitosamente!" << endl;
    } else {
        cout << "No se encontr� la nota del estudiante con el c�digo ingresado." << endl;
    }
}

void NotaCrud::DesplegarNotas() {
    system("cls");
    cout << "-----------------Despliegue de notas registradas---------------------" << endl;
    ifstream archivo("notas.dat", ios::binary);
    if (!archivo) {
        cout << "No hay notas registradas." << endl;
        return;
    }

    Nota nota;
    while (archivo.read(reinterpret_cast<char*>(&nota), sizeof(Nota))) {
        cout << "C�digo del estudiante: " << nota.codigoEstudiante << endl;
        cout << "Nombre del estudiante: " << nota.nombreEstudiante << endl;
        cout << "Nombre del curso: " << nota.nombreCurso << endl;
        cout << "Nota: " << nota.nota << endl;
        cout << "-----------------------------" << endl;
    }

    archivo.close();

    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}
