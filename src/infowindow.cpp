#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <math.h>
#include <fstream>

#include "infowindow.h"

InfoWindow::InfoWindow(std::vector<Satellite> &satellites, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Statistic");

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    QGridLayout *mainLayout = new QGridLayout(centralWidget);

    satellitesCount = satellites.size();
    QLabel *countLabelText = new QLabel("Count of satellites: ", this);
    QLabel *countLabelValue = new QLabel(QString::number(satellitesCount), this);
    mainLayout->addWidget(countLabelText, 0, 0);
    mainLayout->addWidget(countLabelValue, 0, 1);

    oldestDate = Satellite::getOldestDate(satellites).toString("dd.MM.yyyy");
    QLabel *oldestDataDateText = new QLabel("The oldest download data date: ", this);
    QLabel *oldestDataDateValue = new QLabel(oldestDate, this);
    mainLayout->addWidget(oldestDataDateText, 1, 0);
    mainLayout->addWidget(oldestDataDateValue, 1, 1);

    QLabel *yearGroupedText = new QLabel("Count of satellites grouped by year: ", this);
    mainLayout->addWidget(yearGroupedText, 2, 0);
    int curRow = 2;
    groupedByYearSatellites = Satellite::groupByDate(satellites);
    for (auto &[year, sc] : groupedByYearSatellites) {
        int correctYear = year > 30 ? year + 1900 : year + 2000;
        QLabel *yearGroupedValue = new QLabel(QString::number(correctYear) + ": " + QString::number(sc), this);
        mainLayout->addWidget(yearGroupedValue, curRow, 1);
        curRow++;
    }

    QLabel *inclinationText = new QLabel("Count of satellites grouped by inclination: ", this);
    mainLayout->addWidget(inclinationText, curRow, 0);
    groupedByInclinationSatellites = Satellite::groupByInclination(satellites);
    for (auto &[inc, sc] : groupedByInclinationSatellites) {
        QLabel *incGroupedValue = new QLabel(QString::number(inc) + ": " + QString::number(sc), this);
        mainLayout->addWidget(incGroupedValue, curRow, 1);
        curRow++;
    }

    QPushButton *saveToFileButton = new QPushButton("Save to file", this);
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
    std::ofstream file(filePath.toStdString());
    if (file.is_open()) {
        file << "Count of satellites: " << satellitesCount << std::endl;
        file << "The oldest download data date: " << oldestDate.toStdString() << std::endl;
        file << "Count of satellites grouped by year: " << std::endl;
        for (auto &[year, sc] : groupedByYearSatellites) {
            int correctYear = year > 30 ? year + 1900 : year + 2000;
            file << correctYear << ": " << sc << std::endl;
        }
        file << "Count of satellites grouped by inclination: " << std::endl;
        for (auto &[inc, sc] : groupedByInclinationSatellites) {
            file << inc << ": " << sc << std::endl;
        }
        file.close();
    }
}

InfoWindow::~InfoWindow() {}
