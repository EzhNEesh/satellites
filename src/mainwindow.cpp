#include <QLabel>
#include <QPushButton>

#include "mainwindow.h"
#include "infowindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Satellites");
    tleParser = new TLEParser(this);
    connect(tleParser, &TLEParser::dataIsReady, this, &MainWindow::dataReceived);
    connect(tleParser, &TLEParser::errorOcurred, this, &MainWindow::showErrorWindow);

    centralWidget = new QWidget(this);
    centralWidget->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainLayout = new QGridLayout(centralWidget);

    pathLabel = new QLabel("Input path to data: ");
    pathLabel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainLayout->addWidget(pathLabel, 0, 0);

    pathInput = new QLineEdit();
    pathInput->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed));
    // pathInput->resize(100, 0);

    mainLayout->addWidget(pathInput, 0, 1);

    choosePathType = new QGroupBox();
    choosePathType->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    fileRadio = new QRadioButton("File source");
    urlRadio = new QRadioButton("Web source");
    fileRadio->setChecked(true);

    radioLayout = new QVBoxLayout;
    radioLayout->addWidget(fileRadio);
    radioLayout->addWidget(urlRadio);
    choosePathType->setLayout(radioLayout);
    mainLayout->addWidget(choosePathType, 1, 0);

    showInfoButton = new QPushButton("Show info");
    showInfoButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainLayout->addWidget(showInfoButton, 2, 0);

    connect(showInfoButton, &QPushButton::released, this, &MainWindow::showInfoClicked);

    setCentralWidget(centralWidget);
    errorWindow = new QMessageBox(this);

    centralWidget->setMaximumHeight(200);
    setMinimumSize(400, 200);
}

void MainWindow::showInfoClicked() {
    showInfoButton->setDisabled(true);
    if (fileRadio->isChecked()) {
        tleParser->fromFile(pathInput->text());
    } else {
        tleParser->fromURL(pathInput->text());
    }
}

void MainWindow::dataReceived(std::vector<Satellite> satellites) {
    InfoWindow *iWindow = new InfoWindow(satellites, this);
    iWindow->setAttribute(Qt::WA_DeleteOnClose);
    iWindow->show();
    showInfoButton->setDisabled(false);
}

void MainWindow::showErrorWindow(const QString &message) {
    errorWindow->setText(message);
    errorWindow->show();
    showInfoButton->setDisabled(false);
}

MainWindow::~MainWindow() {}
