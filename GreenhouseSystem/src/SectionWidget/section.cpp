#include "section.h"
#include "ui_section.h"

Section::Section(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Section)
{
    ui->setupUi(this);
}

Section::~Section()
{
    delete ui;
}
