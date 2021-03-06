#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->sectionsManager);
    Messenger::createInstance();
    setWindowTitle("Greenhouse Application");

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(closeApp()));
    connect(ui->actionLoadSection, SIGNAL(triggered()), this, SLOT(loadSection()));
    connect(ui->actionAddSection, SIGNAL(triggered()), this, SLOT(addSection()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addSection()
{
    SectionSettings sectionSettings;

    SettingsDialog* settingsDialog = new SettingsDialog(this);
    settingsDialog->setParameters(sectionSettings);

    if(settingsDialog->exec() == QDialog::Accepted){
        sectionSettings = settingsDialog->downloadParameters();
        Section *section = new Section(sectionSettings);
        ui->sectionsManager->addSection(section);
        section->setPicture(sectionSettings.picture_path);
    }
    delete settingsDialog;
}

void MainWindow::closeApp()
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
            ui->sectionsManager->saveAllSectionsToFile(QDir::homePath());
        }
    QApplication::quit();
    }

    delete cancelButton;
    delete dontSaveButton;
    delete saveButton;
}

void MainWindow::loadSection()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose section file"), tr("Image files(*.section)"));
    if(filename == "") return;

    SectionSettings parameters;
    Section *section = new Section(parameters);
    if(!(ui->sectionsManager->loadSection(filename, section))){
        QMessageBox msgBox;
        msgBox.setText("Can't load section");
        msgBox.setInformativeText("Section path:  " + filename);
        msgBox.exec();
        return;
    }
    ui->sectionsManager->addSection(section);
}

