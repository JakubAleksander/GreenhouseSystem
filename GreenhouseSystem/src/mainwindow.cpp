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
    QMessageBox msgBox;
    QPushButton *cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::ActionRole);
    QPushButton *dontSaveButton = msgBox.addButton(tr("Don't save and quit"), QMessageBox::ActionRole);
    QPushButton *saveButton = msgBox.addButton(tr("Save and quit"), QMessageBox::ActionRole);
    msgBox.setText("Turn off the greenhouse system?");
    msgBox.setInformativeText("Do you want to save the current section settings?");
    msgBox.exec();

    if(msgBox.clickedButton() != cancelButton){
        if(msgBox.clickedButton() == saveButton){
            ui->sectionsManager->saveAllSectionsToFile("/home/jakub/Desktop");
        }
    QApplication::quit();
    }

    delete cancelButton;
    delete dontSaveButton;
    delete saveButton;
}

void MainWindow::on_btn_loadSection_clicked()
{
    Parameters parameters;
    Section *section = new Section(parameters);

    QString filename = QFileDialog::getOpenFileName(this, tr("Choose section file"), tr("Image files(*.section)"));
    if(!(ui->sectionsManager->loadSection(filename, section))){
        QMessageBox msgBox;
        msgBox.setText("Can't load section");
        msgBox.setInformativeText("Section path:  " + filename);
        msgBox.exec();
        return;
    }
    connect(messenger, &Messenger::signalNewParamsFromGreenhouse, section, &Section::setReseivedParameters);
    ui->sectionsManager->addSection(section);
}
