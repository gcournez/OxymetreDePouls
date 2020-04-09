#include "integration.h"
#include "fichiers.h"
#include "affichage.h"
#include "iir.h"
#include "fir.h"
#include "mesure.h"
#include "lecture.h"


void integrationTest(char* filename)
{
    int etat=0;
    FILE* myFile = initFichier(filename);
    absorp myAbsorp;
    param_fir myFIR ={0};
    param_iir myIIR ={0};
    param_mesure myMes ={0};
    init_iir(&myIIR);// init IIR
    init_fir(&myFIR);//init FIR
    init_mesure(&myMes);//init mesure
    //myAbsorp = lecture(myFile, &etat);
    myAbsorp = lireFichier(myFile, &etat);
    while(etat != EOF){ //Lecture du fichier jusqu'à  End Of File signal
        //printf("ACr = %f, DCr = %f, ACir = %f, DCir= %f \n",myAbsorp.acr, myAbsorp.dcr, myAbsorp.acir, myAbsorp.dcir);
        myAbsorp = fir(myAbsorp,&myFIR);//Passage au filtre fir
        myAbsorp = iir(myAbsorp,&myIIR);//Passage au filtre iir
        mesure(myAbsorp,&myMes);//calcul de SPO2 de des puls du signal
        affichage(myMes.myOxy);//Affichage résultat
        //myAbsorp = lecture(myFile, &etat);
        myAbsorp = lireFichier(myFile, &etat);
        }
    finFichier(myFile);//fermeture du fichier filename
}