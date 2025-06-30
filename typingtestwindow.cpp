#include "typingtestwindow.h"
#include "ui_typingtestwindow.h"
#include <QString>
#include <QChar>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>
#include <QPushButton>

typingTestWindow::typingTestWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::typingTestWindow)
{
    ui->setupUi(this);
    initializeKeyMapping();

    ui->pushButton->setFocusPolicy(Qt::NoFocus);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();

}

typingTestWindow::~typingTestWindow()
{
    delete ui;
}

void typingTestWindow::initializeTest(const QString& difficulty, int durationMinutes) {
    selectedDifficulty = difficulty.toLower();
    selectedDuration = durationMinutes * 60;
    remainingTime = selectedDuration;

    correctCount = 0;
    typoCount = 0;
    typedText.clear();
    currentIndex = 0;

    loadTextForTest();
    startTest();
}



void typingTestWindow::loadTextForTest() {
    QString filePath;
    if (selectedDifficulty == "easy")
        filePath = ":/texts/resources/rexts/easy.txt";
    else if (selectedDifficulty == "medium")
        filePath = ":/texts/resources/rexts/medium.txt";
    else if (selectedDifficulty == "hard")
        filePath = ":/texts/resources/rexts/hard.txt";

    QFile file(filePath);
    sentenceList.clear();

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty()) sentenceList.append(line);
        }
        file.close();
    }

    currentSentenceIndex = 0;
    if (!sentenceList.isEmpty()) {
        targetText = sentenceList[currentSentenceIndex];
    } else {
        targetText = "Default fallback text.";
    }

    ui->textLabel->setText(targetText);


}


void typingTestWindow::startTest() {
    testTimer = new QTimer(this);
    connect(testTimer, &QTimer::timeout, this, &typingTestWindow::updateTimer);
    testTimer->start(1000);

    updateTypingDisplay();
}


void typingTestWindow::updateTimer() {
    remainingTime--;
    int minutes = remainingTime / 60;
    int seconds = remainingTime % 60;

    ui->timerLabel->setText(QString("%1:%2")
                                .arg(minutes, 2, 10, QChar('0'))
                                .arg(seconds, 2, 10, QChar('0')));

    if (remainingTime <= 0) {
        testTimer->stop();
        showResult();
    }
}

void typingTestWindow::keyPressEvent(QKeyEvent *event) {
    if (targetText.isEmpty() || remainingTime <= 0)
        return;

    int key = event->key();
    QString text = event->text();

    if (specialKeyButtons.contains(key)) {
        QPushButton *btn = specialKeyButtons[key];
        btn->setStyleSheet("background-color: yellow");
        QTimer::singleShot(150, [btn]() {
            btn->setStyleSheet("");
        });
    }

    if (key == Qt::Key_CapsLock) {
        capsLockOn = !capsLockOn;
        return;
    }

    if (key == Qt::Key_Return || key == Qt::Key_Enter) {
        return;
    }

    if (text.isEmpty()) return;

    QChar pressedChar = text[0];
    bool isShift = event->modifiers() & Qt::ShiftModifier;

    if (capsLockOn ^ isShift) {
        pressedChar = pressedChar.toUpper();
    } else {
        pressedChar = pressedChar.toLower();
    }

    QChar expectedChar = targetText[currentIndex];
    if (pressedChar == expectedChar) {
        correctCount++;
    } else {
        typoCount++;
    }

    typedText += pressedChar;
    currentIndex++;

    if (currentIndex >= targetText.length()) {
        currentSentenceIndex++;
        if (currentSentenceIndex < sentenceList.size()) {
            targetText = sentenceList[currentSentenceIndex];
            typedText.clear();
            currentIndex = 0;
            updateTypingDisplay();
        } else {
            typedText.clear();
            targetText.clear();
            ui->textLabel->setText("🎉 Great! You've typed all sentences.");
            ui->typedTextLabel->clear();
        }
        return;
    }

    updateTypingDisplay();

    if (keyButtons.contains(pressedChar)) {
        QPushButton *btn = keyButtons[pressedChar];
        btn->setStyleSheet("background-color: yellow");
        QTimer::singleShot(150, [btn]() {
            btn->setStyleSheet("");
        });
    }
}

void typingTestWindow::updateTypingDisplay() {
    QString correct = targetText.left(currentIndex);
    QString remaining = targetText.mid(currentIndex);

    ui->textLabel->setText(
        "<span style='color:green'>" + correct + "</span><span>" + remaining + "</span>"
        );
    ui->typedTextLabel->setText(typedText);
}

void typingTestWindow::showResult() {
    double accuracy = correctCount + typoCount > 0 ?
                          (double)correctCount / (correctCount + typoCount) * 100.0 : 0;
    int wpm = (correctCount / 5.0) / (selectedDuration / 60.0);

    QString result = QString("Typing Test Completed!\n\nWPM: %1\nAccuracy: %2%\nTypos: %3")
                         .arg(wpm)
                         .arg(accuracy, 0, 'f', 2)
                         .arg(typoCount);

    QMessageBox::information(this, "Test Result", result);
}




void typingTestWindow::on_pushButton_clicked()
{
    mainWin = new MainWindow();
    mainWin->show();
    this->close();
}

