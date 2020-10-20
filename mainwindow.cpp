#include "mainwindow.h"
#include "mypushbutton.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //配置主场景

    //设置固定大小
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("翻金币主场景");
    //退出
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
    //准备开始按钮的音效
    QSound * startSound=new QSound(":/res/TapButtonSound.wav",this);

    //开始的按钮
    MyPushButton * startButton=new MyPushButton(":/res/MenuSceneStartButton.png");
    startButton->setParent(this);
    startButton->move(this->width()*0.5-startButton->width()*0.5,this->height()*0.7);
    //实例化选择关卡的场景
    chooseScene=new ChooseLevelScene;
    //监听选择关卡的返回按钮的信号
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
        //设置场景的位置
        this->setGeometry(chooseScene->geometry());
        chooseScene->hide();
        this->show();
    });
    connect(startButton,&MyPushButton::clicked,[=](){
        qDebug()<<"点击了开始按钮";
        //播放音效
        startSound->play();

        startButton->zoom1();
        startButton->zoom2();

        //进入到选择关卡场景中
        QTimer::singleShot(500,this,[=](){
            //设置场景的位置信息
            chooseScene->setGeometry(this->geometry());
            //自身隐藏
            this->hide();
            //显示选择关卡场景
            chooseScene->show();

        });



    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
    //画背景上图标
    pixmap.load(":/res/Title.png");
    pixmap.scaled(pixmap.width()*0.5,pixmap.height()*0.5);
    painter.drawPixmap(10,20,pixmap);
}
