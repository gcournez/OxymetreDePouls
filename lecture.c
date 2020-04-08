#include "lecture.h"
#include "fichiers.h"
#include <string.h>

absorp lecture(FILE* file_pf,  int* file_state){// poiteur à mon fichier et pointeur à l'état de mon fichier

    absorp myAbsorp={0};
    char actualCaractere = 0;
    int i =0; //indice
    float tramDataStr[21]; //Tableau pour stocker chaque caractère de la tram, taille d'une tram = 21 caratèrere


    if(file_pf == NULL) { //vérification du le fichier est bien lu
        *file_state = EOF; // fin de fichier
        printf("Pas de fichier en entrée de lecture");//Affiche une erreur de lecture de fichier
    }else{
        while (*file_state != EOF){ // boucle pour traverser tout le fichier.
            while (i<21){ //boucle pour obetenir les 21 caractères de la tram
                actualCaractere = (char)fgetc(file_pf); //lecture caractère par caractère
                printf("%c",actualCaractere); //test print values

                tramDataStr[i]= atof(actualCaractere);//remplir la tram dans le tableau

                printf("%f",tramDataStr[i]);

                if (strcmp("\n", &actualCaractere) == 0){ //si on arrive à la fin de la ligne
                    *file_state+=21; //nombre
                    i=21;
                }else if (actualCaractere == EOF){ //arrivée au dernie caractère
                    *file_state = EOF; //fin de fichier

                }

                i+=1;
            }

            i=0;

            myAbsorp.acr =tramDataStr[0] *1000 + tramDataStr[1] * 100 + tramDataStr[2] * 10 + tramDataStr[3];
            myAbsorp.dcr =tramDataStr[0] *1000 + tramDataStr[1] * 100 + tramDataStr[2] * 10 + tramDataStr[3];
            myAbsorp.acir = tramDataStr[0] *1000 + tramDataStr[1] * 100 + tramDataStr[2] * 10 + tramDataStr[3];
            myAbsorp.dcir = tramDataStr[0] *1000 + tramDataStr[1] * 100 + tramDataStr[2] * 10 + tramDataStr[3];

            myAbsorp.acir -=2048 ; //Centrer acir en 0 car avant elles ocillaient entre 0 et 4096
            myAbsorp.acr -= 2048 ;//centrer acr en 0


        }
    finFichier(file_pf);
    }



	return myAbsorp; // return EOF flag

}

