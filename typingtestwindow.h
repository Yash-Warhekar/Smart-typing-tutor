#ifndef TYPINGTESTWINDOW_H
#define TYPINGTESTWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QPushButton>
#include <QString>
#include "mainwindow.h"
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QRandomGenerator>

namespace Ui {
class typingTestWindow;
}

class typingTestWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit typingTestWindow(QWidget *parent = nullptr);
    ~typingTestWindow();
    void initializeTest(const QString& difficulty, int durationMinutes);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_pushButton_clicked();
    void updateTimer();
    void on_restartButton_clicked();
    
private:
    Ui::typingTestWindow *ui;
    QMainWindow *mainWin;


    QMap<QChar, QPushButton*> keyButtons;
    QMap<int, QPushButton*> specialKeyButtons;
    void initializeKeyMapping();
    bool capsLockOn = false;


    QString targetText;
    QString typedText;
    int currentIndex = 0;
    int typoCount = 0;
    int correctCount = 0;


    QStringList sentenceList;
    int currentSentenceIndex = 0;


    QTimer* testTimer = nullptr;
    QString selectedDifficulty;
    int selectedDuration = 0;
    int remainingTime = 0;


    void loadTextForTest();
    void startTest();
    void updateTypingDisplay();
    void showResult();


    //for keyboard cursor(variables)
    bool cursorVisible = true;
    QTimer *cursorTimer = nullptr;

};

#endif // TYPINGTESTWINDOW_H
