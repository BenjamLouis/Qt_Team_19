#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QPalette>
#include <QFileDialog>

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
