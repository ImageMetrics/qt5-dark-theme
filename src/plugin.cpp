
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

QStyle* KvantumStylePlugin::create(const QString& key)
{
    // the keys are listed in kvantum.json

    Kvantum::Style* ret = nullptr;
    if (key == "kvantum")
        ret = new Kvantum::Style();
    else if (key == "darklines") {
        ret = new Kvantum::Style();
        ret->setTheme(":DarkLines/DarkLines.config",
                      ":DarkLines/DarkLines.svg",
                      ":DarkLines/DarkLines.colors");
    }
    else if (key == "kvantum-curves") {
        ret = new Kvantum::Style();
        ret->setTheme(":KvCurves/KvCurves.config",
                      ":KvCurves/KvCurves.svg",
                      ":KvCurves/KvCurves.colors");
    } else if (key == "kvantum-dark-red") {
        ret = new Kvantum::Style();
        ret->setTheme(":KvDarkRed/KvDarkRed.config",
                      ":KvDarkRed/KvDarkRed.svg",
                      ":KvDarkRed/KvDarkRed.colors");
    }
    else return nullptr;
    ret->setProperty("__kvantum_theme_hack", QVariant::fromValue((void*)&theme_changer));
    return ret;
}