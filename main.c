#include <stdio.h>
#include "iir.h"
#include "fir.h"
#include "fichiers.h"
#include "define.h"
#include "affichage.h"


int main() {
    chdir(".."); // positionnement dans le bon repertoire courant

    absorp myAbsorp = firTest("record_file/record1.dat");
    printf("acr=%f   acir=%f\n",myAbsorp.acr,myAbsorp.acir);
    myAbsorp=iirTest("record_file/record1_fir.dat");
    printf("acr=%f   acir=%f\n",myAbsorp.acr,myAbsorp.acir);


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