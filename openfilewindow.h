#ifndef OPENFILEWINDOW_H
#define OPENFILEWINDOW_H

#include <dictionary.h>
#include <QMainWindow>

namespace Ui {
class OpenFileWindow;
}

class OpenFileWindow : public QMainWindow
{
    Q_OBJECT

public:
    OpenFileWindow(const QString *filename,
                   Dictionary *dictionary,
                   QWidget *parent = nullptr);
    ~OpenFileWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::OpenFileWindow *ui;
    Dictionary *dictionary;
};

#endif // OPENFILEWINDOW_H
