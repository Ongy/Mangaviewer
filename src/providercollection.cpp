#include "providercollection.h"
#include <QDir>


ProviderCollection::ProviderCollection(QObject *parent)
    : QObject(parent)
    , last(NULL)
{
    QString path = QDir::homePath();
    path.append("/.mangaviewer/plugins");
    QDir dir(path);
    if(!dir.exists()) {
        qDebug("Plugin dir does not exist, this is not acceptable, this application cannot run without plugins");
        qDebug("Please create directory and place at least one plugin in there: %s", dir.absolutePath().toStdString().c_str());
        return;
    }
    QStringList list = dir.entryList();
    foreach (const QString & plugin, list) {
        if( plugin == "" || plugin == "." || plugin == ".." )
            continue;
        QString file = path + "/" + plugin;
        qDebug("Considering Plugin: %s", file.toStdString().c_str());
        QPointer<QPluginLoader> loader (new QPluginLoader(file));
        this->plugins.insert(plugin.section(".", 0, 0), loader);
    }
}


QStringList ProviderCollection::getPluginList()
{
    return this->plugins.keys();
}

ImageProvider * ProviderCollection::getPlugin(const QString & name)
{
    if(this->last)
        this->last->unload();
     QPointer<QPluginLoader> loader = this->last = this->plugins.find(name).value();
     return qobject_cast<ImageProvider *>(loader->instance());
}

ProviderCollection::~ProviderCollection()
{
    if(this->last)
        this->last->unload();
}
