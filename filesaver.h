#ifndef FILESAVER_H
#define FILESAVER_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class filesaver;
}

class filesaver : public QDialog
{
    Q_OBJECT

public:
    explicit filesaver(QWidget *parent = nullptr);
    ~filesaver();

private slots:
    void on_yesButton_clicked();

    void on_noButton_clicked();

private:
    Ui::filesaver *ui;

signals:
    void newFileName(QString);
};

#endif // FILESAVER_H
