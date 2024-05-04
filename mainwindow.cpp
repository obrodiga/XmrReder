#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

<<<<<<< Updated upstream
=======
QString AtributRead (QXmlStreamAttributes elementAtrib, QString nameElement)
{
    QString TempStr;
    TempStr.clear();
    if (nameElement=="logical_device")
    {
        if(elementAtrib.hasAttribute("address"))
        {
            TempStr="address='" +elementAtrib.value("address").toString()+"'";
        }
        if (elementAtrib.hasAttribute("module"))
        {
            TempStr=TempStr+" module='"+ elementAtrib.value("module").toString()+"'";
        }
        if (TempStr!=NULL)
        {
            TempStr="logical_device "+TempStr;
        }
    }
    if (nameElement=="line")
    {
        if(elementAtrib.hasAttribute("type"))
        {
            TempStr="type='"+elementAtrib.value("type").toString()+"'";
        }
        if (elementAtrib.hasAttribute("port"))
        {
            TempStr=TempStr+" port='"+elementAtrib.value("port").toString()+"'";
        }
        if (elementAtrib.hasAttribute("address"))
        {
            TempStr=TempStr+" address='"+elementAtrib.value("address").toString()+"'";
        }
        if (TempStr!=NULL)
        {
            TempStr="line "+TempStr;
        }
    }
    if (nameElement=="object")
    {
        if(elementAtrib.hasAttribute("class_id"))
        {
            TempStr="class_id='"+ elementAtrib.value("class_id").toString()+"'";
        }
        if (elementAtrib.hasAttribute("logical_name"))
        {
            TempStr=TempStr+" logical_name='"+elementAtrib.value("logical_name").toString()+"'";
        }
        if (elementAtrib.hasAttribute("data_source"))
        {
            TempStr=TempStr+" data_source='"+elementAtrib.value("data_source").toString()+"'";
        }
        if (TempStr!=NULL)
        {
            TempStr="object "+TempStr;
        }
    }
    return TempStr;
}
>>>>>>> Stashed changes

void MainWindow::on_pushButton_clicked()
{
    QXmlStreamReader XmlReader;//элемент класса для работы с XML файлами
    XmlReader.addData(ui->textEdit->toPlainText());//получение введённых данных
    QStack<QTreeWidgetItem*> StackTags; //список элементов для создания иерархии

    ui->treeWidget->clear();//очистка поля для вывода тегов
    ui->textBrowser->clear();

    while (!XmlReader.atEnd())//перебор всех элементов
    {
<<<<<<< Updated upstream
=======
        attrib=XmlReader.attributes();
        TempStr.clear();
        TempStr=AtributRead(attrib, XmlReader.name().toString());
        if (TempStr==NULL)
        {
            TempStr=XmlReader.name().toString();
        }


>>>>>>> Stashed changes
        if (XmlReader.isStartElement())//проверка на открывающий элемент
        {
            QStringList Tags;
            Tags<<XmlReader.name().toString();//получение имени текущего элемента
            QTreeWidgetItem* item = new QTreeWidgetItem(Tags); //создание элементов для последующего добавления в дерево
            if (StackTags.count()==0)
            {
                ui->treeWidget->addTopLevelItem(item);//добавление корневых элементов в дерево
            }
            else
            {
                StackTags.top()->addChild(item);//добавление дочернего элемента
            }
            StackTags.push_back(item);
        }
        if (XmlReader.isEndElement())//закрывающие элементы
        {
            StackTags.pop();//уадление верхнего элемнета из стека
        }
        XmlReader.readNext();//переход к следующему элементу
    }
    if (XmlReader.hasError())
    {
        ui->textBrowser->setPlainText(XmlReader.errorString());//вывод ошибки
    }
}

