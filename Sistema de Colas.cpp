/* Definiciones externas para el sistema de colas simple */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lcgrand.cpp"  /* Encabezado para el generador de numeros aleatorios */
#include "global.h"
#include "estadisticas.cpp"
#include "generadorreporte.cpp"
#include "inicializacion.cpp"
#include "manejotiempoespacio.cpp"
#include "eventollegada.cpp"
#include "eventosalida.cpp"

#define LIMITE_COLA 100  /* Capacidad maxima de la cola */
#define OCUPADO      1  /* Indicador de Servidor Ocupado */
#define LIBRE      0  /* Indicador de Servidor Libre */

int   sig_tipo_evento, num_clientes_espera, num_esperas_requerido, num_eventos,
      num_entra_cola, estado_servidor;
float area_num_entra_cola, area_estado_servidor, media_entre_eventollegadas, media_atencion,
      tiempo_simulacion, tiempo_eventollegada[LIMITE_COLA + 1], tiempo_ultimo_evento, tiempo_sig_evento[3],
      total_de_esperas;
FILE  *parametros, *resultados;

void  inicializacion(void);
void  manejotiempoespacio(void);
void  eventollegada(void);
void  eventosalida(void);
void  generadorreporte(void);
void  actualizar_estad_prom_tiempo(void);
float expon(float mean);


int main(void)  /* Funcion Principal */
{
    /* Abre los archivos de entrada y eventosalida */

    parametros  = fopen("param.txt",  "r");
    resultados = fopen("result.txt", "w");

    /* Especifica el numero de eventos para la funcion manejotiempoespacio. */

    num_eventos = 2;

    /* Lee los parametros de enrtrada. */

    fscanf(parametros, "%f %f %d", &media_entre_eventollegadas, &media_atencion,
           &num_esperas_requerido);

    /* Escribe en el archivo de eventosalida los encabezados del reporte y los parametros iniciales */

    fprintf(resultados, "Sistema de Colas Simple\n\n");
    fprintf(resultados, "Tiempo promedio de eventollegada%11.3f minutos\n\n",
            media_entre_eventollegadas);
    fprintf(resultados, "Tiempo promedio de atencion%16.3f minutos\n\n", media_atencion);
    fprintf(resultados, "Numero de clientes%14d\n\n", num_esperas_requerido);

    /* iInicializa la simulacion. */

    inicializacion();

    /* Corre la simulacion mientras no se llegue al numero de clientes especificaco en el archivo de entrada*/

    while (num_clientes_espera < num_esperas_requerido) {

        /* Determina el siguiente evento */

        manejotiempoespacio();

        /* Actualiza los acumuladores estadisticos de tiempo promedio */

        actualizar_estad_prom_tiempo();

        /* Invoca la funcion del evento adecuado. */

        switch (sig_tipo_evento) {
            case 1:
                eventollegada();
                break;
            case 2:
                eventosalida();
                break;
        }
    }

    /* Invoca el generador de generadorreporte y termina la simulacion. */

    generadorreporte();

    fclose(parametros);
    fclose(resultados);

    return 0;
}



