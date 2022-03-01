#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Slover.h"
#include <QtCore/qmath.h>
#include <QSpinBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>
#include <QFont>
#include <QString>
#include <QMainWindow>
#include <QLabel>
#include <QTableWidgetItem>
#include <QGraphicsDropShadowEffect>
#include <QSlider>
#include <QDialog>
#include <QMessageBox>
#include <QEvent>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


//-----------------------------上面的两个滑条----------------------------------------------
    //ui->NX_Slider->setTickPosition(QSlider::TicksAbove);  //刻度线在上方
    //ui->NPS_Slider->setTickPosition(QSlider::TicksBothSides);  //刻度线左右两边
    this->setWindowOpacity(1);
    this->setWindowFlags(Qt::FramelessWindowHint);//设置窗体无边框,允许任务栏按钮右键菜单
    this->setAttribute(Qt::WA_TranslucentBackground);//设置背景透明

    ui->NX_Slider->setStyleSheet("QSlider::handle:horizontal{width:24px;background-color:rgb(255,255,255);margin:-11px 0px -11px 0px;border-radius:12px;}"
                             "QSlider::groove:horizontal{height:4px;background-color:rgb(219,219,219);}"
                             "QSlider::add-page:horizontal{background-color:rgb(219,219,219);}"
                             "QSlider::sub-page:horizontal{background-color:rgb(26,217,110);}");
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setOffset(4,4);
    effect->setColor(QColor(0,0,0,50));
    effect->setBlurRadius(10);
    ui->NX_Slider->setGraphicsEffect(effect);

    ui->NPS_Slider->setStyleSheet("  \
         QSlider::add-page:vertical\
         {     \
            background-color: rgb(219, 219, 219);\
         }\
         QSlider::sub-page:vertical \
        {\
            background-color: rgb(37, 168, 198);\
         }\
        QSlider::groove:vertical \
        {\
           width:4px;background-color:rgb(219,219,219);\
        }\
        QSlider::handle:vertical\
        {\
            height:24px;background-color:rgb(255,255,255);\
            margin: 0px -10px 0px -10px;border-radius:12px;}\
        ");
     QGraphicsDropShadowEffect *effect1 = new QGraphicsDropShadowEffect;
     effect1->setOffset(4,4);
     effect1->setColor(QColor(0,0,0,50));
     effect1->setBlurRadius(10);
     ui->NPS_Slider->setGraphicsEffect(effect1);
     ui->tabWidget->setCurrentIndex(0);


//------------------------------输入的表格--------------------------------------------------
    int NX = ui->NX_Slider->value();          //NX是输入X的数量
    int NPS =12 - ui->NPS_Slider->value();        //NPS是状态S的数量

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(1);    // 初始化表格2列1行


//------------------------------表格View设置-----------------------------------------------------
    connect(ui->NX_Slider,&QSlider::valueChanged,[=]()mutable{
        NX = ui->NX_Slider->value();
        ui->tableWidget->setColumnCount(NX);
        QStringList headerText1;
    });     //列数为NX 列
    connect(ui->NPS_Slider,&QSlider::valueChanged,[=]()mutable{
        NPS =12 - ui->NPS_Slider->value();
        ui->tableWidget->setRowCount(NPS);
        QStringList headerText2;
        for (int i =0 ;i<NPS; i++)
        {
             headerText2<<"S"+QString::number(i+1);
             ui->tableWidget->setVerticalHeaderLabels(headerText2);

        }   //行数为S
    });


    QFont font = ui->tableWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->tableWidget->horizontalHeader()->setFont(font);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//设置充满表宽度

    QFont font1 = ui->tableWidget->verticalHeader()->font();
    font1.setBold(true);
    ui->tableWidget->verticalHeader()->setFont(font);
    ui->tableWidget->verticalHeader()->setStretchLastSection(true);//设置充满表宽度


    ui->tableWidget->horizontalHeader()->setSectionsClickable(false);               //水平方向的头不可点击
    ui->tableWidget->horizontalHeader()->setHighlightSections(false);               //点击表时不对表头行光亮（获取焦点）
    ui->tableWidget->verticalHeader()->setSectionsClickable(false);               //水平方向的头不可点击
    ui->tableWidget->verticalHeader()->setHighlightSections(false);               //点击表时不对表头行光亮（获取焦点）
    ui->tableWidget->resizeColumnsToContents(); //将行和列的大小设为与内容相匹配
    ui->tableWidget->resizeRowsToContents();

    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //自适应
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自适应

    ui->tableWidget->horizontalHeader()->setFocusPolicy(Qt::NoFocus);               //设置表头不可选
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);            //去掉水平滚动条
    ui->tableWidget->verticalHeader()->setFocusPolicy(Qt::NoFocus);               //设置表头不可选
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);            //去掉水平滚动条
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(220 ,220, 220,230);color: black;}");
    ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background:rgb(220 ,220, 220,230);color: black;}");
    ui->tableWidget->horizontalHeader()->setFixedHeight(50);//设置表头的高度
    ui->tableWidget->verticalHeader()->setFixedWidth(50);
    ui->tableWidget->setFrameShape(QFrame::NoFrame); //设置无边框
    ui->tableWidget2->setFrameShape(QFrame::NoFrame); //设置无边框
    ui->tableWidget->setStyleSheet(QString("QTableWidget QHeaderView::section{background:rgb(	220 ,220, 220,230);font-weight:bold; border:none; height:35px; color:black;} QTableWidget::item:selected { background-color: rgb(107,170,162,230) }"));//改变选中颜色 表头颜色 没有凸起
    ui->tableWidget2->setStyleSheet(QString("QTableWidget QHeaderView::section{background:rgb(	220 ,220, 220,230);font-weight:bold; border:none; height:35px; color:black;} QTableWidget::item:selected { background-color: rgb(107,170,162,230) }"));//改变选中颜色 表头颜色 没有凸起

    QPalette pll = ui->tableWidget->palette();
    pll.setBrush(QPalette::Base,QBrush(QColor(224,255,255)));
    ui->tableWidget->setPalette(pll);



