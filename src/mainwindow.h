#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QRadioButton>
#include <QMessageBox>

#include "infowindow.h"
// #include "tlereader.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
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

// signals:

private slots:
    void showInfoClicked();
    void dataReceived(std::vector<Satellite>);
    void showErrorWindow(const QString &);
};
#endif // MAINWINDOW_H
