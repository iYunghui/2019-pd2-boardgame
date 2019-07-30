#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(850,780);
    this->setWindowTitle("象棋");

    for(int i=0; i<10; i++)
        for(int j=0; j<9; j++) {
            coordinate[i][j] = 0;
            move[i][j] = 0;
        }
    set = state = 0;

    Time = new QLabel("時間 00:00:00", this);
    Time->setGeometry(690,80,160,80);
    Timer = new QTimer(this);

    StartGame = new QPushButton("開始", this);
    StartGame->setGeometry(660,180,160,80);

    Setting = new QPushButton("布置棋局", this);
    Setting->setGeometry(660,280,160,80);

    DeleteChess = new QPushButton("刪除棋子", this);
    DeleteChess->setGeometry(660,380,160,80);

    Instruction = new QPushButton("操作說明", this);
    Instruction->setGeometry(660,480,160,80);

    connect(Timer, SIGNAL(timeout()), this, SLOT(TimeSlot()));
    connect(StartGame, SIGNAL(clicked()), this, SLOT(StartGameSlot()));
    connect(Setting, SIGNAL(clicked()), this, SLOT(SettingSlot()));
    connect(DeleteChess, SIGNAL(clicked()), this, SLOT(DeleteChessSlot()));
    connect(Instruction, SIGNAL(clicked()), this, SLOT(InstructionSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TimeSlot(){
    TimeNumber++;
    QString time = QString("時間 %1:%2:%3").arg(TimeNumber/3600%60,2,10,QChar('0')).arg(TimeNumber/60%60,2,10,QChar('0')).arg(TimeNumber%60,2,10,QChar('0'));
    Time->setText(time);
}

void MainWindow::StartGameSlot(){
    Xclick = Yclick = set = 0;
    step = 1;
    state = 1;
    GameOver = false;
    TimeNumber = 0;
    StartGame->setText("重新開始");
    Setting->setText("布置棋局");
    InitializeBoard();
    this->repaint();
    Timer->start(1000);
}

void MainWindow::SettingSlot(){
    if(set == 0) {
        state = 2;
        set++;
        Timer->stop();
        TimeNumber = 0;
        StartGame->setText("開始");
        Setting->setText("開始計時");
        InitializeBoard();
        this->repaint();
    }
    else if(set == 1) {
        set = 0;
        Xclick = Yclick = 0;
        step = 1;
        state = 1;
        GameOver = false;
        Setting->setText("重新布置棋局");
        TimeNumber = 0;
        UpdateMove();
        this->repaint();
        Timer->start(1000);
    }
}

void MainWindow::DeleteChessSlot(){
    if(state==2 && coordinate[Xclick][Yclick]!=0) {
        coordinate[Xclick][Yclick] = 0;
        UpdateMove();
        this->repaint();
    }
}

void MainWindow::InstructionSlot(){
    QString instructions = "按鍵介紹 \n"
                           "1.開始: 棋局開始時棋子位置固定,為標準盤面。\n"
                           "2.布置棋局: 可以自由移動棋子,擺放成想要棋局後按下開始計時即可開始遊戲。\n"
                           "3.刪除棋子: 在布置棋盤的過程中,可刪除棋子以製造殘局。";
    QMessageBox::information(this, "操作說明", instructions, QMessageBox::Ok);
}

void MainWindow::InitializeBoard(){
    for(int i=0; i<10; i++)
        for(int j=0; j<9; j++)
            coordinate[i][j] = 0;

    coordinate[0][4] = 1; // 黑將
    coordinate[0][3] = coordinate[0][5] = 2; // 黑士
    coordinate[0][2] = coordinate[0][6] = 3; // 黑象
    coordinate[0][1] = coordinate[0][7] = 4; // 黑馬
    coordinate[0][0] = coordinate[0][8] = 5; // 黑車
    coordinate[2][1] = coordinate[2][7] = 6; // 黑炮
    coordinate[3][0] = coordinate[3][2] = coordinate[3][4] = coordinate[3][6] = coordinate[3][8] = 7; // 黑卒
    coordinate[9][4] = -1; // 紅帥
    coordinate[9][3] = coordinate[9][5] = -2; // 紅仕
    coordinate[9][2] = coordinate[9][6] = -3; // 紅相
    coordinate[9][1] = coordinate[9][7] = -4; // 紅馬
    coordinate[9][0] = coordinate[9][8] = -5; // 紅車
    coordinate[7][1] = coordinate[7][7] = -6; // 紅炮
    coordinate[6][0] = coordinate[6][2] = coordinate[6][4] = coordinate[6][6] = coordinate[6][8] = -7; // 紅兵
    step = 1;
    UpdateMove();
}

void MainWindow::UpdateMove() {
    for(int i=0; i<10; i++)
        for(int j=0; j<9; j++)
            move[i][j] = coordinate[i][j];
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(QRect(10,30,620,730),QPixmap(":/images/board.jpg"));
    for (int i=0; i<10; i++) {
        for (int j=0; j<9; j++) {
            switch(coordinate[i][j]) {
            case 1: painter.drawPixmap(QRect(20+68*j,50+69*i,70,70),QPixmap(":/images/黑將.png"));  break;
            case 2: painter.drawPixmap(QRect(20+68*j,50+69*i,70,70),QPixmap(":/images/黑士.png"));  break;
            case 3: painter.drawPixmap(QRect(20+68*j,50+69*i,70,70),QPixmap(":/images/黑象.png"));  break;
            case 4: painter.drawPixmap(QRect(20+68*j,50+69*i,70,70),QPixmap(":/images/黑馬.png"));  break;
            case 5: painter.drawPixmap(QRect(20+68*j,50+69*i,70,70),QPixmap(":/images/黑車.png"));  break;
            case 6: painter.drawPixmap(QRect(20+68*j,50+69*i,70,70),QPixmap(":/images/黑炮.png"));  break;
            case 7: painter.drawPixmap(QRect(20+68*j,50+69*i,70,70),QPixmap(":/images/黑卒.png"));  break;
            case -1: painter.drawPixmap(QRect(20+68*j,50+69*i,70,70),QPixmap(":/images/紅帥.png"));  break;
            case -2: painter.drawPixmap(QRect(20+68*j,50+69*i,70,70),QPixmap(":/images/紅仕.png"));  break;
            case -3: painter.drawPixmap(QRect(20+68*j,50+69*i,70,70),QPixmap(":/images/紅相.png"));  break;
            case -4: painter.drawPixmap(QRect(20+68*j,50+69*i,70,70),QPixmap(":/images/紅馬.png"));  break;
            case -5: painter.drawPixmap(QRect(20+68*j,50+69*i,70,70),QPixmap(":/images/紅車.png"));  break;
            case -6: painter.drawPixmap(QRect(20+68*j,50+69*i,70,70),QPixmap(":/images/紅炮.png"));  break;
            case -7: painter.drawPixmap(QRect(20+68*j,50+69*i,70,70),QPixmap(":/images/紅兵.png"));  break;
            default: break;
            }

            if(move[i][j] == 9)
                painter.drawPixmap(QRect(28+68*j,65+69*i,30,30),QPixmap(":/images/dot.png"));
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    int i,j;
    if(10<=event->pos().x() && event->pos().x()<=640 && 50<=event->pos().y() && event->pos().y()<=760) {
        i = (event->pos().y()-50)/69;
        j = (event->pos().x()-20)/68;
        if(move[i][j]==9)
            MoveChessman(Xclick, Yclick, i, j);
        else if(step%2==1 && coordinate[i][j]<0 && state==1) {
            UpdateMove();
            ToMoveChessman(i, j);
        }
        else if(step%2==0 && coordinate[i][j]>0 && state==1) {
            UpdateMove();
            ToMoveChessman(i, j);
        }
        else if(coordinate[i][j]!=0 && state==2) {
            UpdateMove();
            SetToMoveChessman(i, j);
        }
        else
            UpdateMove();            

        Xclick = i;
        Yclick = j;
        this->repaint();
    }
}

void MainWindow::ToMoveChessman(int x, int y) {
    int num;
    int chess = coordinate[x][y];
    switch(chess) {
    case 1: // 黑將
        num = 0;
        if((x-1)>=0 && coordinate[x-1][y]<=0 && state==1) move[x-1][y] = 9;
        if((x+1)<=2 && coordinate[x+1][y]<=0 && state==1) move[x+1][y] = 9;
        if((y-1)>=3 && coordinate[x][y-1]<=0 && state==1) move[x][y-1] = 9;
        if((y+1)<=5 && coordinate[x][y+1]<=0 && state==1) move[x][y+1] = 9;
        for(int i=x+1; i<=9; i++) {
            if(coordinate[i][y-1] == -1 && state==1)
               num = 1;
            else if(coordinate[i][y-1] != 0)
                break;
        }
        if(num == 1) move[x][y-1] = 0;
        num = 0;
        for(int i=x+1; i<=9; i++) {
            if(coordinate[i][y+1] == -1 && state==1)
               num = 1;
            else if(coordinate[i][y+1] != 0)
                break;
        }
        if(num == 1) move[x][y+1] = 0;
        break;
    case 2: // 黑士
        if((x-1)>=0 && (y-1)>=3 && coordinate[x-1][y-1]<=0) move[x-1][y-1] = 9;
        if((x-1)>=0 && (y+1)<=5 && coordinate[x-1][y+1]<=0) move[x-1][y+1] = 9;
        if((x+1)<=2 && (y-1)>=3 && coordinate[x+1][y-1]<=0) move[x+1][y-1] = 9;
        if((x+1)<=2 && (y+1)<=5 && coordinate[x+1][y+1]<=0) move[x+1][y+1] = 9;
        break;
    case 3: // 黑象
        if((x-2)>=0 && (y-2)>=0 && coordinate[x-1][y-1]==0 && coordinate[x-2][y-2]<=0) move[x-2][y-2] = 9;
        if((x-2)>=0 && (y+2)<=8 && coordinate[x-1][y+1]==0 && coordinate[x-2][y+2]<=0) move[x-2][y+2] = 9;
        if((x+2)<=4 && (y-2)>=0 && coordinate[x+1][y-1]==0 && coordinate[x+2][y-2]<=0) move[x+2][y-2] = 9;
        if((x+2)<=4 && (y+2)<=8 && coordinate[x+1][y+1]==0 && coordinate[x+2][y+2]<=0) move[x+2][y+2] = 9;
        break;
    case 4: // 黑馬
        if((x-1)>=0 && (y-2)>=0 && coordinate[x][y-1]==0 && coordinate[x-1][y-2]<=0) move[x-1][y-2] = 9;
        if((x-2)>=0 && (y-1)>=0 && coordinate[x-1][y]==0 && coordinate[x-2][y-1]<=0) move[x-2][y-1] = 9;
        if((x-2)>=0 && (y+1)<=8 && coordinate[x-1][y]==0 && coordinate[x-2][y+1]<=0) move[x-2][y+1] = 9;
        if((x-1)>=0 && (y+2)<=8 && coordinate[x][y+1]==0 && coordinate[x-1][y+2]<=0) move[x-1][y+2] = 9;
        if((x+1)<=9 && (y+2)<=8 && coordinate[x][y+1]==0 && coordinate[x+1][y+2]<=0) move[x+1][y+2] = 9;
        if((x+2)<=9 && (y+1)<=8 && coordinate[x+1][y]==0 && coordinate[x+2][y+1]<=0) move[x+2][y+1] = 9;
        if((x+2)<=9 && (y-1)>=0 && coordinate[x+1][y]==0 && coordinate[x+2][y-1]<=0) move[x+2][y-1] = 9;
        if((x+1)<=9 && (y-2)>=0 && coordinate[x][y-1]==0 && coordinate[x+1][y-2]<=0) move[x+1][y-2] = 9;
        break;
    case 5: // 黑車
        for(int i=x+1; i<=9; i++) {
            if(coordinate[i][y] <= 0)
                move[i][y] = 9;
            if(coordinate[i][y] != 0)
                break;
        }
        for(int i=x-1; i>=0; i--) {
            if(coordinate[i][y] <= 0)
                move[i][y] = 9;
            if(coordinate[i][y] != 0)
                break;
        }
        for(int i=y+1; i<=8; i++) {
            if(coordinate[x][i] <= 0)
                move[x][i] = 9;
            if(coordinate[x][i] != 0)
                break;
        }
        for(int i=y-1; i>=0; i--) {
            if(coordinate[x][i] <= 0)
                move[x][i] = 9;
            if(coordinate[x][i] != 0)
                break;
        }
        break;
    case 6: // 黑炮
        num = 0;
        for(int i=x+1; i<=9; i++) {
            if(coordinate[i][y]==0 && num==0)
                move[i][y] = 9;
            else if(coordinate[i][y] != 0)
                num++;
            if(num == 2) {
                if(coordinate[i][y] < 0)
                    move[i][y] = 9;
                break;
            }
        }
        num = 0;
        for(int i=x-1; i>=0; i--) {
            if(coordinate[i][y]==0 && num==0)
                move[i][y] = 9;
            else if(coordinate[i][y] != 0)
                num++;
            if(num == 2) {
                if(coordinate[i][y] < 0)
                    move[i][y] = 9;
                break;
            }
        }
        num = 0;
        for(int i=y+1; i<=8; i++) {
            if(coordinate[x][i]==0 && num==0)
                move[x][i] = 9;
            else if(coordinate[x][i] != 0)
                num++;
            if(num == 2) {
                if(coordinate[x][i] < 0)
                    move[x][i] = 9;
                break;
            }
        }
        num = 0;
        for(int i=y-1; i>=0; i--) {
            if(coordinate[x][i]==0 && num==0)
                move[x][i] = 9;
            else if(coordinate[x][i] != 0)
                num++;
            if(num == 2) {
                if(coordinate[x][i] < 0)
                    move[x][i] = 9;
                break;
            }
        }
        break;
    case 7: // 黑卒
        if(x<=4 && coordinate[x+1][y] <= 0) move[x+1][y] = 9;
        else if(x>4) {
            if((x+1)<=9 && coordinate[x+1][y] <= 0) move[x+1][y] = 9;
            if((y-1)>=0 && coordinate[x][y-1] <= 0) move[x][y-1] = 9;
            if((y+1)<=8 && coordinate[x][y+1] <= 0) move[x][y+1] = 9;
        }
        break;
    case -1: // 紅帥
        num = 0;
        if((x-1)>=7 && coordinate[x-1][y]>=0) move[x-1][y] = 9;
        if((x+1)<=9 && coordinate[x+1][y]>=0) move[x+1][y] = 9;
        if((y-1)>=3 && coordinate[x][y-1]>=0) move[x][y-1] = 9;
        if((y+1)<=5 && coordinate[x][y+1]>=0) move[x][y+1] = 9;
        for(int i=x-1; i>=0; i--) {
            if(coordinate[i][y-1] == 1 && state==1)
               num = 1;
            else if(coordinate[i][y-1] != 0)
                break;
        }
        if(num == 1) move[x][y-1] = 0;
        num = 0;
        for(int i=x-1; i>=0; i--) {
            if(coordinate[i][y+1] == 1 && state==1)
               num = 1;
            else if(coordinate[i][y+1] != 0)
                break;
        }
        if(num == 1) move[x][y+1] = 0;
        break;
    case -2: // 紅仕
        if((x-1)>=7 && (y-1)>=3 && coordinate[x-1][y-1]>=0) move[x-1][y-1] = 9;
        if((x-1)>=7 && (y+1)<=5 && coordinate[x-1][y+1]>=0) move[x-1][y+1] = 9;
        if((x+1)<=9 && (y-1)>=3 && coordinate[x+1][y-1]>=0) move[x+1][y-1] = 9;
        if((x+1)<=9 && (y+1)<=5 && coordinate[x+1][y+1]>=0) move[x+1][y+1] = 9;
        break;
    case -3: // 紅相
        if((x-2)>=5 && (y-2)>=0 && coordinate[x-1][y-1]==0 && coordinate[x-2][y-2]>=0) move[x-2][y-2] = 9;
        if((x-2)>=5 && (y+2)<=8 && coordinate[x-1][y+1]==0 && coordinate[x-2][y+2]>=0) move[x-2][y+2] = 9;
        if((x+2)<=9 && (y-2)>=0 && coordinate[x+1][y-1]==0 && coordinate[x+2][y-2]>=0) move[x+2][y-2] = 9;
        if((x+2)<=9 && (y+2)<=8 && coordinate[x+1][y+1]==0 && coordinate[x+2][y+2]>=0) move[x+2][y+2] = 9;
        break;
    case -4: // 紅馬
        if((x-1)>=0 && (y-2)>=0 && coordinate[x][y-1]==0 && coordinate[x-1][y-2]>=0) move[x-1][y-2] = 9;
        if((x-2)>=0 && (y-1)>=0 && coordinate[x-1][y]==0 && coordinate[x-2][y-1]>=0) move[x-2][y-1] = 9;
        if((x-2)>=0 && (y+1)<=8 && coordinate[x-1][y]==0 && coordinate[x-2][y+1]>=0) move[x-2][y+1] = 9;
        if((x-1)>=0 && (y+2)<=8 && coordinate[x][y+1]==0 && coordinate[x-1][y+2]>=0) move[x-1][y+2] = 9;
        if((x+1)<=9 && (y+2)<=8 && coordinate[x][y+1]==0 && coordinate[x+1][y+2]>=0) move[x+1][y+2] = 9;
        if((x+2)<=9 && (y+1)<=8 && coordinate[x+1][y]==0 && coordinate[x+2][y+1]>=0) move[x+2][y+1] = 9;
        if((x+2)<=9 && (y-1)>=0 && coordinate[x+1][y]==0 && coordinate[x+2][y-1]>=0) move[x+2][y-1] = 9;
        if((x+1)<=9 && (y-2)>=0 && coordinate[x][y-1]==0 && coordinate[x+1][y-2]>=0) move[x+1][y-2] = 9;
        break;
    case -5: // 紅車
        for(int i=x+1; i<=9; i++) {
            if(coordinate[i][y] >= 0)
                move[i][y] = 9;
            if(coordinate[i][y] != 0)
                break;
        }
        for(int i=x-1; i>=0; i--) {
            if(coordinate[i][y] >= 0)
                move[i][y] = 9;
            if(coordinate[i][y] != 0)
                break;
        }
        for(int i=y+1; i<=8; i++) {
            if(coordinate[x][i] >= 0)
                move[x][i] = 9;
            if(coordinate[x][i] != 0)
                break;
        }
        for(int i=y-1; i>=0; i--) {
            if(coordinate[x][i] >= 0)
                move[x][i] = 9;
            if(coordinate[x][i] != 0)
                break;
        }
        break;
    case -6: // 紅炮
        num = 0;
        for(int i=x+1; i<=9; i++) {
            if(coordinate[i][y]==0 && num==0)
                move[i][y] = 9;
            else if(coordinate[i][y] != 0)
                num++;
            if(num == 2) {
                if(coordinate[i][y] > 0)
                    move[i][y] = 9;
                break;
            }
        }
        num = 0;
        for(int i=x-1; i>=0; i--) {
            if(coordinate[i][y]==0 && num==0)
                move[i][y] = 9;
            else if(coordinate[i][y] != 0)
                num++;
            if(num == 2) {
                if(coordinate[i][y] > 0)
                    move[i][y] = 9;
                break;
            }
        }
        num = 0;
        for(int i=y+1; i<=8; i++) {
            if(coordinate[x][i]==0 && num==0)
                move[x][i] = 9;
            else if(coordinate[x][i] != 0)
                num++;
            if(num == 2) {
                if(coordinate[x][i] > 0)
                    move[x][i] = 9;
                break;
            }
        }
        num = 0;
        for(int i=y-1; i>=0; i--) {
            if(coordinate[x][i]==0 && num==0)
                move[x][i] = 9;
            else if(coordinate[x][i] != 0)
                num++;
            if(num == 2) {
                if(coordinate[x][i] > 0)
                    move[x][i] = 9;
                break;
            }
        }
        break;
    case -7: // 紅兵
        if(x>=5 && coordinate[x-1][y] >= 0) move[x-1][y] = 9;
        else if(x<5) {
            if((x-1)>=0 && coordinate[x-1][y] >= 0) move[x-1][y] = 9;
            if((y-1)>=0 && coordinate[x][y-1] >= 0) move[x][y-1] = 9;
            if((y+1)<=8 && coordinate[x][y+1] >= 0) move[x][y+1] = 9;
        }
        break;
    default:
        break;

    }
}

void MainWindow::SetToMoveChessman(int x, int y) {
    int chess = coordinate[x][y];
    switch(chess) {
    case 1: // 黑將
    case 2: // 黑士
        for(int i=0; i<=2; i++)
            for(int j=3; j<=5; j++)
                if(coordinate[i][j]==0)
                    move[i][j] = 9;
        break;
    case 3: // 黑象
        if(coordinate[0][2]==0) move[0][2] = 9;
        if(coordinate[0][6]==0) move[0][6] = 9;
        if(coordinate[2][0]==0) move[2][0] = 9;
        if(coordinate[2][4]==0) move[2][4] = 9;
        if(coordinate[2][8]==0) move[2][8] = 9;
        if(coordinate[4][2]==0) move[4][2] = 9;
        if(coordinate[4][6]==0) move[4][6] = 9;
        break;
    case 4: // 黑馬
    case 5: // 黑車
    case 6: // 黑炮
        for(int i=0; i<=9; i++)
            for(int j=0; j<=8; j++)
                if(coordinate[i][j]==0)
                    move[i][j] = 9;
        break;
    case 7: // 黑卒
        /*for(int i=3; i<=4; i++)
            for(int j=0; j<=8; j+=2)
                if(coordinate[i][j]==0)
                    move[i][j] = 9;*/
        if(x==3 && coordinate[4][y]==0) move[4][y] = 9;
        if(x==4 && coordinate[3][y]==0) move[3][y] = 9;
        for(int j=0; j<=8; j+=2)
            if(coordinate[3][j]==0 && coordinate[4][j]==0)
                move[3][j] = move[4][j] = 9;
        for(int i=5; i<=9; i++)
            for(int j=0; j<=8; j++)
                if(coordinate[i][j]==0)
                    move[i][j] = 9;
        break;
    case -1: // 紅帥
    case -2: // 紅仕
        for(int i=7; i<=9; i++)
            for(int j=3; j<=5; j++)
                if(coordinate[i][j]==0)
                    move[i][j] = 9;
        break;
    case -3: // 紅相
        if(coordinate[9][2]==0) move[9][2] = 9;
        if(coordinate[9][6]==0) move[9][6] = 9;
        if(coordinate[7][0]==0) move[7][0] = 9;
        if(coordinate[7][4]==0) move[7][4] = 9;
        if(coordinate[7][8]==0) move[7][8] = 9;
        if(coordinate[5][2]==0) move[5][2] = 9;
        if(coordinate[5][6]==0) move[5][6] = 9;
        break;
    case -4: // 紅馬
    case -5: // 紅車
    case -6: // 紅炮
        for(int i=0; i<=9; i++)
            for(int j=0; j<=8; j++)
                if(coordinate[i][j]==0)
                    move[i][j] = 9;
        break;
    case -7: // 紅兵
        if(x==5 && coordinate[6][y]==0) move[6][y] = 9;
        if(x==6 && coordinate[5][y]==0) move[5][y] = 9;
        for(int j=0; j<=8; j+=2)
            if(coordinate[5][j]==0 && coordinate[6][j]==0)
                move[5][j] = move[6][j] = 9;
        for(int i=0; i<=4; i++)
            for(int j=0; j<=8; j++)
                if(coordinate[i][j]==0)
                    move[i][j] = 9;
        break;
    default: break;

    }
}

void MainWindow::MoveChessman(int Xclick, int Yclick, int Xnew, int Ynew) {
    step++;
    coordinate[Xnew][Ynew] = coordinate[Xclick][Yclick];
    coordinate[Xclick][Yclick] = 0;
    UpdateMove();
    Judge();
}

void MainWindow::Judge() {
    int flag = 0;
    GameOver = true;
    for(int i=0; i<3; i++)
        for(int j=3; j<6; j++)
            if(coordinate[i][j] == 1)
                GameOver = false;

    if(GameOver) flag = 1;
    GameOver = true;

    for(int i=7; i<10; i++)
        for(int j=3; j<6; j++)
            if(coordinate[i][j] == -1)
                GameOver = false;

    if(GameOver==true || flag) {
        QString winner = (step%2==0 ? "紅棋" : "黑棋");
        Timer->stop();
        step = 0;
        QMessageBox::information(this, "結果", winner+"獲勝!", QMessageBox::Yes);
    }
}
