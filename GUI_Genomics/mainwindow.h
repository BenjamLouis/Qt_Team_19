#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <array>

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

    void on_FastaButton_Tab2_clicked();

    void on_BedButton_clicked();

    void on_ButtonFunction2_clicked();

private:
    Ui::MainWindow *ui;
    QString FastafileName_Tab2;
    QString BedfileName;


};

#endif // MAINWINDOW_H
