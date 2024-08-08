#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[50];
    int edad;
    int matricula;
} Alumno;

void grabarAlumno(Alumno **alumnos, int *n);
void leerAlumnosDisco();
void guardarAlumnosDisco(Alumno *alumnos, int n);

int main() {
    int opcion;
    Alumno *alumnos = NULL;
    int cantidadAlumnos = 0;

    do {
        printf("\nMenu:\n");
        printf("1. Leer disco\n");
        printf("2. Grabar dato\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                leerAlumnosDisco();
                break;
            case 2:
                grabarAlumno(&alumnos, &cantidadAlumnos);
                break;
            case 3:
                if (cantidadAlumnos > 0) {
                    guardarAlumnosDisco(alumnos, cantidadAlumnos);
                    free(alumnos);
                }
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 3);

    return 0;
}

void grabarAlumno(Alumno **alumnos, int *n) {
    char opcion;

    do {
        *alumnos = realloc(*alumnos, (*n + 1) * sizeof(Alumno));
        if (*alumnos == NULL) {
            printf("Error al asignar memoria.\n");
            exit(1);
        }

        printf("\nIngrese el nombre del alumno: ");
        scanf("%s", (*alumnos)[*n].nombre);
        printf("Ingrese la edad del alumno: ");
        scanf("%d", &(*alumnos)[*n].edad);
        printf("Ingrese la matricula del alumno: ");
        scanf("%d", &(*alumnos)[*n].matricula);

        (*n)++;

        printf("Desea ingresar otro registro? (s/n): ");
        scanf(" %c", &opcion);
    } while (opcion == 's');
}

void leerAlumnosDisco() {
    FILE *archivo = fopen("alumnos.dat", "rb");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    Alumno alumno;
    while (fread(&alumno, sizeof(Alumno), 1, archivo)) {
        printf("Nombre: %s, Edad: %d, Matricula: %d\n", alumno.nombre, alumno.edad, alumno.matricula);
    }

    fclose(archivo);
}

void guardarAlumnosDisco(Alumno *alumnos, int n) {
    FILE *archivo = fopen("alumnos.dat", "wb");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para escritura.\n");
        return;
    }

    fwrite(alumnos, sizeof(Alumno), n, archivo);
    fclose(archivo);
}
