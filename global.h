// globals.h
#include <stdio.h>
#ifndef GLOBALS_H
#define GLOBALS_H

#define LIMITE_COLA 100  /* Capacidad maxima de la cola */
#define OCUPADO      1    /* Indicador de Servidor Ocupado */
#define LIBRE        0    /* Indicador de Servidor Libre */

extern int sig_tipo_evento;
extern int num_clientes_espera;
extern int num_esperas_requerido;
extern int num_eventos;
extern int num_entra_cola;
extern int estado_servidor;
extern float area_num_entra_cola;
extern float area_estado_servidor;
extern float media_entre_llegadas;
extern float media_atencion;
extern float tiempo_simulacion;
extern float tiempo_llegada[LIMITE_COLA + 1];
extern float tiempo_ultimo_evento;
extern float tiempo_sig_evento[3];
extern float total_de_esperas;
extern FILE* parametros;
extern FILE* resultados;

#endif