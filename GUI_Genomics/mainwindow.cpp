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
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(987,566);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    QString MatrixfileName = QFileDialog::getOpenFileName(this,
        tr("Open Matrix File"), "", tr("Matrix Files (*.mat)"));
    ui->pushButton_3->setText(MatrixfileName);
}


void MainWindow::on_pushButton_4_clicked()
{
    QString FastafileName = QFileDialog::getOpenFileName(this,
        tr("Open Fasta File"), "", tr("Fasta Files (*.fa *.fasta)"));
}





//-------------- Tab2 ------------------


void MainWindow::on_FastaButton_Tab2_clicked()
{
    FastafileName_Tab2 = QFileDialog::getOpenFileName(this,
        tr("Open Fasta File"), "", tr("Fasta Files (*.fa *.fasta)"));
    ui->FastaButton_Tab2->setText(FastafileName_Tab2);
}

void MainWindow::on_BedButton_clicked()
{
    BedfileName = QFileDialog::getOpenFileName(this,
        tr("Open Bed File"), "", tr("Bed Files (*.bed)"));
    ui->BedButton->setText(BedfileName);
}


void MainWindow::on_ButtonFunction2_clicked()
{
    // Bouton depart programme

    QString errors("Missing: \n");
    bool error_arguments;
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

    }else {

        QString length(ui->LengthLine->text());
        LinksFile Links(BedfileName.toStdString(), FastafileName_Tab2.toStdString(), length.toInt());
        Links.creationMatrice();

    }

}
