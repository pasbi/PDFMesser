#ifndef CANVAS_H
#define CANVAS_H

#include <QLabel>
#ifdef Q_OS_WIN32
#include "poppler-qt5/poppler-qt5.h"
#else
#include "poppler/qt5/poppler-qt5.h"
#endif

class Canvas : public QLabel
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);

public:
    void openPDF( const QString& filename );
    void zoom( double f );
    double area() const;
    double lastLength() const { return m_lastLength; }


protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);

private:
    QVector<QPointF> m_points;
    QPixmap m_pixmap;
    double m_zoom;
    double m_lastLength;

signals:
    void pointsChanged();

};

#endif // CANVAS_H
