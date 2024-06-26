#include "filesaver.h"
#include "ui_filesaver.h"

filesaver::filesaver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filesaver)
{
    ui->setupUi(this);
    this->setWindowTitle("Сохранение файла");
}

filesaver::~filesaver()
{
    delete ui;
}

void filesaver::on_yesButton_clicked()
{
    QDialog::close();
}


void filesaver::on_noButton_clicked()
{
    QString FileName= QFileDialog::getOpenFileName(this, tr("Open XML File"), "", tr("XML file (*.xml)"));;
    emit newFileName(FileName);
    QDialog::close();
}

