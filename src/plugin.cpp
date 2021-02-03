
#include "plugin.h"
#include "Kvantum.h"

namespace {
class ThemeChanger : public Kvantum::IKvantumThemeChanger
{
public:
    virtual bool setTheme(void* kvantum_style, const QString &config, const QString& svg, const QString& color_config) override
    {
       auto* ptr = static_cast<Kvantum::Style*>(kvantum_style);
       return ptr->setTheme(config, svg, color_config);
    }
};

ThemeChanger theme_changer;
} // namespace

QStringList KvantumStylePlugin::keys() const
{
    QStringList ret;
    ret << "kvantum";
    return ret;
}

QStyle* KvantumStylePlugin::create(const QString& key)
{
    QStyle* ret = nullptr;
    if (key == "kvantum")
        ret = new Kvantum::Style();
    else return nullptr;
    ret->setProperty("__kvantum_theme_hack", QVariant::fromValue((void*)&theme_changer));
    return ret;
}