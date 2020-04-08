#include "mesure.h"
#include "fichiers.h"

oxy mesureTest(char* filename){
    absorp	myAbsorp; // input de la mesure
    int etat=0;
  FILE* p_Fichier=initFichier(filename); //Ouverture du fichier
  param_mesure myMes;
  init_mesure(&myMes);// création et innitialisation de myMes

  myAbsorp=lireFichier(p_Fichier, &etat); // lecture première ligne
  while (etat!= EOF) {
      mesure(myAbsorp, &myMes); // mesure
      myAbsorp=lireFichier(p_Fichier, &etat); // lecture ligne suivante
  }
    finFichier(p_Fichier);
    return myMes.myOxy; // On retourne la derière ligne filtrée sans risquer de retourner une erreur de lecture

}

void mesure(absorp myAbsorp,param_mesure* myMes){

    int newPeriodR = machineEtat(myAbsorp.acr,myAbsorp.dcr,&myMes->R); // mesure perriode et pic to pic de acR
    int newPeriodIR = machineEtat(myAbsorp.acir,myAbsorp.dcir,&myMes->IR); // mesure perriode et pic to pic de acIR
    if (newPeriodR || newPeriodIR){ // si une des deux période est fini
        float RsIR= myMes->R.quotient/myMes->IR.quotient; // On calcul le rapport des quotients
        if (RsIR<1){ // table de correspondance entre RSIR etSpO2 deux fonctions affines avec intersection en 1
            myMes->myOxy.spo2= -25*RsIR+110;
        } else{
            myMes->myOxy.spo2=-35.4*RsIR+120.4;
        }
        int i,BPM_R=0,BPM_IR=0;
        for ( i = 0; i < 5; ++i) {
            BPM_R+=myMes->R.BPM[i]; // somme des 5 dernières valeurs de BPM
            BPM_IR+=myMes->IR.BPM[i];
        }
        myMes->myOxy.pouls=(BPM_IR+BPM_R)/10; // La sortie est la moyenne des fréquence mesuré avec le signal acr et acir
    }
}

int machineEtat(float acValue,float dcValue, param_couleur* couleur){  // une même machine d'état est utilisé deux fois pour les calculs des couleurs Rouge et InfraRouge
    int newPeriod=0; // permet de savoir
    switch (couleur->etat){ // Les deux premiers états de la machines d'état permettent de commencer la première période au bon moment
        case 1:
            if (acValue > 0){
                couleur->etat=2;
            }
            break;
        case 2:
            if (acValue < 0){
                couleur->etat=3;
                couleur->countEchantillon=1;
            }
            break;
        case 3:
            couleur->countEchantillon++; // j'incremente le compteur tant que l'on as pas atteint 0
            if (acValue < couleur->acMin){ // je récupère les valeurs ac et dc du minimum
                couleur->acMin=acValue;
                couleur->dcMin=dcValue;
            }
            if (acValue > 0){
                couleur->BPM[couleur->indice]= 30000 / couleur->countEchantillon;
                couleur->indice=(couleur->indice+1)%5; // indice de mon tableau varie entre 0 et 5
                couleur->quotient= 2 * (couleur->acMax - couleur->acMin) / (couleur->dcMax + couleur->dcMin); //Calcul du quotient PtP/Dc avec comme valeur de dc la moyenne des dc pour les valeurs de ac min et max
                couleur->acMax=0;  // réinitialisation des min et max à 0
                couleur->dcMax=0;
                couleur->acMin=0;
                couleur->dcMin=0;
                newPeriod=1;
                couleur->countEchantillon=0;
                couleur->etat=4;
            }
            break;
        case 4:
            couleur->countEchantillon++; // j'incremente le compteur tant que l'on as pas atteint la valeur barrière basse
            if (acValue > couleur->acMax){// je récupère les valeurs ac et dc du maximum
                couleur->acMax=acValue;
                couleur->dcMax=dcValue;
            }
            if (acValue < 0){
                couleur->etat=3; // On reboucle sur l'état 3
            }
            break;

        default:
            printf("dans mesure.c : erreur valeur du switch: etat= %d\n",couleur->etat);
            exit(EXIT_FAILURE);
            break;
    }
    return newPeriod;
}

void init_mesure(param_mesure* myMes){
    absorp initMinMax={0,0,0,0};
    oxy initOxy={60,95};

    init_couleur(&myMes->R);
    init_couleur(&myMes->IR);
    myMes->myOxy=initOxy;
}

void init_couleur(param_couleur* couleur){
    couleur->etat=1;
    couleur->countEchantillon=0;
    couleur->acMax=0;
    couleur->acMin=0;
    couleur->quotient=1;
    couleur->indice=0;
    int i;
    for ( i = 0; i < 5; ++i) {
        couleur->BPM[i]=95; // le tableau des 5 derniers BPM est initialisé à 95
    }
}



