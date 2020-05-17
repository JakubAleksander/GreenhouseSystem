#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    messenger = new Messenger();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_addSection_clicked()
{
    Parameters parameters;

    SectionSettings* sectionSettings = new SectionSettings(this);
    sectionSettings->setParameters(parameters);

    if(sectionSettings->exec() == QDialog::Accepted){
        parameters = sectionSettings->downloadParameters();
        Section *section = new Section(parameters);
        connect(messenger, &Messenger::signalNewParamsFromGreenhouse, section, &Section::setReseivedParameters);
        ui->sectionsManager->addSection(section);
    }
    delete sectionSettings;
}

void MainWindow::on_btn_quit_clicked()
{
    QApplication::quit();
}
