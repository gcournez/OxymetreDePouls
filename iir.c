#include "fichiers.h"
#include "iir.h"




absorp iirTest(char* filename){ //absorp est un objet structuré
    absorp exit_FIR_Value; //valeur de ACir, ACr, DCir et DCr en sortie du filtre FIR = entrée du filtre IRR
    param_iir myIIR;//Strucutre paramètre du signal IIR (Coef, et valeur précédentes filtrées et non filtrées par IIR)
    init_iir(&myIIR);
    absorp myAbsorp; //Valeur de ACir, ACr, DCir et DCr en sortie du filtre IRR

    int etat=0; //compte le nombre de valaure envoyées au filtre IRR
    FILE* p_Fichier_exitFIR = initFichier(filename);//Ouverture en lecture du fichier, renvoie un pointeur sur p_Fichier_exitFIIR
    exit_FIR_Value = lireFichier(p_Fichier_exitFIR, &etat);

    while(etat != EOF){
        myAbsorp = iir(exit_FIR_Value, &myIIR); // Calcul filtre
        exit_FIR_Value = lireFichier(p_Fichier_exitFIR, &etat);//Lecture du fichier
    }

    finFichier( p_Fichier_exitFIR);
    return myAbsorp;

}

absorp iir(absorp exit_FIR_Value, param_iir* myIIR ){

    absorp myAbsorp=exit_FIR_Value;

    myAbsorp.acir =  (exit_FIR_Value.acir)  - (myIIR->precedentValue.acir) + (myIIR->ALPHA)* (myIIR->precedentIIR_Value.acir); //Calcul du filtre
    myAbsorp.acr = ((exit_FIR_Value.acr) - (myIIR->precedentValue.acr) + (myIIR->ALPHA) * (myIIR->precedentIIR_Value.acr));

    myIIR->precedentValue = exit_FIR_Value; // La précédente valeur du signal d'entrée devient l'entrée actuelle de IRR soit la sortie de FIR
    myIIR->precedentIIR_Value = myAbsorp; // La dernière valeur filtrée devient la valeur filtrée actuelle (pour le prochain calcul de irr)

    return myAbsorp ;
}

void init_iir(param_iir* myIIR){
    myIIR->ALPHA =  0.992; //Initialisation de la valaur alpha constante
    myIIR->precedentValue.acir = 0 ;//initalisation des valeur "-1" (précédentes)  à  0
    myIIR->precedentValue.acr = 0 ;
}