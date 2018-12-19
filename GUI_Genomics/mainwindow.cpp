#include "mainwindow.h"
#include "../src/fastareader.h"
#include "../src/BEDreader.h"
#include "../src/FastaWriter.h"
#include "../src/LinksFile.h"
#include "../src/Matrice.h"
#include "../src/MatrixReader.h"
#include "../src/MatrixWriter.h"
#include "../src/TxtWriter.h"
#include "../src/Writer.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QPalette>
#include <QFileDialog>
#include <QFileInfo>
#include <QIcon>
#include <QMessageBox>
#include <QDesktopServices>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <iostream>
#include <QColor>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1000,600);
    QIcon startCreate(":/hubert.png");
    ui->pushButton->setIcon(startCreate);
    QIcon startCreate2(":/hubert.png");
    ui->ButtonFunction2->setIcon(startCreate2);
    setWindowIcon(QIcon(":/background.png"));
    ui->tab->setStyleSheet("QWidget#tab{background-image: url(:/tabs.png)}");
    ui->tab_2->setStyleSheet("QWidget#tab_2{background-image: url(:/tabs.png)}");
    ui->lineEdit->setAlignment(Qt::AlignCenter);
    ui->lineEdit->setFont(QFont("Calibri", 14));
    ui->LengthLine->setAlignment(Qt::AlignCenter);
    ui->LengthLine->setFont(QFont("Calibri", 14));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(process_1()));
    ui->BedButton->setCursor(Qt::PointingHandCursor);
    ui->FastaButton_Tab2->setCursor(Qt::PointingHandCursor);
    ui->pushButton_3->setCursor(Qt::PointingHandCursor);
    ui->pushButton_4->setCursor(Qt::PointingHandCursor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//----------Tab 1---------------------------

void MainWindow::on_pushButton_3_clicked()
{
    MatrixFileName = QFileDialog::getOpenFileName(this,
        tr("Open Matrix File"),"", tr("Matrix Files (*.mat)"));
    QFileInfo fi(MatrixFileName);
    QString withoutpath(fi.fileName());
    if(!MatrixFileName.isEmpty()) ui->pushButton_3->setText(withoutpath);
}


void MainWindow::on_pushButton_4_clicked()
{
    FastaFileName = QFileDialog::getOpenFileName(this,
        tr("Open Fasta File"), "", tr("Fasta Files (*.fa *.fasta)"));
    QFileInfo fi(FastaFileName);
    QString withoutpath(fi.fileName());
    if(!FastaFileName.isEmpty()) ui->pushButton_4->setText(withoutpath);
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
   threshold = arg1.toDouble();
}

void MainWindow::process_1() {
    // Bouton depart programme

    QString errors("Missing: \n");
    bool error_arguments(false);
    if ((ui->pushButton_3->text() == "Browse Files") or (ui->pushButton_3->text() == "") or (ui->pushButton_3->text() == "Please Select a file")) {
        ui->pushButton_3->setText("Please Select a file");
        errors += "\t-Matrix File \n";
        error_arguments = true;
    };

    if ((ui->pushButton_4->text() == "Browse Files") or (ui->pushButton_4->text() == "") or (ui->pushButton_4->text() == "Please Select a file")) {
        ui->pushButton_4->setText("Please Select a file");
        errors += "\t-Fasta File \n";
        error_arguments = true;
    };

    if (ui->lineEdit->text() == "") {
        errors += "\t-Threshold \n";
        error_arguments = true;

    }

    if (error_arguments) {

       errors += "\nPlease enter the missing information";
       QMessageBox::warning(this, tr("Missing Information(s)"),
                               errors,
                               QMessageBox::Ok);

    }else {

        Fastareader fasta(FastaFileName.toStdString());
        fasta.ReadAndCreate(MatrixFileName.toStdString(), threshold);
        QPushButton* result = new QPushButton("OUTPUT", ui->tab);
        result->setGeometry(40, 510, 875, 40);
        result->setText("OUTPUT");
        result->show();
        on_result();
        connect(result, SIGNAL(clicked()), this, SLOT(on_result()));
    }
}

void MainWindow::on_result()
{
    DIR* dir = opendir("result");

    if (dir) {
         QDesktopServices::openUrl(QUrl(QApplication::applicationDirPath() + "/../result", QUrl::TolerantMode));
    } else {
        mkdir("../result", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        QDesktopServices::openUrl(QUrl(QApplication::applicationDirPath() + "/../result", QUrl::TolerantMode));
    }
}

//-------------- Tab2 ------------------


void MainWindow::on_FastaButton_Tab2_clicked()
{
    FastafileName_Tab2 = QFileDialog::getOpenFileName(this,
        tr("Open Fasta File"), "", tr("Fasta Files (*.fa *.fasta)"));
    QFileInfo fi(FastafileName_Tab2);
    QString withoutpath(fi.fileName());
    if(!FastafileName_Tab2.isEmpty()) ui->FastaButton_Tab2->setText(withoutpath);
}

void MainWindow::on_BedButton_clicked()
{
    BedfileName = QFileDialog::getOpenFileName(this,
        tr("Open Bed File"), "", tr("Bed Files (*.bed)"));
    QFileInfo fi(BedfileName);
    QString withoutpath(fi.fileName());
    if(!BedfileName.isEmpty()) ui->BedButton->setText(withoutpath);
}


void MainWindow::on_ButtonFunction2_clicked()
{
    // Bouton depart programme

    QString errors("Missing: \n");
    bool error_arguments(false);
    if ((ui->BedButton->text() == "Browse Files") or (ui->BedButton->text() == "") or (ui->BedButton->text() == "Please Select a file")) {
        ui->BedButton->setText("Please Select a file");
        errors += "\t-Bed File \n";
        error_arguments = true;
    };

    if ((ui->FastaButton_Tab2->text() == "Browse Files") or (ui->FastaButton_Tab2->text() == "") or (ui->FastaButton_Tab2->text() == "Please Select a file")) {
        ui->FastaButton_Tab2->setText("Please Select a file");
        errors += "\t-Fasta File \n";
        error_arguments = true;
    };

    if (ui->LengthLine->text() == "") {
        errors += "\t-Length \n";
        error_arguments = true;

    }

    if (error_arguments) {

       errors += "\nPlease enter the missing information";
       QMessageBox::warning(this, tr("Missing Information(s)"),
                               errors,
                               QMessageBox::Ok);

    } else {
        QString length(ui->LengthLine->text());
        LinksFile Links(BedfileName.toStdString(), FastafileName_Tab2.toStdString(), length.toInt());
        Links.creationMatrice();
        QPushButton* result2 = new QPushButton("OUTPUT", ui->tab_2);
        result2->setGeometry(40, 510, 875, 40);
        result2->setText("OUTPUT");
        result2->show();
        on_result2();
        connect(result2, SIGNAL(clicked()), this, SLOT(on_result2()));
    }

}

void MainWindow::on_result2()
{

    DIR* dir = opendir("result");

    if (dir) {
         QDesktopServices::openUrl(QUrl(QApplication::applicationDirPath() + "/../result", QUrl::TolerantMode));
    } else {
        mkdir("../result", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        QDesktopServices::openUrl(QUrl(QApplication::applicationDirPath() + "/../result", QUrl::TolerantMode));
    }
}
