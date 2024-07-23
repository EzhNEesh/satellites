#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Satellites");
    tleReader = new TLEReader(this);
    connect(tleReader, &TLEReader::dataIsReady, this, &MainWindow::dataReceived);
    connect(tleReader, &TLEReader::errorOcurred, this, &MainWindow::showErrorWindow);
    // connect(tleReader, &TLEReader::readingError, this, &MainWindow::errorOcurred);

    centralWidget = new QWidget();
    centralWidget->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    centralWidget->setMaximumSize(450, 150);
    mainLayout = new QGridLayout(centralWidget);

    pathLabel = new QLabel("Input path to data: ");
    pathLabel->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    mainLayout->addWidget(pathLabel, 0, 0);

    pathInput = new QLineEdit();
    pathInput->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum));
    mainLayout->addWidget(pathInput, 0, 1);

    choosePathType = new QGroupBox();
    choosePathType->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum));
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

    this->setCentralWidget(centralWidget);
    errorWindow = new QMessageBox(this);
}

void MainWindow::showInfoClicked() {
    showInfoButton->setDisabled(true);
    if (fileRadio->isChecked()) {
        // QString pathInputText = pathInput->text();
        tleReader->fromFile(pathInput->text());
    } else {
        tleReader->fromURL(pathInput->text());
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

MainWindow::~MainWindow()
{
    delete ui;
}
