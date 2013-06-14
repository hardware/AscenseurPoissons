#include "interfacecandlg.h"

InterfaceCANDlg::InterfaceCANDlg() {}

void InterfaceCANDlg::run()
{
    int choix, nbCanaux = 0, quitter = 0;
    short canal, tailleDonnee;
    bool err;
    ulong idTrame;

    while(quitter == 0)
    {
        cout << "\n-----------------------------------------------------------------------" << endl;
        cout << "## PROGRAMME PERMETTANT DE CONFIGURER ET D UTILISER LA CARTE CAN NSI ##" << endl;
        cout << "-----------------------------------------------------------------------\n\n";

        cout << "[1] Ouvrir un canal" << endl;
        cout << "[2] Fermer le canal" << endl;
        cout << "[3] Afficher les informations du peripherique" << endl;
        cout << "[4] Initialiser le controleur CAN (debit et echantillonnage)" << endl;
        cout << "[5] Initialiser le mode de fonctionnement" << endl;
        cout << "[6] Initialiser la trame" << endl;
        cout << "[7] Demarrer le controleur CAN" << endl;
        cout << "[8] Arreter le controleur CAN" << endl;
        cout << "[9] Envoyer une trame" << endl;
        cout << "[10] Quitter\n\n";

        cout << "Votre choix ? ";
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

            try { iCan.fermerCanal(); }
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
                cout << "Quel est l'identificateur de la trame ? ";
                cin >> hex >> idTrame;

                iCan.setIdTrame(idTrame);

                if(idTrame == CAPTEURS_ID || idTrame == ENTREESTOR_COFFRET_ID || idTrame == ENTREESTOR_SOMMET_ID)
                {
                    iCan.initialiserIdentificateur(_CAN_RX_DATA);
                }
                else if(idTrame == SORTIESTOR_COFFRET_ID || idTrame == SORTIESTOR_SOMMET_ID)
                {
                    cout << "Entrez la taille de la donnee : ";
                    cin >> tailleDonnee;

                    iCan.initialiserIdentificateur(_CAN_TX_DATA, tailleDonnee);
                }

            }
            catch(const std::string &e)
            {
                err = true;
                cout << "(!!) Une erreur est survenue ---> " << e;
            }

            if(!err)
                cout << "\n--> [OK] La trame est bien initialisee !" << endl;

            break;
        case 7:
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
        case 8:
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
        case 9:
            err = false;
            try {
                coffret.sTor.word_16bits.descenteGrille = 0;

                uchar data = coffret.sTor.val;

                iCan.setDonnees(data);
                iCan.ecrireDonnee();
            }
            catch(const std::string &e)
            {
                err = true;
                cout << "(!!) Une erreur est survenue ---> " << e;
            }

            if(!err)
                cout << "\n--> [OK] Les donnees ont ete mises a jour" << endl;

            break;
        case 10:
            quitter = 1;
            break;
        }
    }

}
