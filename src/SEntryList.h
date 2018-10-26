#ifndef SENTRYLIST_H
#define SENTRYLIST_H

#include <QThread>
#include <QDir>

#include <string>
#include <vector>

using namespace std;

class SEntryList : public QObject
{
    Q_OBJECT
public:
    explicit SEntryList(const QStringList& dirs, const QStringList& filters, QObject* parent = nullptr);
    virtual ~SEntryList() override;


Q_SIGNALS:
    void entryFileList(const QVector<QString>& s);

public Q_SLOTS:
     void run();

private:
    QVector<QString> generateFilesList(const QStringList& dirs, const QStringList& filters);
    const QStringList entryList(const QString& rootPath, const QStringList& filters);

private:
    QStringList _dirs;
    QStringList _filters;
};

#endif // SENTRYLIST_H
