#include "satellite.h"

Satellite::Satellite(const QString &_name) {
    // if (name.size() > 24) {
    //     throw std::out_of_range("Satellite " + _name.toStdString() + ": length error");
    // }
    name = _name.trimmed();
}

bool Satellite::checkControlSum(const QString &row) {
    int digSum = 0;
    for (QChar &c : row.sliced(0, row.size() - 1)) {
        if (c.isDigit()) {
            digSum += c.digitValue();
        } else if (c == '-') {
            digSum++;
        }
    }
    return digSum % 10 == row[row.size() - 1].digitValue();
}

void Satellite::parseAndSetFirstRow(const QString &row) {
    if (row.size() != 69) {
        throw std::out_of_range("Satellite " + name.toStdString() + ": first row length error");
    }
    if (checkControlSum(row)) {
        number = row.sliced(2, 5).toInt();
        classification = row.sliced(7, 1).trimmed();
        yearLaunch = row.sliced(9, 2).toInt() > 30 ? row.sliced(9, 2).toInt() + 1900 : row.sliced(9, 2).toInt() + 2000;
        numberInYearLaunch = row.sliced(11, 3).toInt();
        partInYearLaunch = row.sliced(14, 3);
        yearOfTheEra = row.sliced(18, 2).toInt();
        timeOfEra = std::pair<int, int> (row.sliced(20, 3).toInt(), row.sliced(24, 8).toInt());
    } else {
        throw std::logic_error("Satellite " + name.toStdString() + ": First row checksum error");
    }
}

void Satellite::parseAndSetSecondRow(const QString &row) {
    if (row.size() != 69) {
        throw std::out_of_range("Satellite " + name.toStdString() + ": second row length error");
    }
    if (checkControlSum(row)) {
        if (row.sliced(2, 5).toInt() == number){
            inclination = row.sliced(8, 6).toFloat();
        } else {
            throw std::logic_error("Satellite " + name.toStdString() + ": The numbers in the rows are different");
        }
    } else {
        throw std::logic_error("Satellite " + name.toStdString() + ": Second row checksum error");
    }
}

int Satellite::getYearLaunch() {
    return yearLaunch;
}

QDate Satellite::getDataDate() {
    int correctYear = yearOfTheEra > 30 ? yearOfTheEra + 1900 : yearOfTheEra + 2000;
    return QDate{correctYear, 1, 1}.addDays(timeOfEra.first);
}

float Satellite::getInclination() {
    return inclination;
}

QDate Satellite::getOldestDate(std::vector<Satellite> &satellites) {
    QDate oldestDataDate = satellites[0].getDataDate();
    for (int i = 1; i < satellites.size(); i++) {
        QDate curDate = satellites[i].getDataDate();
        if (curDate < oldestDataDate) {
            oldestDataDate = curDate;
        }
    }
    return oldestDataDate;
}

std::map<int, int> Satellite::groupByDate(std::vector<Satellite> &satellites) {
    std::map<int, int> groupedByYearSatellites;
    for (auto &satellite : satellites) {
        int curYear = satellite.getYearLaunch();
        if (groupedByYearSatellites.find(curYear) == groupedByYearSatellites.end()) {
            groupedByYearSatellites[curYear] = 0;
        }
        groupedByYearSatellites[curYear] += 1;
    }
    return groupedByYearSatellites;
}

std::map<int, int> Satellite::groupByInclination(std::vector<Satellite> &satellites) {
    std::map<int, int> groupedByInclinationSatellites;
    for (auto &satellite : satellites) {
        int curInc = std::roundf(satellite.getInclination());
        if (groupedByInclinationSatellites.find(curInc) == groupedByInclinationSatellites.end()) {
            groupedByInclinationSatellites[curInc] = 0;
        }
        groupedByInclinationSatellites[curInc] += 1;
    }
    return groupedByInclinationSatellites;
}
