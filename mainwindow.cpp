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

QString AtributRead (QXmlStreamAttributes elementAtrib, QString nameElement)
{
    QString TempStr;
    QChar kav=34;
    TempStr.clear();
    if (nameElement=="logical_device")
    {
        if(elementAtrib.hasAttribute("address"))
        {
            TempStr="address=";
            TempStr.push_back(kav);
            TempStr+=elementAtrib.value("address").toString();
            TempStr.push_back(kav);
        }
        if (elementAtrib.hasAttribute("module"))
        {
            TempStr=TempStr+" module=";
            TempStr.push_back(kav);
            TempStr+=elementAtrib.value("module").toString();
            TempStr.push_back(kav);
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
            TempStr="type=";
            TempStr.push_back(kav);
            TempStr+=elementAtrib.value("type").toString();
            TempStr.push_back(kav);
        }
        if (elementAtrib.hasAttribute("port"))
        {
            TempStr=TempStr+" port=";
            TempStr.push_back(kav);
            TempStr+=elementAtrib.value("port").toString();
            TempStr.push_back(kav);
        }
        if (elementAtrib.hasAttribute("address"))
        {
            TempStr=TempStr+" address=";
            TempStr.push_back(kav);
            TempStr+=elementAtrib.value("address").toString();
            TempStr.push_back(kav);
        }
        if (elementAtrib.hasAttribute("baudrate"))
        {
            TempStr=TempStr+" baudrate=";
            TempStr.push_back(kav);
            TempStr+=elementAtrib.value("baudrate").toString();
            TempStr.push_back(kav);
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
            TempStr="class_id=";
            TempStr.push_back(kav);
            TempStr+=elementAtrib.value("class_id").toString();
            TempStr.push_back(kav);
        }
        if (elementAtrib.hasAttribute("logical_name"))
        {
            TempStr=TempStr+" logical_name=";
            TempStr.push_back(kav);
            TempStr+=elementAtrib.value("logical_name").toString();
            TempStr.push_back(kav);
        }
        if (elementAtrib.hasAttribute("data_source"))
        {
            TempStr=TempStr+" data_source=";
            TempStr.push_back(kav);
            TempStr+=elementAtrib.value("data_source").toString();
            TempStr.push_back(kav);
        }
        if (TempStr!=NULL)
        {
            TempStr="object "+TempStr;
        }
    }
    return TempStr;
}

void MainWindow::on_pushButton_clicked()
{
    QXmlStreamReader XmlReader;//элемент класса для работы с XML файлами
    XmlReader.addData(ui->textEdit->toPlainText());//получение введённых данных
    QStack<QTreeWidgetItem*> StackTags; //список элементов для создания иерархии
    QXmlStreamAttributes attrib;
    QString TempStr;

    ui->treeWidget->clear();//очистка поля для вывода тегов
    ui->textBrowser->clear();

    XmlReader.readNext();
    while (!XmlReader.atEnd())//перебор всех элеменов
    {
        attrib=XmlReader.attributes();
        TempStr.clear();
        TempStr=AtributRead(attrib, XmlReader.name().toString());
        if (TempStr==NULL)
        {
            TempStr=XmlReader.name().toString();
        }
        if (XmlReader.isStartElement())//проверка на открывающий элемент
        {
            QStringList Tags;
            Tags<<TempStr;//получение имени текущего элемента
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
        ui->textEdit->clear();

        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            ui->textBrowser->setPlainText("Не удалось открыть файл");
        }
        else
        {
            ui->treeWidget->clear();
            ui->textEdit->clear();
            QStack<QTreeWidgetItem*> StackTags;
            QXmlStreamReader XmlReader;
            QString TempStr;
            QXmlStreamAttributes attrib;
            XmlReader.setDevice(&file);//выставление файла откуда происходит чтение
            XmlReader.readNext();

            while (!XmlReader.atEnd())
            {
                attrib=XmlReader.attributes();
                TempStr.clear();
                TempStr=AtributRead(attrib, XmlReader.name().toString());
                if (TempStr.isEmpty())
                {
                    TempStr=XmlReader.name().toString();
                }
                ui->textBrowser->append(TempStr);

                if (XmlReader.isStartElement())
                {
                    itemCount++;
                    QStringList Tags;
                    Tags<<TempStr;
                    QTreeWidgetItem* item = new QTreeWidgetItem(Tags);

                    if (StackTags.count()==0)
                    {
                        ui->treeWidget->addTopLevelItem(item);
                    }
                    else
                    {
                        StackTags.top()->addChild(item);
                    }
                    StackTags.push_back(item);
                    TempStr="<"+TempStr;
                    for (int i=0; i<itemCount;i++)
                    {
                        TempStr="   "+TempStr;
                    }
                    TempStr+=">";
                    ui->textEdit->append(TempStr);
                }
                if (XmlReader.isEndElement())
                {
                    StackTags.pop();//уадление верхнего элемнета из стека
                    TempStr="</"+TempStr;
                    for (int i=0; i<itemCount;i++)
                    {
                        TempStr="   "+TempStr;
                    }
                    TempStr+=">";
                    ui->textEdit->append(TempStr);
                    itemCount--;
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
    QXmlStreamReader XmlReader;
    QXmlStreamAttributes atributs;
    QString string, nameElement, tempStringAN, tempStringAV;

    int index;
    QChar kav=34;

    if (!fileWrite.open(QFile::WriteOnly))
    {
        ui->textBrowser->setPlainText("Не удалось открыть файл для записи");
    }
    else
    {
        ui->textBrowser->clear();

        QXmlStreamWriter XmlWriter(&fileWrite);
        XmlWriter.setCodec("UTF-16");
        XmlWriter.setAutoFormatting(true);
        XmlWriter.writeStartDocument();

        XmlReader.addData(ui->textEdit->toPlainText());
        XmlReader.readNext();
        while (!XmlReader.atEnd())
        {
            atributs=XmlReader.attributes();
            nameElement=XmlReader.name().toString();
            string.clear();
            string=AtributRead(atributs, nameElement);
            if (XmlReader.isStartElement())
            {
                XmlWriter.writeStartElement(nameElement);
                if (!string.isEmpty())
                {
                    index = string.indexOf(" ", index = 0);
                    string.remove(0, index);//удалить имя тега
                    string.remove(QChar(' '), Qt::CaseInsensitive);//удалить пробелы

                    while (!string.isEmpty())
                    {
                        tempStringAN.clear();
                        tempStringAV.clear();
                        index=0;
                        index = string.indexOf(kav, index);
                        index--;
                        tempStringAN = string.left(index);//сохраннение имя атрибута
                        index+=2;
                        string.remove(0, index);//удаление названия атрибута и открывающую '
                        index=0;
                        index = string.indexOf(kav, index);
                        tempStringAV = string.left(index);//сохранение значения атрибута
                        index++;
                        string.remove(0, index);//удаление значения атрибута
                        XmlWriter.writeAttribute(tempStringAN, tempStringAV);//записать атрибут и значение
                    }
                }
            }
            if (XmlReader.isEndElement())
            {
                XmlWriter.writeEndElement();
            }
            XmlReader.readNext();
        }
        XmlWriter.writeEndDocument();
        if (XmlReader.hasError())
        {
            ui->textBrowser->setText(XmlReader.errorString());
        }
    }
}
