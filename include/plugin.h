
#pragma once

#include <QStylePlugin>


// plugin interface for Qt to consider this dll as a style
// https://doc.qt.io/qt-5.12/qtwidgets-tools-styleplugin-example.html
class QStringList;
class QStyle;

class KvantumStylePlugin : public QStylePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QStyleFactoryInterface" FILE "kvantum.json")

public:
    virtual QStyle *create(const QString &key) override;
};