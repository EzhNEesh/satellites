#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "satellite.h"

class InfoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InfoWindow(std::vector<Satellite> &satellites, QWidget *parent = nullptr);
    ~InfoWindow();

private:
    int satellitesCount;
    QString oldestDate;
    std::map<int, int> groupedByYearSatellites;
    std::map<int, int> groupedByInclinationSatellites;

    QWidget *centralWidget;
    QGridLayout *mainLayout;
    QLabel *countLabelText;
    QLabel *countLabelValue;
    QLabel *oldestDataDateText;
    QLabel *oldestDataDateValue;
    QLabel *yearGroupedText;
    QLabel *inclinationText;
    QPushButton *saveToFileButton;

private slots:
    void saveToFile();
};

#endif // INFOWINDOW_H
