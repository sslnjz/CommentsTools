#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    //setWindowFlags( windowFlags() & ~Qt::WindowMaximizeButtonHint );
#ifdef Q_OS_MACOS

    QSize size = QSize(16, 16);
    tbtnAdd->setIconSize(size);
    tbtnDelete->setIconSize(size);
    tbtnFilter->setIconSize(size);
    tbtnStart->setIconSize(size);
    tbtnStop->setIconSize(size);
    tbtnUpdate->setIconSize(size);

    QString stylesheet = "QToolButton {background-color: transparent;}"
       "QToolButton:hover{ background-color: lightgray; border-radius: 0px;}"
       "QToolButton:pressed{ margin: 1px;}";
    tbtnAdd->setStyleSheet(stylesheet);
    tbtnDelete->setStyleSheet(stylesheet);
    tbtnFilter->setStyleSheet(stylesheet);
    tbtnStart->setStyleSheet(stylesheet);
    tbtnStop->setStyleSheet(stylesheet);
    tbtnUpdate->setStyleSheet(stylesheet);

    setStyleSheet(
                "QDockWidget {titlebar-close-icon: url(://resources/557950.png);titlebar-normal-icon: url(://resources/558058.png);}"
                "QDockWidget::title { background: lightgray; padding: 2px; text-align: center; padding-right: 50px;}"
                "QDockWidget::close-button, QDockWidget::float-button {border: none;icon-size: 12px;}"
    );

#endif
}

MainWindow::~MainWindow()
{

}
