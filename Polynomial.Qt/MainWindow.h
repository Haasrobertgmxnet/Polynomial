#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#define POLYNOMIAL_NOLIB 1
#include "..\Polynomial.Dll\Polynomial.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void calculate();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
