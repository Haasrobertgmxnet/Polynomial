#include <QVariant>
#include <QDebug>
#include <string>
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("1.0");
    ui->lineEdit_2->setText("0.0");
    ui->lineEdit_3->setText("0.0");
    ui->lineEdit_4->setText("0.0");
    ui->lineEdit_5->setText("0.0");
    ui->lineEdit_6->setText("0.0");
    ui->lineEdit_7->setText("0.0");
    ui->lineEdit_8->setText("0.0");
    ui->lineEdit_9->setText("0.0");
    ui->lineEdit_10->setText("0.0");
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::calculate);
    connect(ui->pushButton_2,&QPushButton::clicked,QApplication::instance(),&QApplication::quit);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculate(){

    std::vector<cplx> v{ cplx(0.0,0.0), cplx(0.0,0.0), cplx(0.0,0.0), cplx(0.0,0.0), cplx(0.0,0.0) };
    poly.Create<CreateArg::Coefficients>(v);

    poly.Coefficients.at(4).real(QVariant(ui->lineEdit->text()).toDouble());
    poly.Coefficients.at(4).imag(QVariant(ui->lineEdit_2->text()).toDouble());

    poly.Coefficients.at(3).real(QVariant(ui->lineEdit_4->text()).toDouble());
    poly.Coefficients.at(3).imag(QVariant(ui->lineEdit_3->text()).toDouble());

    poly.Coefficients.at(2).real(QVariant(ui->lineEdit_6->text()).toDouble());
    poly.Coefficients.at(2).imag(QVariant(ui->lineEdit_5->text()).toDouble());

    poly.Coefficients.at(1).real(QVariant(ui->lineEdit_8->text()).toDouble());
    poly.Coefficients.at(1).imag(QVariant(ui->lineEdit_7->text()).toDouble());

    poly.Coefficients.at(0).real(QVariant(ui->lineEdit_10->text()).toDouble());
    poly.Coefficients.at(0).imag(QVariant(ui->lineEdit_9->text()).toDouble());


    poly.FindRoots();
    //poly.ValidateRoots();

    std::string sRoot1= std::to_string(poly.Roots.at(0).real()) + "+" + std::to_string(poly.Roots.at(0).imag()) + "i";
    std::string sRoot2= std::to_string(poly.Roots.at(1).real()) + "+" + std::to_string(poly.Roots.at(1).imag()) + "i";
    std::string sRoot3= std::to_string(poly.Roots.at(2).real()) + "+" + std::to_string(poly.Roots.at(2).imag()) + "i";
    std::string sRoot4= std::to_string(poly.Roots.at(3).real()) + "+" + std::to_string(poly.Roots.at(3).imag()) + "i";
    std::string sResultError= std::to_string(poly.ResultError);
    std::string sDiscriminant= std::to_string(poly.Discriminant.real()) + "+" + std::to_string(poly.Discriminant.imag()) + "i";
    std::string sDelta= std::to_string(poly.Delta.real()) + "+" + std::to_string(poly.Delta.imag()) + "i";
    std::string sQ= std::to_string(poly.Q.real()) + "+" + std::to_string(poly.Q.imag()) + "i";

    QString qs= "Lösungen der Nullstellengleichung\nfür ein komplexes Polynom vierten Grades: \n";
    qs= qs + "Root1: " + QString(sRoot1.c_str()) + "\n";
    qs= qs + "Root2: " + QString(sRoot2.c_str()) + "\n";
    qs= qs + "Root3: " + QString(sRoot3.c_str()) + "\n";
    qs= qs + "Root4: " + QString(sRoot4.c_str()) + "\n";
    qs= qs + "Result Error: " + QString(sResultError.c_str()) + "\n";
    qs= qs + "Discriminant: " + QString(sDiscriminant.c_str()) + "\n";
    qs= qs + "Delta: " + QString(sDelta.c_str()) + "\n";
    qs= qs + "Q: " + QString(sQ.c_str()) + "\n";


    ui->textBrowser->setText(qs);
    qDebug() << "Berechne....";
}
