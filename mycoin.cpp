#include "mycoin.h"
#include <QDebug>
#include "mypushbutton.h"
#include <QTimer>

//MyCoin::MyCoin(QWidget *parent) : MyPushButton(parent)
//{

//}

MyCoin::MyCoin(QString btnImg):MyPushButton(btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret){
        qDebug()<<"加载图片失败";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    this->timer1=new QTimer(this);
    this->timer2=new QTimer(this);
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1").arg(this->min++);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //判断 如果翻完了 将min重置为1
        if(this->min>this->max){
            this->min=1;
            this->timer1->stop();
            this->isAnimation=false;
        }
    });

    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1").arg(this->max--);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //判断 如果翻完了 将max重置为8
        if(this->min>this->max){
            this->max=8;
            this->timer2->stop();
            this->isAnimation=false;
        }
    });
}

void MyCoin::changeFlag()
{
    //如果是正面 翻成反面
    if(this->flag){
        this->timer1->start(30);
        this->isAnimation=true;//开始做动画
         this->flag=!this->flag;
    }else{
        this->timer2->start(30);
        this->isAnimation=true;//开始做动画
        this->flag=!this->flag;
    }

}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation||this->isWin){
        return;
    }
    QPushButton::mousePressEvent(e);
}
