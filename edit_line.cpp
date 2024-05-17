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

void edit_line::SetStr(QString NewStr)
{
    QString s, type, address;
    QStringList list;
    list=NewStr.split(' ');

    for (int i=0; i<list.size();i++)
    {
        s.clear();
        s=list[i];
        if (s.contains("line")==true)
        {
            s=s.remove("line ");
        }
        if (s.contains("type")==true)
        {
            s=s.remove("type=");
            s.remove(0, 1);
            s.remove((s.size()-1), 1);
            ui->lineType->setText(s);
        }
        if (s.contains("port")==true)
        {
            s=s.remove("port=");
            s.remove(0, 1);
            s.remove((s.size()-1), 1);
            ui->linePort->setText(s);
        }
        if (s.contains("address")==true)
        {
            s=s.remove("address=");
            s.remove(0, 1);
            s.remove((s.size()-1), 1);
            ui->lineAddress->setText(s);
        }
        if (s.contains("baudrate")==true)
        {
            s=s.remove("baudrate=");
            s.remove(0, 1);
            s.remove((s.size()-1), 1);
            ui->lineBodrei->setText(s);
        }
    }
}

void edit_line::on_pushButton_2_clicked()
{
    QDialog::close();
}


void edit_line::on_discasCange_clicked()
{
    QString temp, newLineValue="line ", KavStr;
    QChar kav=34;
    KavStr.push_back(kav);
    temp=ui->lineType->text();
    if (!temp.isEmpty())
    {
        newLineValue=newLineValue+"type="+KavStr+temp+KavStr;
    }
    temp=ui->linePort->text();
    if (!temp.isEmpty())
    {
        newLineValue=newLineValue+" port="+KavStr+temp+KavStr;
    }
    temp=ui->lineAddress->text();
    if (!temp.isEmpty())
    {
        newLineValue=newLineValue+" address="+KavStr+temp+KavStr;
    }
    temp=ui->lineBodrei->text();
    if (!temp.isEmpty())
    {
        newLineValue=newLineValue+" baudrate="+KavStr+temp+KavStr;
    }
    ui->label->setText(newLineValue);
    emit newLine(newLineValue);
    QDialog::close();
}

