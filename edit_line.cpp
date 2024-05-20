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
    QString s;
    QStringList list;
    list=NewStr.split(' ');

    s=list[0];
    if (s.contains("line")==true)
    {
        s=s.remove("line ");
        ui->EditName->setText("line");
        ui->label1->setText("Адрес");
        ui->label1->setVisible(true);
        ui->line1->setVisible(true);

        ui->label2->setText("Порт");
        ui->label2->setVisible(true);
        ui->line2->setVisible(true);

        ui->label3->setText("Тип");
        ui->label3->setVisible(true);
        ui->line3->setVisible(true);

        ui->label4->setText("Бодрей");
        ui->label4->setVisible(true);
        ui->line4->setVisible(true);
    }
    if (s.contains("logical_device")==true)
    {
        s=s.remove("logical_device ");
        ui->EditName->setText("logical_device");
        ui->label1->setText("Адрес");
        ui->label1->setVisible(true);
        ui->line1->setVisible(true);

        ui->label2->setText("Модуль");
        ui->label2->setVisible(true);
        ui->line2->setVisible(true);

        ui->label3->setText(" ");
        ui->label3->setVisible(false);
        ui->line3->setVisible(false);

        ui->label4->setText(" ");
        ui->label4->setVisible(false);
        ui->line4->setVisible(false);
    }
    if (s.contains("object")==true)
    {
        s=s.remove("object ");
        ui->EditName->setText("object");
        ui->label1->setText("ID");
        ui->label1->setVisible(true);
        ui->line1->setVisible(true);

        ui->label2->setText("Логическое имя");
        ui->label2->setVisible(true);
        ui->line2->setVisible(true);

        ui->label3->setText("Источник данных");
        ui->label3->setVisible(true);
        ui->line3->setVisible(true);

        ui->label4->setText(" ");
        ui->label4->setVisible(false);
        ui->line4->setVisible(false);
    }

    for (int i=0; i<list.size();i++)
    {
        s.clear();
        s=list[i];
        if (s.contains("type")==true)
        {
            s=s.remove("type=");
            s.remove(0, 1);
            s.remove((s.size()-1), 1);
            ui->line3->setText(s);
        }
        if (s.contains("port")==true)
        {
            s=s.remove("port=");
            s.remove(0, 1);
            s.remove((s.size()-1), 1);
            ui->line2->setText(s);
        }
        if (s.contains("address")==true)
        {
            s=s.remove("address=");
            s.remove(0, 1);
            s.remove((s.size()-1), 1);
            ui->line1->setText(s);
        }
        if (s.contains("baudrate")==true)
        {
            s=s.remove("baudrate=");
            s.remove(0, 1);
            s.remove((s.size()-1), 1);
            ui->line4->setText(s);
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
    temp=ui->line3->text();
    if (!temp.isEmpty())
    {
        newLineValue=newLineValue+"type="+KavStr+temp+KavStr;
    }
    temp=ui->line2->text();
    if (!temp.isEmpty())
    {
        newLineValue=newLineValue+" port="+KavStr+temp+KavStr;
    }
    temp=ui->line1->text();
    if (!temp.isEmpty())
    {
        newLineValue=newLineValue+" address="+KavStr+temp+KavStr;
    }
    temp=ui->line4->text();
    if (!temp.isEmpty())
    {
        newLineValue=newLineValue+" baudrate="+KavStr+temp+KavStr;
    }
    emit newLine(newLineValue);
    QDialog::close();
}

