#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

	connect(tbtnAdd, &QToolButton::clicked, this, &MainWindow::addFilterPath);
    connect(listWidget, &QListWidget::currentRowChanged, [&](int row){ tbtnDelete->setEnabled(row >= 0); });
    connect(tbtnDelete, &QToolButton::clicked, [&](){ removeFromSourceList(listWidget->currentRow()); });

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
                "QDockWidget::title { background: lightgray; padding: 2px; text-align: center;}"
                "QDockWidget::close-button, QDockWidget::float-button {border: none;icon-size: 12px;}"
    );

#endif
}

MainWindow::~MainWindow()
{

}

void MainWindow::addFilterPath()
{
	QString path = QFileDialog::getExistingDirectory(this, tr("Select Directory"), QDir::homePath(), QFileDialog::ReadOnly);
	if (path.isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("Please select a directory"));
	}
	else
    {
        addItem2SourceList(path);
	}
}

void MainWindow::addItem2SourceList(const QString& s)
{
    if(listWidget->findItems(s, Qt::MatchCaseSensitive).count() == 0){
        QListWidgetItem* item = new QListWidgetItem(s);
        item->setIcon(QIcon("://resources/1201081.png"));
        item->setSelected(true);
        item->setToolTip(s);
        listWidget->setIconSize(QSize(16, 16));
        listWidget->addItem(item);
    }
}

void MainWindow::removeFromSourceList(int index)
{
    delete listWidget->takeItem(index);
}
