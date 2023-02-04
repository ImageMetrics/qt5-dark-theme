
#include <QApplication>
#include <QStyle>

#include <iostream>

#include "mainwindow.h"

class IKvantumThemeChanger
{
public:
    virtual ~IKvantumThemeChanger() = default;
    virtual bool setTheme(void* kvantum_style, const QString& config, const QString& svg, const QString& color_config) = 0;
};

bool SetTheme(const QString& theme)
{
    QStyle* kvantum = QApplication::style();
    if (kvantum)
    {
        // this hack is done so that this executable doesn't need to
        // link against kvantum.dll
        QVariant hack = kvantum->property("__kvantum_theme_hack");
        if (!hack.isValid())
            return false;

        void* ptr = qvariant_cast<void*>(hack);
        auto* theme_changer = static_cast<IKvantumThemeChanger*>(ptr);
        bool ret = true;
        if (theme == "darklines")
        {
            if (!theme_changer->setTheme(kvantum,
                ":DarkLines/DarkLines.kvconfig",
                ":DarkLines/DarkLines.svg",
                ":DarkLines/DarkLines.colors"))
                return false;
        }
        else if (theme == "kvantum-curves")
        {
            if (!theme_changer->setTheme(kvantum,
                ":KvCurves/KvCurves.kvconfig",
                ":KvCurves/KvCurves.svg",
                ":KvCurves/KvCurves.colors"))
                return false;
        }
        else if (theme == "kvantum-dark-red") {
            if (!theme_changer->setTheme(kvantum,
                ":KvDarkRed/KvDarkRed.kvconfig",
                ":KvDarkRed/KvDarkRed.svg",
                ":KvDarkRed/KvDarkRed.colors"))
                return false;
        }
        else if (theme == "glow-dark")
        {
            if (!theme_changer->setTheme(kvantum,
                ":kvGlowDark/kvGlowDark.kvconfig",
                ":kvGlowDark/kvGlowDark.svg",
                ":kvGlowDark/kvGlowDark.colors"))
                return false;
        }
        qApp->setPalette(kvantum->standardPalette());
        return true;
    }
    return false;
}

int main(int argc, char* argv[])
{
    QString style = "kvantum";
    QString theme;
    for (int i = 1; i < argc; ++i)
    {
        if (!strcmp(argv[i], "--style"))
            style = argv[i + 1];
        else if (!strcmp(argv[i], "--theme"))
            theme = argv[i + 1];
    }

    QApplication a(argc, argv);


    if (auto* engine = QApplication::setStyle(style))
    {
        std::cout << "Set application style to 'kvantum with default theme.'";
        std::cout << std::endl;
        QApplication::setPalette(engine->standardPalette());
    }
    else
    {
        std::cout << "Failed to create kvantum style.\n";
        std::cout << "Do you have styles/Kvantum.dll?\n";
        std::cout << "It should have been built when this executable was built.\n";
        std::cout << "If styles/Kvantum.dll exists when I have no idea. Sorry :(\n";
        return 1;
    }

    MainWindow w;
    w.show();

    if (!theme.isEmpty())
    {
        if (SetTheme(theme))
        {
            std::cout << "Set application style to 'kvantum with " << theme.toStdString() << " theme.";
            std::cout << std::endl;
        }
        else
        {
            std::cout << "Failed to set kvantum theme.";
            std::cout << std::endl;
            return 1;
        }
    }
    return a.exec();
}
