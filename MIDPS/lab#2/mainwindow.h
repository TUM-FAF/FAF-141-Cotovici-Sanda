#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QPushButton>
#include <QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void numberEmitted(int number);

private slots:
    void buttonPushed();
    void operationPushed();
    void equals();
    void setGeo();
    double root(double,double);
    void signf();



private:

    QLabel *label;
    QPushButton *operationButton[10];
    QPushButton *buttons[10];


};

#endif // MAINWINDOW_H
