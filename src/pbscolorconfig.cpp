
#include <QFile>
#include <QDebug>

#include "pbscolorconfig.h"

PBSColorConfig::PBSColorConfig(const QString& file)
{
    load(file);
}

bool PBSColorConfig::load(const QString& file)
{
    // the QSettings doesn't seem to report any failures to open the settings  file
    // sync() changes status() but thats only for writes. There's no "isValid" either..
    // what a piece of shit...
    QFile io(file);
    if (!io.open(QIODevice::ReadOnly))
        return false;

    colorSettings = std::make_unique<QSettings>(file, QSettings::IniFormat);
    return true;
}

QString PBSColorConfig::readString(const QString &group, const QString &key, QString aDefault)
{
    colorSettings->beginGroup(group);
    QVariant v = colorSettings->value(key, aDefault);

    colorSettings->endGroup();

    return v.type() == QVariant::StringList ? v.toStringList().join(",") : v.toString();
}

qreal PBSColorConfig::contrastF()
{
    return 0.1 * readQReal("KDE", "contrast", 7);
}

QColor PBSColorConfig::readBrush(const QString &group, const QString &key, QColor cl)
{
    QString sD(QString("%1,%2,%3").arg(cl.red()).arg(cl.green()).arg(cl.blue()));

    QColor sCl(readColor(group, key, sD));

    return sCl;
}

int PBSColorConfig::readInt(const QString &group, const QString &key, int aDefault)
{
    QString s(QString("%1").arg(aDefault));
    QString ix = readString(group, key, s);

    bool b;
    qreal d = ix.toInt(&b);

    return b ? d : aDefault;
}

bool PBSColorConfig::readBool(const QString &group, const QString &key, bool aDefault)
{
    QString s(QString("%1").arg(aDefault ? "1" : "0"));

    QString ss =  readString(group, key, s).trimmed().toUpper();
    if(!ss.isEmpty())
    {
        bool b;
        int ix = readString(group, key, s).toInt(&b);
        return b ? ix == 1 : ss.at(0) == 'T';
    }

    return false;
}

qreal PBSColorConfig::readQReal(const QString &group, const QString &key, qreal aDefault)
{
    QString s(QString("%1").arg(aDefault));
    bool b;
    qreal ix = readString(group, key, s).toDouble(&b);

    return b ? ix : aDefault;
}

QColor PBSColorConfig::readColor(const QString &group, const QString &key, QColor aDefault)
{
    QString s(QString("%1,%2,%3").arg(aDefault.red()).arg(aDefault.green()).arg(aDefault.blue()));
    QString ix = readString(group, key, s);

    QStringList clL = ix.split(",");
    if(clL.count() > 2)
        return QColor(clL[0].toInt(), clL[1].toInt(), clL[2].toInt());

    return QColor(0, 0, 0);
}
