#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boardview.h"
#include "setupview.h"
#include "audio.h"
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGraphicsScene>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // BOARD CONFIGS
    board_player_ = new Board(true);
    board_cpu_ = new Board(false);
    board_view_player_ = new BoardView(this, board_player_);
    board_view_cpu_ = new BoardView(this, board_cpu_);

    // DRAW EMPTY BOARDS
    board_view_player_->drawBoard();
    board_view_cpu_->drawBoard();
    ui->graphicsView->setScene(board_view_player_);
    ui->graphicsView_2->setScene(board_view_cpu_);
    ui->graphicsView->setMouseTracking(true);

    // SETUP CONFIG
    setup_view_ = new SetupView(this);
    setup_view_->drawSetup();
    ui->graphicsView_3->setScene(setup_view_);

    // SETUP-BOARD CONNECTION
    QObject::connect(setup_view_, SIGNAL(sendFamily(int)), board_view_player_, SLOT(receiveFamily(int)));
    QObject::connect(board_view_player_, SIGNAL(returnFamily(int)), setup_view_, SLOT(retakeFamily(int)));
    QObject::connect(board_view_cpu_, SIGNAL(cpu_lost()), board_view_player_, SLOT(win()));

    // AUDIO CONFIG
    QMediaPlayer* audio = new Audio(this);
    QObject::connect(board_view_cpu_, SIGNAL(duckSound()), audio, SLOT(playRandom()));
    QObject::connect(board_view_player_, SIGNAL(duckSound()), audio, SLOT(playRandom()));

    // BACKGROUND MUSIC
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/resources/assets/duckstroll.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->setVolume(5);
    music->play();

}

MainWindow::~MainWindow()
{
    delete ui;
}
