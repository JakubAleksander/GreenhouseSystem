#include "section.h"
#include "ui_section.h"

Section::Section(quint8 id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Section), id(id)
{
    ui->setupUi(this);
    //connect(w, &MainWindow::signalNewParamsFromGreenhouse, this, &Section::setParameters);
}

Section::~Section()
{
    delete ui;
}

void Section::on_btn_settings_clicked()
{

}

void Section::setReseivedParameters(Current_parameters parameters)
{
 ui->pb_watering->setValue(parameters.humidity);
 ui->pb_lighting->setValue(parameters.insolation);
}