//-------------------------------将表格元素保存到A数组中---------------------------------------------
    int A[20][20];
    int NS_Array[20][20];
    int Z_Array[20][20];

    connect(ui->btn1,&QPushButton::clicked,[=]()mutable{

        int col = ui->NX_Slider->value();
        int row = 12 - ui->NPS_Slider->value();

        for(int i=0 ;i<row;i++)
       {
           for(int k=0;k<col;k++)
           {
              if(ui->tableWidget->item(i,k) != NULL)
              {
                 A[i][k] = ui->tableWidget->item(i,k)->text().toInt();               
                 NS_Array[i][k] = ( A[i][k] -  A[i][k] % 10) /10;
                 Z_Array[i][k] = A[i][k] % 10;
              }
              else
              {
                   QMessageBox ::critical(this,"Error","输入有误，请重新输入");
                   return;
              }
            }
       }


//------------------------------------状态化简----------------------------------------------
        //Z_Array[][]是输出，NS_Array[][]是下一个状态，col是列数，row是行数
        int NS_Array2[20][20];
        int Z_Array2[20][20];
        int id[105], row2, col2;  // id[] 第i行的状态

        State_Map State_Reduce;
        State_Reduce.Init(row, col, NS_Array, Z_Array);
        State_Reduce.Solver(row2, id, NS_Array2, Z_Array2);
        col2 = col;


//---------------------------------------Output表格----------------------------------------
        //row2 是简化后的行数
        //col2 是简化后的列数
        //Z_Array2 是简化后的输出
        //NS_Array2 是简化后的NS
        //以上均是int类型

        ui->tableWidget2->setRowCount(row2);
        ui->tableWidget2->setColumnCount(col2);

        QFont font3 = ui->tableWidget2->horizontalHeader()->font();
        font3.setBold(true);
        ui->tableWidget2->horizontalHeader()->setFont(font3);
        ui->tableWidget2->horizontalHeader()->setStretchLastSection(true);//设置充满表宽度
        QFont font4 = ui->tableWidget2->verticalHeader()->font();
        font4.setBold(true);
        ui->tableWidget2->verticalHeader()->setFont(font4);
        ui->tableWidget2->verticalHeader()->setStretchLastSection(true);//设置充满表宽度

        ui->tableWidget2->resizeColumnsToContents(); //将行和列的大小设为与内容相匹配
        ui->tableWidget2->resizeRowsToContents();
        ui->tableWidget2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //自适应
        ui->tableWidget2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自适应
        ui->tableWidget2->horizontalHeader()->setFocusPolicy(Qt::NoFocus);               //设置表头不可选
        ui->tableWidget2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);            //去掉水平滚动条
        ui->tableWidget2->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(220 ,220, 220,230);}");
        ui->tableWidget2->verticalHeader()->setStyleSheet("QHeaderView::section{background:rgb(220 ,220, 220,230);}");
        ui->tableWidget2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableWidget2->horizontalHeader()->setSectionsClickable(false);               //水平方向的头不可点击
        ui->tableWidget2->horizontalHeader()->setHighlightSections(false);               //点击表时不对表头行光亮（获取焦点）
        ui->tableWidget2->verticalHeader()->setSectionsClickable(false);               //水平方向的头不可点击
        ui->tableWidget2->verticalHeader()->setHighlightSections(false);               //点击表时不对表头行光亮（获取焦点）
        ui->tableWidget2->resizeColumnsToContents(); //将行和列的大小设为与内容相匹配
        ui->tableWidget2->horizontalHeader()->setFixedHeight(50);//设置表头的高度
        ui->tableWidget2->verticalHeader()->setFixedWidth(50);

        for(int i=0 ; i < row2; i++)
        {
            for(int k =0 ;k< col2; k++)
            {
               QString str=QString::asprintf("S%d/%d ",NS_Array2[i][k],Z_Array2[i][k]);
               ui-> tableWidget2->setItem(i,k,new QTableWidgetItem(str));
               ui->tableWidget2->item(i,k)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//居中
               QStringList headerText3;
               for (int i =0 ;i<row2; i++)
               {
                    headerText3<<"S"+QString::number(id[i]+1);
                    ui->tableWidget2->setVerticalHeaderLabels(headerText3);
               }
               if (i % 2 != 0)
                   ui->tableWidget2->item(i,k)->setBackground(QColor(240,240,240));//设置单元格背景色
            }
        }
        ui->tabWidget->setCurrentIndex(1);
    });

//---------------------------------------------刷新按钮-------------------------------------------------
    connect(ui->btn2,&QPushButton::clicked,[=]()mutable{
       ui->tableWidget->setRowCount(1);
       ui->tableWidget->setColumnCount(2);
       ui->tableWidget->clearContents();
       ui->tableWidget2->setRowCount(1);
       ui->tableWidget2->setColumnCount(2);
       ui->tableWidget2->clearContents();

       ui->NX_Slider->setValue(2);
       ui->NPS_Slider->setValue(11);

       ui->tabWidget->setCurrentIndex(0);
    });
//---------------------------------------------关闭按钮--------------------------------------------------
    connect(ui->btn3,&QPushButton::clicked,[=]()mutable{
        this->close();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}





























