#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qframe.h"

/*
 * Sachen die man im Kopf behalten sollte (Notebox):
 * 1. Alles ausser Labels sollten einen custom Namen bekommen. Bsp: QLineEdit_3 -> Uebersicht_Profession_Line
 *    Diese Beschriftung sollte nach folgendem Schema aufgebaut sein: REITERNAME_FELDNAME_OBJEKTTYP
 * 2. Datengruppen (zB nach PDF Heldendokument Schema, wenn übernommen) sollten in einem QFrame sein, dass entsprechend bennant ist.
 *    QFrame anschließend als FrameStyle Panel in mainwindow.cpp ab Zeile 24 gesetzt werden. Bsp: ui->Charakter_Basisdaten->setFrameStyle(QFrame::Panel)
 *    Hierbei ist das QFrame Objekt nach dem "ui->" einzutragen.
 * 3. Vor dem Commiten, sollte im Designer der erste Reiter (Uebersicht) ausgewält sein, da der ausgewählte Reiter als standard Ansicht gespeichert wird.
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString Character_Name;
    QString Filepath;
    QStringList Character_Liste;
    QStringList Character_daten;
    bool ok = false;

    ui->centralwidget->setStyleSheet("QFrame {border-width: 1; border-style: solid; border-color: rgb(10, 10, 10)}"
                                         "QLabel {border-width: 0}");

    Character_Liste.append("NEUER_CHARAKTER");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DB_PATH);
    QSqlQuery query(db);
    if(db.open())
    {
        if(query.exec("SELECT Name FROM Uebersicht"))
        {
            while(query.next())
            {
                Character_Liste.append(query.value(0).toString());
            }
        }
    }

    while(!ok)
        Character_Name = QInputDialog::getItem(this,"Characterauswahl","Wähle einen Character aus, oder erstelle einen neuen:",Character_Liste,0,false,&ok);
    if(Character_Name != "NEUER_CHARAKTER")
    {
        query.clear();
        if(query.exec("SELECT \"Name\",  \"Rasse\",  \"Kultur\",  \"Profession\",  \"Geschlecht\",  \"Alter\",  \"Groesse\",  \"Gewicht\",  \"Haarfarbe\",  \"Augenfarbe\", \"Aussehen\",  \"Stand\",  \"Titel\",  \"Sozialstatus\", \"Hintergrund\", \"Characterbild\" FROM Uebersicht WHERE Name='"+Character_Name+"';"))        {
            query.first();
            for(int i = 0;i<16;i++)
                Character_daten.append(query.value(i).toString());
            qDebug() << Character_daten.join(",");
            ui->Uebersicht_Character_Name_Line->setText(Character_daten.at(0));
            ui->Uebersicht_Rasse_Line->setText(Character_daten.at(1));
            ui->Uebersicht_Kultur_Line->setText(Character_daten.at(2));
            ui->Uebersicht_Profession_Line->setText(Character_daten.at(3));
            ui->Uebersicht_Geschlecht_Line->setText(Character_daten.at(4));
            ui->Uebersicht_Alter_Line->setText(Character_daten.at(5));
            ui->Uebersicht_Groesse_Line->setText(Character_daten.at(6));
            ui->Uebersicht_Gewicht_Line->setText(Character_daten.at(7));
            ui->Uebersicht_Haarfarbe_Line->setText(Character_daten.at(8));
            ui->Uebersicht_Augenfarbe_Line->setText(Character_daten.at(9));
            ui->Uebersicht_Aussehen_Text->setText(Character_daten.at(10));
            ui->Uebersicht_Stand_Line->setText(Character_daten.at(11));
            ui->Uebersicht_Titel_Line->setText(Character_daten.at(12));
            ui->Uebersicht_Sozialstatus_Line->setText(Character_daten.at(13));
            ui->Uebersicht_Hintergrund_Text->setText(Character_daten.at(14));
            Filepath = Character_daten.at(15);
            Filepath.replace("\\","/");
            qDebug() << Filepath;
            ui->Uebersicht_Character_Bild->setStyleSheet("QWidget {image: url("+Filepath+") center center fixed;}");
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

