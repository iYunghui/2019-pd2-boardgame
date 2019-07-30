#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>
#include <QMessageBox>
#include <QPushButton>
#include <QTimer>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void InitializeBoard(); //初始化棋盤
    void UpdateMove(); //更新棋子可移動的位置
    void paintEvent(QPaintEvent *); //畫出棋盤、棋子和棋子可移動的點
    void mousePressEvent(QMouseEvent *event); //滑鼠點擊處理
    void ToMoveChessman(int x, int y); //判斷棋子可移動的位置
    void SetToMoveChessman(int x, int y); //判斷布置棋盤時棋子可移動的位置
    void MoveChessman(int Xclick, int Yclick, int Xnew, int Ynew); //移動棋子
    void Judge(); //遊戲輸贏判斷

private slots:
    void StartGameSlot();
    void SettingSlot();
    void DeleteChessSlot();
    void TimeSlot();
    void InstructionSlot();

private:
    Ui::MainWindow *ui;
    int coordinate[10][9]; //棋子座標
    int move[10][9]; //標示棋子可移動的位置
    int Xclick, Yclick; //紀錄點擊棋盤的座標
    int step; //紀錄步數,判斷下棋方
    int TimeNumber, set, state;
    QPushButton *StartGame; //開始遊戲按鍵
    QPushButton *Setting; //布置棋盤按鍵
    QPushButton *DeleteChess; //刪除棋子按鍵
    QPushButton *Instruction; //操作說明按鍵
    bool GameOver; //遊戲狀態
    QTimer *Timer;
    QLabel *Time;
};

#endif // MAINWINDOW_H
