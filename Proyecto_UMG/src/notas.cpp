//Creado por Diana Mishel Loeiza Ramírez 9959-23-3457 //proceso notas// 
#include "notas.h" // Incluye el archivo de encabezado "notas.h"
#include <fstream> // Incluye la biblioteca para manejar archivos  
#include <iostream> // Incluye la biblioteca estándar de entrada y salida
#include <cstdlib> // Incluye la biblioteca estándar de C para funciones de sistema
#include <conio.h> // Incluye la biblioteca para funciones de entrada y salida del sistema en Windows

using namespace std; // Usa el espacio de nombres estándar de C++

// Definición de la clase Nota  //
class Nota { 
public:
    int codigoEstudiante; // Variable para almacenar el código del estudiante
    string nombreEstudiante; // Variable para almacenar el nombre del estudiante
    string nombreCurso; // Variable para almacenar el nombre del curso
    float nota; // Variable para almacenar la nota del estudiante
};      

// Definición de la función miembro de la clase NotaCrud
void NotaCrud::CrudNota() {
    int opcion; // Variable para almacenar la opción seleccionada por el usuario

    do {
        system("cls"); // Limpia la pantalla de la consola
        // Muestra el menú principal del sistema de gestión de notas
        cout << "\t\t\t--------------------------------------------" << endl;
        cout << "\t\t\t|     SISTEMA DE GESTION UMG - Notas       |" << endl;
        cout << "\t\t\t--------------------------------------------" << endl;
        cout << "\t\t\t 1. Ingresar Nota" << endl;
        cout << "\t\t\t 2. Modificar Nota" << endl;
        cout << "\t\t\t 3. Borrar Nota" << endl;
        cout << "\t\t\t 4. Desplegar Notas" << endl;
        cout << "\t\t\t 5. Regresar al Menú Anterior" << endl;
        cout << "\t\t\t --------------------------------------------" << endl;
        cout << "\t\t\t |   Opción a escoger:[1|2|3|4|5|]           |" << endl;
        cout << "\t\t\t --------------------------------------------" << endl;
        cout << "\t\t\tIngrese tu Opción: ";
        cin >> opcion; // Lee la opción seleccionada por el usuario

        // Ejecuta la opción seleccionada por el usuario
        switch (opcion) {
            case 1:
                IngresarNota(); // Llama a la función para ingresar una nueva nota
                break;
            case 2:
                ModificarNota(); // Llama a la función para modificar una nota existente
                break;
            case 3:
                BorrarNota(); // Llama a la función para borrar una nota existente
                break;
            case 4:
                DesplegarNotas(); // Llama a la función para desplegar todas las notas
                break;
            case 5:
                break; // Sale del bucle do-while si se selecciona la opción 5
            default:
                cout << "\n\t\t\tOpción inválida. Por favor, prueba otra vez." << endl;
                cin.ignore();
                cin.get();
        }
    } while (opcion != 5); // Continúa el bucle hasta que se seleccione la opción 5
}

// Definición de la función miembro de la clase NotaCrud para ingresar una nueva nota
void NotaCrud::IngresarNota() {
    system("cls"); // Limpia la pantalla de la consola
    cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n-------------------------------------------------Agregar Nota--------------------------------------------" << endl;
    Nota nota; // Crea un objeto de la clase Nota para almacenar la nueva nota
    // Solicita al usuario ingresar los datos de la nueva nota
    cout << "Ingrese el código del estudiante: ";
    cin >> nota.codigoEstudiante;
    cin.ignore();

    cout << "Ingrese el nombre del estudiante: ";
    getline(cin, nota.nombreEstudiante);

    cout << "Ingrese el nombre del curso: ";
    getline(cin, nota.nombreCurso);

    cout << "Ingrese la nota: ";
    cin >> nota.nota;

    // Abre el archivo de notas en modo binario y de adjuntar
    ofstream archivo("notas.dat", ios::binary | ios::app);
    // Escribe la nueva nota en el archivo
    archivo.write(reinterpret_cast<const char*>(&nota), sizeof(Nota));
    archivo.close(); // Cierra el archivo

    cout << "Nota agregada exitosamente!" << endl; // Muestra un mensaje de éxito
}

