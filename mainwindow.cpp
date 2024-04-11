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

