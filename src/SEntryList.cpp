#include "SEntryList.h"

#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>


#include <QDebug>

using namespace boost;
using namespace boost::filesystem;

const QVector<QString>& filterDirs(const QString& rootPath, const QVector<QString>& filters, QVector<QString>& container=*(new QVector<QString>())){
    namespace fs = boost::filesystem;
    fs::path p(rootPath.toStdString());
    QVector<QString> &ret = container;

    if(!fs::exists(p))
    {
        return ret;
    }

    fs::recursive_directory_iterator end_iter;
    for(fs::recursive_directory_iterator iter(p);iter!=end_iter;iter++)
    {
        try
        {
            if (fs::is_regular_file( *iter ))
            {
                for(QVector<QString>::const_iterator vt = filters.begin(); vt != filters.end(); vt++)
                {
                    if((*vt) == QString::fromStdString( iter->path().extension().string())){
                        ret.push_back(QString::fromStdString( iter->path().string()) );
                        std::cout << *iter << std::endl;
                    }
                }
            }
        }
        catch ( const std::exception & ex )
        {
            std::cerr << ex.what() << std::endl;
            continue;
        }
    }
    return ret;
}


SEntryList::SEntryList(const QStringList& dirs, const QStringList& filters, QObject* parent)
    : QObject (parent)
    , _dirs(dirs)
    , _filters(filters)
{

}

SEntryList::~SEntryList()
{
    qDebug() << "~SEntryListThread";
}

QVector<QString> SEntryList::generateFilesList(const QStringList& dirs, const QStringList& filters)
{

    QVector<QString> sources;
    foreach(auto d, dirs)
    {
        QVector<QString> s = filterDirs(d, filters.toVector());
        sources << s;
    }

    return sources;
}


void SEntryList::run()
{
    QVector<QString> s = generateFilesList(_dirs, _filters);
    emit entryFileList(s);
}

