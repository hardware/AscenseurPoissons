#include "grille.h"

/**
 * @fn Grille::Grille(InterfaceCAN *pIcan, Capteurs *pCapteurs, t_coffretPecheur *pCoffretPecheur)
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
Grille::Grille(InterfaceCAN *pIcan, Capteurs *pCapteurs, t_coffretPecheur *pCoffretPecheur)
{
    this->pIcan = pIcan;
    this->pCapteurs = pCapteurs;
    this->pCoffretPecheur = pCoffretPecheur;
}

/**
 * @fn void Grille::ouvrir()
 * @brief Permet d'ouvrir la grille
 */
void Grille::ouvrir()
{

}

/**
 * @fn void Grille::fermer()
 * @brief Permet de fermer la grille
 */
void Grille::fermer()
{

}
