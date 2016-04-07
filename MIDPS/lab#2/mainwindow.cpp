#include "mainwindow.h"
#include <math.h>
#include "ui_mainwindow.h"
#include <QtCore/QCoreApplication>

QString value = "",total = "";
double fNum, sNum;
bool addBool = false, subtractBool = false, multiplyBool = false, divideBool = false, powerBool = false, sqrtBool = false, rootBool = false,signBool = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)

{
    label = new QLabel("0", this);
    label -> setGeometry(QRect(QPoint(50,70),QSize(250,50)));
    label->setStyleSheet("background-color: rgb(221,160,221); font: bold 14px;");
    label->setAlignment(Qt::AlignCenter);



    for(int i =0; i<10; i++){
        QString operations[] = {"C","=","+","-","*","/","^","root","sqrt","+-"};
        operationButton[i] = new QPushButton(operations[i],this);

        if(i == 1){
          connect(operationButton[i],SIGNAL(released()),this, SLOT(equals()));
        }
        else if(i == 9){
            connect(operationButton[i],SIGNAL(released()),this, SLOT(signf()));
        }
        else{
        connect(operationButton[i],SIGNAL(released()),this, SLOT(operationPushed()));
            }
        }

    for(int i =0; i<10; i++){
        QString digit = QString::number(i);
        buttons[i] = new QPushButton(digit,this);
        connect(buttons[i],SIGNAL(released()),this, SLOT(buttonPushed()));
    }
    setGeo();

}

void MainWindow::buttonPushed(){
    QPushButton *button = (QPushButton *)sender();
    emit numberEmitted(button->text()[0].digitValue());
    value =value + QString::number(button->text()[0].digitValue());
    label -> setText(value);
}

void MainWindow::operationPushed(){
    QPushButton *button = (QPushButton *)sender();
    fNum = value.toDouble();
    if(button->text() == "C"){
        value = "";
        fNum = 0;
        sNum = 0;
    }
    if(button->text() == "+"){
        addBool = true;
    }
    if(button->text() == "-"){
        subtractBool = true;
    }
    if(button->text() == "*"){
        multiplyBool = true;
    }
    if(button->text() == "/"){
        divideBool = true;
    }
    if(button->text() == "^"){
        powerBool = true;
    }
    if(button->text() == "root"){
        rootBool = true;
    }
    if(button->text() == "sqrt"){
        sqrtBool = true;
    }
    if(button->text() == "+-"){
        signBool = true;
    }


    value = "";
    label -> setText(value);

}

void MainWindow::setGeo(){
    for(int i=0;i<1;i++){
        buttons[i]->setGeometry(QRect(QPoint(50,300), QSize(50,50)));
        buttons[i]->setStyleSheet("background-color: rgb(255,192,203); font: bold 14px;");
        operationButton[i]->setGeometry(QRect(QPoint(100,300), QSize(50,50)));
        operationButton[i+1]->setGeometry(QRect(QPoint(150,300), QSize(50,50)));
        operationButton[i+2]->setGeometry(QRect(QPoint(200,300), QSize(50,50)));
        operationButton[i+6]->setGeometry(QRect(QPoint(250,300), QSize(50,50)));
        operationButton[i]->setStyleSheet("background-color: rgb(255,255,0); font: bold 14px;");
        operationButton[i+2]->setStyleSheet("background-color: rgb(176,196,222); font: bold 14px;");
        operationButton[i+6]->setStyleSheet("background-color: rgb(176,196,222); font: bold 14px;");
        operationButton[i+1]->setStyleSheet("background-color: rgb(0,255,127); font: bold 14px;");

    }
    for(int i=1;i<4;i++){
        buttons[i]->setGeometry(QRect(QPoint(50*i,250), QSize(50,50)));
        buttons[i]->setStyleSheet("background-color: rgb(255,192,203); font: bold 14px;");
        if(i == 3){
        operationButton[i]->setGeometry(QRect(QPoint(200,250), QSize(50,50)));
        operationButton[i]->setStyleSheet("background-color: rgb(176,196,222); font: bold 14px;");
        operationButton[i+4]->setGeometry(QRect(QPoint(250,250), QSize(50,50)));
        operationButton[i+4]->setStyleSheet("background-color: rgb(176,196,222); font: bold 14px;");

        }

    }
    for(int i=4; i<7; i++){
        buttons[i]->setGeometry(QRect(QPoint(50*(i-3),200), QSize(50,50)));
        buttons[i]->setStyleSheet("background-color: rgb(255,192,203); font: bold 14px;");
        if(i == 4){
        operationButton[i]->setGeometry(QRect(QPoint(200,200), QSize(50,50)));
        operationButton[i]->setStyleSheet("background-color: rgb(176,196,222); font: bold 14px;");
        operationButton[i+4]->setGeometry(QRect(QPoint(250,200), QSize(50,50)));
        operationButton[i+4]->setStyleSheet("background-color: rgb(176,196,222); font: bold 14px;");
        }
    }
    for(int i=7; i<10; i++){
        buttons[i]->setGeometry(QRect(QPoint(50*(i-6),150), QSize(50,50)));
        buttons[i]->setStyleSheet("background-color: rgb(255,192,203); font: bold 14px;");
        if(i == 7){
        operationButton[i+2]->setGeometry(QRect(QPoint(200,150), QSize(50,50)));
        operationButton[i+2]->setStyleSheet("background-color: rgb(176,196,222); font: bold 14px;");
        operationButton[i-2]->setGeometry(QRect(QPoint(250,150), QSize(50,50)));
        operationButton[i-2]->setStyleSheet("background-color: rgb(176,196,222); font: bold 14px;");
        }
    }

}

void MainWindow::equals(){
    sNum = value.toDouble();
    if (addBool) {
        total = QString::number(fNum+sNum);
        label->setText(total);
        addBool = false;
    }
    if (subtractBool) {
        total = QString::number(fNum-sNum);
        label->setText(total);
        subtractBool = false;
    }
    if (multiplyBool) {
        total = QString::number(fNum*sNum);
        label->setText(total);
        multiplyBool = false;
    }
    if (divideBool) {
        total = QString::number(fNum/sNum);
        label->setText(total);
        divideBool = false;
    }

    if (powerBool) {
        total = QString::number(pow(fNum,sNum));
        label->setText(total);
        powerBool = false;
    }
    if (rootBool) {
        total = QString::number(root((double)fNum,(double)sNum));
        label->setText(total);
        rootBool = false;
    }
    if (sqrtBool) {
        total = QString::number(sqrt((double)fNum));
        label->setText(total);
        sqrtBool = false;
    }

    fNum = 0.0;
    sNum = 0.0;
    value = "";
    total = "";



}

double MainWindow::root(double a, double b){
    double result;
    double res;
    double reverce;
    if(a < 0){
       this->label= new QLabel("ERROR");
    }
    else{
    reverce = 1.0/b;
    result = pow(a,reverce);
    res = (double)round(result);
    }
    return res;
}

void MainWindow::signf(){
    QString text = label->text();
    double value = text.toDouble();
    if(value > 0.0){
        value = (-1)*value;
        text.prepend("-");
    }
    else if(value < 0.0){
        value = (-1)*value;
        text.remove(0, 1);
    }
    label->setText(text);

}

MainWindow::~MainWindow()
{

}
