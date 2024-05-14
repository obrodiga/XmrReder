#include "edit_line.h"
#include "ui_edit_line.h"

edit_line::edit_line(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_line)
{
    ui->setupUi(this);
    this->setWindowTitle("Редактирование парметров");
}

edit_line::~edit_line()
{
    delete ui;
}
