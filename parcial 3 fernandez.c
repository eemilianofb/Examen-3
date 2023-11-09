// Examen de Fefe
// Examen 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxColumnas 3100
#define FilasAProcesar 51
#define TamanoBuffer 1024 * 1024

int main() {
    const char *nombreArchivo = "emails.csv";
    FILE *archivoCsv = fopen(nombreArchivo, "r");
    if (!archivoCsv) {
        perror("Error al abrir el archivo");
        return 1;
    }

    char buffer[TamanoBuffer];
    int conteoPalabras[MaxColumnas] = {0};
    char *nombresPalabras[MaxColumnas];
    int filaInicio = 357;
    int columnaEmailNo = -1;

    if (fgets(buffer, sizeof(buffer), archivoCsv) != NULL) {
        char *token = strtok(buffer, ",");
        int indiceColumna = 0;
        while (token && indiceColumna < MaxColumnas) {
            if (strcmp(token, "Email No.") == 0) {
                columnaEmailNo = indiceColumna;
            } else {
                nombresPalabras[indiceColumna] = strdup(token);
            }
            token = strtok(NULL, ",");
            indiceColumna++;
        }
    } else {
        fclose(archivoCsv);
        return 1;
    }
	int i;
    for ( i = 0; i < filaInicio; ++i) {
        if (fgets(buffer, sizeof(buffer), archivoCsv) == NULL) {
            fclose(archivoCsv);
            return 1;
        }
    }
		
    for (i = 0; i < FilasAProcesar; ++i) {
        if (fgets(buffer, sizeof(buffer), archivoCsv) == NULL) {
            break;
        }
        char *token = strtok(buffer, ",");
        int indiceColumna = 0;
        while (token && indiceColumna < MaxColumnas) {
            if (indiceColumna != columnaEmailNo) {
                long val = strtol(token, NULL, 10);
                if (val != 0 || (val == 0 && token[0] == '0')) {
                    conteoPalabras[indiceColumna] += val;
                }
            }
            token = strtok(NULL, ",");
            indiceColumna++;
        }
    }

    fclose(archivoCsv);

    FILE *archivoSalida = fopen("180358.txt", "w");
    if (!archivoSalida) {
        perror("Error al abrir el archivo");
        return 1;
    }

    for ( i = 0; i < MaxColumnas; i++) {
        if (i != columnaEmailNo && nombresPalabras[i] != NULL) {
            fprintf(archivoSalida, "%s, %d\n", nombresPalabras[i], conteoPalabras[i]);
            free(nombresPalabras[i]);
        }
    }

    fclose(archivoSalida);
    printf("Aqui esta la lista con mi ID 180358.txt\n");

    return 0;
}

