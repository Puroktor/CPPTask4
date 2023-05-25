#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dictchangedevent.h"
#include "dictionary.h"
#include "fileutils.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Dictionary");

    dictionary = new Dictionary();

    dictModel = new QStandardItemModel(0, 2, this);
    dictModel->setHorizontalHeaderLabels({ "Word", "Count" });
    ui->dictView->setModel(dictModel);
    ui->dictView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->dictView->setSortingEnabled(true);
}

void MainWindow::paintDictionary()
{
    qDebug() << "Repaining dictionary";
    dictModel->setRowCount(dictionary->map->size());

    int i = 0;
    for (const auto& entry : *(dictionary->map))
    {
        QModelIndex wordIndex = dictModel->index(i, 0);
        dictModel->setData(wordIndex, entry.first);

        QModelIndex countIndex = dictModel->index(i, 1);
        dictModel->setData(countIndex, entry.second);
        i++;
    }
}

bool MainWindow::event(QEvent *event)
{
    if (event->type() == DictChangedEvent::eventType)
    {
        paintDictionary();
        return true;
    }

    return QWidget::event(event);
}


void MainWindow::on_open_file_action_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File", ".", "Text Files(*.txt)");
    if (filename.isNull())
        return;

    openFileWindow = new OpenFileWindow(&filename, dictionary, this);
    openFileWindow->show();
}


void MainWindow::on_save_dict_action_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Dictionary", ".", FileUtils::DICT_FILE_FILTER);
    if (filename.isNull())
        return;

    bool status;
    Dictionary::writeToFile(&filename, dictionary, &status);
    if (status)
        ui->statusbar->showMessage("Dictionary is saved");
    else
        ui->statusbar->showMessage("Error during dictionary saving");
}


void MainWindow::on_open_dict_action_triggered()
{
     QString filename = QFileDialog::getOpenFileName(this, "Open Dictionary", ".", FileUtils::DICT_FILE_FILTER);
     if (filename.isNull())
         return;

     bool status;
     Dictionary* parsedDict = Dictionary::readFromFile(&filename, &status);
     if (status)
     {
         dictionary = parsedDict;
         paintDictionary();
     }
     else
     {
         QMessageBox::critical(this, "Error", "Dictionary file had wrong format");
     }

}

MainWindow::~MainWindow()
{
    delete openFileWindow;
    delete dictionary;
    delete ui;
}
