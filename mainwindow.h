#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QXmlStreamAttributes>
#include <QStack>
#include <QTextBrowser>
#include <QFileDialog>
#include <QFile>
#include <QVector>
#include <QDebug>
#include <struct.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Servers m_servers;
    Server m_lastserver;


private slots:
    void on_pushButton_clicked();

    void on_FileOpen_clicked();

    void on_FileSave_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
