#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "openfilewindow.h"
#include <dictionary.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void paintDictionary();
    bool event(QEvent *event) override;
    ~MainWindow();

private slots:
    void on_open_file_action_triggered();

    void on_save_dict_action_triggered();

    void on_open_dict_action_triggered();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *dictModel;
    OpenFileWindow *openFileWindow;
    Dictionary *dictionary;
};
#endif // MAINWINDOW_H
