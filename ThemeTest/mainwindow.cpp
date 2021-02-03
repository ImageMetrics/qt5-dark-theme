#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QMessageBox>

#include <Kvantum.h>

#define USEKVANTUM

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDir path("Themes/kvantum/");
    QStringList files = path.entryList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
    ui->cmbSvgThemes->addItems(files);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnApply_clicked()
{
    QString dir = "Themes/Kvantum/";

    QString theme_name = ui->cmbSvgThemes->currentText();
    QString config_file  = dir + theme_name + "/" + theme_name + ".kvconfig";
    QString svg_file     = dir + theme_name + "/" + theme_name + ".svg";
    QString color_config = dir + theme_name + "/" + theme_name + ".colors";
    if (!QFile::exists(color_config))
        color_config.clear();

    // get the current style engine, it's expected to be kvantum,
    // if not then bork
    QStyle* style = qApp->style();

    // this hack is done so that this executable doesn't need to
    // link against kvantum.dll
    QVariant hack = style->property("__kvantum_theme_hack");
    void* ptr = qvariant_cast<void*>(hack);

    auto* theme_changer = static_cast<Kvantum::IKvantumThemeChanger*>(ptr);
    if (!theme_changer->setTheme(style, config_file, svg_file, color_config)) {
        QMessageBox msg(this);
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setText("Failed to load the theme.");
        msg.setWindowTitle("Oopsie!");
        msg.setIcon(QMessageBox::Critical);
        msg.exec();
        return;
    }
    qApp->setPalette(style->standardPalette());

    ui->lblTheme->setText(QString("Current Theme: %1").arg(theme_name));
}

void MainWindow::on_pushButton_8_clicked()
{
    QMessageBox::question(this, "Test", "Deneme 123",
                                    QMessageBox::Yes|QMessageBox::No);
}
