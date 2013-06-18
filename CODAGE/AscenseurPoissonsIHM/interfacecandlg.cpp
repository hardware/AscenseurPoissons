#include "interfacecandlg.h"

InterfaceCANDlg::InterfaceCANDlg(InterfaceCAN *pIcan)
{
    this->pIcan = pIcan;

    bool err = false;

    // Procédure de configuration et de mise en service de la carte CAN
    try {
        // Ouverture du canal 0
        pIcan->ouvrirCanal(0);

        // Initialisation des paramètres du contrôleur de protocole CAN
        pIcan->initialiserControleur();

        // Initialisation de l'interface CAN en mode BUFFER
        pIcan->initialiserModeFonctionnement();

        // Initialisation des paramètres de l'évènement du buffer global
        pIcan->initialiserEvenementGlobal();

        // Initialisation des identificateurs CAN et des évènements associés

        // Trame TxPDO1 | COB-ID = 0x190 | 3 octets
        pIcan->initialiserIdentificateur(_CAN_RX_DATA, _ENTREESTOR_COFFRET_ID);
        pIcan->initialiserEvenement(_ENTREESTOR_COFFRET_ID);

        // Trame TxPDO2 | COB-ID = 0x290 | 2 mots
        pIcan->initialiserIdentificateur(_CAN_RX_DATA, _CAPTEURS_COFFRET_ID);
        pIcan->initialiserEvenement(_CAPTEURS_COFFRET_ID);

        // Trame TxPDO1 | COB-ID = 0x200 | 3 octets
        pIcan->initialiserIdentificateur(_CAN_RX_DATA, _ENTREESTOR_SOMMET_ID);
        pIcan->initialiserEvenement(_ENTREESTOR_SOMMET_ID);

        // Trame RxPDO1 | COB-ID = 0x210 | 2 octets
        pIcan->initialiserIdentificateur(_CAN_TX_DATA, _SORTIESTOR_COFFRET_ID, 2);

        // Trame RxPDO1 | COB-ID = 0x220 | 1 octet
        pIcan->initialiserIdentificateur(_CAN_TX_DATA, _SORTIESTOR_SOMMET_ID, 1);

        // Initialisation du masque de réception
        pIcan->initialiserMasque();

        // Démarrage du contrôleur de protocole CAN
        pIcan->demarrerControleur();

        // Création des 4 threads de l'application
        pIcan->demarrerThread();
    }
    catch(const std::string &e)
    {
        err = true;

        journal.ajouterLog("Une erreur est survenue lors de la mise en service de la carte : " + QString::fromUtf8(e.c_str()), CRITICAL);
    }

    if(!err)
        journal.ajouterLog("L'interface CAN a été mise en service", INFO);
}
