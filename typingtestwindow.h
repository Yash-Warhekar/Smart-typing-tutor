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

private:
    Ui::typingTestWindow *ui;
    QMainWindow *mainWin;

    //key mapping
    QMap<QChar, QPushButton*> keyButtons;
    QMap<int, QPushButton*> specialKeyButtons;
    void initializeKeyMapping();
    bool capsLockOn = false;

    //typing logic
    QString targetText;
    QString typedText;
    int currentIndex = 0;
    int typoCount = 0;
    int correctCount = 0;


    QStringList sentenceList;
    int currentSentenceIndex = 0;

    // Timer & test logic
    QTimer* testTimer = nullptr;
    QString selectedDifficulty;
    int selectedDuration = 0;  // in seconds
    int remainingTime = 0;

    // 🧠 Methods for logic
    void loadTextForTest();         // Load text based on difficulty
    void startTest();               // Starts timer and resets counters
    void updateTypingDisplay();     // Color-code the typing progress
    void showResult();              // Show result in popup

    // void restartTest(); --> for restarting test
};

#endif // TYPINGTESTWINDOW_H
