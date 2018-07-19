#ifndef AUDIO_H
#define AUDIO_H

#include <QMediaPlayer>

class Audio : public QMediaPlayer
{
    Q_OBJECT
public:
    Audio(QObject *parent = 0);

private:
    QMediaPlaylist* sounds_;

public slots:
    void playRandom();
    void play_blank();
    void play_win_sound();
    void play_lose_sound();

signals:
    void stopMusic();
};

#endif // AUDIO_H
