#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Populate dropdown with available cities
    ui->cityComboBox->addItems({"Cairo", "London", "New York", "Tokyo"});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fetchButton_clicked()
{
    ui->fetchButton->setEnabled(false);
    ui->tempLabel->setText("Loading...");

    QString selectedCity = ui->cityComboBox->currentText();
    std::string apiUrl = cityManager.getApiUrl(selectedCity.toStdString());

    // Run curl fetch in background thread
    QFutureWatcher<std::string> *watcher = new QFutureWatcher<std::string>(this);
    connect(watcher, &QFutureWatcher<std::string>::finished, this, [this, watcher]() {
        std::string rawJson = watcher->result();
        watcher->deleteLater();

        ui->fetchButton->setEnabled(true);

        if (rawJson.empty()) {
            ui->tempLabel->setText("Error: Network Timeout");
            return;
        }

        WeatherData weather = jsonParser.parseCurrentWeather(rawJson);
        ui->tempLabel->setText("Temperature: " + QString::number(weather.temperature) + " °C");
        ui->windLabel->setText("Wind Speed: " + QString::number(weather.windSpeed) + " km/h");

        renderForecastChart(weather.dailyMaxTemp);
    });

    QFuture<std::string> future = QtConcurrent::run([this, apiUrl]() {
        return curlClient.fetchData(apiUrl);
    });

    watcher->setFuture(future);
}

void MainWindow::renderForecastChart(const std::vector<double> &dailyTemps)
{
    if (dailyTemps.empty()) return;

    QLineSeries *series = new QLineSeries();
    series->setName("Max Temperature (°C)");

    for (size_t i = 0; i < dailyTemps.size(); ++i) {
        series->append(i + 1, dailyTemps[i]);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("7-Day Temperature Forecast");
    chart->createDefaultAxes();
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Render directly onto your promoted chartWidget
    QChartView *chartView = qobject_cast<QChartView*>(ui->chartWidget);
    if (chartView) {
        chartView->setChart(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
    }
}