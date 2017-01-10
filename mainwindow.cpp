#include "mainwindow.h"
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    mMotionManager=new MotionManager();
    resize(400,600);
    //startButton=new QPushButton("Start",this);
    //connect(startButton,SIGNAL(clicked(bool)),this,SLOT(step()));
    //update();

    //暂时用qt的计时器触发绘图
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(step()));
    timer->start(16);
}

MainWindow::~MainWindow()
{
    delete mMotionManager;
}


void MainWindow::paintEvent(QPaintEvent *event){
    this->updateGameDrawing();//更新游戏图形
}

void MainWindow::updateGameDrawing(){
    //绘制所有实体
    for (int t=0;t<mMotionManager->getBodyAmount();t++){
        drawBody(mMotionManager->getEneity(t));
    }
}

QAction *saveAct = new QAction( this );
saveAct->setText( "Save" );
saveAct->setIconSet( QPixmap("save.png") );
connect( saveAct, SIGNAL(activated()), this, SLOT(save()) );
saveAct->addTo( fileMenu );
saveAct->addTo( toolbar );
//设置一个“Save”菜单项和一个“Save”工具按钮

void MainWindow::drawBody(PsyEntity *psyEntity){

    //设置qt画笔
    QPainter painter(this);
    QColor hourColor(127, 0, 127);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);
    painter.save();

    int x=0,y=0,r=0;

    //根据实体类型进行绘图
    switch (psyEntity->type) {
    case 1:

        x=int((psyEntity->body->GetPosition().x)*30+60);
        y=int(700-(psyEntity->body->GetPosition().y)*30);
        r=int(psyEntity->r*2*30);
        painter.drawEllipse(x,y,r,r);
        painter.restore();
        break;

    case 2:
        x=int((psyEntity->body->GetPosition().x-psyEntity->w/2)*30+60);
        y=int(700-(psyEntity->body->GetPosition().y+psyEntity->h/2)*30);

        painter.drawRect(x,y,psyEntity->w*30,psyEntity->h*30);
        painter.restore();

        break;
    default:
        break;
    }
}
//调用motion manager的step方法
void MainWindow::step(){
    for(int x=0;x<1;x++){
        mMotionManager->step();
    }
    update();
}

