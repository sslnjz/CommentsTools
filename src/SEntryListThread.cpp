#include "SEntryListThread.h"

#include <QDebug>

SEntryListThread::SEntryListThread(const QStringList& dirs, const QStringList& filters, QObject* parent)
    : QThread (parent)
    , _dirs(dirs)
    , _filters(filters)
{

}

SEntryListThread::~SEntryListThread()
{
    qDebug() << "~SEntryListThread";
}

QStringList SEntryListThread::generateFilesList(const QStringList& dirs, const QStringList& filters)
{
    QStringList sources;
    foreach(auto d, dirs)
    {
        entryFileList(d, sources, filters);
    }

    return sources;
}

void SEntryListThread::entryFileList(const QDir& dir, QStringList& s, const QStringList& filters /*= QStringList()*/)
{
    QFileInfoList infos = dir.entryInfoList(QDir::Dirs| QDir::Files | QDir::NoDotAndDotDot);
    foreach(QFileInfo info, infos)
    {
        if(info.isDir())
            entryFileList(QDir(info.absoluteFilePath()), s, filters);
        else if(info.isFile() && filters.contains(info.suffix().insert(0, '.')))
        {
            s.append(info.absoluteFilePath());
            if(s.count() == 100){
                emit entryList(s);
                s.clear();
            }
        }
    }
}

void SEntryListThread::run()
{
    QStringList s = generateFilesList(_dirs, _filters);
    emit entryList(s);
}

void SEntryListThread::setDirsAndFilters(const QStringList& dirs, const QStringList& filters)
{
    _dirs = dirs;
    _filters = filters;
}
