#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>

#define LECTURA 0
#define ESCRITURA 1


int contarComas(char * entradaLong){
    int comas = 0;
    int comillas = 0;
    for(int i = 0; i < strlen(entradaLong); i++){
            if(entradaLong[i] == ',' && comillas != 1){
                comas++;
            }
            else if(entradaLong[i] == '"'){
                comillas++;
            }

        }
    return comas;
}

int getYear(char * entradaLong){
    
    int comas = 0;
    int comillas = 0;
    char year[4];
    for(int i = 0; i < strlen(entradaLong); i++){
        if(entradaLong[i] == ',' && comillas != 1){
            comas++;
        }
        else if(entradaLong[i] == '"'){
            comillas++;
        }
        if(comas == 5){
            year[0] = entradaLong[i+1];
            year[1] = entradaLong[i+2];
            year[2] = entradaLong[i+3];
            year[3] = entradaLong[i+4];
            //printf("Año: %s\n", year);
            return atoi(year);
        }
    }
}

int getId(char * str){
    int posComa;
    for(int i = 0; i < strlen(str); i++){
        if(str[i]==','){
            posComa = i;
            break;
        }
    }
    char id[posComa];
    for(int i = 0; i < posComa; i++){
        id[i] = str[i];
    }

    return atoi(id);
}
float getPrice(char * str1){
    int count = 0;
    int count2 = 0;
    int poscoma1 = 0;
    int poscoma2 = 0;
    for(int i = 0; i < strlen(str1); i++){
        if(str1[i] == ',' && count2 != 1){
            count++;
            if(count == 3){
                poscoma1 = i;
            }
            if(count == 4){
                poscoma2 = i;
            }
            
        }else if (str1[i]=='"'){
            printf("aaa\n");
            count2++;
        }
    }
    char price[poscoma2-poscoma1-1];
    for(int i = 0; i < poscoma2-poscoma1-1; i++){
        price[i] = str1[poscoma1+i+1];
    }
    return atof(price);
}

int juegoMasCaro(char listaGames[1000][120], int pos1, int pos2){
    
    float caro = getPrice(listaGames[pos1];

    while(pos1 < pos2){
        if(getPrice(listaGames[pos1] < getPrice(listaGames[pos1+1])){
            caro = getPrice(listaGames[pos1+1]);
        }
        pos1++;
    }
    return caro;
}

void bubbleSort(char listaGames[1000][120], int n)
{
    int i, j;
    char aux[120];
    for (i = 0; i < n - 1; i++){
 
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++){
            if (getYear(listaGames[j]) > getYear(listaGames[j+1])){
                strcpy(aux, listaGames[j]);
                strcpy(listaGames[j], listaGames[j+1]);
                strcpy(listaGames[j+1], aux);  
            }
        }
    }
    
    
}
void main(int argc, char ** argv){
    
    //char entrada1[40];        // String para nombre del archivo de entrada.
    //char salida1[40];        // String para nombre del archivo de salida.

    int start;
    float minPrecio;

    printf("\nStart: %d\nminPrecio: %f\n\n", start, minPrecio);

    // -------------------------------

	int c;
    int grafico = 0;

    // --- GETOPT ---

    opterr = 0;

    /*while((c = getopt(argc, argv, "i:o:d:p:b")) != -1){
        switch(c){
            case 'i':
                sscanf(optarg, "%s", entrada1);
                break;
            case 'o':
                sscanf(optarg, "%s", salida1);
                break;
            case 'd':
                sscanf(optarg, "%d", &start);            // Getopt con casos.
                break;
			case 'n':
                sscanf(optarg, "%f", &minPrecio);            // Getopt con casos.
                break;
            case 'b':
                grafico = 1;
                break;
            case '?':
                if(optopt == 'i' || optopt == 'o' || optopt == 'd' || optopt == 'p'){
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
    }*/

    FILE * entrada = fopen(argv[1],"r");
    
    char entradaLong[120];
    
    char listaGames[1000][120];

    int contador1 = 0;
    while(fgets(entradaLong, 120, entrada)){
        strtok(entradaLong, "\n");
        strcpy(listaGames[contador1], entradaLong);
        contador1++;
    }

    bubbleSort(listaGames, contador1);
    
    /*for(int i = 0; i < contador1; i++){
        int a = getYear(listaGames[i]);
        printf("Año: %d\n", a);
        printf("%s\n", listaGames[i]);
    }*/

    FILE * inter = fopen("archivoIntermedio.csv", "w");

    for(int i = 0; i < contador1; i++){
        fprintf(inter,"%s\n", listaGames[i]);
    }
    
    fclose(inter);
    
    int canYears = 0;
    int y;
    int y1;    
    for(int i = 0; i <  1000; i++){
        y = getYear(listaGames[i]);
        y1 = getYear(listaGames[i+1]);
        if(y != y1){
            y = i;
            printf("%s\n", listaGames[i]);
            canYears++;
        }
    }
    printf("Cantidad de años:%d\n", canYears);

    int posYears[canYears];
    int contador3 = 0;
    for(int i = 0; i < contador1; i++){
        y = getYear(listaGames[i]);
        y1 = getYear(listaGames[i+1]);
        if(y != y1){
            canYears[contador3] = i;
            contador3++;
    }
/*
    visibilidad * mensajeConfirmado;
	int status;
    visibilidad* mensajeRecibido = (visibilidad*)malloc(sizeof(visibilidad));
    visibilidad* ack = (visibilidad*)malloc(sizeof(visibilidad));
   	pid_t pid;
    visibilidad * listaFinal = NULL;
    FILE * salida = fopen(salida1, "w");
    pid_t pid;
    
    for (int i = 0; i < canYears; ++i)
	{

        //file descriptors
		int* pipes1 = (int*)malloc(sizeof(int)*2); //pipe para que hijo lea y padre escriba
		int* pipes2 = (int*)malloc(sizeof(int)*2);//pipe para que hijo escriba y padre lea
		pipe(pipes1);
		pipe(pipes2);
		pid = fork();
		if(pid > 0){
			close(pipes1[LECTURA]);
			close(pipes2[ESCRITURA]);
			write(pipes1[ESCRITURA],posYears[i],sizeof(int));
			read(pipes2[LECTURA],ack, sizeof(visibilidad));
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

*/    
    fclose(entrada);
    /*FILE * salida = fopen(argv[2], "w");

    fprintf(salida, "aber presta");
    //


    fclose(salida);
*/
    return;
    
    
    
    
    
    
    
}
