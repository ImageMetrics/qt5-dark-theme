
#include "plugin.h"
#include "Kvantum.h"

#include <memory>

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

    auto ret = true;
    auto style = std::make_unique<Kvantum::Style>();
    if (key == "darklines") {
        ret = style->setTheme(":DarkLines/DarkLines.kvconfig",
                              ":DarkLines/DarkLines.svg",
                              ":DarkLines/DarkLines.colors");
    }
    else if (key == "kvantum-curves") {
        ret = style->setTheme(":KvCurves/KvCurves.kvconfig",
                              ":KvCurves/KvCurves.svg",
                              ":KvCurves/KvCurves.colors");
    }
    else if (key == "kvantum-dark-red") {
        ret = style->setTheme(":KvDarkRed/KvDarkRed.kvconfig",
                              ":KvDarkRed/KvDarkRed.svg",
                              ":KvDarkRed/KvDarkRed.colors");
    }
    else if (key != "kvantum") return nullptr;

    if (!ret)
        return nullptr;

    style->setProperty("__kvantum_theme_hack", QVariant::fromValue((void*)&theme_changer));
    return style.release();
}