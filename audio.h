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
};

#endif // AUDIO_H
