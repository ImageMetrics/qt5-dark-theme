#ifndef PBSCOLORCONFIG_H
#define PBSCOLORCONFIG_H

#include <QSettings>
#include <QColor>
#include <QBrush>
#include <memory>

class PBSColorConfig
{
public:
    PBSColorConfig(const QString& file);
    PBSColorConfig() = default;
    bool load(const QString& file);
    QString readString(const QString &group, const QString &key, QString aDefault);
    int readInt(const QString &group, const QString &key, int aDefault);
    qreal readQReal(const QString &group, const QString &key, qreal aDefault);
    bool readBool(const QString &group, const QString &key, bool aDefault);
    QColor readColor(const QString &group, const QString &key, QColor aDefault);

    QColor readBrush(const QString &group, const QString &key, QColor);

    QSettings &settings() { return *colorSettings; }

    static QByteArray serializeList(const QList<QByteArray> &list);
    static QStringList deserializeList(const QString &data);

    qreal contrastF();
private:
    std::unique_ptr<QSettings> colorSettings;
};

#endif // PBSCOLORCONFIG_H
