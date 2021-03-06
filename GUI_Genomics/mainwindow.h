#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <array>
#include "waitingspinnerwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
    
    void on_lineEdit_textChanged(const QString &arg1);

    void on_FastaButton_Tab2_clicked();

    void on_BedButton_clicked();

    void on_ButtonFunction2_clicked();

    void on_result();

    void on_result2();

    void process_1();

private:
    Ui::MainWindow *ui;
    QString MatrixFileName;
    QString FastaFileName;
    double threshold;
    QString FastafileName_Tab2;
    QString BedfileName;
};

#endif // MAINWINDOW_H
