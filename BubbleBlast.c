//Bubble Blast di JACOPO SCUDIERI Mat. 986645 SSRI ONLINE a.a. 2021/2022 

#include <stdio.h>      //Librerie standard per I/O, stringhe, gestione della memoria (memcpy), funzione random, etc
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>   

        //Definizione costanti
#define RIGHE 5         //numero di righe della griglia di gioco
#define COLONNE 6       //numero di colonne della griglia di gioco

        //Definizione prototipi
//Matrici
    void creaMatrice(int matrice[RIGHE][COLONNE]);
    void riempiMatrice(int matrice[RIGHE][COLONNE], int bolleDaCreare);
    void stampaMatrice(int matrice[RIGHE][COLONNE]);
    void copiaMatrice(void * matriceDestinazione, void * matriceOrigine);

//Gameplay
    void stampaRegole();
    int scegliDifficoltà();
    void getName(char name[30]);
    void click(int matrice[RIGHE][COLONNE], int riga, int colonna);
    int mosse(int matrice[RIGHE][COLONNE]);
    void esplosione(int matrice[RIGHE][COLONNE], int riga, int colonna);
    void esp(int matrice[RIGHE][COLONNE], int riga, int colonna, int dx,int dy);
    bool winGame(int matrice[RIGHE][COLONNE]);
    bool loseGame(int mosseDaBattere);
    
//Grafica
    void spazio();
    void caricamento();
    void clear();

int main(){

    //Definizione variabili
    int matrice[RIGHE][COLONNE];                //Matrice base
    int matriceModificata[RIGHE][COLONNE];      //Matrice modificata dopo ogni mossa del giocatore
    int bolleDaCreare;                          //Variabile per salvare il numero di bolle da creare nella matrice
    int contaMosse = 0;                         //Contatore mosse del giocatore
    int mosseDaBattere;                         //Variabile per salvare le mosse da battere
    int rigaScelta;                             //Variabili per la scelta delle coordinate del giocatore
    int colonnaScelta;
    bool giocoVinto;                            //Variabile per la vittoria
    bool giocoPerso;                            //Variabile per la sconfitta
    char playerName[30];
    
    //Variabili e funzioni per la stampa su file delle statistiche della partita
    char stampaVinto[] = "vinto";
    char stampaPerso[] = "perso";
    time_t rawtime;
	time (&rawtime);
	struct tm *dataEora;
    dataEora = localtime(&rawtime);

    //Si inizia!
    stampaRegole();
    getName(playerName);
    bolleDaCreare = scegliDifficoltà();
    clear();
    caricamento();
    spazio();   
    creaMatrice(matrice);
    riempiMatrice(matrice, bolleDaCreare);
    copiaMatrice(matriceModificata, matrice);
    clear();
    spazio();
    stampaMatrice(matrice);
    mosseDaBattere = mosse(matrice);
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

        if (matriceModificata[rigaScelta][colonnaScelta] == 1){                                 //Bolla selezionata con stato 1, viene diminuito di 1 
            click(matriceModificata, rigaScelta, colonnaScelta);
            printf("\nHai fatto esplodere la bolla!!! L'esplosione si e' propagata!!!\n");
            spazio();                                              
        }else if (matriceModificata[rigaScelta][colonnaScelta] == 2){                           //Bolla selezionata con stato 2, viene diminuito di 1
            click(matriceModificata, rigaScelta, colonnaScelta);
            printf("\nHai colpito una bolla gonfia a metà! Ora e' pronta ad esplodere!\n");
            spazio();    
        }else if (matriceModificata[rigaScelta][colonnaScelta] == 3){                           //Bolla selezionata con stato 3, viene diminuito di 1
            click(matriceModificata, rigaScelta, colonnaScelta);
            printf("\nHai colpito una bolla sgonfia! Ora e' gonfia a metà!\n");
            spazio();
        }else{printf("\nHai mancato la bolla!\n"); spazio();}

        stampaMatrice(matriceModificata);
        spazio();

        printf("\nMosse effettuate: %d - Mosse rimanenti: %d\n", contaMosse, mosseDaBattere);

        giocoVinto = winGame(matriceModificata);
        giocoPerso = loseGame(mosseDaBattere);

        } while (giocoVinto != true && giocoPerso != true);
    
    if (giocoVinto == true)
    {
        printf("\nCOMPLIMENTI HAI VINTO IN %d MOSSE!!\n", contaMosse);      

        FILE *file_handle = fopen("statistiche.txt", "a+");         //Apertura del file txt con controllo

        if (file_handle == NULL){
            printf("\nErrore di apertura file. Il risultato non è stato salvato!\n");
            exit(1);
        }
                                                                    //Scrittura in append delle statistiche della partita appena terminata
        fprintf(file_handle, "\n==> Il %d/%d/%d alle %d:%d %s ha %s in %d mosse.\n", dataEora->tm_mday, dataEora->tm_mon+1, dataEora->tm_year+1900, dataEora->tm_hour, dataEora->tm_min, playerName, stampaVinto, contaMosse);
        fclose(file_handle);                                        //Chiusura del file
        printf("\nIl risultato e' stato salvato!\n");

        printf("\nPremi un tasto per uscire...\n");
        fflush(stdin);
        getchar();
    }else if (giocoPerso == true)
    {
        printf("\nHAI PERSO IN %d MOSSE!!\n", contaMosse);         

        FILE *file_handle = fopen("statistiche.txt", "a+");

        if (file_handle == NULL){
            printf("\nErrore di apertura file. Il risultato non è stato salvato\n");
            exit(1);
        }

        fprintf(file_handle, "\n==> Il %d/%d/%d alle %d:%d %s ha %s in %d mosse.\n", dataEora->tm_mday, dataEora->tm_mon, dataEora->tm_year+1900, dataEora->tm_hour, dataEora->tm_min, playerName, stampaPerso, contaMosse);
        fclose(file_handle);
        printf("\nIl risultato e' stato salvato!\n");

        printf("\nPremi un tasto per uscire...\n");
        fflush(stdin);
        getchar();
    }

}

