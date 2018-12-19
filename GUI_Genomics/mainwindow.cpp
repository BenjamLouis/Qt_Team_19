#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QPalette>
#include <QFileDialog>
#include <QFileInfo>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1000,600);
    QIcon startCreate(":/hubert.png");
    ui->pushButton->setIcon(startCreate);
    setWindowIcon(QIcon(":/background.png"));
    ui->tab->setStyleSheet("QWidget#tab{background-image: url(:/tabs.png)}");
    ui->tab_2->setStyleSheet("QWidget#tab_2{background-image: url(:/tabs.png)}");
    ui->lineEdit->setAlignment(Qt::AlignCenter);
    ui->lineEdit->setFont(QFont("Calibri", 14));
}

MainWindow::~MainWindow()
{
    delete ui;
}

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
    if(!FastaFileName.isEmpty()) ui->pushButton_3->setText(withoutpath);
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
   threshold = arg1.toDouble();
}

void MainWindow::on_pushButton_clicked()
{

}
