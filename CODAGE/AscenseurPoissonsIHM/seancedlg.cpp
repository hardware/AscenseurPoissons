#include "seancedlg.h"

const int PV_MAX = 100;
const int PV_MIN = 5;
const int PV_OFFSET = 5;

SeanceDlg::SeanceDlg(QWidget *parent) : QWidget(parent)
{
    QSize LESize(60, 50),
          PBSize(60, 50);

    QFont LEFont("MS Shell Dlg 2", 28),
          GBFont("Arial", 11),
          PBSeanceFont("Arial", 11, 75),
          PBPlusFont("MS Shell Dlg 2", 18),
          PBMoinsFont("MS Shell Dlg 2", 26);

    params = new QSettings(QApplication::applicationDirPath() + "/seance.ini", QSettings::IniFormat);

    GBPv = new QGroupBox("PETITE VITESSE");
    GBPv->setFont(GBFont);

        LEPv = new QLineEdit(params->value("seance/PV", 5).toString());
        LEPv->setMaximumSize(LESize);
        LEPv->setFont(LEFont);
        LEPv->setAlignment(Qt::AlignHCenter);
        LEPv->setReadOnly(true);

        PBPvPlus = new QPushButton("+");
        PBPvPlus->setFont(PBPlusFont);
        PBPvPlus->setMaximumSize(PBSize);
        PBPvPlus->setCursor(Qt::PointingHandCursor);

        PBPvMoins = new QPushButton("-");
        PBPvMoins->setFont(PBMoinsFont);
        PBPvMoins->setMaximumSize(PBSize);
        PBPvMoins->setCursor(Qt::PointingHandCursor);

        GLPv = new QGridLayout(GBPv);
        GLPv->addWidget(LEPv, 0, 0, 2, 1);
        GLPv->addWidget(PBPvPlus, 0, 1);
        GLPv->addWidget(PBPvMoins, 1, 1);
        GBPv->setLayout(GLPv);

    GBGv = new QGroupBox("GRANDE VITESSE");
    GBGv->setFont(GBFont);

    LEGv = new QLineEdit(params->value("seance/GV", 5).toString());
        LEGv->setMaximumSize(LESize);
        LEGv->setFont(LEFont);
        LEGv->setAlignment(Qt::AlignHCenter);
        LEGv->setReadOnly(true);

        PBGvPlus = new QPushButton("+");
        PBGvPlus->setFont(PBPlusFont);
        PBGvPlus->setMaximumSize(PBSize);
        PBGvPlus->setCursor(Qt::PointingHandCursor);

        PBGvMoins = new QPushButton("-");
        PBGvMoins->setFont(PBMoinsFont);
        PBGvMoins->setMaximumSize(PBSize);
        PBGvMoins->setCursor(Qt::PointingHandCursor);

        GLGv = new QGridLayout(GBGv);
        GLGv->addWidget(LEGv, 0, 0, 2, 1);
        GLGv->addWidget(PBGvPlus, 0, 1);
        GLGv->addWidget(PBGvMoins, 1, 1);
        GBGv->setLayout(GLGv);

    GBTempsPeche = new QGroupBox("TEMPS DE PECHE");
    GBTempsPeche->setFont(GBFont);

        LETempsPeche = new QLineEdit(params->value("seance/TempsPeche", 60).toString());
        LETempsPeche->setMaximumSize(LESize);
        LETempsPeche->setFont(LEFont);
        LETempsPeche->setAlignment(Qt::AlignHCenter);
        LETempsPeche->setReadOnly(true);

        PBTempsPechePlus = new QPushButton("+");
        PBTempsPechePlus->setFont(PBPlusFont);
        PBTempsPechePlus->setMaximumSize(PBSize);
        PBTempsPechePlus->setCursor(Qt::PointingHandCursor);

        PBTempsPecheMoins = new QPushButton("-");
        PBTempsPecheMoins->setFont(PBMoinsFont);
        PBTempsPecheMoins->setMaximumSize(PBSize);
        PBTempsPecheMoins->setCursor(Qt::PointingHandCursor);

        LBTempsPeche = new QLabel("MINUTES");

        vboxTempsPeche = new QVBoxLayout;
        vboxTempsPeche->addWidget(LETempsPeche);
        vboxTempsPeche->addWidget(LBTempsPeche);

        GLTempsPeche = new QGridLayout(GBTempsPeche);
        GLTempsPeche->addLayout(vboxTempsPeche, 0, 0, 2, 1, Qt::AlignVCenter);
        GLTempsPeche->addWidget(PBTempsPechePlus, 0, 1);
        GLTempsPeche->addWidget(PBTempsPecheMoins, 1, 1);
        GBTempsPeche->setLayout(GLTempsPeche);

    GBTempsVidange = new QGroupBox("TEMPS DE VIDANGE");
    GBTempsVidange->setFont(GBFont);

        LETempsVidange = new QLineEdit(params->value("seance/TempsVidange", 10).toString());
        LETempsVidange->setMaximumSize(LESize);
        LETempsVidange->setFont(LEFont);
        LETempsVidange->setAlignment(Qt::AlignHCenter);
        LETempsVidange->setReadOnly(true);

        PBTempsVidangePlus = new QPushButton("+");
        PBTempsVidangePlus->setFont(PBPlusFont);
        PBTempsVidangePlus->setMaximumSize(PBSize);
        PBTempsVidangePlus->setCursor(Qt::PointingHandCursor);

        PBTempsVidangeMoins = new QPushButton("-");
        PBTempsVidangeMoins->setFont(PBMoinsFont);
        PBTempsVidangeMoins->setMaximumSize(PBSize);
        PBTempsVidangeMoins->setCursor(Qt::PointingHandCursor);

        LBTempsVidange = new QLabel("SECS");
        LBTempsVidange->setAlignment(Qt::AlignCenter);

        vboxTempsVidange = new QVBoxLayout;
        vboxTempsVidange->addWidget(LETempsVidange);
        vboxTempsVidange->addWidget(LBTempsVidange);

        GLTempsVidange = new QGridLayout(GBTempsVidange);
        GLTempsVidange->addLayout(vboxTempsVidange, 0, 0, 2, 1, Qt::AlignVCenter);
        GLTempsVidange->addWidget(PBTempsVidangePlus, 0, 1);
        GLTempsVidange->addWidget(PBTempsVidangeMoins, 1, 1);
        GBTempsVidange->setLayout(GLTempsVidange);

    GBNombreCycles = new QGroupBox("NOMBRE DE CYCLES");
    GBNombreCycles->setFont(GBFont);

        LENombreCycles = new QLineEdit(params->value("seance/NbCycles", 10).toString());
        LENombreCycles->setMaximumSize(LESize);
        LENombreCycles->setFont(LEFont);
        LENombreCycles->setAlignment(Qt::AlignHCenter);
        LENombreCycles->setReadOnly(true);

        PBNombreCyclesPlus = new QPushButton("+");
        PBNombreCyclesPlus->setFont(PBPlusFont);
        PBNombreCyclesPlus->setMaximumSize(PBSize);
        PBNombreCyclesPlus->setCursor(Qt::PointingHandCursor);

        PBNombreCyclesMoins = new QPushButton("-");
        PBNombreCyclesMoins->setFont(PBMoinsFont);
        PBNombreCyclesMoins->setMaximumSize(PBSize);
        PBNombreCyclesMoins->setCursor(Qt::PointingHandCursor);

        GLNombreCycles = new QGridLayout(GBNombreCycles);
        GLNombreCycles->addWidget(LENombreCycles, 0, 0, 2, 1);
        GLNombreCycles->addWidget(PBNombreCyclesPlus, 0, 1);
        GLNombreCycles->addWidget(PBNombreCyclesMoins, 1, 1);
        GBNombreCycles->setLayout(GLNombreCycles);

    GBPeriodicite = new QGroupBox("PERIODICITE");
    GBPeriodicite->setFont(GBFont);

        LEPeriodicite = new QLineEdit(params->value("seance/Periodicite", 10).toString());
        LEPeriodicite->setMaximumSize(LESize);
        LEPeriodicite->setFont(LEFont);
        LEPeriodicite->setAlignment(Qt::AlignHCenter);
        LEPeriodicite->setReadOnly(true);

        PBPeriodicitePlus = new QPushButton("+");
        PBPeriodicitePlus->setFont(PBPlusFont);
        PBPeriodicitePlus->setMaximumSize(PBSize);
        PBPeriodicitePlus->setCursor(Qt::PointingHandCursor);

        PBPeriodiciteMoins = new QPushButton("-");
        PBPeriodiciteMoins->setFont(PBMoinsFont);
        PBPeriodiciteMoins->setMaximumSize(PBSize);
        PBPeriodiciteMoins->setCursor(Qt::PointingHandCursor);

        GLPeriodicite = new QGridLayout(GBPeriodicite);
        GLPeriodicite->addWidget(LEPeriodicite, 0, 0, 2, 1);
        GLPeriodicite->addWidget(PBPeriodicitePlus, 0, 1);
        GLPeriodicite->addWidget(PBPeriodiciteMoins, 1, 1);
        GBPeriodicite->setLayout(GLPeriodicite);

    PBSeanceEnregistrer = new QPushButton("ENREGISTRER");
    PBSeanceEnregistrer->setMinimumHeight(50);
    PBSeanceEnregistrer->setFont(PBSeanceFont);
    PBSeanceEnregistrer->setStyleSheet("color: rgb(0, 170, 0);");
    PBSeanceEnregistrer->setCursor(Qt::PointingHandCursor);

    PBSeanceLancer = new QPushButton("LANCER");
    PBSeanceLancer->setMinimumHeight(50);
    PBSeanceLancer->setFont(PBSeanceFont);
    PBSeanceLancer->setCursor(Qt::PointingHandCursor);

    PBSeanceArreter = new QPushButton("ARRETER");
    PBSeanceArreter->setMinimumHeight(50);
    PBSeanceArreter->setFont(PBSeanceFont);
    PBSeanceArreter->setStyleSheet("color: rgb(255, 0, 0);");
    PBSeanceArreter->setCursor(Qt::PointingHandCursor);

    hbox = new QHBoxLayout;
    hbox->addWidget(PBSeanceEnregistrer);
    hbox->addWidget(PBSeanceLancer);
    hbox->addWidget(PBSeanceArreter);

    GLMain = new QGridLayout;
    GLMain->addWidget(GBPv, 0, 0);
    GLMain->addWidget(GBGv, 0, 1);
    GLMain->addWidget(GBTempsPeche, 0, 2);
    GLMain->addWidget(GBTempsVidange, 1, 0);
    GLMain->addWidget(GBNombreCycles, 1, 1);
    GLMain->addWidget(GBPeriodicite, 1, 2);

    vbox = new QVBoxLayout(this);
    vbox->addLayout(GLMain);
    vbox->addLayout(hbox);

    setLayout(vbox);

    // Signaux & slots
    QObject::connect(PBPvPlus, SIGNAL(clicked()), this, SLOT(augmenterPV()));
    QObject::connect(PBPvMoins, SIGNAL(clicked()), this, SLOT(diminuerPV()));
    QObject::connect(PBSeanceEnregistrer, SIGNAL(clicked()), this, SLOT(enregistrerParametres()));
}

