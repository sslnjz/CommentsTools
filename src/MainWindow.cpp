#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    //setWindowFlags( windowFlags() & ~Qt::WindowMaximizeButtonHint );
}

MainWindow::~MainWindow()
{

}
