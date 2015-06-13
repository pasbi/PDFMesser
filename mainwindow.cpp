#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QWheelEvent>
#include <qmath.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect( ui->label, SIGNAL(pointsChanged()), this, SLOT(updateArea()) );
    connect( ui->doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateArea()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->label->zoom( 1.1 );
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->label->zoom( 1/1.1 );
}

void MainWindow::on_action_ffnen_triggered()
{
    QString filename = QFileDialog::getOpenFileName( this,
                                                     QString::fromUtf8("PDF öffnen"),
                                                     QDir::homePath(),
                                                     "PDF *.pdf" );
    if (!filename.isEmpty())
    {
        ui->label->openPDF( filename );
    }
}

void MainWindow::updateArea()
{
    double factor = ui->doubleSpinBox->value();
    double area = ui->label->area();
    double length = ui->label->lastLength();

    area /= factor * factor;
    length /= factor;

    QString text = QString::fromUtf8("Fläche: %1, Länge: %2").arg(area).arg(length);
    ui->label_2->setText( text );
}
