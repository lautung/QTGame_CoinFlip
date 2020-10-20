#include "chooselevelscene.h"

#include <QLabel>
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include "mypushbutton.h"
#include <QDebug>
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //设置选择关卡场景
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置图标
    this->setWindowTitle("选择关卡场景");
    //创建菜单栏
    QMenuBar* menuBar=new QMenuBar(this);
    setMenuBar(menuBar);
    QMenu * startMenu=menuBar->addMenu("开始");
    //创建退出的菜单项
    QAction* quitAction=startMenu->addAction("退出");
    //点击退出
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //选择关卡的音效
    QSound * chooseSound=new QSound(":/res/TapButtonSound.wav",this);
    //返回按钮的音效
    QSound * backBtnSound=new QSound(":/res/BackButtonSound.wav",this);

    //返回按钮
    MyPushButton * backPushButton = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backPushButton->setParent(this);
    backPushButton->move((this->width()-backPushButton->width()),(this->height()-backPushButton->height()));

    //点击返回按钮
    connect(backPushButton,&MyPushButton::clicked,[=](){
        qDebug()<<"点击了返回按钮";
        backBtnSound->play();
        //
        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });
    });

    //创建选择关卡的按钮
    for(int i= 0;i<20;i++){
        MyPushButton * menuButton=new MyPushButton(":/res/LevelIcon.png");
        menuButton->setParent(this);
        menuButton->move(i%4*70+25,i/4*70+130);
        connect(menuButton,&MyPushButton::clicked,[=](){
            //播放音效
           chooseSound->play();
           qDebug()<<QString("您选择的是第%1关").arg(QString::number(i+1));
           //进入到游戏的场景
           playScene=new PlayScene(i+1);
           playScene->show();
           playScene->setGeometry(this->geometry());
           this->hide();
           //监听选择关卡的返回按钮的信号
           connect(playScene,&PlayScene::chooseSceneBack,[=](){
               this->setGeometry(playScene->geometry());
               this->show();
               delete playScene;
               playScene=NULL;
           });
        });
        QLabel * label=new QLabel;
        label->setAttribute(Qt::WA_TransparentForMouseEvents);//使得鼠标事件能够穿透label标签
        label->setParent(this);
        label->setFixedSize(menuButton->width(),menuButton->height());
        label->setText(QString::number(i+1));
        label->move(i%4*70+25,i/4*70+130);
        label->setAlignment(Qt::AlignCenter);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