void typingTestWindow::initializeKeyMapping() {
        keyButtons['a'] = ui->button_A;
        keyButtons['b'] = ui->button_B;
        keyButtons['c'] = ui->button_C;
        keyButtons['d'] = ui->button_D;
        keyButtons['e'] = ui->button_E;
        keyButtons['f'] = ui->button_F;
        keyButtons['g'] = ui->button_G;
        keyButtons['h'] = ui->button_H;
        keyButtons['i'] = ui->button_I;
        keyButtons['j'] = ui->button_J;
        keyButtons['k'] = ui->button_K;
        keyButtons['l'] = ui->button_L;
        keyButtons['m'] = ui->button_M;
        keyButtons['n'] = ui->button_N;
        keyButtons['o'] = ui->button_O;
        keyButtons['p'] = ui->button_P;
        keyButtons['q'] = ui->button_Q;
        keyButtons['r'] = ui->button_R;
        keyButtons['s'] = ui->button_S;
        keyButtons['t'] = ui->button_T;
        keyButtons['u'] = ui->button_U;
        keyButtons['v'] = ui->button_V;
        keyButtons['w'] = ui->button_W;
        keyButtons['x'] = ui->button_X;
        keyButtons['y'] = ui->button_Y;
        keyButtons['z'] = ui->button_Z;

        // Digits 0–9
        keyButtons['0'] = ui->button_0;
        keyButtons['1'] = ui->button_1;
        keyButtons['2'] = ui->button_2;
        keyButtons['3'] = ui->button_3;
        keyButtons['4'] = ui->button_4;
        keyButtons['5'] = ui->button_5;
        keyButtons['6'] = ui->button_6;
        keyButtons['7'] = ui->button_7;
        keyButtons['8'] = ui->button_8;
        keyButtons['9'] = ui->button_9;

        // Spacebar and punctuation
        keyButtons[' ']  = ui->button_Space;
        keyButtons[',']  = ui->button_Comma;
        keyButtons['.']  = ui->button_Period;
        keyButtons['/']  = ui->button_Slash;
        keyButtons['\\'] = ui->button_Backslash;
        keyButtons[';']  = ui->button_Semicolon;
        keyButtons['\''] = ui->button_Apostrophe;
        keyButtons['[']  = ui->button_LBracket;
        keyButtons[']']  = ui->button_RBracket;
        keyButtons['-']  = ui->button_Dash;
        keyButtons['=']  = ui->button_Equals;
        keyButtons['`']  = ui->button_Backtick;



        specialKeyButtons[Qt::Key_Shift] = ui->button_LShift;
        specialKeyButtons[Qt::Key_Shift] = ui->button_RShift;
        specialKeyButtons[Qt::Key_CapsLock] = ui->button_CapsLock;
        specialKeyButtons[Qt::Key_Return] = ui->button_Enter;
        specialKeyButtons[Qt::Key_Enter] = ui->button_Enter;
        specialKeyButtons[Qt::Key_Space] = ui->button_Space;



        keyButtons['A'] = ui->button_A;
        keyButtons['B'] = ui->button_B;
        keyButtons['C'] = ui->button_C;
        keyButtons['D'] = ui->button_D;
        keyButtons['E'] = ui->button_E;
        keyButtons['F'] = ui->button_F;
        keyButtons['G'] = ui->button_G;
        keyButtons['H'] = ui->button_H;
        keyButtons['I'] = ui->button_I;
        keyButtons['J'] = ui->button_J;
        keyButtons['K'] = ui->button_K;
        keyButtons['L'] = ui->button_L;
        keyButtons['M'] = ui->button_M;
        keyButtons['N'] = ui->button_N;
        keyButtons['O'] = ui->button_O;
        keyButtons['P'] = ui->button_P;
        keyButtons['Q'] = ui->button_Q;
        keyButtons['R'] = ui->button_R;
        keyButtons['S'] = ui->button_S;
        keyButtons['T'] = ui->button_T;
        keyButtons['U'] = ui->button_U;
        keyButtons['V'] = ui->button_V;
        keyButtons['W'] = ui->button_W;
        keyButtons['X'] = ui->button_X;
        keyButtons['Y'] = ui->button_Y;
        keyButtons['Z'] = ui->button_Z;


        keyButtons['!'] = ui->button_1;
        keyButtons['@'] = ui->button_2;
        keyButtons['#'] = ui->button_3;
        keyButtons['$'] = ui->button_4;
        keyButtons['%'] = ui->button_5;
        keyButtons['^'] = ui->button_6;
        keyButtons['&'] = ui->button_7;
        keyButtons['*'] = ui->button_8;
        keyButtons['('] = ui->button_9;
        keyButtons[')'] = ui->button_0;


        keyButtons['_'] = ui->button_Dash;
        keyButtons['+'] = ui->button_Equals;
        keyButtons['{'] = ui->button_LBracket;
        keyButtons['}'] = ui->button_RBracket;
        keyButtons['|'] = ui->button_Backslash;
        keyButtons[':'] = ui->button_Semicolon;
        keyButtons['"'] = ui->button_Apostrophe;
        keyButtons['<'] = ui->button_Comma;
        keyButtons['>'] = ui->button_Period;
        keyButtons['?'] = ui->button_Slash;
        keyButtons['~'] = ui->button_Backtick;

}
