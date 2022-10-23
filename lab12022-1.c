/*
OBS: No pude hacer execv ni el makefile se compila a mano con gcc lab1.c -lm -o lab1
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


#define LECTURA 0
#define ESCRITURA 1


typedef struct visibilidad{
	float u;
	float v;
	float r;
	float i;
	float w;
	struct visibilidad * sig;
}visibilidad;

/*
Entrada: posicion de la visibilidad (u,v)
Salida: flotante
Desc: calcula la distancia con la formula del enunciado
*/

float distancia(float u , float v){
	float d = pow(pow(u,2) + pow(v,2), 0.5);
	return d;
}

/*
Entrada: visibilidad
Salida: void
Desc: muestra la visibilidad por consola
*/

void mostrarVis(visibilidad * vis){
	if (vis == NULL)
	{
		printf("NULL\n");
		return;
	}
	printf("u: %f, v: %f, r: %f, i: %f, w: %f\n", vis->u, vis->v, vis->r, vis->i, vis->w);
	printf("Radio: %f\n", distancia(vis->u,vis->v));
}

/*
Entrada: lista de vis
Salida: entero
Desc: calcula cuantas vis hay por disco
*/

int mostrarDisco(visibilidad * vis){
	visibilidad * aux = vis;
	int c = 0;
	while(aux != NULL){
		aux = aux->sig;
		c++;
	}
	return c;
}

/*
Entrada: flotantes con los datos de una vis
Salida: un struct con la vis
Desc: crea una visibilidad
*/

visibilidad * crearVisibilidad(float u, float v, float r, float i, float w){
	visibilidad * newVis = malloc(sizeof(visibilidad));
	newVis->u = u;
	newVis->v = v;
	newVis->r = r;
	newVis->i = i;
	newVis->w = w;
	newVis->sig = NULL;
}

/*
Entrada: distancia de la vis, ancho del disco, cantidad de discos
Salida: entero que indica a que disco pertenece
Desc: calcula a que disco pertenece cada visibilidad
*/


int queDiscoEs(float p, int ancho, int canDiscos){

    int count = 0;
    while(p > ancho && count < canDiscos){
    	p = p/ancho;
    	count++;
    }
    return count;
}

/*
Entrada: lista de visibilidades y una visibilidad nueva
Salida: una lista de visibilidades
Desc: sirve para agreagar una visibilidad a un disco
*/

visibilidad * insertarVisibilidad(visibilidad * lista, visibilidad * vis){
	
	visibilidad * aux = lista;

	if (lista == NULL)
	{
		lista = vis;
		return lista;
	}

	while(aux->sig != NULL){
		aux = aux->sig;
	}
	aux->sig = vis;
	return lista;	
}

/*
Entrada: una lista de visibilidades (disco)
Salida: un entero con el resultado
Desc: sirve para calcular la media real de un disco
*/

float mediaReal(visibilidad * vis){
	float acum = 0;
	float n = 0;
	visibilidad * aux = vis;
	while(aux != NULL){
		acum = acum + aux->r;
		n++;
		aux = aux->sig;
	}
	acum = acum / n;
	return acum;

}

/*
Entrada: una lista de visibilidades (disco)
Salida: un entero con el resultado
Desc: sirve para calcular la media imaginaria de un disco
*/

float mediaImaginaria(visibilidad * vis){
	float acum = 0;
	float n = 0;
	visibilidad * aux = vis;
	while(aux != NULL){
		acum = acum + aux->i;
		n++;
		aux = aux->sig;
	}
	acum = acum / n;
	return acum;

}

/*
Entrada: una lista de visibilidades (disco)
Salida: un entero con el resultado
Desc: sirve para calcular el ruido total de un disco
*/

float ruidoTotal(visibilidad * vis){
	
	float acum = 0;
	visibilidad * aux = vis;
	while(aux != NULL){
		acum = acum + aux->w;
		aux = aux->sig;
	}
	
	return acum;

}

/*
Entrada: una lista de visibilidades (disco)
Salida: un entero con el resultado
Desc: sirve para calcular la potencia de un disco
*/

float potencias(visibilidad * vis){

	float acum = 0;
	visibilidad * aux = vis;
	while(aux != NULL){
		acum = pow(pow(aux->r, 2) + pow(aux->i, 2), 0.5) + acum;
		aux = aux->sig;
	}
	return acum;
}

