#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//funcion para calcular la media tanto real como imaginaria.

typedef struct visibilidad{
	float u;
	float v;
	float r;
	float i;
	float w;
	struct visibilidad * sig;
}visibilidad;


void mostrarVis(visibilidad * vis){
	if (vis == NULL)
	{
		printf("NULL\n");
		return;
	}
	printf("u: %f, v: %f, r: %f, i: %f, w: %f\n", vis->u, vis->v, vis->r, vis->i, vis->w);
}


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
int main(int argc, char ** argv){
	
	
	return 0;
}



