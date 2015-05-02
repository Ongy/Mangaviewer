#ifndef PROVIDERCOLLECTION_H
#define PROVIDERCOLLECTION_H

#include <QObject>
#include <QPluginLoader>
#include <QMap>
#include <QStringList>
#include <QPointer>
#include "mangaviewer/plugins.h"

class ProviderCollection : public QObject
{
    Q_OBJECT
    QMap<QString, QPointer<QPluginLoader> > plugins;
    QPointer<QPluginLoader> last;
public:
    explicit ProviderCollection(QObject *parent = 0);
    QStringList getPluginList();
    ImageProvider * getPlugin(const QString & name);

signals:

public slots:
};

#endif // PROVIDERCOLLECTION_H
