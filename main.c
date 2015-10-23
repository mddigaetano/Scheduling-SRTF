#include <stdio.h>
#include <stdlib.h>

typedef struct s_task{                                                          //Record di ogni singolo processo;
    char ID[2];                                                                 //PID;
    unsigned int ExecutionTime;                                                 //Tempo di Esecuzione;
    unsigned int RemainingTime;                                                 //Tempo rimanente;
    unsigned int WaitTime;                                                      //Tempo di Attesa;
    unsigned int ArrivalTime;                                                   //Tempo di Arrivo;
}task;

void rialloca(task **older, int *n);                                            //Funzione per riallocare array;
void insertionSort(task *v, int n, int clock);                                  //Insertion sort per ordinare processi in ordine di tempo rimanente;
void dropZero(task v[], int n);                                                 //Serve a mettere in coda all'array i processi terminati;
//int TempoMedioAttesa(task v[], int n);                                          //Funzione per calcolare il tempo medio di attesa ||TODO;

int main(int argc, char** argv) {
    int ctrl = 1;                                                               //Flag per esecuzione;
    int clock;                                                                  //Indica a quale tempo macchina è arrivata l'esecuzione;
    int counter;                                                                //Contatore per controllo cambio flag;
    task *v = NULL;                                                             //Puntatore che conterrà l'array dinamico;
    int n = 0;                                                                  //Dimensione dell'array;
    int choice;                                                                 //Scelta utente di inserire un nuovo processo;
    int i;                                                                      //Contatore tuttofare;
    
    for(clock = 0; ctrl; clock++){                                              //Inizio corpo principale;
        printf("Tempo Clock: %d\n", clock);
        printf("Vuoi inserire un nuovo processo? (1)Si' / (0)No\n");            //Scelta per nuovo processo;
        scanf("%d", &choice);
        
        if(choice){                                                             //Se scelta positiva
            rialloca(&v, &n);                                                   //  riallocare array (+1)
            insertionSort(v, n, clock);                                         //  e ordinamento;
        }
        
        v[0].RemainingTime += -1;                                               //Diminuizione tempo rimanente per procasso in esecuzione (v[0]);
        
        for(i=1; i<n && v[i].RemainingTime != 0; i++){                          //Aumento tempo di attesa di tutti gli altri processi;
            v[i].WaitTime += 1;
        }
        
        dropZero(v, n);                                                         //Sposto in fondo processi terminati;
        
        counter = 0;                                                            //Inizio controllo cambio flag;
        for(i=0;i<n;i++){
            if(v[i].RemainingTime == 0)
                counter++;
        }
        if(counter == n)                                                        //Se tutti processi terminati
            ctrl = 0;                                                           //  cambio flag;
        
    }
    
    //TODO AWT();
    
    return (EXIT_SUCCESS);
}

void rialloca(task **older,int *n){                                             //Funzione per riallocare array;
    task *newer=NULL;                                                           //Puntatore dove andrà allocato il nuovo array;
    int i;                                                                      //Semplice contatore;
    
    if(*older){                                                                 //Se il puntatore vecchio non punta a NULL
        newer=(task*)malloc((++(*n))*sizeof(task));                             //alloca il nuovo con un elemento in più,

        for(i=0;i<(*n)-1;i++){                                                  //copia tutti gli elementi,
            newer[i] = (*older)[i];
        }
        free(*older);                                                           //dealloca il vecchio

        *older = newer;                                                         //e sostituiscilo col nuovo;
    }
    else{                                                                       //Altrimenti
        *older = (task*)malloc((++(*n))*sizeof(task));                          //alloca il primo elemento;
    }
    
    return;
}

void dropZero(task v[], int n){                                                 //Serve a mettere in coda all'array i processi terminati;
    int i;                                                                      //Semplice contatore;
    task temp;                                                                  //Variabile temporanea per scambiare;
    
    for(i=0; i<n-1 && v[i+1].RemainingTime != 0; i++){                          //Se non è finito l'array AND il prossimo processo non è terminato
        if(v[i].RemainingTime == 0){                                            //  se l'attuale processo è terminato
            temp = v[i];                                                        //      effettua lo scambio;
            v[i] = v[i+1];
            v[i+1] = temp;
        }
    }
}

void insertionSort(task *v, int n, int clock){                                  //Insertion sort per ordinare processi in ordine di tempo rimanente;
    int i;                                                                      //Semplice contatore;
    task temp;                                                                  //Variabile temporanea per scambiare;
    
    printf("Inserisci l'ID del nuovo processo: ");                              //Inserisci tutti i dati;
    scanf("%s", temp.ID);
    printf("Inserisci la durata del processo: ");
    scanf("%d", &(temp.ExecutionTime));
    printf("\n");
    temp.ArrivalTime = clock;                                                   //Inizializza il tempo di arrivo,
    temp.RemainingTime = temp.ExecutionTime;                                    //il tempo rimanente,
    temp.WaitTime = 0;                                                          //e quello di attesa;
    
    if(n == 1){                                                                 //Se è il primo processo
        v[0]=temp;                                                              //  mettilo al primo posto
    }
    else{                                                                       //Altrimenti
        for(i=n-1; (i>0) && (v[i-1].RemainingTime>temp.RemainingTime); i--){    //  (Partendo dalla fine)se il precedente è maggiore di quello da inserire
            if(v[i-1].RemainingTime != 0)                                       //      se il processo non è terminato
                v[i]=v[i-1];                                                    //          scala di un posto;
        }
        v[i]=temp;                                                              //  metti il nuovo processo al suo posto;
    }
}
