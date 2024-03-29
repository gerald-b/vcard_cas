#ifndef FRMMAIN_HPP
#define FRMMAIN_HPP

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class FrmMain; }
QT_END_NAMESPACE

class FrmMain : public QMainWindow
{
    Q_OBJECT

public:
    FrmMain(QWidget *parent = nullptr);
    ~FrmMain();

private slots:
    void on_actionAbout_triggered();

private:
    Ui::FrmMain *ui;
};
#endif // FRMMAIN_HPP
