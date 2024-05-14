#ifndef EDIT_LINE_H
#define EDIT_LINE_H

#include <QDialog>

namespace Ui {
class edit_line;
}

class edit_line : public QDialog
{
    Q_OBJECT

public:
    explicit edit_line(QWidget *parent = nullptr);
    ~edit_line();

private:
    Ui::edit_line *ui;
};

#endif // EDIT_LINE_H
