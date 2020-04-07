#include "fir.h"
#include "fichiers.h"

absorp firTest(char* filename){
	absorp	myAbsorpInput,myAbsorpOutput; // input et output du filtre
	int etat=0;
	FILE* p_Fichier=initFichier(filename); //Ouverture du fichier
	param_fir myFIR;
	init_fir(&myFIR);// création et innitialisation de myFIR
    myAbsorpInput=lireFichier(p_Fichier, &etat); // lecture première ligne

	while (etat!= EOF) {
        myAbsorpOutput=fir(myAbsorpInput, &myFIR); // filtrage
        myAbsorpInput=lireFichier(p_Fichier, &etat); // lecture ligne suivante
    }
	finFichier(p_Fichier);
	return myAbsorpOutput; // On retourne la derière ligne filtrée sans risquer de retourner une erreur de lecture
}

absorp fir(absorp myAbsorp, param_fir* myFIR){
    int indexPrev=myFIR->curent, indexFactor =50 ,end=0;
    float sommeR=0,sommeIR=0;
    myFIR->prev[indexPrev]=myAbsorp;
    while (!end){
        sommeR  += myFIR->prev[indexPrev] .acr * myFIR->factor[indexFactor]; // Calcul somme pondéré R
        sommeIR += myFIR->prev[indexPrev] .acir * myFIR->factor[indexFactor]; // Calcul somme pondéré IR

        indexFactor--;
        if (indexPrev == myFIR->first){
            end=1; // Condition d'arret
        }
        else{ // tableau en boucle
            if (indexPrev == 0){
                indexPrev=50;
            }
            else{
                indexPrev--;
            }
        }
    }

    myAbsorp.acir= sommeIR; //résultat du filtre
    myAbsorp.acr= sommeR;

    // gestion tableau circulaire
    if (myFIR->first==50){
        myFIR->curent++;
        myFIR->first=0;
    }
    else if (myFIR->curent==50){
        myFIR->curent=0;
        myFIR->first++;
    }
    else if (myFIR->first!=0){
        myFIR->first++;
        myFIR->curent++;
    }
    else{
        myFIR->curent++;
    }

    return myAbsorp;
}


void init_fir(param_fir* myFIR){
    float FIR_TAPS[51]={ // Déclaration des coefficients
            1.4774946e-019,
            1.6465231e-004,
            3.8503956e-004,
            7.0848037e-004,
            1.1840522e-003,
            1.8598621e-003,
            2.7802151e-003,
            3.9828263e-003,
            5.4962252e-003,
            7.3374938e-003,
            9.5104679e-003,
            1.2004510e-002,
            1.4793934e-002,
            1.7838135e-002,
            2.1082435e-002,
            2.4459630e-002,
            2.7892178e-002,
            3.1294938e-002,
            3.4578348e-002,
            3.7651889e-002,
            4.0427695e-002,
            4.2824111e-002,
            4.4769071e-002,
            4.6203098e-002,
            4.7081811e-002,
            4.7377805e-002,
            4.7081811e-002,
            4.6203098e-002,
            4.4769071e-002,
            4.2824111e-002,
            4.0427695e-002,
            3.7651889e-002,
            3.4578348e-002,
            3.1294938e-002,
            2.7892178e-002,
            2.4459630e-002,
            2.1082435e-002,
            1.7838135e-002,
            1.4793934e-002,
            1.2004510e-002,
            9.5104679e-003,
            7.3374938e-003,
            5.4962252e-003,
            3.9828263e-003,
            2.7802151e-003,
            1.8598621e-003,
            1.1840522e-003,
            7.0848037e-004,
            3.8503956e-004,
            1.6465231e-004,
            1.4774946e-019
    };

    for (int i = 0; i < 51; ++i) {
        myFIR->factor[i]=FIR_TAPS[i]; // recopie des coefficient dans la structure
    }
    myFIR->curent=0;
    myFIR->first=0;
}