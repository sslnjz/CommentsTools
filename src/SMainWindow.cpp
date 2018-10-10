#include "SMainWindow.h"
#include "ui_MainWindow.h"
#include "STypeDialog.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

class SMainWindowPrivate
{
public:
	SMainWindowPrivate(SMainWindow* q) : q_ptr(q)
	{

	}

public:
	QStringList _types;
	int _enableTimer;

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
    connect(listWidget, &QListWidget::currentRowChanged, [&](int row){ tbtnDelete->setEnabled(row >= 0); });
    connect(tbtnDelete, &QToolButton::clicked, [&](){ removeFromSourceList(listWidget->currentRow()); });
	connect(tbtnFilter, &QToolButton::clicked, [&]() {
		Q_D(SMainWindow);

		STypeDialog dlg(this);
		if (dlg.exec() == QDialog::Accepted)
		{
			d->_types.append(dlg.types());
		}

		comboBox->addItem(d->_types.join(";"));
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
	{
		QMessageBox::warning(this, tr("Warning"), tr("Please select a directory"));
	}
	else
    {
        addItem2SourceList(path);
	}
}

void SMainWindow::addItem2SourceList(const QString& s)
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

void SMainWindow::removeFromSourceList(int index)
{
    delete listWidget->takeItem(index);
}

void SMainWindow::timerEvent(QTimerEvent *event)
{
	Q_D(SMainWindow);

	if (event->timerId() == d->_enableTimer)
	{
		if (listWidget->count() > 0)
		{
			tbtnFilter->setEnabled(true);
			comboBox->setEnabled(true);
		}
		else
		{
			tbtnDelete->setEnabled(false);
			tbtnFilter->setEnabled(false);
			comboBox->setEnabled(false);
		}

		if (comboBox->count() > 0)
		{
			tbtnStart->setEnabled(true);
		}
		else
		{
			tbtnStart->setEnabled(false);
		}
	}
}
