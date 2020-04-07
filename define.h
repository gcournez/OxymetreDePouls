#ifndef DEFINE_H
#define DEFINE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


/*! ------------------------------------------------------------
  
  \struct absorp
 
  \brief measures
  
  ------------------------------------------------------------*/

typedef struct {
    float acr;  /*!< AC R */
    float dcr;  /*!< DC R */
    float acir;  /*!< AC IR */
    float dcir;  /*!< DC IR */
    } absorp;


/*! ------------------------------------------------------------
  
  \struct oxy
 
  \brief   
  
  ------------------------------------------------------------*/

typedef struct{
    int spo2;  /*!< SPO2 */
	int pouls;  /*!< Pouls */
	} oxy;

/*! ------------------------------------------------------------

  \struct param_fir

  \brief

  ------------------------------------------------------------*/
typedef struct{
    float factor[51];  // les coefficients
    absorp prev[51];   // Les 51 dernières valeurs
    int curent;        // indice de la dernière valeur
    int first;         // indice de la plus anciène valeur
    }param_fir;

/*! ------------------------------------------------------------

  \struct param_iir

  \brief

  ------------------------------------------------------------*/

typedef struct{
    absorp precedentValue; //champ pour la valaur précédente de iir pendant le calcul du filtrage.
    absorp precedentIIR_Value; //chcamp pour y(n-1) la valeur précédement filtrée.
    float ALPHA;
} param_iir;

#endif // DEFINE_H
