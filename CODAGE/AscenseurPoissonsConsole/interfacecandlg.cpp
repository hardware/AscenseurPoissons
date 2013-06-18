#include "interfacecandlg.h"

InterfaceCANDlg::InterfaceCANDlg()
{
    // Initialisation du champ de bits (tous les bits à 1)
    coffretPecheur.sTor.val         = 0xFFFF;
    coffretPecheur.eTor.val         = 0xFFFFFF;
    coffretPecheur.eAnalogique.val  = 0xFFFFFFFF;
    sommetAscenseur.sTor.val        = 0xFF;
    sommetAscenseur.eTor.val        = 0xFFFFFF;
}

void InterfaceCANDlg::run()
{
    int choix, quitter = 0;
    short canal, nbCanaux = 0, choixEntreesTor = -1;
    bool err;

    cout << "-----------------------------------------------------------------------" << endl;
    cout << "## PROGRAMME PERMETTANT DE CONFIGURER ET D UTILISER LA CARTE CAN NSI ##" << endl;
    cout << "-----------------------------------------------------------------------" << endl;

    while(quitter == 0)
    {
        cout << endl << endl;
        cout << " [1] Ouvrir un canal" << endl;
        cout << " [2] Fermer le canal" << endl;
        cout << " [3] Afficher les informations du peripherique" << endl;
        cout << " [4] Initialiser le controleur CAN (debit et echantillonnage)" << endl;
        cout << " [5] Initialiser le mode de fonctionnement (mode BUFFER)" << endl;
        cout << " [6] Initialiser les trames" << endl;
        cout << " [7] Initialiser le masque de reception" << endl;
        cout << " [8] Demarrer le controleur CAN" << endl;
        cout << " [9] Arreter le controleur CAN" << endl;
        cout << "[10] Envoyer une trame au sommet ascenseur" << endl;
        cout << "[11] Envoyer une trame au coffret pecheur" << endl;
        cout << "[12] Lire les valeurs des entrees analogiques" << endl;
        cout << "[13] Lire les valeurs des entrees TOR" << endl;
        cout << "[14] Activer la reception des trames" << endl;
        cout << "[15] Quitter\n\n";

        cout << "Choisir une action : ";
        cin >> choix;
        cout << endl;

        switch(choix)
        {
        case 1:
            err = false;

            try
            {
                cout << "Liste des canaux disponibles : " << endl;
                nbCanaux = iCan.listeCanaux();

                cout << "Quel canal voulez-vous utiliser ? (0-" << nbCanaux - 1 << ") ";
                cin >> canal;
                cout << endl;

                if(canal >= 0 && canal < nbCanaux)
                {
                    iCan.ouvrirCanal(canal);
                }
            }
            catch(const std::string &e)
            {
                err = true;
                cout << "(!!) Une erreur est survenue ---> " << e;
            }

            if(!err)
                cout << "--> [OK] Le canal " << canal << " a bien ete ouvert !" << endl;

            break;
        case 2:
            err = false;

            try {
                iCan.fermerCanal();
            }
            catch(const std::string &e)
            {
                err = true;
                cout << "(!!) Une erreur est survenue ---> " << e;
            }

            if(!err)
                cout << "--> [OK] Le canal a bien ete ferme !" << endl;

            break;
        case 3:
            try {
                cout << "INFORMATIONS SUR LE PERIPHERIQUE : " << endl;
                iCan.getInfos();
            }
            catch(const std::string &e)
            {
                cout << "(!!) Une erreur est survenue ---> " << e;
            }

            break;
        case 4:
            err = false;

            try {
                cout << "PARAMETRES DU BUS : " << endl;
                iCan.initialiserControleur();
            }
            catch(const std::string &e)
            {
                err = true;
                cout << "(!!) Une erreur est survenue ---> " << e;
            }

            if(!err)
                cout << "\n--> [OK] Le controleur CAN a bien ete configure !" << endl;

            break;
        case 5:
            err = false;

            try {
                iCan.initialiserModeFonctionnement();
            }
            catch(const std::string &e)
            {
                err = true;
                cout << "(!!) Une erreur est survenue ---> " << e;
            }

            if(!err)
                cout << "\n--> [OK] Le controleur a ete initialise en mode BUFFER !" << endl;

            break;
        case 6:
            err = false;

            try {
                iCan.initialiserEvenementGlobal();

                // Trame TxPDO1 | COB-ID = 0x190 | 3 octets
                iCan.initialiserIdentificateur(_CAN_RX_DATA, _ENTREESTOR_COFFRET_ID);
                iCan.initialiserEvenement(_ENTREESTOR_COFFRET_ID);

                // Trame TxPDO2 | COB-ID = 0x290 | 2 mots
                iCan.initialiserIdentificateur(_CAN_RX_DATA, _CAPTEURS_COFFRET_ID);
                iCan.initialiserEvenement(_CAPTEURS_COFFRET_ID);

                // Trame TxPDO1 | COB-ID = 0x200 | 3 octets
                iCan.initialiserIdentificateur(_CAN_RX_DATA, _ENTREESTOR_SOMMET_ID);
                iCan.initialiserEvenement(_ENTREESTOR_SOMMET_ID);

                // Trame RxPDO1 | COB-ID = 0x210 | 2 octets
                iCan.initialiserIdentificateur(_CAN_TX_DATA, _SORTIESTOR_COFFRET_ID, 2);

                // Trame RxPDO1 | COB-ID = 0x220 | 1 octet
                iCan.initialiserIdentificateur(_CAN_TX_DATA, _SORTIESTOR_SOMMET_ID, 1);
            }
            catch(const std::string &e)
            {
                err = true;
                cout << "(!!) Une erreur est survenue ---> " << e;
            }

            if(!err)
                cout << "\n--> [OK] Les trames ont bien ete initialisees !" << endl;

            break;
        case 7:
            err = false;

            try {
                iCan.initialiserMasque();
            }
            catch(const std::string &e)
            {
                err = true;
                cout << "(!!) Une erreur est survenue ---> " << e;
            }

            if(!err)
                cout << "\n--> [OK] Le masque de reception a ete initialise !" << endl;

            break;
        case 8:
            err = false;

            try {
                iCan.demarrerControleur();
            }
            catch(const std::string &e)
            {
                err = true;
                cout << "(!!) Une erreur est survenue ---> " << e;
            }

            if(!err)
                cout << "\n--> [OK] Le controleur a ete demarre !" << endl;

            break;
        case 9:
            err = false;

            try {
                iCan.arreterControleur();
            }
            catch(const std::string &e)
            {
                err = true;
                cout << "(!!) Une erreur est survenue ---> " << e;
            }

            if(!err)
                cout << "\n--> [OK] Le controleur a ete arrete !" << endl;

            break;
        case 10:
            err = false;

            try {
                sommetAscenseur.sTor.byte_8bits.defautGeneral = 0;

                UCHAR data = sommetAscenseur.sTor.val;

                iCan.ecrireDonneeSommetAscenseur(data);
            }
            catch(const std::string &e)
            {
                err = true;
                cout << "(!!) Une erreur est survenue ---> " << e;
            }

            if(!err)
                cout << "\n--> [OK] Les donnees du sommet ascenseur ont ete mises a jour" << endl;

            break;
        case 11:
            err = false;

            try {
                coffretPecheur.sTor.word_16bits.monteeGrille = 0;

                UCHAR data = coffretPecheur.sTor.val;

                iCan.ecrireDonneeCoffretPecheur(data);
            }
            catch(const std::string &e)
            {
                err = true;
                cout << "(!!) Une erreur est survenue ---> " << e;
            }

            if(!err)
                cout << "\n--> [OK] Les donnees du coffret pecheur ont ete mises a jour" << endl;

            break;
        case 12:
            try {
                iCan.lireValeur();
            }
            catch(const std::string &e)
            {
                cout << "(!!) Une erreur est survenue ---> " << e;
            }

            break;
        case 13:
            try {
            cout << "Lecture des entrees TOR (Coffret pecheur [0] | Sommet ascenseur [1]) : ";
            cin >> choixEntreesTor;

            if(choixEntreesTor == 0)
                iCan.lireEtat(_ENTREESTOR_COFFRET_ID);

            if(choixEntreesTor == 1)
                iCan.lireEtat(_ENTREESTOR_SOMMET_ID);

            }
            catch(const std::string &e)
            {
                cout << "(!!) Une erreur est survenue ---> " << e;
            }

            break;
        case 14:
            err = false;

            try {
                iCan.demarrerThread();
            }
            catch(const std::string &e)
            {
                err = true;
                cout << "(!!) Une erreur est survenue ---> " << e;
            }

            if(!err)
                cout << "\n--> [OK] La reception des trames est activee. " << endl;

            break;
        case 15:
            quitter = 1;
            break;
        }
    }

}
