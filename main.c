#include <stdio.h>
#include "iir.h"
#include "fir.h"
#include "fichiers.h"
#include "define.h"
#include "affichage.h"


int main() {
    chdir(".."); // positionnement dans le bon repertoire courant

    absorp myAbsorp = firTest("record_file/record1.dat");
    myAbsorp=iirTest("record_file/record1_fir.dat");



    /*
   * Filtre IIR
   */
    absorp OldAbsorp;
    absorp MyNewAbsorp;
    OldAbsorp.acir=3;
    OldAbsorp.acr=5;

    param_iir myIIR;
    init_iir(&myIIR);

    MyNewAbsorp = iir(&OldAbsorp, &myIIR);
    printf("OldAbsorb acir = %f , OldAbsorb acr = %f \n", OldAbsorp.acir, OldAbsorp.acr);
    printf("MyNewAbsorp acir = %f , MyNewAbsorp acr = %f \n", MyNewAbsorp.acir, MyNewAbsorp.acr);


    return 0;
}