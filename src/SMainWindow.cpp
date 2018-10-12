#include "SMainWindow.h"
#include "ui_MainWindow.h"
#include "STypeDialog.h"
#include "SEntryListThread.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfoList>
#include <QDebug>
#include <QThread>

class SMainWindowPrivate
{
public:
	SMainWindowPrivate(SMainWindow* q) : q_ptr(q)
	{

	}

public:
    QStringList _currentFiles;
    int _enableTimer = -1;
    bool _generateStop = false;

private:
	SMainWindow * const q_ptr;
	Q_DECLARE_PUBLIC(SMainWindow)
};

SMainWindow::SMainWindow(QWidget *parent) :
    QMainWindow(parent)
	, d_ptr(new SMainWindowPrivate(this))
{
	Q_D(SMainWindow);

    setupUi(this);

    d->_enableTimer = startTimer(100);
	connect(tbtnAdd, &QToolButton::clicked, this, &SMainWindow::addFilterPath);
    connect(listWidgetDirs, &QListWidget::currentRowChanged, [&](int row){ tbtnDelete->setEnabled(row >= 0); });
    connect(tbtnDelete, &QToolButton::clicked, [&](){ removeFromSourceList(listWidgetDirs->currentRow()); });
    connect(tbtnStart, &QToolButton::clicked, this, &SMainWindow::generateFilesList);

    connect(tbtnFilter, &QToolButton::clicked, [&]() {
		Q_D(SMainWindow);
		STypeDialog dlg(this);
        if (dlg.exec() == QDialog::Accepted){
            QStringList f = dlg.types();
            if(!f.isEmpty())
                comboBox->addItem(f.join(";"));
        }
	});

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

SMainWindow::~SMainWindow()
{

}

void SMainWindow::addFilterPath()
{
	QString path = QFileDialog::getExistingDirectory(this, tr("Select Directory"), QDir::homePath(), QFileDialog::ReadOnly);
	if (path.isEmpty())
		QMessageBox::warning(this, tr("Warning"), tr("Please select a directory"));
	else
        addItem2SourceList(path);
}

void SMainWindow::addItem2SourceList(const QString& s)
{
    bool duplicated = false;
    for(int i = 0; i < listWidgetDirs->count(); i++)
    {
        if(s.startsWith(listWidgetDirs->item(i)->text()))
        {
            duplicated = true;
        }
    }

    if(!duplicated){
        QListWidgetItem* item = new QListWidgetItem(s);
        item->setIcon(QIcon("://resources/1201081.png"));
        item->setSelected(true);
        item->setToolTip(s);

        listWidgetDirs->setIconSize(QSize(16, 16));
        listWidgetDirs->addItem(item);
    }
    else
    {
        QMessageBox::warning(this, tr("Warning"), tr("Already have a parent directory, subdirs will not append."));
    }
}

void SMainWindow::removeFromSourceList(int index)
{
    delete listWidgetDirs->takeItem(index);
}

void SMainWindow::timerEvent(QTimerEvent *event)
{
	Q_D(SMainWindow);

	if (event->timerId() == d->_enableTimer)
	{
        tbtnFilter->setEnabled(listWidgetDirs->count() > 0);
        comboBox->setEnabled(listWidgetDirs->count() > 0);

        tbtnStart->setEnabled(comboBox->count() > 0);
	}
}

void SMainWindow::generateExtensionList(const QStringList& list)
{
    foreach(auto l, list)
    {
        QListWidgetItem* item = new QListWidgetItem(l);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setIcon(QIcon(QString(":/resources/%1.png").arg(QFileInfo(l).suffix())));
        listWidgetFiles->addItem(item);
        listWidgetFiles->scrollToItem(item);
    }
}

void SMainWindow::generateFilesList()
{
    listWidgetFiles->clear();

    tbtnStop->setEnabled(true);
    tbtnStart->setEnabled(false);

    QStringList dirs;
    for(int i = 0; i < listWidgetDirs->count(); i++)
        dirs.append(listWidgetDirs->item(i)->text());

    SEntryListThread* thread = new SEntryListThread(dirs, comboBox->currentText().split(";"), this);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    connect(tbtnStop, &QToolButton::clicked, [&](){ thread->terminate(); thread->wait(); delete thread; });
    connect(thread, &SEntryListThread::entryList, this, &SMainWindow::generateExtensionList, Qt::QueuedConnection);
    thread->start();

    tbtnStop->setEnabled(false);
    tbtnStart->setEnabled(true);
}


