#include "cageascenseur.h"

/**
 * @fn CageAscenseur::CageAscenseur(InterfaceCAN *pIcan, Capteurs *pCapteurs)
 * @brief Constructeur paramétré
 *
 * Initialisation des 3 attributs permettant d'intéragir
 * avec la carte d'interface CAN, les capteurs et le coffret
 * pêcheur.
 *
 * @param pIcan[in] Pointeur sur l'instance de l'interface CAN
 * @param pCapteurs[in] Pointeur sur l'instance de la classe Capteurs
 * @param pCoffretPecheur[in] Pointeur sur un champ de bits de type t_coffretPecheur
 */
CageAscenseur::CageAscenseur(InterfaceCAN *pIcan, Capteurs *pCapteurs, t_coffretPecheur *pCoffretPecheur)
{
    this->pIcan = pIcan;
    this->pCapteurs = pCapteurs;
    this->pCoffretPecheur = pCoffretPecheur;
}

/**
 * @fn void CageAscenseur::monter()
 * @brief Permet de faire monter la cage
 */
void CageAscenseur::monter()
{

}

/**
 * @fn void CageAscenseur::descendre()
 * @brief Permet de faire descendre la cage
 */
void CageAscenseur::descendre()
{

}
