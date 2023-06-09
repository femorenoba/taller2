#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "global.h"
#include "lcgrand.h"

void eventosalida(void)  /* Funcion de eventosalida. */
{
    int   i;
    float espera;

    /* Revisa si la cola esta vacia */

    if (num_entra_cola == 0) {

        /* La cola esta vacia, pasa el servidor a LIBRE y
        no considera el evento de eventosalida*/     
        estado_servidor      = LIBRE;
        tiempo_sig_evento[2] = 1.0e+30;
    }

    else {

        /* La cola no esta vacia, disminuye el numero de clientes en cola. */
        --num_entra_cola;

        /*Calcula la espera del cliente que esta siendo atendido y
        actualiza el acumulador de espera */

        espera            = tiempo_simulacion - tiempo_eventollegada[1];
        total_de_esperas += espera;

        /*Incrementa el numero de clientes en espera, y programa la eventosalida. */   
        ++num_clientes_espera;
        tiempo_sig_evento[2] = tiempo_simulacion + expon(media_atencion);

        /* Mueve cada cliente en la cola ( si los hay ) una posicion hacia adelante */
        for (i = 1; i <= num_entra_cola; ++i)
            tiempo_eventollegada[i] = tiempo_eventollegada[i + 1];
    }
}