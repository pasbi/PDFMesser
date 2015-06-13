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
    ~Canvas();

public:
    bool openPDF( const QString& filename );
    void zoom( double f );
    double zoom() const;
    double area() const;
    double lastLength() const { return m_lastLength; }
    void setDPI( double dpi );
    void reload();


protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);

private:
    QVector<QPointF> m_points;
    QPixmap m_pixmap;
    double m_zoom;
    double m_lastLength;
    double m_dpi;
    QString m_filename;

signals:
    void pointsChanged();

};

#endif // CANVAS_H
