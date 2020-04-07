#include "fichiers.h"
#include "iir.h"




absorp iirTest(char* filename){ //absorp est un objet structurÃ©
    absorp exit_FIR_Value; //valeur de ACir, ACr, DCir et DCr en sortie du filtre FIR = entrÃ©e du filtre IRR
    param_iir myIIR;//Strucutre paramÃ¨tre du signal IIR (Coef, et valeur prÃ©cÃ©dentes filtrÃ©es et non filtrÃ©es par IIR)
    init_iir(&myIIR);
    absorp myAbsorp; //Valeur de ACir, ACr, DCir et DCr en sortie du filtre IRR
    int etat=0; //compte le nombre de valaure envoyÃ©es au filtre IRR
    FILE* p_Fichier_exitFIR = initFichier(filename);//Ouverture en lecture du fichier, renvoie un pointeur sur p_Fichier_exitFIIR
    if (p_Fichier_exitFIR != NULL){
        do{
            exit_FIR_Value = lireFichier(p_Fichier_exitFIR, &etat);//Lecture du fichier
            myAbsorp = iir(&exit_FIR_Value, &myIIR);//Autre strucuture ou ajout de champs dans ma strucutre pour les valaurs prÃ©cÃ©dentes );

        }while(etat != EOF);//End Of File
    }
    finFichier( p_Fichier_exitFIR);
    return myAbsorp;
}

absorp iir(absorp* exit_FIR_Value, param_iir* myIIR ){
    absorp myAbsorp = *exit_FIR_Value;
    myAbsorp.acir = (exit_FIR_Value->acir) - (myIIR->precedentValue.acir) + (myIIR->ALPHA)*(myIIR->precedentIIR_Value.acir); //Calcul du filtre
    myAbsorp.acr  = (exit_FIR_Value->acr) - (myIIR->precedentValue.acr) + (myIIR->ALPHA)*(myIIR->precedentIIR_Value.acr); //
    printf("%f",myAbsorp.acr);
    myIIR->precedentValue = *exit_FIR_Value; // La prÃ©cÃ©dente valeur du signal d'entrÃ©e devient l'entrÃ©e actuelle de IRR soit la sortie de FIR
    myIIR->precedentIIR_Value = myAbsorp; // La derniÃ¨re valeur filtrÃ©e devient la valeur filtrÃ©e actuelle (pour le prochain calcul de irr)

    return myAbsorp ;
}

void init_iir(param_iir* myIIR){
    myIIR->ALPHA = 0.992; //Initialisation de la valaur alpha constante
    myIIR->precedentValue.acir = 0 ;//initalisation des valeur "-1" (prÃ©cÃ©dentes)  Ã  0
    myIIR->precedentValue.acr = 0 ;
}