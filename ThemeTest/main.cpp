
#include <QApplication>
#include <QStyle>

#include <iostream>

#include "mainwindow.h"


int main(int argc, char *argv[])
{
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

    QStyle* kvantum = QApplication::setStyle("kvantum");
    if (kvantum == nullptr) {
        std::cout << "Failed to create kvantum style.\n";
        std::cout << "Do you have styles/Kvantum.dll?\n";
        std::cout << "It should have been built when this executable was built.\n";
        std::cout << "If styles/Kvantum.dll exists when I have no idea. Sorry :(\n";
        return 1;
    } else {
        std::cout << "Set application style to 'kvantum with default theme.'";
        std::cout << std::endl;
    }
    MainWindow w;
    w.show();
    return a.exec();
}
