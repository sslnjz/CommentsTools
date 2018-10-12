#ifndef SENTRYLISTTHREAD_H
#define SENTRYLISTTHREAD_H

#include <QThread>
#include <QDir>

class SEntryListThread : public QThread
{
    Q_OBJECT
public:
    explicit SEntryListThread(const QStringList& dirs, const QStringList& filters, QObject* parent = nullptr);
    virtual ~SEntryListThread() override;

    void setDirsAndFilters(const QStringList& dirs, const QStringList& filters);

Q_SIGNALS:
    void entryList(QStringList list);

protected:
    virtual void run() override;

private:
    void entryFileList(const QDir& dir, QStringList& list, const QStringList& filters = QStringList());
    QStringList generateFilesList(const QStringList& dirs, const QStringList& filters);

private:
    QStringList _dirs;
    QStringList _filters;
};

#endif // SENTRYLISTTHREAD_H
