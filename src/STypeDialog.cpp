#include "STypeDialog.h"

#include <QtDebug>

STypeDialog::STypeDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);

	connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accepted);
	connect(checkBox, &QCheckBox::stateChanged, [&](int state) {
		for (int i = 0; i < listWidget->count(); i++)
		{
			listWidget->item(i)->setCheckState((Qt::CheckState)state);
		}
	});
}

STypeDialog::~STypeDialog()
{
    qDebug() << "~STypeDialog()";
}

QStringList STypeDialog::types() const
{
	QStringList ts;
	for (int i = 0; i < listWidget->count(); i++)
	{
		QListWidgetItem* item = listWidget->item(i);
		if (item->checkState() & Qt::Checked)
            ts.append(item->text().split("-").first().trimmed());
	}

	return ts;
}
