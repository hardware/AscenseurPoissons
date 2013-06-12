#include "interfacecandlg.h"

InterfaceCANDlg::InterfaceCANDlg() {}

void InterfaceCANDlg::run()
{
    int choix, nbCanaux = 0, quitter = 0;
    short canal;
    bool err;

    while(quitter == 0)
    {
        cout << "\n-----------------------------------------------------------------------" << endl;
        cout << "## PROGRAMME PERMETTANT DE CONFIGURER ET D UTILISER LA CARTE CAN NSI ##" << endl;
        cout << "-----------------------------------------------------------------------\n\n";

        cout << "[1] Ouvrir un canal" << endl;
        cout << "[2] Fermer le canal" << endl;
        cout << "[3] Quitter\n\n";

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
            quitter = 1;
            break;
        }
    }

}
