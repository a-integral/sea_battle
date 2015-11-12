#include "gameover_window.h"
#include "ui_gameover_window.h"

gameover_window::gameover_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameover_window)
{
    ui->setupUi(this);   
}

gameover_window::~gameover_window()
{
    delete ui;
}

void gameover_window::on_pushButton_clicked()
{
    close();
}
void gameover_window::settext(char *s)
{
    strcpy(message,s);
    ui->label->setText(message);
}
