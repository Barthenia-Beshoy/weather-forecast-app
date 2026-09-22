#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "curl.h"
#include "rapidjson.h"
#include "cities.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_fetchButton_clicked();

private:
    Ui::MainWindow *ui;
    Curl curlClient;
    Rapidjson jsonParser;
    Cities cityManager;
    void renderForecastChart(const std::vector<double> &dailyTemps);
};

#endif // MAINWINDOW_H