#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QRadioButton>
#include <QMessageBox>

#include "tleparser.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *centralWidget;
    QGridLayout *mainLayout;
    QLabel *pathLabel;
    QLineEdit *pathInput;
    QGroupBox *choosePathType;
    QVBoxLayout *radioLayout;
    QRadioButton *fileRadio;
    QRadioButton *urlRadio;
    QPushButton *showInfoButton;
    TLEParser *tleParser;
    QMessageBox *errorWindow;

private slots:
    void showInfoClicked();
    void dataReceived(std::vector<Satellite> satellites);
    void showErrorWindow(const QString &message);
};
#endif // MAINWINDOW_H
