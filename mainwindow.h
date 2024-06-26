#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QXmlStreamAttributes>
#include <QStack>
#include <QTextBrowser>
#include <QFile>
#include <QVector>
#include <QDebug>
#include <struct.h>
#include <QMessageBox>
#include <QAbstractItemView>
#include <QStringList>

#include <filesaver.h>
#include <edit_line.h>

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

    void on_closeButton_triggered();

    void on_infoButton_triggered();

    void on_gideButton_triggered();

private:
    Ui::MainWindow *ui;
    filesaver *fileSaver;
    edit_line *editLine;

public slots:
    void newFileFolder(QString FileFolder);
    void twoDoubleClicked(const QModelIndex &index);
    void newTypeString(QString OldLn, QString NewLn);
};
#endif // MAINWINDOW_H
