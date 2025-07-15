#include "learnwindow.h"
#include "ui_learnwindow.h"
#include  "mainwindow.h"
LearnWindow::LearnWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LearnWindow)
{
    ui->setupUi(this);
    ui->textBrowser->setOpenExternalLinks(true);
}

LearnWindow::~LearnWindow()
{
    delete ui;
}

void LearnWindow::on_pushButton_clicked()
{
    mainWin = new MainWindow();
    mainWin->show();
    this->close();
}

