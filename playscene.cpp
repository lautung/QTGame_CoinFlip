#include "dataconfig.h"
#include "mycoin.h"
#include "playscene.h"

#include <QPainter>
#include <QDebug>
#include <QMenuBar>
#include <QLabel>
#include "mypushbutton.h"
#include <QTimer>
#include <QPropertyAnimation>
#include <QPixmap>
#include <QSound>

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}



PlayScene::PlayScene(int level)
{
    this->level=level;
    qDebug()<<"进入第"<<this->level<<"关！";
    //设置选择关卡场景
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置图标
    this->setWindowTitle("翻金币场景");
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
    //返回按钮的音效
    QSound * flipSound=new QSound(":/res/ConFlipSound.wav",this);
    //返回按钮的音效
    QSound * winSound=new QSound(":/res/LevelWinSound.wav",this);
    //返回按钮的音效
    QSound * backBtnSound=new QSound(":/res/BackButtonSound.wav",this);

    //返回按钮
    MyPushButton * backPushButton = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backPushButton->setParent(this);
    backPushButton->move((this->width()-backPushButton->width()),(this->height()-backPushButton->height()));

    //点击返回按钮
    connect(backPushButton,&MyPushButton::clicked,[=](){
        qDebug()<<"翻金币的场景点击了返回按钮";
        backBtnSound->play();
        //
        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });
    });

    //显示当前的关卡数
    QLabel * label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("黑体");
    font.setPointSize(20);
    font.setBold(true);
    label->setFont(font);
    label->setText(QString("Level：%1").arg(this->level));
    label->setGeometry(30,this->height()-50,140,50);

    dataConfig config;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            this->gameArray[i][j]=config.mData[this->level][i][j];
        }
    }

    //胜利图片效果
    QLabel * winLabel=new QLabel;
    QPixmap temPix;
    bool load = temPix.load(":/res/LevelCompletedDialogBg.png");
    if(!load){
       qDebug()<<"图片加载失败";
    }
    winLabel->setGeometry(0,0,temPix.width(),temPix.height());
    winLabel->setPixmap(temPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-temPix.width())*0.5,-temPix.height());


    //显示金币背景图片
    for(int i =0 ;i<4;i++){
        for(int j=0;j<4;j++){
            //绘制背景图片
            QPixmap pix=QPixmap(":/res/BoardNode.png");
            QLabel* label=new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57+i*50,200+j*50);
            //创建金币
            QString str;
            if(this->gameArray[i][j]==1){
                str=":/res/Coin0001.png";
            }else{
                str=":/res/Coin0008.png";
            }
            MyCoin *coin=new MyCoin(str);
            this->coinBtn[i][j]=coin;
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            //给金币属性赋值
            coin->posX=i;
            coin->posY=j;
            coin->flag=gameArray[i][j]; //1正面 0反面
            //点击金币 进行翻转
            connect(coin,&MyCoin::clicked,[=](){
                flipSound->play();
                for(int i=0;i<4;i++){
                   for(int j=0;j<4;j++){
                       this->coinBtn[i][j]->isWin=true;
                   }
                };

                coin->changeFlag();
                this->gameArray[i][j]=!this->gameArray[i][j];
                //翻转周围的硬币 延时
                QTimer::singleShot(300,this,[=](){
                    if(coin->posX+1<=3){
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY]=!this->gameArray[coin->posX+1][coin->posY];
                    }
                    if(coin->posX-1>=0){
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY]=!this->gameArray[coin->posX-1][coin->posY];
                    }
                    if(coin->posY+1<=3){
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1]=!this->gameArray[coin->posX][coin->posY+1];
                    }
                    if(coin->posY-1>=0){
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1]=!this->gameArray[coin->posX][coin->posY-1];
                    }

                    for(int i=0;i<4;i++){
                       for(int j=0;j<4;j++){
                           this->coinBtn[i][j]->isWin=false;
                       }
                    };

                    //判断是否胜利
                    this->isWin =true;
                    for(int i=0;i<4;i++){
                       for(int j=0;j<4;j++){
                           if(coinBtn[i][j]->flag==false){
                              this->isWin=false;
                               break;
                           }
                       }
                    };
                    //
                    if(this->isWin==true){
                      qDebug()<<"游戏胜利了";
                      winSound->play();
                      for(int i=0;i<4;i++){
                         for(int j=0;j<4;j++){
                             coinBtn[i][j]->isWin=true;
                         }
                      };

                      //                    //将胜利的图片移动下来
                      //                    QPropertyAnimation *animation=new QPropertyAnimation(winLabel,"geometry");
                      //                    //设置时间的间隔
                      //                    animation->setDuration(1000);
                      //                    //设置开始的位置
                      //                    animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                      //                    //设置结束的位置
                      //                    animation->setEndValue(QRect(winLabel->x(),-winLabel->y(),winLabel->width(),winLabel->height()));
                      //                    //设置缓和曲线
                      //                    animation->setEasingCurve(QEasingCurve::OutBounce);
                      //                    //开始
                      //                    animation->start();
                      //                    qDebug()<<"动画执行了";

                      QPropertyAnimation * animation=new QPropertyAnimation(winLabel,"geometry");
                      animation->setDuration(200);
                      //起始位置
                      animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                      //结束位置
                      animation->setEndValue(QRect(winLabel->x(),winLabel->y()+120,winLabel->width(),winLabel->height()));
                      //设置弹跳曲线
                      animation->setEasingCurve(QEasingCurve::OutBounce);
                      //执行动画
                      animation->start();
                    }



                });
            });
        }
    }

}

void PlayScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
