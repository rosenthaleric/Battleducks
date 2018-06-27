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
    QGraphicsScene* scene = new QGraphicsScene(this);
    BoardView* board_0 = new BoardView(scene);

    // DRAW EMPTY BOARD
    board_0->drawBoard();
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
