#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //重新paintEvent事件 画背景图
    void paintEvent(QPaintEvent *);

    PlayScene * playScene=NULL;


signals:
    //写一个自定义的信号 告诉主场景 点击了返回
    void chooseSceneBack();

public slots:
};

#endif // CHOOSELEVELSCENE_H
