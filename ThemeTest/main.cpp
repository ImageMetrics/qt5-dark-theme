
#include <QApplication>
#include <QStyle>

#include <iostream>

#include "mainwindow.h"


bool SetKvantum()
{
    QStyle* kvantum = QApplication::setStyle("kvantum");
    if (kvantum)
    {
        std::cout << "Set application style to 'kvantum with default theme.'";
        std::cout << std::endl;
        return true;
    }

    std::cout << "Failed to create kvantum style.\n";
    std::cout << "Do you have styles/Kvantum.dll?\n";
    std::cout << "It should have been built when this executable was built.\n";
    std::cout << "If styles/Kvantum.dll exists when I have no idea. Sorry :(\n";
    return false;
}

int main(int argc, char* argv[])
{
    bool has_style_arg = false;

    for (int i = 1; i < argc; ++i)
    {
        if (!strcmp(argv[i], "-style"))
            has_style_arg = true;
    }

    QApplication a(argc, argv);

    // Kvantum style test application.
    //
    // kvantum style engine is a Qt plugin that has 2 built-in themes.
    // kvantum and kvantum-dark.
    // It also has potential to load more themes (see themes/kvantum)
    // through PBSSkin style which is an extension of the kvantum base style
    // which is a QStyle implementation.
    // the plugin needs to be built and installed into styles/ then Qt
    // will try to find it.
    //
    // Qt also understands the -style command line parameter but here
    // we try to set the style programmatically.

    if (!has_style_arg)
    {
        if (!SetKvantum())
            return 1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
