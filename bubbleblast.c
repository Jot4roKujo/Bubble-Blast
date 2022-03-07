#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>    //libreria per operare con valori booleani
#include <time.h>       //libreria per l'uso della funzione random

        //Definizione costanti
#define RIGHE 5         //numero di righe della griglia di gioco
#define COLONNE 6       //numero di colonne della griglia di gioco
#define BOLLE_MAX 20    //limite di bolle da inserire nella matrice

        //Definizione prototipi
//Matrici
    void creaGriglia(int griglia[RIGHE][COLONNE]);
    void stampaGriglia(int griglia[RIGHE][COLONNE]);
    void copiaGriglia(void * grigliaDestinazione, void * grigliaOrigine);
    void riempiGriglia(int griglia[RIGHE][COLONNE]);

//Esplosione Bolle
    void esplosione(int griglia[RIGHE][COLONNE], int riga, int colonna);
    void expUp(int griglia[RIGHE][COLONNE], int riga, int colonna);
    void expDown(int griglia[RIGHE][COLONNE], int riga, int colonna);
    void expL(int griglia[RIGHE][COLONNE], int riga, int colonna);
    void expR(int griglia[RIGHE][COLONNE], int riga, int colonna);

//Gioco
    bool winGame(int griglia[RIGHE][COLONNE]);
    bool loseGame(int mosseDaBattere);
    int mosse(int griglia[RIGHE][COLONNE], int riga, int colonna);

//Grafica
    void stampaRegole();
    void spazio();
    void caricamento();
    void clear();


int main(){

    //Definizione variabili
    int griglia[RIGHE][COLONNE];                //Matrice base
    int grigliaModificata[RIGHE][COLONNE];      //Matrice modificata dopo ogni mossa del giocatore
    int contaMosse = 0;                         //Contatore mosse del giocatore
    int mosseDaBattere;                         //Variabile per salvare le mosse da battere
    int rigaScelta;                             //Variabili per la scelta delle coordinate del giocatore
    int colonnaScelta;
    bool giocoVinto;                            //Variabile per la vittoria
    bool giocoPerso;                            //Variabile per la sconfitta

    //Si inizia!
    stampaRegole();
    fflush(stdin);
    getchar();
    clear();
    caricamento();
    spazio();
    creaGriglia(griglia);
    riempiGriglia(griglia);
    copiaGriglia(grigliaModificata, griglia);
    clear();
    spazio();
    stampaGriglia(grigliaModificata);
    mosseDaBattere = mosse(griglia, RIGHE, COLONNE);
    spazio();
    printf("\nAttenzione! Le mosse a tua disposizione sono: %d!\n", mosseDaBattere);
    spazio();
    

    do

        {

        //Selezione riga da parte del giocatore con controllo input
        printf("\nSeleziona la riga della bolla da colpire ==> ");

        while (scanf("%d", &rigaScelta) != 1 || rigaScelta <0 || rigaScelta > RIGHE-1)
        {
           printf("La riga scelta non esiste, scegline un'altra ==> ");
                // rimuovo eventuali caratteri rimasti nel buffer fino al newline
		    while (getchar() != '\n');
        }
        
        //Selezione colonna da parte del giocatore con controllo input
        printf("\nSeleziona la colonna della bolla da colpire ==> ");

        while (scanf("%d", &colonnaScelta) != 1 || colonnaScelta <0 || colonnaScelta > COLONNE-1)
        {
           printf("La colonna scelta non esiste, scegline un'altra ==> ");
                // rimuovo eventuali caratteri rimasti nel buffer fino al newline
		    while (getchar() != '\n');
        }        

        contaMosse++;
        mosseDaBattere--;
        clear();

        //Stampo a video i valori inseriti dal giocatore
        printf("\nHai scelto le coordinate [%d,%d]\n", rigaScelta, colonnaScelta);

        if (grigliaModificata[rigaScelta][colonnaScelta] == 1){                                 //Bolla selezionata con stato 1, viene diminuito di 1 
            grigliaModificata[rigaScelta][colonnaScelta]--;                                 
            esplosione(grigliaModificata, rigaScelta, colonnaScelta);
            printf("\nHai fatto esplodere la bolla!!! L'esplosione si è propagata!!!\n");
            spazio();                                              
        }else if (grigliaModificata[rigaScelta][colonnaScelta] == 2){                           //Bolla selezionata con stato 2, viene diminuito di 1
            printf("\nHai colpito una bolla gonfia a metà! Ora è pronta ad esplodere!\n");
            spazio();
            grigliaModificata[rigaScelta][colonnaScelta]--;     
        }else if (grigliaModificata[rigaScelta][colonnaScelta] == 3){                           //Bolla selezionata con stato 3, viene diminuito di 1
            printf("\nHai colpito una bolla sgonfia! Ora è gonfia a metà!\n");
            spazio();
            grigliaModificata[rigaScelta][colonnaScelta]--;
        }else{printf("\nHai mancato la bolla!\n"); spazio();}

        stampaGriglia(grigliaModificata);
        spazio();

        printf("\nMosse effettuate: %d - Mosse rimanenti: %d\n", contaMosse, mosseDaBattere);

        giocoVinto = winGame(grigliaModificata);
        giocoPerso = loseGame(mosseDaBattere);

        } while (giocoVinto != true && giocoPerso != true);
    
    if (giocoVinto == true)
    {
        printf("\nCOMPLIMENTI HAI VINTO!!\n");
        printf("\nPremi un tasto per uscire...\n");
        fflush(stdin);
        getchar();
    }else if (giocoPerso == true)
    {
        printf("\nHAI PERSO!!\n");
        printf("\nPremi un tasto per uscire...\n");
        fflush(stdin);
        getchar();
    }
    

}


