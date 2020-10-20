#ifndef MYCOIN_H
#define MYCOIN_H

#include "mypushbutton.h"

class MyCoin : public MyPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);

    //参数代表 传入的金币图片路径
    explicit MyCoin(QString btnImg);

    //金币的属性
    int posX;//X坐标
    int posY;//Y坐标
    bool flag;//是否正面
    void changeFlag();

    QTimer * timer1; //正面翻反面定时器
    QTimer * timer2; //反面翻正面定时器
    int min=1;//最小图片
    int max=8;//最大图片

    //正在执行动画 标志
    bool isAnimation=false;

    //重写按下
    void mousePressEvent(QMouseEvent *e);

    //是否胜利的标志
    bool isWin=false;


signals:

public slots:
};

#endif // MYCOIN_H
