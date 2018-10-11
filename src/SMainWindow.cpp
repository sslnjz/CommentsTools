#include "SMainWindow.h"
#include "ui_MainWindow.h"
#include "STypeDialog.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfoList>
#include <QDebug>

class SMainWindowPrivate
{
public:
	SMainWindowPrivate(SMainWindow* q) : q_ptr(q)
	{

	}

public:
	QStringList _types;
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

    connect(tbtnStart, &QToolButton::clicked, [&](){

        listWidgetFiles->clear();

        tbtnStop->setEnabled(true);
        tbtnStart->setEnabled(false);

        generateExtensionList(generateFileList());

        tbtnStop->setEnabled(false);
        tbtnStart->setEnabled(true);
    });

    connect(tbtnFilter, &QToolButton::clicked, [&]() {
		Q_D(SMainWindow);
		STypeDialog dlg(this);
        if (dlg.exec() == QDialog::Accepted){
			d->_types.append(dlg.types());
            comboBox->addItem(d->_types.join(";"));
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
    if(listWidgetDirs->findItems(s, Qt::MatchCaseSensitive).count() == 0){
        QListWidgetItem* item = new QListWidgetItem(s);
        item->setIcon(QIcon("://resources/1201081.png"));
        item->setSelected(true);
        item->setToolTip(s);

        listWidgetDirs->setIconSize(QSize(16, 16));
        listWidgetDirs->addItem(item);
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

QStringList SMainWindow::generateFileList()
{
    Q_D(SMainWindow);
    QStringList sources;

    for(int i = 0; i < listWidgetDirs->count(); i++)
    {
        if(d->_generateStop)
            break;

        QString dp = listWidgetDirs->item(i)->text();
        QDir dir(dp);

        entryFileList(dir, sources, d->_types);
    }
    return sources;
}

void SMainWindow::entryFileList(const QDir& dir, QStringList& s, const QStringList& filters /*= QStringList()*/)
{
    Q_D(SMainWindow);
    if(d->_generateStop)
        return;

    QFileInfoList infos = dir.entryInfoList(QDir::Dirs|QDir::Files | QDir::NoDotAndDotDot);
    qDebug() << infos;
    for(int i = 0; i < infos.count(); i++)
    {
        if(infos[i].isDir())
            entryFileList(QDir(infos[i].absoluteFilePath()), s, filters);
        else if(infos[i].isFile() && filters.contains(infos[i].suffix().insert(0, '.')))
        {
            s.append(infos[i].absoluteFilePath());
        }
    }
}

void SMainWindow::generateExtensionList(const QStringList& list)
{
    foreach(auto l, list)
    {
        QListWidgetItem* item = new QListWidgetItem(l);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setIcon(QIcon(QString(":/resources/%1++.png").arg(QFileInfo(l).suffix().contains("h") ? "h" : "c")));
        listWidgetFiles->addItem(item);
    }
}


