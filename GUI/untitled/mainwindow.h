#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <fstream>
#include "Course.hpp"
#include "Classes.hpp"
#include "Schedule.hpp"
#include <vector>
#include "CompulsoryCourse.hpp"
#include "ElectiveCourses.hpp"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Schedule mySchedule = Schedule();
    vector<Course *> myCourses;
    string course;
    string classes;
    string services;
    string busy;


private slots:


    void on_Course_clicked();

    void on_Classes_clicked();

    void on_Services_clicked();

    void on_Busy_clicked();

    void on_makeSchedule_clicked();

    void on_clearButton_clicked();


    void on_addButton_clicked();

    void on_exportBut_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
