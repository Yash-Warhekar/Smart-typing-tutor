#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox_time->setCurrentIndex(1);
    ui->radioButton_easy->setChecked(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_start_clicked()
{    typingTestWindow *testWindow = new typingTestWindow(this);

    QString selectedDifficulty;
    if (ui->radioButton_easy->isChecked()) {
        selectedDifficulty = "easy";
    } else if (ui->radioButton_medium->isChecked()) {
        selectedDifficulty = "medium";
    } else if (ui->radioButton_hard->isChecked()) {
        selectedDifficulty = "hard";
    }

    QString timeText = ui->comboBox_time->currentText();
    int selectedDuration = timeText.split(" ").first().toInt();
    testWindow->initializeTest(selectedDifficulty, selectedDuration);
    testWindow->show();
    this->hide();

}

