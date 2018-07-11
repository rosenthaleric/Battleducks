#include "audio.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <random>

Audio::Audio(QObject *parent)
    : QMediaPlayer(parent)
{
    sounds_ = new QMediaPlaylist();
    sounds_->addMedia(QUrl("qrc:/resources/assets/quack0.mp3"));
    sounds_->addMedia(QUrl("qrc:/resources/assets/quack1.mp3"));
    sounds_->addMedia(QUrl("qrc:/resources/assets/quack2.mp3"));
    sounds_->addMedia(QUrl("qrc:/resources/assets/quack3.mp3"));
    this->setVolume(10);
}

void Audio::playRandom() {
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<float> dist(0, 4);

   this->setMedia(sounds_->media(std::floor(dist(e2))));
   this->play();
}