//Definizione funzioni

    //Funzione che crea la matrice e la inizializza con solo zeri
    void creaGriglia(int griglia[RIGHE][COLONNE]){
    int i, j;
    for(i = 0; i < RIGHE; i++){
        for(j = 0; j < COLONNE; j++){
            griglia[i][j]=0;
        }
    }
}
    
    //Funzione che stampa a schermo la griglia di gioco
    void stampaGriglia(int griglia[RIGHE][COLONNE]){
    int i, j;
    printf("\n");
    for(i = 0; i < RIGHE; i++){
        for(j = 0; j < COLONNE; j++){
            printf("\t");
            printf("%d", griglia[i][j]);
        }
    printf("\n");
    }
}

    //Funzione che copia la matrice base
    void copiaGriglia(void * grigliaDestinazione, void * grigliaOrigine){
        memcpy(grigliaDestinazione, grigliaOrigine, RIGHE*COLONNE*sizeof(int));     //Funzione della Libreria di C: richiede due puntatori destinazione/origine e il numero di bytes da copiare
    }

    //Funzione che riempie la matrice base con bolle a stato variabile
    void riempiGriglia(int griglia[RIGHE][COLONNE]){
        int bolleCreate = BOLLE_MAX;            //Contatore delle bolle create. Serve per non creare più bolle delle max fissate
        
        do
        {
            int rigaRandom;                     //Variabile che contiene le coordinate della riga in cui inserire la bolla
            int colonnaRandom;                  //Variabile che contiene le coordinate colonne in cui inserire la bolla
            int statoBolla;                     //Variabile che contiene lo stato della bolla (1, 2 o 3)

            srand(time(NULL));                  //Funzione per la generazione casuale di interi: basta chiamarla una volta per randomizzare il seed e poi utilizzarla per ogni variabile
            rigaRandom = rand() % RIGHE;        //Generazione casuale della coordinata riferita alla riga della matrice fra 0 e il valore della costante RIGHE definita
            colonnaRandom = rand() % COLONNE;   //Generazione casuale della coordinata riferita alla colonna della matrice fra 0 e il valore della costante RIGHE definita
            statoBolla = rand() % 3+1;          //Stato variabile generato fra 1 e 3 compresi. "+1" per evitare che genereri lo stato "0"

            if(griglia[rigaRandom][colonnaRandom] == 0){            //L'elemento trovato dev'essere vuoto (=0) per poterci inserire una bolla
                griglia[rigaRandom][colonnaRandom] = statoBolla;    //Inserisce nell'indice trovato il valore della bolla
            bolleCreate--;                                          //Riduce il contatore delle bolle create
            }

        } while (bolleCreate != 0);             //Ripete finchè non è stato raggiunto il limite massimo di bolle creabili

    }

    //Funzione che gestisce la vittoria
    bool winGame(int griglia[RIGHE][COLONNE]){
        int i, j;
        bool fine = true;                                       //Fine se la griglia è composta da tutti zeri
        for(i=0; i<RIGHE; i++){
            for(j=0; j<COLONNE; j++){
                if(griglia[i][j] != 0){fine = false;}
            }
        }
        return fine;
    }

    //Funzione che gestisce la sconfitta
    bool loseGame(int mosseDaBattere){
        bool fine = false;
        if (mosseDaBattere < 1)
        {
            fine = true;
        }
        return fine;
    }

    //Funzione che calcola le mosse necessarie per completare il gioco
    int mosse(int griglia[RIGHE][COLONNE], int riga, int colonna){
        int mosseDaBattere = 0;
        bool fineCiclo;
        do
            {
                fineCiclo = true;
                for(riga=0; riga < RIGHE; riga++){
                    for(colonna = 0; colonna < COLONNE; colonna++)
                        if(griglia[riga][colonna] == 1){
                            griglia[riga][colonna]--;
                            esplosione(griglia, riga, colonna);
                            mosseDaBattere++;
                            fineCiclo = false;
                        }
                        else if(griglia[riga][colonna] == 2 || griglia[riga][colonna] == 3){
                            griglia[riga][colonna]--;
                            mosseDaBattere++;
                            fineCiclo = false;
                        }
                }        
            } while (fineCiclo == false);
        return mosseDaBattere;
    }

    //Funzione che mette in moto l'esplosione nelle 4 direzioni rispetto alle coordinate della bolla esplosa
    void esplosione(int griglia[RIGHE][COLONNE], int riga, int colonna){
        expUp(griglia, riga, colonna);
        expDown(griglia, riga, colonna);
        expL(griglia, riga, colonna);
        expR(griglia, riga, colonna);
    }

    //Funzione che propaga l'esplosione verso l'alto
    void expUp(int griglia[RIGHE][COLONNE], int riga, int colonna){
        bool fineCiclo = false;                                         //Variabile booleana da utilizzare come condizione di terminazione

        if(riga > 0){                                                   //Controllo di non essere già al bordo
            riga--;                                                     //Se non lo sono, salgo di una riga per propagare l'esplosione modificando il valore della bolla
        do
            {
            if(griglia[riga][colonna] != 0) {fineCiclo = true;          //Controllo il valore della bolla: se diverso da 0 la diminuisco e pongo vera la condizione di terminazione
            if(griglia[riga][colonna] == 1) {griglia[riga][colonna]--; esplosione(griglia, riga, colonna);}     //scende a 0 quindi propago nuovamente l'esplosione 
            else {griglia[riga][colonna]--;}                                                                      //Altrimenti diminuisco il valore di 1 e basta
            } else riga--;                                              //Se invece il valore della bolla è 0 salgo ancora di una cella
            if(riga < 0){fineCiclo = true;}                             //Controllo se il bordo è stato superato, in quel caso esco dal ciclo
            } while (fineCiclo != true);                           
        } else return;                                                  //Se ero già al bordo non faccio nulla
    }

    //Funzione che propaga l'esplosione verso il basso
    void expDown(int griglia[RIGHE][COLONNE], int riga, int colonna){
        bool fineCiclo = false;

        if(riga < RIGHE-1){
            riga++;
        do
            {
            if(griglia[riga][colonna] != 0) {fineCiclo = true;
            if(griglia[riga][colonna] == 1) {griglia[riga][colonna]--; esplosione(griglia, riga, colonna);}
            else {griglia[riga][colonna]--;}
            } else riga++;
            if(riga == RIGHE){fineCiclo = true;}
            } while (fineCiclo != true);
        } else return;
    }

    //Funzione che propaga l'esplosione verso sinistra
    void expL(int griglia[RIGHE][COLONNE], int riga, int colonna){
        bool fineCiclo = false;

        if(colonna > 0){
            colonna--;
        do
            {
            if(griglia[riga][colonna] != 0) {fineCiclo = true;
            if(griglia[riga][colonna] == 1) {griglia[riga][colonna]--; esplosione(griglia, riga, colonna);}
            else {griglia[riga][colonna]--;}
            } else colonna --;
            if(colonna < 0){fineCiclo = true;}
            } while (fineCiclo != true);
        } else return;
    }

    //Funzione che propaga l'espolosione verso destra
    void expR(int griglia[RIGHE][COLONNE], int riga, int colonna){
        bool fineCiclo = false;

        if(colonna < COLONNE-1){
            colonna++;
        do
            {
            if(griglia[riga][colonna] != 0) {fineCiclo = true;
            if(griglia[riga][colonna] == 1) {griglia[riga][colonna]--; esplosione(griglia, riga, colonna);}
            else {griglia[riga][colonna]--;}
            } else colonna++;
            if(colonna == COLONNE){fineCiclo = true;}
            } while (fineCiclo != true);
        } else return;
    }

    //Funzione che inserisce uno riga di = per fare ordine a schermo
    void spazio(){
        int i;
        printf("\n");
        for(i=0; i<97; i++){
            printf("=");
        }
        printf("\n");
    }

    //Funzione che inserisce uno spazio e invita l'utente ad attendere la generazione della griglia di gioco
    void caricamento(){
        int i;
        printf("\n");
        for(i=0; i<97; i++){
            printf("=");
        }
        printf("\n");
        printf("\n\t\t\t\t   LOADING... PLEASE WAIT!\n");
    }

    //Funzione che pulisce la console
    void clear(){
        printf("\e[1;1H\e[2J");             //Molto più veloce della funzione 'system("clear")'
    }

    //Funzione che stampa a video le regole del gioco
    void stampaRegole(){

        printf("\t\t\t\tB U B B L E\t B L A S T\n");
        printf("\n\t\t\t\t\tBenvenuto!");
        printf("\n");
        printf("\nLo scopo del gioco è far esplodere tutte le bolle entro i tentativi a disposizione.");
        printf("\nLe bolle sono rappresentate dai numeri presenti nella griglia di gioco ed ognuno di essi");
        printf("\nindica lo stato in cui si trova la bolla: \n");
        printf("\n(3) la bolla è sgonfia\n");
        printf("\n(2) la bolla è gonfia a meta'\n");
        printf("\n(1) la bolla è pronta ad esplodere\n");
        printf("\n(0) la bolla è esplosa\n");
        printf("\nSe colpisci una bolla questa passerà allo stato successivo: \n");
        printf("\nda sgonfia(3) a gonfia a meta'(2), fino ad essere pronta ad esplodere(1)...\n");
        printf("\nQuando una bolla esplode verrà propagata l'esplosione alle bolle limitrofe in tutte le direzioni!\n");
        printf("\nPer selezionare una bolla inserisci le sue coordinate (riga e colonna)");
        printf("\nricordando che esse partono da zero! Ad esempio: per colpire la bolla che si trova nel primo slot");
        printf("\nin alto a sinistra dovrai selezionare [0,0]\n");
        printf("\nTutto chiaro?\n");
        printf("\nPremi INVIO per iniziare...\n");   
    }
