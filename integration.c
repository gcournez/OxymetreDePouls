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
    param_fir myFIR ={0};//initialisation de param_fir
    param_iir myIIR ={0};//initialisation de param_iir
    param_mesure myMes ={0};//initialisation de mesure
    init_iir(&myIIR);// init IIR
    init_fir(&myFIR);//init FIR
    init_mesure(&myMes);//init mesure
    //myAbsorp = lecture(myFile, &etat); //décommenter ligne  pour utiliser la fonction lecture
    myAbsorp = lireFichier(myFile, &etat);// commenter  cette ligne pour utiliser la fonction lecture

    while(etat != EOF){ //Lecture du fichier jusqu'à  End Of File signal

        myAbsorp = fir(myAbsorp,&myFIR);//Passage au filtre fir
        myAbsorp = iir(myAbsorp,&myIIR);//Passage au filtre iir
        mesure(myAbsorp,&myMes);//calcul de SPO2 de des puls du signal
        affichage(myMes.myOxy);//Affichage résultat
        //myAbsorp = lecture(myFile, &etat);//décommenter ligne  pour utiliser la fonction lecture
        myAbsorp = lireFichier(myFile, &etat);// commenter  cette ligne pour utiliser la fonction lecture
        //printf("ACr = %f, DCr = %f, ACir = %f, DCir= %f \n",myAbsorp.acr, myAbsorp.dcr, myAbsorp.acir, myAbsorp.dcir);

        }
    finFichier(myFile);//fermeture du fichier filename
}