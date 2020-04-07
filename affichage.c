#include "affichage.h"

void affichage(oxy myOxy){

    if( access( ".verrouData", F_OK ) == 0 ){ // On teste l'existance de .verrouData
        // Fichier existe
        printf(".verrouData est en cour d'utilisation");
    }
    else{
        // Fichier n'existe pas
        FILE* verrou = fopen(".verrouData","w"); // Création du fichier .verrouData
        fclose(verrou);
        FILE* data = fopen("Data.txt","w"); // On ouvre Data.txt
        fprintf(data,"%d",myOxy.spo2);  // Ecriture de spo2
        fprintf(data,"\n");
        fprintf(data,"%d",myOxy.pouls); // Ecriture de pouls
        fclose(data);
        remove(".verrouData");  // On supprime le fichier .verrouData
    }
}

void affichageTest(){
    oxy myOxy;
    myOxy.spo2=94;
    myOxy.pouls=76;
    affichage(myOxy);
}