#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QWidget *parent = nullptr);
    explicit PlayScene(int level);
    int level;

    void paintEvent(QPaintEvent *event);

    int gameArray[4][4];//二维数组，维护每个关卡的具体数据

    MyCoin* coinBtn[4][4]; //用户维护MyCoin实例的数组

    //是否胜利的标志
    bool isWin;
signals:
    void chooseSceneBack();

public slots:
};

#endif // PLAYSCENE_H