void MainWindow::on_FileOpen_clicked()
{
    bool Check=ui->checkBox->checkState();
    if (Check)
    {
        int itemCount=0;
        QString FileName;
        FileName = QFileDialog::getOpenFileName(this, tr("Open XML File"), "", tr("XML file (*.xml)"));
        ui->FileFolder->setText(FileName);
        QFile file(ui->FileFolder->text());

        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            ui->textBrowser->setPlainText("Не удалось открыть файл");
        }
        else
        {
            ui->treeWidget->clear();
            ui->textBrowser->clear();
            ui->textEdit->clear();
            QStack<QTreeWidgetItem*> StackTags;
            QXmlStreamReader XmlReader;
            QString TempStr;
            QXmlStreamAttributes attrib;
            XmlReader.setDevice(&file);//выставление файла откуда происходит чтение
            XmlReader.readNext();

            while (!XmlReader.atEnd())
            {
                bool flagAtr=false;
                attrib=XmlReader.attributes();
                TempStr.clear();
<<<<<<< Updated upstream
                if (XmlReader.name().toString()=="logical_device")
                {
                    if(attrib.hasAttribute("address"))
                    {
                        TempStr="address = ";
                        TempStr += attrib.value("address").toString();
                    }
                    if (attrib.hasAttribute("module"))
                    {
                        TempStr+="  module = ";
                        TempStr += attrib.value("module").toString();
                    }
                    if (TempStr!=NULL)
                    {
                        TempStr="logical_device  "+TempStr;
                    }
                }
                if (XmlReader.name().toString()=="line")
                {
                    if(attrib.hasAttribute("type"))
                    {
                        TempStr="type = ";
                        TempStr += attrib.value("type").toString();
                    }
                    if (attrib.hasAttribute("port"))
                    {
                        TempStr+="  port = ";
                        TempStr += attrib.value("port").toString();
                    }
                    if (attrib.hasAttribute("address"))
                    {
                        TempStr+="  address = ";
                        TempStr += attrib.value("address").toString();
                    }
                    if (TempStr!=NULL)
                    {
                        TempStr="line  "+TempStr;
                    }
                }
                if (XmlReader.name().toString()=="object")
                {
                    if(attrib.hasAttribute("class_id"))
                    {
                        TempStr="class_id = ";
                        TempStr += attrib.value("class_id").toString();
                    }
                    if (attrib.hasAttribute("logical_name"))
                    {
                        TempStr+="  logical_name = ";
                        TempStr += attrib.value("logical_name").toString();
                    }
                    if (attrib.hasAttribute("data_source"))
                    {
                        TempStr+="  data_source = ";
                        TempStr += attrib.value("data_source").toString();
                    }
                    if (TempStr!=NULL)
                    {
                        TempStr="object  "+TempStr;
                    }
                }
                if (TempStr!=NULL)
                {
                    flagAtr=true;
                    ui->textBrowser->append(TempStr);
                }
                else
                {
                    TempStr=XmlReader.name().toString();
                }
=======
                TempStr=AtributRead(attrib, XmlReader.name().toString());
                if (TempStr==NULL)
                {
                    TempStr=XmlReader.name().toString();
                }
                ui->textBrowser->append(TempStr);
>>>>>>> Stashed changes

                if (XmlReader.isStartElement())
                {
                    QStringList Tags;
                    Tags<<TempStr;
                    QTreeWidgetItem* item = new QTreeWidgetItem(Tags);

                    if (StackTags.count()==0)
                    {
                        ui->treeWidget->addTopLevelItem(item);
                    }
                    else
                    {
                        if (flagAtr)
                        {
                            StackTags.top()->addChild(item);
                        }
                        else
                        {
                            StackTags.top()->addChild(item);//добавление дочернего элемента
                        }

                    }
                    StackTags.push_back(item);
                    TempStr="<"+TempStr;
                    for (int i=0; i<itemCount;i++)
                    {
                        TempStr="   "+TempStr;
                    }
                    TempStr+=">";
                    ui->textEdit->append(TempStr);
                    itemCount+=1;
                }
                if (XmlReader.isEndElement())//закрывающие элементы
                {
                    StackTags.pop();//уадление верхнего элемнета из стека
                    TempStr="<"+TempStr;
                    for (int i=0; i<itemCount;i++)
                    {
                        TempStr="   "+TempStr;
                    }
                    TempStr+=">";
                    ui->textEdit->append(TempStr);
                    itemCount-=1;
                }
                XmlReader.readNext();//переход к следующему элементу
            }
            if (XmlReader.hasError())
            {
                ui->textBrowser->append(XmlReader.errorString());//вывод ошибки
            }
        }
    }
    else
    {
        ui->FileFolder->clear();
        ui->FileFolder->setText("Для использования локальных файлов отметьте данную настройку");
    }
}


void MainWindow::on_FileSave_clicked()
{
    QFile fileWrite(ui->FileFolder->text());
    fileWrite.open(QFile::WriteOnly);
    QXmlStreamWriter XmlWriter;
    QXmlStreamReader XmlReader;
    QXmlStreamAttributes atributs;
    QString string, nameElement, tempStringAN, tempStringAV;

    int index;

    ui->textBrowser->clear();

    XmlWriter.setDevice(&fileWrite);
    XmlWriter.setAutoFormatting(true);
    XmlWriter.writeStartDocument();

    XmlReader.addData(ui->textEdit->toPlainText());
    XmlReader.readNext();
    while (!XmlReader.atEnd())
    {
        tempStringAN.clear();
        tempStringAV.clear();
        atributs=XmlReader.attributes();
        string=AtributRead(atributs, XmlReader.name().toString());
        nameElement=XmlReader.name().toString();
        if (XmlReader.isStartElement())
        {
            if (string==NULL)
            {
                XmlWriter.writeStartElement(nameElement);
            }
            else
            {
                index=string.indexOf(" ", index=0);
                string.remove(0, index-1);//удалить имя тега
                string.remove(QChar(' '));//удалить пробелы

                XmlWriter.writeStartElement(nameElement);
                while (!string.isEmpty())
                {
                    index=string.indexOf("'", index=0);
                    tempStringAN=string.left(index-1);//имя атрибута
                    string.remove(0, index);//удаление названия атрибута
                    index=string.indexOf("'", index=0);
                    tempStringAV=string.left(index);//значение атрибута
                    string.remove(0, index);//удаление названия атрибута
                    XmlWriter.writeAttribute(tempStringAN, tempStringAV);//записать атрибут и значение
                }
            }
        }
        else
        {
            XmlWriter.writeEndElement();
        }
    }
    XmlWriter.writeEndDocument();
}

