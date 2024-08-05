#include <math.h>
#include <fstream>

#include "infowindow.h"
#include "tleparser.h"

InfoWindow::InfoWindow(std::vector<Satellite> &satellites, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Statistic");

    centralWidget = new QWidget(this);
    centralWidget->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainLayout = new QGridLayout(centralWidget);

    satellitesCount = satellites.size();
    countLabelText = new QLabel("Count of satellites: ", this);
    countLabelValue = new QLabel(QString::number(satellitesCount), this);
    mainLayout->addWidget(countLabelText, 0, 0);
    mainLayout->addWidget(countLabelValue, 0, 1);

    oldestDate = Satellite::getOldestDate(satellites).toString("dd.MM.yyyy");
    oldestDataDateText = new QLabel("The oldest download data date: ", this);
    oldestDataDateValue = new QLabel(oldestDate, this);
    mainLayout->addWidget(oldestDataDateText, 1, 0);
    mainLayout->addWidget(oldestDataDateValue, 1, 1);

    yearGroupedText = new QLabel("Count of satellites grouped by year: ", this);
    mainLayout->addWidget(yearGroupedText, 2, 0);
    int curRow = 2;
    groupedByYearSatellites = Satellite::groupByDate(satellites);
    for (auto &[year, sc] : groupedByYearSatellites) {
        QLabel *yearGroupedValue = new QLabel(QString::number(year) + ": " + QString::number(sc), this);
        mainLayout->addWidget(yearGroupedValue, curRow, 1);
        curRow++;
    }

    inclinationText = new QLabel("Count of satellites grouped by inclination: ", this);
    mainLayout->addWidget(inclinationText, curRow, 0);
    groupedByInclinationSatellites = Satellite::groupByInclination(satellites);
    for (auto &[inc, sc] : groupedByInclinationSatellites) {
        QLabel *incGroupedValue = new QLabel(QString::number(inc) + ": " + QString::number(sc), this);
        mainLayout->addWidget(incGroupedValue, curRow, 1);
        curRow++;
    }

    saveToFileButton = new QPushButton("Save to file", this);
    saveToFileButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    connect(saveToFileButton, &QPushButton::released, this, &InfoWindow::saveToFile);
    mainLayout->addWidget(saveToFileButton, curRow, 0);
    curRow++;

    centralWidget->resize(400, curRow * 35);
    setMinimumSize(400, curRow * 35);
}

void InfoWindow::saveToFile() {
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Save satellites statistic", "",
                                                    "Text (*.txt)");
    TLEParser tleParser;
    tleParser.saveToFile(filePath, satellitesCount, oldestDate, groupedByYearSatellites, groupedByInclinationSatellites);
}

InfoWindow::~InfoWindow() {}
