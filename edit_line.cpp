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