//Definizione funzioni

    //Funzione che crea la matrice e la inizializza con solo zeri
    void creaMatrice(int matrice[RIGHE][COLONNE]){
    int i, j;
        for(i = 0; i < RIGHE; i++){
            for(j = 0; j < COLONNE; j++){
            matrice[i][j]=0;
            }
        }
    }
    
    //Funzione che stampa a schermo la matrice di gioco quando richiesto
    void stampaMatrice(int matrice[RIGHE][COLONNE]){
    int i, j;
    printf("\n");
        for(i = 0; i < RIGHE; i++){
            for(j = 0; j < COLONNE; j++){
            printf("\t");
            printf("%d", matrice[i][j]);
            }
        printf("\n");
        }
    }

    //Funzione che copia la matrice
    void copiaMatrice(void * matriceDestinazione, void * matriceOrigine){           //Funzione standard della Libreria di C:
        memcpy(matriceDestinazione, matriceOrigine, RIGHE*COLONNE*sizeof(int));     //richiede due puntatori destinazione/origine e il numero di bytes da copiare
    }

    //Funzione che riempie la matrice base con bolle a stato variabile
    void riempiMatrice(int matrice[RIGHE][COLONNE], int bolleDaCreare){
        int bolleCreate = bolleDaCreare;                    //Contatore delle bolle create, posto uguale al numero di bolle impostate dalla difficoltà scelta

        do
        {
            srand(time(NULL));       //Funzione per la generazione casuale di interi: basta chiamarla una volta per randomizzare il seed e poi utilizzarla per ogni variabile
            int rigaRandom = rand() % RIGHE;                //Funzione che genera un numero casuale compreso tra 0 e 4 e lo assegna alla variabile per le coordinate della riga
            int colonnaRandom = rand() % COLONNE;           //Funzione che genera un numero casuale compreso tra 0 e 5 e lo assegna alla variabile per le coordinate della colonna
            int statoBolla = (rand() % 3)+1;                //Funzione che genera un numero casuale compreso tra 1 e 3 (+1 per evitare lo 0) e lo assegna alla variabile statoBolla

            if(matrice[rigaRandom][colonnaRandom] == 0){            //L'elemento trovato dev'essere vuoto (=0) per poterci inserire una bolla
                matrice[rigaRandom][colonnaRandom] = statoBolla;    //Inserisce nell'indice trovato il valore della bolla
                bolleCreate--;                                      //Riduce il contatore delle bolle create
            }

        } while (bolleCreate != 0);             //Ripete finchè non è stato raggiunto il limite di bolle impostato dalla difficoltà

    }
    
    //Funzione che stampa le regole del gioco
    void stampaRegole(){
        printf("\t\t\t\tB U B B L E\t B L A S T\n");
        printf("\n\t\t\t\t\tBenvenuto!");
        printf("\n");
        printf("\nLo scopo del gioco e' far esplodere tutte le bolle entro i tentativi a disposizione.");
        printf("\nLe bolle sono rappresentate dai numeri presenti nella griglia di gioco ed ognuno di essi");
        printf("\nindica lo stato in cui si trova la bolla: \n");
        printf("\n(3) la bolla e' sgonfia\n");
        printf("\n(2) la bolla e' gonfia a meta'\n");
        printf("\n(1) la bolla e' pronta ad esplodere\n");
        printf("\n(0) la bolla e' esplosa\n");
        printf("\nSe colpisci una bolla questa passera' allo stato successivo: \n");
        printf("\nda sgonfia(3) a gonfia a meta'(2), fino ad essere pronta ad esplodere(1)...\n");
        printf("\nQuando una bolla esplode verra' propagata l'esplosione alla bolla più vicina in tutte le direzioni!\n");
        printf("\nPer selezionare una bolla inserisci le sue coordinate (riga e colonna) facendo attenzione al fatto");
        printf("\nche esse partono da zero! Ad esempio: per colpire la bolla che si trova nel primo slot");
        printf("\nin alto a sinistra dovrai selezionare [0,0]\n");
        printf("\nTutto chiaro?\n");
    }

    //Funzione per registrare il nome del giocatore
    void getName(char name[30]){
        printf("\nPer iniziare inserisci il tuo nome: ");
        fgets(name, 30, stdin);
        name[strlen(name)-1] =  '\0';                  //Rendo nullo il penultimo carattere della stringa in modo da non salvare l'INVIO premuto dall'utente nel flusso INPUT
    }

    //Funzione per scegliere la difficoltà
    int scegliDifficoltà(){
        int diff;                                     //Variabile per salvare la scelta del giocatore
        int bolleDaCreare;                                  //Numero di bolle restituito dalla funzione che servirà per la funzione riempiMatrice

        printf("\nScegli ora la difficolta': ");
        printf("\n1) Facile - 2) Media - 3) Difficile\n");
        printf("\n===> ");

        while (scanf("%d", &diff) != 1 || diff > 3)                         //Controllo input e assegnazione variabile
        {
           printf("L'elemento inserito non e' corretto, riprova ==> ");
                // rimuovo eventuali caratteri rimasti nel buffer fino al newline
		    while (getchar() != '\n');
        }

        if (diff == 1)                                                            //Impostazione del numero di bolle in relazione alla difficoltà
        {
            bolleDaCreare = 15;

        } else if (diff == 2)
        {
            bolleDaCreare = 20;
        } else if (diff == 3)
        {
            bolleDaCreare = 25;
        }
        
        return bolleDaCreare;
    }

    //Funzione che gestisce la selezione di un elemento "1" della matrice
    void click(int matrice[RIGHE][COLONNE], int riga, int colonna){
        matrice[riga][colonna]--;                                                   //Diminuisce di 1 il valore dell'indice selezionato 
        if (matrice[riga][colonna]== 0){                                            //Se lo porta a 0 mette in moto l'esplosione
            esplosione(matrice, riga, colonna);
        }
    }

    //Funzione che scorre la matrice e cerca l'elemento "1" al suo interno
    bool ciclaMatriceUno(int matrice[RIGHE][COLONNE]){
    int riga, colonna;
    bool cond;
        for(riga = 0; riga < RIGHE; riga++){
            for(colonna = 0; colonna < COLONNE; colonna++)
                if (matrice[riga][colonna] == 1)
                {
                    cond = true;
                } else (cond = false);
        }
    return cond;      //Se lo trova restituisce TRUE, altrimenti FALSE
    }

    //Funzione che calcola le mosse necessarie per completare il gioco
    int mosse(int matrice[RIGHE][COLONNE]){
        int riga, colonna;
        int mosseDaBattere = 0;                                                 //Contatore mosse che parte da 0
        bool fineCiclo;                                                         //Variabile booleana per controllare la fine del gioco
    
        do                                                                      //Prima voglio selezionare le bolle già pronte ad esplodere
            {
                for(riga=0; riga < RIGHE; riga++){
                    for(colonna = 0; colonna < COLONNE; colonna++)
                        if (matrice[riga][colonna] == 1){
                            click(matrice, riga, colonna);
                            mosseDaBattere++;   
                        }            
                }

            ciclaMatriceUno(matrice);

            } while (ciclaMatriceUno(matrice) == true);

        do                                                                      //Quando (e se) non ce ne sono più, passo alle altre
            {
                for(riga=0; riga < RIGHE; riga++){
                    for(colonna = 0; colonna < COLONNE; colonna++)
                        if (matrice[riga][colonna] == 1){                       //Ma dando sempre precedenza a quelle di stato "1"  che si andranno a creare ad ogni ciclo
                            click(matrice, riga, colonna);
                            mosseDaBattere++;
                        }else if (matrice[riga][colonna] == 2 || matrice[riga][colonna] == 3){
                            click(matrice, riga, colonna);
                            mosseDaBattere++;
                        }
                }

                fineCiclo = winGame(matrice);                                   //Quando la matrice è vuota (gioco vinto) esco dal ciclo

            } while (fineCiclo != true);

        return mosseDaBattere;                                                  //Restituisco il numero di mosse impiegate per vincere
    }

    //Funzione che mette in moto l'esplosione nelle 4 direzioni rispetto alle coordinate della bolla esplosa
    void esplosione(int matrice[RIGHE][COLONNE], int riga, int colonna){
        esp(matrice, riga, colonna,-1,0);               //Salgo di una riga (SU)
        esp(matrice, riga, colonna,1,0);                //Scendo di una riga (GIU')
        esp(matrice, riga, colonna,0,-1);               //Scendo di una colonna (SX)
        esp(matrice, riga, colonna,0,1);                //Salgo di una colonna (DX)
    }

    //Funzione che propaga l'esplosione
    void esp(int matrice[RIGHE][COLONNE], int riga, int colonna, int dx,int dy){                                         
        riga+=dx;                                                               //Sposto "su" e "giù" riga e colonna per propagare l'esplosione
        colonna+=dy;

        while (riga >=0 && riga<RIGHE && colonna>=0 && colonna<COLONNE)         //Controllo di essere dentro ai bordi
        {
            if(matrice[riga][colonna] != 0) {                                   //Se l'indice successivo non è vuoto lo seleziono con la funzione click
                click(matrice, riga, colonna);
            return;
            }                               
            riga+=dx;                                                           //Se invece è vuoto, mi sposto ancora nella stessa direzione finché non ne trovo uno non vuoto
            colonna+=dy;
        }
    }

    //Funzione che gestisce la vittoria
    bool winGame(int matrice[RIGHE][COLONNE]){
        int i, j;
        bool fine = true;                                       
        for(i=0; i<RIGHE; i++){
            for(j=0; j<COLONNE; j++){
                if(matrice[i][j] != 0){
                    fine = false;
                }
            }
        }
        return fine;                        //Restituisco TRUE (quindi gioco vinto) se la matrice è vuota (solo stati "0")
    }

    //Funzione che gestisce la sconfitta
    bool loseGame(int mosseDaBattere){
        bool fine = false;
        if (mosseDaBattere < 1)
        {
            fine = true;
        }
        return fine;                        //Restituisco TRUE (quindi gioco perso) se le mosseDaBattere sono state superate
    }

    //Funzione che inserisce uno riga di "=" per fare ordine a schermo
    void spazio(){
        int i;
        printf("\n");
        for(i=0; i<97; i++){
            printf("=");
        }
        printf("\n");
    }

    //Funzione che inserisce uno spazio e invita l'utente ad attendere la generazione della matrice di gioco
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
        system("clear");
    }

