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
    //Board* board_0{};
    //QGraphicsScene* scene = new QGraphicsScene(this);
    BoardView* board_view_0 = new BoardView(this);

    // DRAW EMPTY BOARD
    board_view_0->drawBoard();
    ui->graphicsView->setScene(board_view_0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
