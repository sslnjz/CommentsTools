#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qglobal.h>
#include <QMainWindow>
#include "ui_MainWindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private Q_SLOTS:
	void addFilterPath();

private:
    void addItem2SourceList(const QString& s);
    void removeFromSourceList(int index);

private:
    Q_DISABLE_COPY(MainWindow)
};

#endif // MAINWINDOW_H
