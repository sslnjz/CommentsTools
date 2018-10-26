#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qglobal.h>
#include <QMainWindow>
#include <QDir>
#include <QVector>
#include "ui_MainWindow.h"

namespace Ui {
class SMainWindow;
}



class SMainWindowPrivate;
class SMainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
public:
    explicit SMainWindow(QWidget *parent = nullptr);
    virtual ~SMainWindow() override;

protected:
	virtual void timerEvent(QTimerEvent *event) override;

private Q_SLOTS:
	void addFilterPath();
    void generateFilesList();

private:
    void addItem2SourceList(const QString& s);
    void removeFromSourceList(int index);
    void generateExtensionList(const QVector<QString>& list);

private:
    QScopedPointer<SMainWindowPrivate> d_ptr;
    Q_DISABLE_COPY(SMainWindow)
	Q_DECLARE_PRIVATE(SMainWindow)
};

#endif // MAINWINDOW_H
