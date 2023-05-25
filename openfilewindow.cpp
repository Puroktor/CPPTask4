#include "openfilewindow.h"
#include "ui_openfilewindow.h"
#include "dictchangedevent.h"
#include "fileutils.h"

#include <QFile>
#include <QDebug>
#include <QApplication>
#include <QMessageBox>

OpenFileWindow::OpenFileWindow(const QString *filename,
                               Dictionary *dictionary,
                               QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenFileWindow),
    dictionary(dictionary)
{
    ui->setupUi(this);
    setWindowTitle("Open File");
    bool status;
    QString fileText = FileUtils::readFile(filename, &status);
    if (status)
    {
        ui->textBrowser->setText(fileText);
    }
    else
    {
        QMessageBox::critical(this, "Error", "Can't open chosen file");
        close();
    }
}

void OpenFileWindow::on_pushButton_clicked()
{
    QString text = ui->textBrowser->toPlainText();
    dictionary->addText(&text);

    DictChangedEvent *event = new DictChangedEvent();
    QApplication::sendEvent(parentWidget(), event);
    close();
}

OpenFileWindow::~OpenFileWindow()
{
    delete ui;
}
