#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boardview.h"
#include "setupview.h"
#include "audio.h"
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGraphicsScene>
#include <QTimer>
#include <memory>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // BOARD CONFIGS
    int* mode = new int(0);
    board_player_ = new Board(true, mode);
    board_view_player_ = new BoardView(this, board_player_);
    board_cpu_ = new Board(false,mode);
    enemy_ = new Enemy(this, board_view_player_, board_player_);
    board_view_cpu_ = new BoardView(this, board_cpu_);
    board_view_cpu_->setEnemy(enemy_);
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
    QObject::connect(board_view_player_, SIGNAL(player_lost()), board_view_player_, SLOT(lose()));

    QObject::connect(ui->pushButton, SIGNAL(released()), board_view_player_, SLOT(start()));
    QObject::connect(ui->pushButton, SIGNAL(released()), board_view_cpu_, SLOT(start()));
    QObject::connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(restart()));

    // AUDIO CONFIG
    QMediaPlayer* audio = new Audio(this);
    QObject::connect(board_view_cpu_, SIGNAL(duckSound()), audio, SLOT(playRandom()));
    QObject::connect(board_view_player_, SIGNAL(duckSound()), audio, SLOT(playRandom()));
    QObject::connect(board_view_player_, SIGNAL(player_lost()), audio, SLOT(play_lose_sound()));
    QObject::connect(board_view_cpu_, SIGNAL(cpu_lost()), audio, SLOT(play_win_sound()));
    QObject::connect(board_view_player_, SIGNAL(blankSound()), audio, SLOT(play_blank()));
    QObject::connect(board_view_cpu_, SIGNAL(blankSound()), audio, SLOT(play_blank()));

    // BACKGROUND MUSIC
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/resources/assets/duckstroll.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    music_ = new QMediaPlayer();
    music_->setPlaylist(playlist);
    music_->setVolume(4);
    music_->play();

    QObject::connect(audio, SIGNAL(stopMusic()), this, SLOT(interruptSong()));
}

void MainWindow::restart() {
    std::cout << "RESET" << std::endl;
    board_cpu_->resetDuckfamilies();
    board_cpu_->resetTiles();
    board_cpu_->setupCPUBoard();
    board_player_->resetDuckfamilies();
    board_player_->resetTiles();
    setup_view_->reset();
    setup_view_->updateSetup();
    board_cpu_->setMode(0);
    board_view_player_->drawBoard();
    board_view_cpu_->drawBoard();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::interruptSong() {
    music_->stop();
    QTimer::singleShot(5400, this, SLOT(continueSong()));
}

void MainWindow::continueSong() {
    music_->play();
}
