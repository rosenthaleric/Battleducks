#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boardview.h"
#include "setupview.h"
#include <QGraphicsView>
#include <QGraphicsScene>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // BOARD CONFIGS
    Board* board_player = new Board(true);
    Board* board_cpu = new Board(false);
    BoardView* board_view_player = new BoardView(this, board_player);
    BoardView* board_view_cpu = new BoardView(this, board_cpu);

    // DRAW EMPTY BOARDS
    board_view_player->drawBoard();
    board_view_cpu->drawBoard();
    ui->graphicsView->setScene(board_view_player);
    ui->graphicsView_2->setScene(board_view_cpu);
    ui->graphicsView->setMouseTracking(true);

    // SETUP CONFIG
    SetupView* setup_view = new SetupView(this);
    setup_view->drawSetup();
    ui->graphicsView_3->setScene(setup_view);

    // SETUP-BOARD CONNECTION
    QObject::connect(setup_view, SIGNAL(sendFamily(int)), board_view_player, SLOT(receiveFamily(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}
