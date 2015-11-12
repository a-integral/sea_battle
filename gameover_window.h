#ifndef GAMEOVER_WINDOW_H
#define GAMEOVER_WINDOW_H

#include <QDialog>

namespace Ui {
class gameover_window;
}

class gameover_window : public QDialog
{
    Q_OBJECT

public:
    explicit gameover_window(QWidget *parent = 0);
    ~gameover_window();
    void settext(char*s="");
private slots:
    void on_pushButton_clicked();

private:
    Ui::gameover_window *ui;
    char message[40];
};

#endif // GAMEOVER_WINDOW_H
