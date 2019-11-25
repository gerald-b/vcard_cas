#include "frmmain.hpp"
#include "ui_frmmain.h"

FrmMain::FrmMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FrmMain)
{
    ui->setupUi(this);
    connect(ui->actionExit,&QAction::triggered,this,&FrmMain::close);
    connect(ui->btnExit, &QPushButton::clicked,this,&FrmMain::close);
}

FrmMain::~FrmMain()
{
    delete ui;
}

