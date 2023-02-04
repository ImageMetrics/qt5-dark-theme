#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QAbstractTableModel>
#include <QABstractListModel>
#include <qstylefactory>
#include <QTimer>

#include <Kvantum.h>

#include <vector>

#define USEKVANTUM

struct Fruit {
    QString name;
    QString color;
};

class TableModel : public QAbstractTableModel
{
public:
    TableModel()
    {
        mFruits.push_back({ "Banana", "Yellow" });
        mFruits.push_back({ "Apple", "Green" });
        mFruits.push_back({ "Orange", "Orange" });
    }
    virtual QVariant data(const QModelIndex& index, int role) const override
    {
        if (role == Qt::DisplayRole)
        {
            if (index.column() == 0)
                return mFruits[index.row()].name;
            else if (index.column() == 1)
                return mFruits[index.row()].color;
        }
        return QVariant();
    }
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override
    {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        {
            if (section == 0) return "Name";
            else if (section == 1) return "Color";
        }
        return QVariant();
    }
    virtual int rowCount(const QModelIndex&) const override
    {
        return mFruits.size();
    }
    virtual int columnCount(const QModelIndex&) const override
    {
        return 2;
    }
private:
    std::vector<Fruit> mFruits;

};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto* table_model = new TableModel();
    ui->tableView1->setModel(table_model);
    ui->tableView2->setModel(table_model);
    ui->listView1->setModel(table_model);
    ui->listView2->setModel(table_model);

    QDir path("Themes/kvantum/");
    QStringList files = path.entryList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
    ui->cmbSvgThemes->addItems(files);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RestyleWindow()
{
    const QWidgetList topLevels = QApplication::topLevelWidgets();
    for (QWidget* widget : topLevels)
    { // this is needed with Qt >= 5.13.1 but is harmless otherwise
        widget->setAttribute(Qt::WA_NoSystemBackground, false);
        widget->setAttribute(Qt::WA_TranslucentBackground, false);
    }

    // Qt5 has QEvent::ThemeChange
    const QWidgetList widgets = QApplication::allWidgets();
    for (QWidget* widget : widgets)
    {
        QEvent event(QEvent::ThemeChange);
        QApplication::sendEvent(widget, &event);
    }
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
    if (hack.isValid())
    {
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

        RestyleWindow();
    }
    else
    {
        ui->lblTheme->setText("Current style engine is not kvantum.");
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    QMessageBox::question(this, "Test", "Deneme 123",
                                    QMessageBox::Yes|QMessageBox::No);
}