// Definición de la función miembro de la clase NotaCrud para modificar una nota existente
void NotaCrud::ModificarNota() {
    int codigo; // Variable para almacenar el código del estudiante cuya nota se modificará
    cout << "Ingrese el código del estudiante cuya nota desea modificar: ";
    cin >> codigo; // Lee el código del estudiante ingresado por el usuario

    // Abre el archivo de notas en modo binario y de lectura y escritura
    fstream archivo("notas.dat", ios::binary | ios::in | ios::out);
    // Verifica si el archivo se abrió correctamente
    if (!archivo) {
        cout << "No hay notas registradas." << endl; // Muestra un mensaje si no hay notas registradas
        return;
    }

    Nota nota; // Variable para almacenar la nota leída del archivo
    bool encontrada = false; // Bandera para indicar si se encontró la nota a modificar
    // Lee todas las notas del archivo
    while (archivo.read(reinterpret_cast<char*>(&nota), sizeof(Nota))) {
        // Si se encuentra la nota con el código ingresado por el usuario
        if (nota.codigoEstudiante == codigo) {
            cout << "Ingrese la nueva nota para el estudiante: ";
            cin >> nota.nota; // Solicita al usuario ingresar la nueva nota

            archivo.seekp(-static_cast<int>(sizeof(Nota)), ios::cur); // Mueve el puntero de escritura al inicio de la nota
            archivo.write(reinterpret_cast<const char*>(&nota), sizeof(Nota)); // Escribe la nueva nota en el archivo

            encontrada = true; // Establece la bandera como verdadera
            break; // Sale del bucle
        }
    }

    archivo.close(); // Cierra el archivo

    // Muestra un mensaje dependiendo del resultado de la operación
    if (!encontrada) {
        cout << "No se encontró la nota del estudiante con el código ingresado." << endl;
    } else {
        cout << "Nota modificada exitosamente!" << endl;
    }
}

// Definición de la función miembro de la clase NotaCrud para borrar una nota existente
void NotaCrud::BorrarNota() {
    int codigo; // Variable para almacenar el código del estudiante cuya nota se eliminará
    cout << "Ingrese el código del estudiante cuya nota desea eliminar: ";
    cin >> codigo; // Lee el código del estudiante ingresado por el usuario

    // Abre el archivo de notas en modo binario y de lectura
    ifstream archivo("notas.dat", ios::binary);
    // Verifica si el archivo se abrió correctamente
    if (!archivo) {
        cout << "No hay notas registradas." << endl; // Muestra un mensaje si no hay notas registradas
        return;
    }

    // Abre un nuevo archivo temporal para escribir las notas excepto la que se desea eliminar
    ofstream archivoTmp("notas_tmp.dat", ios::binary);
    Nota nota; // Variable para almacenar la nota leída del archivo
    bool eliminada = false; // Bandera para indicar si se eliminó la nota
    // Lee todas las notas del archivo
    while (archivo.read(reinterpret_cast<char*>(&nota), sizeof(Nota))) {
        // Si el código del estudiante no coincide con el código ingresado por el usuario
        if (nota.codigoEstudiante != codigo) {
            archivoTmp.write(reinterpret_cast<const char*>(&nota), sizeof(Nota)); // Escribe la nota en el archivo temporal
        } else {
            eliminada = true; // Establece la bandera como verdadera
        }
    }

    archivo.close(); // Cierra el archivo original
    archivoTmp.close(); // Cierra el archivo temporal

    remove("notas.dat"); // Elimina el archivo original
    rename("notas_tmp.dat", "notas.dat"); // Renombra el archivo temporal como el archivo original

    // Muestra un mensaje dependiendo del resultado de la operación
    if (eliminada) {
        cout << "Nota eliminada exitosamente!" << endl;
    } else {
        cout << "No se encontró la nota del estudiante con el código ingresado." << endl;
    }
}

// Definición de la función miembro de la clase NotaCrud para desplegar todas las notas
void NotaCrud::DesplegarNotas() {
    system("cls"); // Limpia la pantalla de la consola
    cout << "-----------------Despliegue de notas registradas---------------------" << endl;
    // Abre el archivo de notas en modo binario y de lectura
    ifstream archivo("notas.dat", ios::binary);
    // Verifica si el archivo se abrió correctamente
    if (!archivo) {
        cout << "No hay notas registradas." << endl; // Muestra un mensaje si no hay notas registradas
        return;
    }

    Nota nota; // Variable para almacenar la nota leída del archivo
    // Lee todas las notas del archivo y las muestra en la consola
    while (archivo.read(reinterpret_cast<char*>(&nota), sizeof(Nota))) {
        cout << "Código del estudiante: " << nota.codigoEstudiante << endl;
        cout << "Nombre del estudiante: " << nota.nombreEstudiante << endl;
        cout << "Nombre del curso: " << nota.nombreCurso << endl;
        cout << "Nota: " << nota.nota << endl;
        cout << "-----------------------------" << endl;
    }

    archivo.close(); // Cierra el archivo

    cout << "Presione Enter para continuar..."; // Solicita al usuario presionar Enter para continuar
    cin.ignore(); // Ignora cualquier carácter en el búfer de entrada
    cin.get(); // Espera a que el usuario presione Enter
}

