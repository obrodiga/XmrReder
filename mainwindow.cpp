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
    QXmlStreamReader XmlReader;
    XmlReader.addData(ui->textEdit->toPlainText());
    ui->treeWidget->clear();
    QStack<QTreeWidgetItem*> StackTags;

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
                StackTags.top()->addChild(item);
            }
            StackTags.push_back(item);
        }
        if (XmlReader.isEndElement())
        {
            StackTags.pop();
        }
        XmlReader.readNext();
    }
    if (XmlReader.hasError())
    {
        ui->textBrowser->setPlainText(XmlReader.errorString());
    }
}

