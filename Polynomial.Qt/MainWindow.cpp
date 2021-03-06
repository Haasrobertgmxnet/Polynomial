#include <QVariant>
#include <QDebug>
#include <string>
#include <array>
#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "..\Polynomial.Core\Polynomial.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for each (auto elem in ui->layoutWidget->children())
    {
        auto key{ elem->objectName() };
        if (!key.contains("Coeff")) {
            continue;
        }
        auto val{ static_cast<QLineEdit*>(elem) };
        val->setText("1.0");
    }

    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::calculate);
    connect(ui->pushButton_2,&QPushButton::clicked,QApplication::instance(),&QApplication::quit);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculate(){

    Polynomial::Core::Polynomial poly;
    poly.Create(4);

    std::map<QString, cplx> Coeffs;
    auto k{ 0 };
    for each (auto elem in ui->layoutWidget->children())
    {
        auto key{ elem->objectName() };
        if (!key.contains("Coeff")) {
            continue;
        }
        auto val{ static_cast<QLineEdit*>(elem) };
        if (key.contains("Re")) {
            Coeffs[key] = cplx(val->text().toDouble(), 0.0);
        }
        if (key.contains("Im")) {
            Coeffs[key] = cplx(0.0, val->text().toDouble());
        }
    }
    unsigned int j{ 0 };
    for each (auto kvp in Coeffs)
    {
        unsigned int index{ 4 - j / 2 };
        poly.Coefficients[index] = poly.Coefficients[index] + kvp.second;
        j++;
    }

    poly.FindRoots();
    poly.ValidateRoots();

    j = 0;
    std::array<std::string, 4> sRoot;
    for (auto& root : poly.Roots){
        sRoot[j++]= std::to_string(root.real()) + "+" + std::to_string(root.imag()) + "i";
    }
    std::string sResultError= std::to_string(poly.ResultError);
    std::string sDiscriminant= std::to_string(poly.Discriminant.real()) + "+" + std::to_string(poly.Discriminant.imag()) + "i";
    std::string sDelta= std::to_string(poly.Delta.real()) + "+" + std::to_string(poly.Delta.imag()) + "i";
    std::string sQ= std::to_string(poly.Q.real()) + "+" + std::to_string(poly.Q.imag()) + "i";

    QString qs = QStringLiteral("L�sungen der Nullstellengleichung\nf�r ein komplexes Polynom vierten Grades: \n");
    for (unsigned int j = 0; j < sRoot.size(); ++j) {
        qs = qs + QStringLiteral("L�sung ") + QString(j+49) + ": " + QString(sRoot[j].c_str()) + "\n";
    }
    qs= qs + "Fehler: " + QString(sResultError.c_str()) + "\n";
    qs= qs + "Diskriminante: " + QString(sDiscriminant.c_str()) + "\n";

    ui->textBrowser->setText(qs);

    


    qDebug() << "Berechne....";
}