void main(int argc, char ** argv){


    char entrada1[20];        // String para nombre del archivo de entrada.
    char salida1[20];        // String para nombre del archivo de salida.

	int canDiscos;
	int ancho;
	int grafico = 0;

    // -------------------------------

	int c;

    // --- GETOPT ---

    opterr = 0;

    while((c = getopt(argc, argv, "i:o:d:n:b")) != -1){
        switch(c){
            case 'i':
                sscanf(optarg, "%s", entrada1);
                break;
            case 'o':
                sscanf(optarg, "%s", salida1);
                break;
            case 'd':
                sscanf(optarg, "%d", &ancho);            // Getopt con casos.
                break;
			case 'n':
                sscanf(optarg, "%d", &canDiscos);            // Getopt con casos.
                break;
            case 'b':
                grafico = 1;
                break;
            case '?':
                if(optopt == 'i' || optopt == 'o' || optopt == 'd' || optopt == 'n'){
                    fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);
                }else if(isprint(optopt)){
                    fprintf(stderr, "Opcion desconocida '-%c'.\n", optopt);
                }else{
                    fprintf(stderr, "Opcion con caracter desconocido '\\x%x'.\n", optopt);
                }
                return;
            default:
                abort();
        }
    }
	

	FILE * entrada = fopen(entrada1,"r");

	float t1;
	float t2;
	float t3;
	float t4;
	float t5;

	visibilidad ** disco = (visibilidad**)malloc((canDiscos)*sizeof(visibilidad));
	for (int i = 0; i < canDiscos; ++i)
	{
		disco[i] = NULL;
	}

	int n;
	while(!feof(entrada)){

        fscanf(entrada, "%f, %f, %f, %f, %f\n", &t1, &t2, &t3, &t4, &t5);
		visibilidad * vis1 = crearVisibilidad(t1, t2, t3, t4, t5);
		n = queDiscoEs(distancia(t1,t2), ancho, canDiscos);
		disco[n] = insertarVisibilidad(disco[n], vis1);
    }
    
	fclose(entrada);
    	

    	visibilidad * mensajeConfirmado;
	int status;
    	visibilidad* mensajeRecibido = (visibilidad*)malloc(sizeof(visibilidad));
    	visibilidad* ack = (visibilidad*)malloc(sizeof(visibilidad));
   	pid_t pid;
    visibilidad * listaFinal = NULL;
    FILE * salida = fopen(salida1, "w");


    //pipe(fd); // Se crea el PIPE
	
	for (int i = 0; i < canDiscos; ++i)
	{
		int* pipes1 = (int*)malloc(sizeof(int)*2); //pipe para que hijo lea y padre escriba
		int* pipes2 = (int*)malloc(sizeof(int)*2);//pipe para que hijo escriba y padre lea
		pipe(pipes1);
		pipe(pipes2);
		pid = fork();
		if(pid > 0){
			
			close(pipes1[LECTURA]);
			close(pipes2[ESCRITURA]);
			write(pipes1[ESCRITURA],disco[i],sizeof(visibilidad));
			read(pipes2[LECTURA],ack, sizeof(visibilidad));
			listaFinal = insertarVisibilidad(listaFinal, ack);
			continue;
		}
		else if(pid == 0){

			close(pipes1[ESCRITURA]);
			close(pipes2[LECTURA]);
			read(pipes1[LECTURA], mensajeRecibido, sizeof(visibilidad));
			ack = crearVisibilidad(mediaReal(mensajeRecibido), mediaImaginaria(mensajeRecibido), ruidoTotal(mensajeRecibido), potencias(mensajeRecibido), 0);
			write(pipes2[ESCRITURA], ack, sizeof(visibilidad));
			if(grafico == 1){
				printf("soy hijo de pid %d, procese %d visibilidades\n", getpid(), mostrarDisco(mensajeRecibido));
			}
	
			return;
		}
		else{
		}
	}

 	for(int i = 0; i < canDiscos; i++){
 		pid = wait(&status);
 		fprintf(salida, "Disco %d:\n", i + 1);
		fprintf(salida, "Media real: %f:\n", listaFinal->u);
		fprintf(salida, "Media imaginaria: %f:\n", listaFinal->v);
		fprintf(salida, "Potencia: %f:\n", listaFinal->i);
		fprintf(salida, "Ruido Total: %f:\n", listaFinal->r);
		listaFinal = listaFinal->sig;
	
 	}
	fclose(salida);

    
	    
	return;
}
