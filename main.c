#include <stdio.h>
#include "iir.h"
#include "fir.h"
#include "fichiers.h"
#include "define.h"
#include "affichage.h"
#include "mesure.h"
#include "integration.h"
#include "lecture.h"


int main() {
    chdir(".."); // positionnement dans le bon repertoire courant



    //Lecture test
    int file_state = 0;
    absorp test;
    FILE* fichier = NULL;
    FILE*  file_pf =initFichier("record_file/record1_bin.dat");
    test=lecture(file_pf,&file_state);


   /*
    absorp myAbsorp = firTest("record_file/record1.dat");
    printf("acr=%f   acir=%f\n",myAbsorp.acr,myAbsorp.acir);
    myAbsorp=iirTest("record_file/record1_fir.dat");
    printf("acr=%f   acir=%f\n",myAbsorp.acr,myAbsorp.acir);




    oxy myOxy = mesureTest("record_file/record1_fir.dat");
    printf("oxy=%d   pouls=%d\n",myOxy.spo2,myOxy.pouls);


    */

    /*
   * Filtre IIR

    absorp OldAbsorp;
    absorp MyNewAbsorp;
    OldAbsorp.acir=250;
    OldAbsorp.acr=300;

    param_iir myIIR = {0}; //essaie d'initalisation en mettant à 0
    init_iir(&myIIR);
    MyNewAbsorp = iir(OldAbsorp, &myIIR);
    printf("OldAbsorp acir = %f , OldAbsorb acr = %f \n", OldAbsorp.acir, OldAbsorp.acr);
    printf("MynewAbsorp cir = %f , MyNewAbsorp acr = %f \n", MyNewAbsorp.acir, MyNewAbsorp.acr);
    */

    return 0;
}