#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "enemyfield.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->myfield.dadui=this->ui->tableWidget;
  //  QPushButton *cells[100];
 //   for (int i=0;i<100;i++) cells[i]=new QPushButton();
//    for (int i=0;i<10;i++)
//        for (int j=0;j<10;j++)
//            connect(cells[i*10+j],SIGNAL(clicked()),&myfield,SLOT(myfieldclick(j,i,2,1)));
    myfield_obj.gui=ui;
    enemyfield_obj.gui=ui;
    enemyfield_obj.playerfield=&myfield_obj;
    enemyfield_obj.gwptr=&gw;
}

MainWindow::~MainWindow()
{

    delete ui;
}



/*void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    this->myfield.put(column,row,2,1,this->ui->tableWidget);
}*/

void MainWindow::on_myfield_cellClicked(int row, int column)
{
    if(!this->myfield_obj.put(column,row))
    {
        this->enemyfield_obj.ai_placement();
    };
}

void MainWindow::on_enemyfield_cellClicked(int row, int column)
{
    this->enemyfield_obj.strike(column,row);
}


void MainWindow::on_radioButton_clicked()
{
    this->myfield_obj.setvert();
    this->ui->radioButton->setChecked(true);
    this->ui->radioButton_2->setChecked(false);
}


void MainWindow::on_radioButton_2_clicked()
{
    this->myfield_obj.sethor();
    this->ui->radioButton->setChecked(false);
    this->ui->radioButton_2->setChecked(true);
}


void MainWindow::on_radioButton_1deck_clicked()
{
    this->myfield_obj.setonedeck();
    this->ui->radioButton_1deck->setChecked(true);
     this->ui->radioButton_2deck->setChecked(false);
     this->ui->radioButton_3deck->setChecked(false);
     this->ui->radioButton_4deck->setChecked(false);
}

void MainWindow::on_radioButton_2deck_clicked()
{
   this->myfield_obj.settwodeck();
    this->ui->radioButton_1deck->setChecked(false);
     this->ui->radioButton_2deck->setChecked(true);
     this->ui->radioButton_3deck->setChecked(false);
     this->ui->radioButton_4deck->setChecked(false);
}

void MainWindow::on_radioButton_3deck_clicked()
{
     this->myfield_obj.setthreedeck();
    this->ui->radioButton_1deck->setChecked(false);
     this->ui->radioButton_2deck->setChecked(false);
     this->ui->radioButton_3deck->setChecked(true);
     this->ui->radioButton_4deck->setChecked(false);
}


void MainWindow::on_radioButton_4deck_clicked()
{
    this->myfield_obj.setfourdeck();
    this->ui->radioButton_1deck->setChecked(false);
     this->ui->radioButton_2deck->setChecked(false);
     this->ui->radioButton_3deck->setChecked(false);
     this->ui->radioButton_4deck->setChecked(true);
}



void MainWindow::on_randomput_clicked()
{
    this->myfield_obj.ai_placement();
    this->ui->randomput->setEnabled(false);
    this->enemyfield_obj.ai_placement();
}

void MainWindow::on_savebutton_clicked()
{
    myfield_obj.save();
    enemyfield_obj.save();
}

void MainWindow::on_newgamebutton_clicked()
{
    myfield_obj.resetfield();
    enemyfield_obj.resetfield();

    this->ui->gui_decknum->setEnabled(true);
    this->ui->gui_shippos->setEnabled(true);
    this->ui->randomput->setEnabled(true);

}


void MainWindow::on_loadbutton_clicked()
{
    myfield_obj.load();
    enemyfield_obj.load();
}
