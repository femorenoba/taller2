#include "global.h"
#include "lcgrand.h"

void inicializacion(void)  /* Funcion de inicializacion. */
{
    /* Inicializa el reloj de la simulacion. */

    tiempo_simulacion = 0.0;

    /* Inicializa las variables de estado */

    estado_servidor   = LIBRE;
    num_entra_cola        = 0;
    tiempo_ultimo_evento = 0.0;

    /* Inicializa los contadores estadisticos. */

    num_clientes_espera  = 0;
    total_de_esperas    = 0.0;
    area_num_entra_cola      = 0.0;
    area_estado_servidor = 0.0;

    /* Inicializa la lista de eventos. Ya que no hay clientes, el e
    vento salida
       (terminacion del servicio) no se tiene en cuenta */

    tiempo_sig_evento[1] = tiempo_simulacion + expon(media_entre_eventollegadas);
    tiempo_sig_evento[2] = 1.0e+30;
}