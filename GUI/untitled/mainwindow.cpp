#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string"
#include "BigClass.hpp"
#include "SmallClass.hpp"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_Course_clicked()
{
    QString prnt;
    myCourses.clear();
    QString file_directory = QFileDialog::getOpenFileName(this,"Open a file","C://","*.csv");
    course = file_directory.toStdString();
    if(course == "")
        ui->message->append("You didn't select course file!");
    else{
        try{
         myCourses = Course::readCoursesFile(course);
        }
        catch(...){
            ui->message->append("Proper Courses file is not found!");
        }
        ui->message->append(prnt.fromStdString(to_string(myCourses.size()))+" course are found!");
    }
}

void MainWindow::on_Classes_clicked()
{
    QString prnt;
    QString file_directory = QFileDialog::getOpenFileName(this,"Open a file","C://","*.csv");
    classes = file_directory.toStdString();
    if(classes == "")
        ui->message->append("You didn't select classes file!");
    else{
        BigClass::bigClass = 0;
        SmallClass::smallClass = 0;
        mySchedule.myClasses.clear();
        try{
           mySchedule.myClasses = Classes::readClassesFile(classes);
        }
        catch(...){
            ui->message->append("Proper Classes file is not found!");
        }
        ui->message->append("You added "+prnt.fromStdString(to_string(mySchedule.myClasses.size()))+" classroom.");
 }

}

void MainWindow::on_Services_clicked()
{
    QString file_directory = QFileDialog::getOpenFileName(this,"Open a file","C://","*.csv");
    services = file_directory.toStdString();
    if(services == "")
        ui->message->append("You didn't select services file!");
}

void MainWindow::on_Busy_clicked()
{
    QString file_directory = QFileDialog::getOpenFileName(this,"Open a file","C://","*.csv");
    busy = file_directory.toStdString();
    if(busy == "")
        ui->message->append("You didn't select Busy file!");
}

void MainWindow::on_makeSchedule_clicked()
{
    if(myCourses.size() == 0)
      ui->message->append("There is no unplaced course!");
    bool cont;
    try{
        cont = mySchedule.takeService(myCourses, services);
           if (!cont) {
               ui->message->append("There is no way to make a perfect schedule for the department.");
               ui->message->append("You can add one more class from leftmost panel.");

            }
    }
    catch(...){
        ui->message->append("Proper Service file is not found!");
        return;
    }

    try{
        cont = mySchedule.takeBusy(myCourses, busy);
          if (!cont) {
               ui->message->append("There is no way to make a perfect schedule for the department.");
               ui->message->append("You can add one more class from leftmost panel.");

          }

     }
    catch(...){
        ui->message->append("Proper Busy file is not found!");
        return;
    }


     cont = mySchedule.putRest(myCourses);
     if (!cont) {
         ui->message->append("There is no way to make a perfect schedule for the department.");
         ui->message->append("You can add one more class from leftmost panel.");
         return;
  }

      QString prnt;
      QString lect;
      Classes *cs = mySchedule.myClasses.at(0);
      ui->table->setColumnCount(mySchedule.myClasses.size());

      for(int i = 0; i <mySchedule.myClasses.size(); i++){
          cs = mySchedule.myClasses.at(i);
          lect = lect.fromStdString(cs->getName());

          ui->table->setItem(1,i,new QTableWidgetItem(lect));
          for(int j = 0; j < 5; j++){
              lect = lect.fromStdString(cs->weekdays[j][0]->code);
              ui->table->setItem(2+j*2,i,new QTableWidgetItem(lect));
              lect = lect.fromStdString(cs->weekdays[j][1]->code);
              ui->table->setItem(3+j*2,i,new QTableWidgetItem(lect));
          }
      }
}

void MainWindow::on_clearButton_clicked()
{
    mySchedule.myClasses.clear();
    myCourses.clear();
    while(ui->table->columnCount() != 0)
        ui->table->removeColumn(0);
    BigClass::bigClass = 0;
    SmallClass::smallClass = 0;
    ui->message->setText("");
    ui->spinNum->setValue(0);
    ui->comboBox->setCurrentIndex(0);
}



void MainWindow::on_addButton_clicked()
{
    int i = ui->spinNum->value();
    if(i == 0)
        ui->message->append("You have to add more than zero class.");
    QString qRoom = ui->comboBox->currentText();
    string room = qRoom.toStdString();
    if(room == "")
        ui->message->append("You have to select classroom size!");

    if(mySchedule.myClasses.size() != 0){
        BigClass::bigClass = 0;
        SmallClass::smallClass = 0;
        mySchedule.myClasses.clear();
        try{
           mySchedule.myClasses = Classes::readClassesFile(classes);
        }
        catch(...){
            ui->message->append("Proper Classes file is not found!");
        }

    }
    else{
        ui->message->append("Please select classes file firstly");
        return;
    }


    try{
     myCourses = Course::readCoursesFile(course);
    }
    catch(...){

    }

    if(room == "smallClass"){
        for(int j = 0; j < i; j++){
            SmallClass* sm = new SmallClass();
            mySchedule.myClasses.push_back(sm);
        }
        ui->message->append("You added "+qRoom.fromStdString(to_string(i))+" small classroom");
        ui->message->append("Now you have "+qRoom.fromStdString(to_string(mySchedule.myClasses.size()))+" classroom");
    }
    else if(room == "bigClass"){
        for(int j = 0; j < i; j++){
            BigClass* bg = new BigClass();
            mySchedule.myClasses.push_back(bg);
        }
        ui->message->append("You added "+qRoom.fromStdString(to_string(i))+" big classroom");
        ui->message->append("Now you have "+qRoom.fromStdString(to_string(mySchedule.myClasses.size()))+" classroom");
    }


}


void MainWindow::on_exportBut_clicked()
{
    QString file_directory = QFileDialog::getSaveFileName(this,"Open a file","C://*csv","*.csv");
    if(!file_directory.endsWith(".csv"))
        file_directory.append(".csv");
    mySchedule.exportFile(file_directory.toStdString());
    ui->message->append("Exported to :"+file_directory);
}
