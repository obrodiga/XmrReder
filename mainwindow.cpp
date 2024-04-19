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


void MainWindow::on_pushButton_clicked()
{
    QXmlStreamReader XmlReader;//элемент класса для работы с XML файлами
    XmlReader.addData(ui->textEdit->toPlainText());//получение введённых данных
    QStack<QTreeWidgetItem*> StackTags; //список элементов для создания иерархии

    ui->treeWidget->clear();//очистка поля для вывода тегов
    ui->textBrowser->clear();

    while (!XmlReader.atEnd())//перебор всех элементов
    {
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
        ui->textEdit->clear();

        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            ui->textBrowser->clear();
            ui->textBrowser->setPlainText("Не удалось открыть файл");
        }
        else
        {
            ui->treeWidget->clear();
            ui->textBrowser->clear();//очистка поля ошибок
            QStack<QTreeWidgetItem*> StackTags;
            QXmlStreamReader XmlReader;
            QString TempStr;
            //QVector<QString> atributs;
            QXmlStreamAttributes attrib;
            XmlReader.setDevice(&file);//выставление файла откуда происходит чтение
            XmlReader.readNext();

            while (!XmlReader.atEnd())
            {
                bool flagAtr=false;
                attrib=XmlReader.attributes();
                TempStr.clear();
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
