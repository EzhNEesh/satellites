#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QWidget>
#include <QFileDialog>

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

private slots:
    void saveToFile();
};

#endif // INFOWINDOW_H
