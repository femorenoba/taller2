#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "global.h"
#include "lcgrand.h"


void eventollegada(void)  /* Funcion de eventollegada */
{
    float espera;

    /* Programa la siguiente eventollegada. */

    tiempo_sig_evento[1] = tiempo_simulacion + expon(media_entre_eventollegadas);

    /* Reisa si el servidor esta OCUPADO. */

    if (estado_servidor == OCUPADO) {

        /* Sservidor OCUPADO, aumenta el numero de clientes en cola */

        ++num_entra_cola;

        /* Verifica si hay condici�n de desbordamiento */

        if (num_entra_cola > LIMITE_COLA) {

            /* Se ha desbordado la cola, detiene la simulacion */

            fprintf(resultados, "\nDesbordamiento del arreglo tiempo_eventollegada a la hora");
            fprintf(resultados, "%f", tiempo_simulacion);
            exit(2);
        }

        /* Todavia hay espacio en la cola, se almacena el tiempo de eventollegada del
        	cliente en el ( nuevo ) fin de tiempo_eventollegada */

        tiempo_eventollegada[num_entra_cola] = tiempo_simulacion;
    }

    else {

        /*  El servidor esta LIBRE, por lo tanto el cliente que llega tiene tiempo de eespera=0
           (Las siguientes dos lineas del programa son para claridad, y no afectan
           el reultado de la simulacion ) */

        espera            = 0.0;
        total_de_esperas += espera;

        /* Incrementa el numero de clientes en espera, y pasa el servidor a ocupado */
        ++num_clientes_espera;
        estado_servidor = OCUPADO;

        /* Programa una salida ( servicio terminado ). */     

        tiempo_sig_evento[2] = tiempo_simulacion + expon(media_atencion);
    }
}