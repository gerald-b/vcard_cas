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

void FrmMain::on_btnSave_clicked()
{
    if (0 == this->ui->tabWidget->currentIndex())
    {
        // Reserved 4 other branch
    }
    else if (1 == this->ui->tabWidget->currentIndex())
    {
        bool finishedWithoutError = true;
        int filecounter = -1;
        QFile * file = new QFile(this->ui->lblSrcVCard->text());
        QFileInfo * fi = new QFileInfo(this->ui->lblSrcVCard->text());
        if (file->open(QIODevice::ReadOnly))
        {
            QTextStream in(file);
            while (!in.atEnd())
            {
                QString line = in.readLine();
                if (line.toUpper().startsWith("BEGIN:VCARD"))
                {
                    ++filecounter;
                }
                QFile output(fi->dir().path().append(QString("/vcard_%1.vcf").arg(filecounter,4,10,QChar('0'))));
                if (!output.open(QIODevice::WriteOnly | QIODevice::Append))
                {
                    QMessageBox::critical(this,
                                          tr("Error"),
                                          tr("File \"%1\" could not opened!\nProcessing is stopped!").arg(output.fileName()),
                                          QMessageBox::Ok
                                          );
                    finishedWithoutError = false;
                    break;
                }
                QTextStream out(&output);
                out << line << "\n";
                if (output.isOpen())
                {
                    output.close();
                }
            }
            file->close();
        }
        if (finishedWithoutError)
        {
            QMessageBox::information(this,tr("Info"),tr("Process finished!"));
        }
        else
        {
            QMessageBox::warning(this,tr("Warning"),tr("Process finished with error(s)!"),QMessageBox::Ok);
        }
    }
    else
    {
        QMessageBox::critical(this,tr("Error"),tr("No valid tab selected!"),QMessageBox::Ok);
    }
}
