#include "lecture.h"
#include "fichiers.h"
#include <string.h>

absorp lecture(FILE* file_pf,  int* file_state){// poiteur à mon fichier et pointeur à l'état de mon fichier

    absorp myAbsorp={0};
    char actualCaractere = 0;
    int i =0; //indice
    char tramDataStr[21]; //Tableau pour stocker chaque caractère de la tram, taille d'une tram = 21 caratèrere


    if(file_pf == NULL) { //vérification que le fichier est bien lu
        *file_state = EOF; // fin de fichier
        printf("Pas de fichier en entrée de lecture");//Affiche une erreur de lecture de fichier
    }else{
        while (*file_state != EOF){ // boucle pour traverser tout le fichier.
            while (i<21){ //boucle pour obetenir les 21 caractères de la tram
                actualCaractere = (char)fgetc(file_pf); //lecture caractère par caractère
                //printf("%c",actualCaractere); //test print values





                if (strcmp("\r", &actualCaractere) == 0) { //si on arrive à la fin de la ligne
                    //actualCaractere = (char)fgetc(file_pf); //passage à la ligne suivante
                    *file_state += 21; // le nombre de trame en faisant file_state%21
                    i = 21;

                }
                if(actualCaractere == EOF){ //arrivée au dernie caractère
                    *file_state = EOF; //fin de fichier
                }else{
                    tramDataStr[i]= (actualCaractere);//remplir la tram dans le tableau
                }
                i+=1;//incrémentation
            }
            i=0;//Revenir au début du tableau


            /*          Exemple format de du tabelau tramDatastr
             *     ____________________________________________________________________________________
             *    [     ACr      | , |       DCr     | , |      ACir     | , |   DCir       | LF | RC ]
             *    [2 | 0 | 8 | 5 | , | 2 | 0 | 3 | 0 | , | 2 | 0 | 2 | 7 | , | 2 | 0 | 3 | 0 |   |    ] = tramDataStr
             *    [32| 30| 38| 35| 2C| 32| 30| 33| 30| 2C| 32| 30| 33| 37| 2C| 32| 30| 33| 30|   |    ]
             *
            */
            //-48 pour passer de ASCII à un nombre entier.
            myAbsorp.acr = (float)((tramDataStr[0]-48)*1000 + (tramDataStr[1]-48)*100 + (tramDataStr[2]-48) * 10 + (tramDataStr[3]-48));
            myAbsorp.dcr = (float)((tramDataStr[5]-48)*1000 + (tramDataStr[6]-48)*100 + (tramDataStr[7]-48) * 10 + tramDataStr[8]-48);
            myAbsorp.acir =(float)((tramDataStr[10]-48) *1000 + (tramDataStr[11]-48) * 100 + (tramDataStr[12]-48) * 10 +( tramDataStr[13]-48));
            myAbsorp.dcir =(float)(( tramDataStr[15] -48)*1000 + (tramDataStr[16]-48) * 100 + (tramDataStr[17]-48) * 10 +( tramDataStr[18]-48));

            myAbsorp.acir -=2048 ; //Centrer acir en 0 car avant elles ocillaient entre 0 et 4096
            myAbsorp.acr -= 2048 ;//centrer acr en 0

            //printf("ACr = %f, DCr = %f, ACir = %f, DCir= %f \n",myAbsorp.acr, myAbsorp.dcr, myAbsorp.acir, myAbsorp.dcir);


        }
    finFichier(file_pf);
    }


	return myAbsorp; // return EOF flag

}

