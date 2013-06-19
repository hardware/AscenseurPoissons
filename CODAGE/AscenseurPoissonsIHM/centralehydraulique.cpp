#include "centralehydraulique.h"

/**
 * @fn CentraleHydraulique::CentraleHydraulique(InterfaceCAN *pIcan, Capteurs *pCapteurs, t_coffretPecheur *pCoffretPecheur)
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
CentraleHydraulique::CentraleHydraulique(InterfaceCAN *pIcan, Capteurs *pCapteurs, t_coffretPecheur *pCoffretPecheur)
{
    this->pIcan = pIcan;
    this->pCapteurs = pCapteurs;
    this->pCoffretPecheur = pCoffretPecheur;
}

/**
 * @fn void CentraleHydraulique::ecrireDonnee()
 * @brief Permet de mettre à jour les sorties TOR du coffret pêcheur
 */
void CentraleHydraulique::ecrireDonnee()
{
    unsigned char dataArray[2];

    dataArray[0] =  pCoffretPecheur->sTor.val & 0xFF;
    dataArray[1] = (pCoffretPecheur->sTor.val >> 8) & 0xFF;

    pIcan->ecrireDonneeCoffretPecheur(dataArray);
}

/**
 * @fn void CentraleHydraulique::demarrer()
 * @brief Permet de démarrer la centrale hydraulique
 */
void CentraleHydraulique::demarrer()
{
    pCoffretPecheur->sTor.word_16bits.marcheCentraleHydralique = 0;
    ecrireDonnee();
}

/**
 * @fn void CentraleHydraulique::arreter()
 * @brief Permet d'arrêter la centrale hydraulique
 */
void CentraleHydraulique::arreter()
{
    pCoffretPecheur->sTor.word_16bits.marcheCentraleHydralique = 1;
    ecrireDonnee();
}
