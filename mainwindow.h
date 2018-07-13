#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "board.h"
#include "boardview.h"
#include "setupview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Board* board_player_;
    Board* board_cpu_;
    BoardView* board_view_player_;
    BoardView* board_view_cpu_;
    SetupView* setup_view_;
};

#endif // MAINWINDOW_H
