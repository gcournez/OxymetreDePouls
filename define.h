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
    float alpha;// valaur de alpha dans calcul du filtre
} param_iir;

/*! ------------------------------------------------------------

  \struct param_couleur

  \brief

  ------------------------------------------------------------*/

typedef struct{
    float acMax; // valeur min et max de ac
    float acMin;
    float dcMin; // valeur de cd pour ac min et max
    float dcMax;
    int BPM[5]; // 5 derières valeurs de BPM pour moyenne
    int indice; // indice du tableau circulaire
    float quotient; // valeur du résulat de ptp/dc
    int countEchantillon; // Nombre de point pendant la période
    int etat;

} param_couleur;

/*! ------------------------------------------------------------

  \struct param_mesure

  \brief

  ------------------------------------------------------------*/

typedef struct{
    param_couleur R; //valeurs correspondante au donnée Rouge
    param_couleur IR; //valeurs correspondante au donnée Infra Rouge
    oxy myOxy;

} param_mesure;


#endif // DEFINE_H
