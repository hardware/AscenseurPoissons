#include "vanneattrait.h"

/**
 * @fn VanneAttrait::VanneAttrait(InterfaceCAN *pIcan, Capteurs *pCapteurs, t_coffretPecheur *pCoffretPecheur)
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
VanneAttrait::VanneAttrait(InterfaceCAN *pIcan, Capteurs *pCapteurs, t_coffretPecheur *pCoffretPecheur)
{
    this->pIcan = pIcan;
    this->pCapteurs = pCapteurs;
    this->pCoffretPecheur = pCoffretPecheur;
}

/**
 * @fn void VanneAttrait::ecrireDonnee()
 * @brief Permet de mettre à jour les sorties TOR du coffret pêcheur
 */
void VanneAttrait::ecrireDonnee()
{
    unsigned char dataArray[2];

    dataArray[0] =  pCoffretPecheur->sTor.val & 0xFF;
    dataArray[1] = (pCoffretPecheur->sTor.val >> 8) & 0xFF;

    pIcan->ecrireDonneeCoffretPecheur(dataArray);
}

/**
 * @fn void VanneAttrait::ouvrir()
 * @brief Permet de monter la vanne d'attrait
 */
void VanneAttrait::ouvrir()
{
    pCoffretPecheur->sTor.word_16bits.monteeVanne = 0;
    ecrireDonnee();
}

/**
 * @fn void VanneAttrait::fermer()
 * @brief Permet de descendre la vanne d'attrait
 */
void VanneAttrait::fermer()
{
    pCoffretPecheur->sTor.word_16bits.monteeVanne = 1;
    pCoffretPecheur->sTor.word_16bits.descenteVanne = 0;
    ecrireDonnee();
}
