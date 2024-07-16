#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <maccategorycombobox.h>
#include <parsec_mac_qt5_global.h>
#include <maccategorylistwidget.h>.


namespace Ui {
class MainWindow;
}

namespace ParsecQt5 {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    ParsecQt5::MacCategoryListWidget *macCategoryListWidget;
};

#endif // MAINWINDOW_H
