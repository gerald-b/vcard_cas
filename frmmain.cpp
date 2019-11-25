#include "frmmain.hpp"
#include "ui_frmmain.h"

FrmMain::FrmMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FrmMain)
{
    ui->setupUi(this);

    this->setWindowTitle(MY_PRODUCT);
    ui->btnSave->setEnabled(false);
    if (ui->tabWidget->count() >= 1)
    {
        ui->tabWidget->setCurrentIndex(1);
    }

    connect(ui->actionExit,&QAction::triggered,this,&FrmMain::close);
    connect(ui->btnExit, &QPushButton::clicked,this,&FrmMain::close);
}

FrmMain::~FrmMain()
{
    delete ui;
}

void FrmMain::on_actionAbout_triggered()
{
    QMessageBox::information(this,tr("Information"),QString("Product: ").append(MY_PRODUCT).append("\nVersion: ").append(MY_VERSION), QMessageBox::Ok);
}

void FrmMain::on_btnSrcVCard_clicked()
{
    QString file = QFileDialog::getOpenFileName(this,tr("Source VCARD"),".",tr("VCard (*.vcf *.vcard);;All files (*.*)"));
    if (!file.isEmpty())
    {
        this->ui->lblSrcVCard->setText(file);
        this->ui->btnSave->setEnabled(true);
    }
    else
    {
        this->ui->lblSrcVCard->setText(tr("Please select a file"));
        this->ui->btnSave->setEnabled(false);
    }
}
