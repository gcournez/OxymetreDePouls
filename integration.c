#include "integration.h"
#include "fichiers.h"
#include "affichage.h"
#include "iir.h"
#include "fir.h"


void integrationTest(char* filename)
{
    int etat=0;
    FILE* myFile = initFichier(filename);
    absorp myAbsorp;
    oxy myOxy_result ={0};
    param_fir myFIR ;
    param_iir myIIR ;
    //param_mesure* myMes ;
    init_iir(&myIIR);// init IIR
    init_fir(&myFIR);//init FIR
    //init_mesure(myMes);//init mesure

    while(etat != EOF){ //Lecture du fichier jusqu'à  End Of File signal
        myAbsorp = lireFichier(myFile, &etat);
        myAbsorp = fir(myAbsorp,&myFIR);//Passage au filtre fir
        myAbsorp = iir(myAbsorp,&myIIR);//Passage au filtre iir
        //myOxy_result = mesure(myAbsorp,myMes);//calcul de SPO2 de des puls du signal
        affichage(myOxy_result);//Affichage résultat
        }
    finFichier(myFile);//fermeture du fichier filename
}