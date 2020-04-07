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
    return 0;
}