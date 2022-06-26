#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("About");
}

void AboutDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen linePen(Qt::black);
    linePen.setWidth(3);

    painter.scale(width() / 611.0, height() / 440.0);

    painter.setPen(linePen);
    painter.drawEllipse(90, 110, 125, 125);
    painter.drawEllipse(90, 140, 125, 125);
    painter.drawEllipse(90, 170, 125, 125);

}

AboutDialog::~AboutDialog()
{
    delete ui;
}
