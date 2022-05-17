#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//funcion para calcular la media tanto real como imaginaria.

int media(int * lista, int n){
	int acum = 0;
	for (int i = 0; i < n; ++i)
	{
		acum = acum + lista[i];
	}
	acum = acum / n;
	return acum;

}

int ruidoTotal(int * lista, int n){
	
	int acum = 0;
	for (int i = 0; i < n; ++i)
	{
		acum = acum + lista[i];
	}
	return acum;

}

int potencias(int * listaR, int listaI, int n){

	int acum = 0;
	for (int i = 0; i < n; ++i)
	{
		acum = pow(pow(listaR[i], 2) + pow(listaI[i], 2), 0.5) + acum;
	}
	return acum;

}