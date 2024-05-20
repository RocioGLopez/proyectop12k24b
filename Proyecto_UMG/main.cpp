
//Creado por Jose Gallardo 9959-23-106

#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "usuarios.h"
#include "Bitacora.h"
<<<<<<< HEAD

#include "alumnos.h"
#include "maestros.h"
=======
#include "alumnos.h"
#include "maestros.h"
#include "login.h"
#define MAX 80
>>>>>>> fe9d22d9aea18290301fb123b219a553b09aa5e8

using namespace std;

void menuGeneral();
void catalogos();
void reportes();
void procesos();
void ayuda();
void seguridad();
string codigoPrograma="1";
Bitacora Auditoria;
string user, contrasena;

<<<<<<< HEAD
int main()
{
        // Llamamos al objeto e ingresamos los parametros
    Login ingreso(user, contrasena);
=======
int main() {
    Login login;
    int intentos = 0;
    bool loginExitoso = false;
>>>>>>> fe9d22d9aea18290301fb123b219a553b09aa5e8

    do {
    int resultadoLogin = login.menuIniciarSesion();
    if (resultadoLogin == 1) {
    loginExitoso = true;
    break;
    } else {
    intentos++;
    cout << "Intento fallido. Intento " << intentos << " de 3." << endl;
    if (intentos >= 3) {
    cout << "Demasiados intentos fallidos. Saliendo del programa."<< endl;
    return 1; // Código de error
    }
    }
    } while (!loginExitoso);

    if (loginExitoso) {
    cout << "Inicio de sesión exitoso. Bienvenido al sistema."<< endl;
    menuGeneral();
    }

    return 0;
}
void menuGeneral()
{
    int choice;


    do
    {
        system("cls");
        cout << "\t\t\t-------------------------------" << endl;
        cout << "\t\t\t|   SISTEMA DE GESTION UMG     |"<< endl;
        cout << "\t\t\t-------------------------------" << endl;
        cout << "\t\t\t 1. Catalogos" << endl;
        cout << "\t\t\t 2. Procesos" << endl;
        cout << "\t\t\t 3. Reportes" << endl;
        cout << "\t\t\t 4. Seguridad" << endl;
        cout << "\t\t\t 5. Ayuda" << endl;
        cout << "\t\t\t 6. Salir del Sistema" << endl;
        cout << "\t\t\t-------------------------------" << endl;
        cout << "\t\t\t|Opcion a escoger:[1/2/3/4/5/6]  |" << endl;
        cout << "\t\t\t-------------------------------" << endl;
        cout << "\t\t\tIngresa tu Opcion: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            catalogos();
            break;
        case 2:
            procesos();
            break;
        case 3:
            reportes();
            break;
        case 4:
            seguridad();
            break;
        case 5:
            ayuda();
            break;
        case 6:
                    Auditoria.ingresoBitacora(user,codigoPrograma,"LGO"); //llamada para registrar la bitacora de seguridad
            exit(0);
        default:
            cout << "\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
            cin.ignore();
            cin.get();
        }
    } while (choice != 6);
}

void catalogos()
{
    int choice;

    do
    {
        system("cls");
        cout << "\t\t\t--------------------------------------------" << endl;
        cout << "\t\t\t|   SISTEMA DE GESTION UMG - CATALOGOS      |" << endl;
        cout << "\t\t\t--------------------------------------------" << endl;
        cout << "\t\t\t 1. Alumnos" << endl;
        cout << "\t\t\t 2. Maestros" << endl;
        cout << "\t\t\t 3. Usuarios del sistema" << endl;
        cout << "\t\t\t 4. Carreras" << endl;
        cout << "\t\t\t 5. Facultades" << endl;
        cout << "\t\t\t 6. Cursos" << endl;
        cout << "\t\t\t 7. Jornadas" << endl;
        cout << "\t\t\t 8. Aulas" << endl;
        cout << "\t\t\t 9. Secciones" << endl;
        cout << "\t\t\t 10. Sedes" << endl;
        cout << "\t\t\t 11. Horarios" << endl;
        cout << "\t\t\t 12. Retornar menu anterior" << endl;
        cout << "\t\t\t --------------------------------------------" << endl;
        cout << "\t\t\t | Opcion a escoger:[1-12]|" << endl;
        cout << "\t\t\t --------------------------------------------" << endl;
        cout << "\t\t\tIngresa tu Opcion: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            alumnos alumno;
            alumno.menu();
        }
            break;
        case 2:
        {
            maestros maestro;
            maestro.menu();
        }
            break;
        case 3:
        {
            Usuario UsuarioS;
            UsuarioS.menuInicial();
            break;
        }
        case 4:
            // Implementación para Carreras
            break;
        case 5:
            // Implementación para Facultades
            break;
        case 6:
            // Implementación para Cursos
            break;
        case 7:
            // Implementación para Jornadas
            break;
        case 8:
            // Implementación para Aulas
            break;
        case 9:
            // Implementación para Secciones
            break;
        case 10:
            // Implementación para Sedes
            break;
        case 11:
            // Implementación para Horarios
            break;
        case 12:
            menuGeneral();
            break;
        default:
            cout << "\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
            cin.ignore();
            cin.get();
        }
    } while (choice != 12);
}

void procesos()
{
    // Implementación de procesos
}

void reportes()
{
    // Implementación de reportes
}

void ayuda()
{
    // Implementación de ayuda
}

void seguridad()
{
    // Implementación de seguridad
    Bitacora Auditoria;
    Auditoria.visualizarBitacora();
}
