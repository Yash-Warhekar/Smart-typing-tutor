#ifndef LEARNWINDOW_H
#define LEARNWINDOW_H

#include <QMainWindow>

namespace Ui {
class LearnWindow;
}

class LearnWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LearnWindow(QWidget *parent = nullptr);
    ~LearnWindow();

private slots:
    void on_pushButton_clicked();


private:
    Ui::LearnWindow *ui;
    QMainWindow *mainWin;
};

#endif // LEARNWINDOW_H
