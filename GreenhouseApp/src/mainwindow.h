#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QPushButton>

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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addSection();
    void closeApp();
    void loadSection();

signals:

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
