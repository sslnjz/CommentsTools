#pragma once

#include <QDialog>
#include "ui_STypeDialog.h"

class STypeDialog : public QDialog, public Ui::STypeDialog
{
	Q_OBJECT

public:
	STypeDialog(QWidget *parent = Q_NULLPTR);
	~STypeDialog();

	QStringList types() const;
};
