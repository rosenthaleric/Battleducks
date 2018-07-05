#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boardView.h"
#include <QGraphicsView>
#include <QGraphicsScene>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // CONFIG
    BoardView* board_view_player = new BoardView(this);
    BoardView* board_view_cpu = new BoardView(this);

    // DRAW EMPTY BOARD
    board_view_player->drawBoard();
    board_view_cpu->drawBoard();
    ui->graphicsView->setScene(board_view_player);
    ui->graphicsView_2->setScene(board_view_cpu);
}

MainWindow::~MainWindow()
{
    delete ui;
}
