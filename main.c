#include <stdio.h>
#include "iir.h"
#include "fir.h"
#include "define.h"
#include "affichage.h"
#include "mesure.h"
#include "lecture.h"
#include "fichiers.h"
#include "integration.h"


int main() {

    //chdir(".."); // positionnement dans le bon repertoire courant
    integrationTest("record_file/record1.dat");
    //integrationTest("record_file/record1_bin.dat");

    return 0;
}