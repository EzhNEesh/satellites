#ifndef SATELLITE_H
#define SATELLITE_H

#include <QDate>
#include <QString>
#include <map>

class Satellite
{
public:
    explicit Satellite(const QString &);
    void parseAndSetFirstRow(const QString &);
    void parseAndSetSecondRow(const QString &);
    int getYearLaunch();
    QDate getDataDate();
    float getInclination();
    static QDate getOldestDate(std::vector<Satellite> &);
    static std::map<int, int> groupByDate(std::vector<Satellite> &);
    static std::map<int, int> groupByInclination(std::vector<Satellite> &);

private:
    QString name;
    int number;
    QString classification;
    int yearLaunch;
    int numberInYearLaunch;
    QString partInYearLaunch;
    int yearOfTheEra;
    std::pair<int, int> timeOfEra;
    float inclination;
    bool checkControlSum(const QString &);
};

#endif // SATELLITE_H
