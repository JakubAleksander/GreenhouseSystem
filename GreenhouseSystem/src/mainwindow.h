#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

#include "digitalclock.h"
#include "sectionsmanager.h"
#include "messenger.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_addSection_clicked();
    void on_btn_quit_clicked();

    void on_btn_loadSection_clicked();

signals:

private:
    Ui::MainWindow *ui;
    Messenger *messenger;
};

#endif // MAINWINDOW_H
