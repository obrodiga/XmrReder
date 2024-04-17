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
        QString FileName;
        FileName = QFileDialog::getOpenFileName(this, tr("Open XML File"), "", tr("XML file (*.xml)"));
        ui->FileFolder->setText(FileName);
        QFile file(ui->FileFolder->text());

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
            XmlReader.setDevice(&file);//выставление файла откуда происходит чтение
            XmlReader.readNext();
            while (!XmlReader.atEnd())
            {
                if (XmlReader.isStartElement())
                {
                    QStringList Tags;
                    Tags<<XmlReader.name().toString();
                    QTreeWidgetItem* item = new QTreeWidgetItem(Tags);
                    if (StackTags.count()==0)
                    {
                        ui->treeWidget->addTopLevelItem(item);
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
    }
    else
    {
        ui->FileFolder->clear();
        ui->FileFolder->setText("Для использования локальных файлов отметьте данную настройку");
    }
}
