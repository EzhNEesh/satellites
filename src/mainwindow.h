#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QRadioButton>
#include <QMessageBox>

#include "tlereader.h"

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
    TLEReader *tleReader;
    QMessageBox *errorWindow;

private slots:
    void showInfoClicked();
    void dataReceived(std::vector<Satellite>);
    void showErrorWindow(const QString &);
};
#endif // MAINWINDOW_H
