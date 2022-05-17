#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>


typedef struct visibilidad{
	float u;
	float v;
	float r;
	float i;
	float w;
	struct visibilidad * sig;
}visibilidad;

float distancia(float u , float v){
	float d = pow(pow(u,2) + pow(v,2), 0.5);
	return d;
}

void mostrarVis(visibilidad * vis){
	if (vis == NULL)
	{
		printf("NULL\n");
		return;
	}
	printf("u: %f, v: %f, r: %f, i: %f, w: %f\n", vis->u, vis->v, vis->r, vis->i, vis->w);
	printf("Radio: %f\n", distancia(vis->u,vis->v));
}

void mostrarDisco(visibilidad * vis){
	visibilidad * aux = vis;
	int c = 0;
	while(aux != NULL){
		mostrarVis(aux);
		aux = aux->sig;
		c++;
	}
	printf("%d\n", c);
	return;
}

visibilidad * crearVisibilidad(float u, float v, float r, float i, float w){
	visibilidad * newVis = malloc(sizeof(visibilidad));
	newVis->u = u;
	newVis->v = v;
	newVis->r = r;
	newVis->i = i;
	newVis->w = w;
	newVis->sig = NULL;
}

int queDiscoEs(float p, int ancho, int canDiscos){

    int count = 0;
    while(p > ancho && count < canDiscos){
    	p = p/ancho;
    	count++;
    }
    return count;
}

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


void main(int argc, char ** argv){
	
	int canDiscos = 2;
	int ancho = 200;

	FILE * entrada = fopen(argv[1],"r");

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
    /*printf("Disco 1:\n");
    mostrarDisco(disco[0]);
    printf("Disco 2:\n");
    mostrarDisco(disco[1]);*/

    //int fd[2];
    //char buffer[30];
    pid_t pid;

    //pipe(fd); // Se crea el PIPE

    for (int i = 0; i < canDiscos; ++i)
    {
    	pid = fork();
    }
    if (pid > 0)
    {
    	printf("soy hijo de pid %d\n", pid);
    }else if(pid == 0){
    	printf("soy padre\n");
    }
    else{
    	printf("error\n");
    }
}