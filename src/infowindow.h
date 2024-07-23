#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <math.h>

#include "tlereader.h"

namespace Ui {
class InfoWindow;
}

class InfoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InfoWindow(std::vector<Satellite> &satellites, QWidget *parent = nullptr);
    ~InfoWindow();

private:
    Ui::InfoWindow *ui;
    int satellitesCount;
    QString oldestDate;
    std::map<int, int> groupedByYearSatellites;
    std::map<int, int> groupedByInclinationSatellites;
    // void closeEvent(QCloseEvent *);

private slots:
    void saveToFile();
};

#endif // INFOWINDOW_H
