#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Построение дерева тегов");
    fileSaver = new filesaver;
    connect(fileSaver, &filesaver::newFileName, this, &MainWindow::newFileFolder);
    editLine=new edit_line;
    connect(ui->treeWidget, &QAbstractItemView::doubleClicked, this, &MainWindow::twoDoubleClicked);
    connect(editLine, &edit_line::newLine, this, &MainWindow::newTypeString);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString AtributRead(QXmlStreamAttributes elementAtrib, QString nameElement)
{
    QChar kav = 34;
    QString TempStr, KavStr;
    KavStr.clear();
    KavStr.push_back(kav);
    TempStr.clear();
    if (nameElement == "logical_device")
    {
        if (elementAtrib.hasAttribute("address"))
        {
            TempStr = "address="+ KavStr+ elementAtrib.value("address").toString()+KavStr;
        }
        if (elementAtrib.hasAttribute("module"))
        {
            TempStr = TempStr + " module="+KavStr + elementAtrib.value("module").toString() + KavStr;
        }
        if (TempStr != NULL)
        {
            TempStr = "logical_device " + TempStr;
        }
    }
    if (nameElement == "line")
    {
        if (elementAtrib.hasAttribute("type"))
        {
            TempStr = "type="+KavStr + elementAtrib.value("type").toString() + KavStr;
        }
        if (elementAtrib.hasAttribute("port"))
        {
            TempStr = TempStr + " port=" + KavStr + elementAtrib.value("port").toString() + KavStr;
        }
        if (elementAtrib.hasAttribute("address"))
        {
            TempStr = TempStr + " address="+KavStr + elementAtrib.value("address").toString() + KavStr;
        }
        if (elementAtrib.hasAttribute("baudrate"))
        {
            TempStr = TempStr + " baudrate="+KavStr + elementAtrib.value("baudrate").toString() + KavStr;
        }
        if (TempStr != NULL)
        {
            TempStr = "line " + TempStr;
        }
    }
    if (nameElement == "object")
    {
        if (elementAtrib.hasAttribute("class_id"))
        {
            TempStr = "class_id=" + KavStr + elementAtrib.value("class_id").toString() + KavStr;
        }
        if (elementAtrib.hasAttribute("logical_name"))
        {
            TempStr = TempStr + " logical_name=" + KavStr + elementAtrib.value("logical_name").toString() + KavStr;
        }
        if (elementAtrib.hasAttribute("data_source"))
        {
            TempStr = TempStr + " data_source="+ KavStr + elementAtrib.value("data_source").toString() + KavStr;
        }
        if (TempStr != NULL)
        {
            TempStr = "object " + TempStr;
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
    QString TempStr, nameElement;

    ui->treeWidget->clear();//очистка поля для вывода тегов
    ui->textBrowser->clear();

    XmlReader.readNext();
    while (!XmlReader.atEnd())//перебор всех элеменов
    {
        attrib = XmlReader.attributes();
        TempStr.clear();
        nameElement = XmlReader.name().toString();
        TempStr = AtributRead(attrib, nameElement);
        if (TempStr == NULL)
        {
            TempStr = nameElement;
        }
        if (XmlReader.isStartElement())//проверка на открывающий элемент
        {
            QStringList Tags;
            Tags << TempStr;//получение имени текущего элемента
            QTreeWidgetItem* item = new QTreeWidgetItem(Tags); //создание элементов для последующего добавления в дерево
            if (StackTags.count() == 0)
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
    int itemCount = 0;
    QString FileName;
    FileName = QFileDialog::getOpenFileName(this, tr("Open XML File"), "", tr("XML file (*.xml)"));
    ui->FileFolder->setText(FileName);
    QFile file(FileName);

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
        QString TempStr, nameElement;
        QXmlStreamAttributes attrib;
        XmlReader.setDevice(&file);//выставление файла откуда происходит чтение
        XmlReader.readNext();

        while (!XmlReader.atEnd())
        {
            attrib = XmlReader.attributes();
            TempStr.clear();
            nameElement = XmlReader.name().toString();
            TempStr = AtributRead(attrib, nameElement);
            if (TempStr.isEmpty())
            {
                TempStr = nameElement;
            }

            if (XmlReader.isStartElement())
            {
                itemCount++;
                QStringList Tags;
                Tags << TempStr;
                QTreeWidgetItem* item = new QTreeWidgetItem(Tags);

                if (StackTags.count() == 0)
                {
                    ui->treeWidget->addTopLevelItem(item);
                    Server NewServer;
                    m_servers.push_back(NewServer);
                }
                else
                {
                    StackTags.top()->addChild(item);
                    if (nameElement == "server")
                    {
                        m_lastserver = m_servers[m_servers.size() - 1];
                    }
                    if (nameElement == "lines")
                    {
                        Line NewLine;
                        m_lastserver.m_lines.push_back(NewLine);
                    }
                    if (nameElement == "logical_devices")
                    {
                        LogicalDevice newLDevice;
                        m_lastserver.Devaices.push_back(newLDevice);
                    }
                }
                StackTags.push_back(item);
                TempStr = "<" + TempStr + ">";
                for (int i = 0; i < itemCount; i++)
                {
                    TempStr = "   " + TempStr;
                }
                ui->textEdit->append(TempStr);
            }
            if (XmlReader.isEndElement())
            {
                StackTags.pop();//уадление верхнего элемнета из стека
                TempStr = "</" + TempStr + ">";
                for (int i = 0; i < itemCount; i++)
                {
                    TempStr = "   " + TempStr;
                }
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


void MainWindow::on_FileSave_clicked()
{
    QString FileName;

    fileSaver->setModal(true);
    fileSaver->exec();
    FileName = (ui->FileFolder->text());
    QFile fileWrite(FileName);
    QXmlStreamReader XmlReader;
    QXmlStreamAttributes atributs;
    QString string, nameElement, tempStringAN, tempStringAV;

    int index;
    QChar kav = 34;

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
            atributs = XmlReader.attributes();
            nameElement = XmlReader.name().toString();
            string.clear();
            string = AtributRead(atributs, nameElement);
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
                        index = string.indexOf(kav, index = 0);
                        tempStringAN = string.left(index = index - 1);//сохраннение имя атрибута
                        string.remove(0, index = index + 2);//удаление названия атрибута и открывающую '
                        index = string.indexOf(kav, index = 0);
                        tempStringAV = string.left(index);//сохранение значения атрибута
                        string.remove(0, index = index + 1);//удаление значения атрибута
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

void MainWindow::on_closeButton_triggered()
{
    QApplication::quit();
}


void MainWindow::on_infoButton_triggered()
{
    QFile file(":/info/about.txt");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        ui->textBrowser->setPlainText("Не удалось открыть файл 'Информация о разработчках'");
    }
    else
    {
        QByteArray data = file.readAll();
        QMessageBox::about(this, "Информация о разработчках", data);
    }
}

void MainWindow::newFileFolder(QString FileFolder)
{
    ui->FileFolder->setText(FileFolder);
}

void MainWindow::twoDoubleClicked(const QModelIndex &index)
{
    QString oldStr=index.data().toString();
    if ((oldStr.contains("line ")==true)||(oldStr.contains("logical_device ")==true)||(oldStr.contains("object ")==true))
    {
        editLine->setModal(true);
        editLine->SetStr(oldStr);
        editLine->exec();
    }
}

void MainWindow::newTypeString(QString OldLn, QString NewLn)
{
    ui->textBrowser->setText(NewLn);
    int ServersCount = 0;
    if (!NewLn.isEmpty())
    {
        ServersCount=ui->treeWidget->topLevelItem(0)->childCount();
        for (int i=0; i<ServersCount;i++)
        {
            QTreeWidgetItem* ptrServerItem=ui->treeWidget->topLevelItem(0)->child(i);
            int ServerObjectsCount=ptrServerItem->childCount();
            for (int j=0; j<ServerObjectsCount;j++)
            {
                QTreeWidgetItem* ptrServerObgectItem=ptrServerItem->child(j);
                if (ptrServerObgectItem->text(0).contains("lines"))
                {
                    int LineCount=ptrServerObgectItem->childCount();
                    for (int k=0;k<LineCount;k++)
                    {
                        if (ptrServerObgectItem->child(k)->text(0)==OldLn)
                        {
                            ptrServerObgectItem->child(k)->setText(0, NewLn);
                        }

                    }
                }
            }

        }
    }
    if (!NewLn.isEmpty())
    {
        QString data=ui->textEdit->toPlainText();//скопировать весь текст из дерева
        int index1, index2;
        index1=data.indexOf(OldLn, index1=0);//начало строки которую заменить
        index2=data.indexOf(">", index1);//конец строки которую заменить
        data.replace(index1, index2-index1, NewLn);
        ui->textEdit->setText(data);
        QString infoMasge;
        infoMasge="String '"+OldLn+"' swap to '"+NewLn+"'";
        ui->textBrowser->setText(infoMasge);
    }
}

void MainWindow::on_gideButton_triggered()
{
    QFile file(":/info/guid.txt");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        ui->textBrowser->setPlainText("Не удалось открыть файл 'Руководство по использованию программы'");        
    }
    else
    {
        QByteArray data = file.readAll();
        QMessageBox::information(this, "Руководство по использованию программы", data);
    }
}
