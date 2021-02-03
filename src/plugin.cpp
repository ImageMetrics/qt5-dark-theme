
#include "plugin.h"
#include "Kvantum.h"
#include "pbsskin.h"

namespace {
class ThemeChanger : public Kvantum::IKvantumThemeChanger
{
public:
    virtual void setTheme(void* kvantum_style, const QString& baseThemeName, bool useDark) override
    {
       auto* ptr = static_cast<Kvantum::Style*>(kvantum_style);
       ptr->setTheme(baseThemeName, useDark);
    }
    virtual QStyle* makeSkin(const QString& theme_home, const QString& theme_name, bool use_dark) override
    {
        auto* ret = new Kvantum::PBSSkin(theme_home, use_dark);
        ret->setTheme(theme_name, use_dark);
        ret->setProperty("__kvantum_theme_hack", QVariant::fromValue((void*)this));
        return ret;
    }
};

ThemeChanger theme_changer;
} // namespace

QStringList KvantumStylePlugin::keys() const
{
    QStringList ret;
    ret << "kvantum";
    ret << "kvantum-dark";
    return ret;
}

QStyle* KvantumStylePlugin::create(const QString& key)
{
    QStyle* ret = nullptr;
    if (key == "kvantum")
        ret = new Kvantum::Style(false);
    else if (key == "kvantum-dark")
        ret = new Kvantum::Style(true);
    else return nullptr;
    ret->setProperty("__kvantum_theme_hack", QVariant::fromValue((void*)&theme_changer));
    return ret;
}