void SeanceDlg::augmenterPV()
{
    int valeur = LEPv->text().toInt();
    valeur += PV_OFFSET;

    if(valeur > PV_MAX)
        valeur = PV_MAX;

    LEPv->setText(QString::number(valeur));
}

void SeanceDlg::diminuerPV()
{
    int valeur = LEPv->text().toInt();
    valeur -= PV_OFFSET;

    if(valeur < PV_MIN)
        valeur = PV_MIN;

    LEPv->setText(QString::number(valeur));
}

void SeanceDlg::enregistrerParametres()
{
    params->beginGroup("seance");
    params->setValue("PV", LEPv->text().toInt());
    params->setValue("GV", LEGv->text().toInt());
    params->setValue("TempsPeche", LETempsPeche->text().toInt());
    params->setValue("TempsVidange", LETempsVidange->text().toInt());
    params->setValue("NbCycles", LENombreCycles->text().toInt());
    params->setValue("Periodicite", LEPeriodicite->text().toInt());
    params->endGroup();

    if(params->status() == QSettings::NoError)
    {
        QMessageBox::information(this, QString::fromUtf8("Enregistrement effectué"),
                                 QString::fromUtf8("Les paramètres ont bien été enregistrés."));
    }
    else
    {
        if(params->status() == QSettings::AccessError)
            QMessageBox::critical(this, QString::fromUtf8("Problème d'accès"),
                                     QString::fromUtf8("Impossible d'accéder au fichier de configuration."));
        if(params->status() == QSettings::FormatError)
            QMessageBox::critical(this, QString::fromUtf8("Erreur de format"),
                                     QString::fromUtf8("Le format du fichier de configuration est incorrect."));
    }
}
