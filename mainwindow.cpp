#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QWheelEvent>
#include <qmath.h>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect( ui->label, SIGNAL(pointsChanged()), this, SLOT(updateArea()) );
    connect( ui->doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateArea()) );

    QSettings settings("PDFMesser", "PDFMesser");
    ui->doubleSpinBox->setValue( settings.value( "factor" ).toDouble() );
    restoreGeometry( settings.value( "geometry").toByteArray() );
    ui->doubleSpinBox1->setValue( settings.value( "dpi" ).toDouble() );
    ui->label->setDPI( ui->doubleSpinBox1->value() );
    ui->pushButton->setShortcut( QKeySequence("Ctrl++") );
}

MainWindow::~MainWindow()
{
    QSettings settings("PDFMesser", "PDFMesser");
    settings.setValue( "factor", ui->doubleSpinBox->value() );
    settings.setValue( "geometry", saveGeometry() );
    settings.setValue( "dpi", ui->doubleSpinBox1->value() );

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
        if (!ui->label->openPDF( filename ))
        {
            QMessageBox::critical( this,
                                   "Fehler",
                                   QString::fromUtf8("Kann \"%1\" nicht öffnen oder \"%1\" ist leer").arg(filename) );
        }
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

void MainWindow::on_doubleSpinBox1_valueChanged(double arg1)
{
    ui->label->setDPI( arg1 );
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->label->reload();
}
