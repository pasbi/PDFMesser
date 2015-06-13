#include "canvas.h"
#include <QDebug>
#include <QWheelEvent>
#include <qmath.h>
#include <QMouseEvent>
#include <QPainter>

Canvas::Canvas(QWidget *parent) :
    QLabel(parent),
    m_zoom( 1 ),
    m_lastLength( 0 ),
    m_dpi( 150 )
{
}

Canvas::~Canvas()
{
}

bool Canvas::openPDF(const QString &filename)
{
    m_filename = filename;
    Poppler::Document* doc = Poppler::Document::load(filename);
    if (doc && doc->numPages() > 0)
    {
        QImage image = doc->page( 0 )->renderToImage( m_dpi, m_dpi );
        m_pixmap = QPixmap::fromImage( image );
    }
    else
    {
        m_pixmap = QPixmap();
        m_filename.clear();
    }
    m_points.clear();
    zoom( 1 );    // does the update
    pointsChanged();

    return !filename.isEmpty();
}

void Canvas::zoom(double f)
{
    m_zoom *= f;

    for (int i = 0; i < m_points.length(); ++i)
    {
        m_points[i] *= f;
    }

    setPixmap( m_pixmap.scaledToWidth( m_pixmap.width() * zoom(), Qt::SmoothTransformation ) );
    update();
}

void Canvas::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);

    QPolygonF polygon( m_points );
    QPainter painter(this);
    painter.setRenderHint( QPainter::Antialiasing );

    painter.setBrush( QColor( 255, 0, 0, 50 ) );
    QPen pen( QColor( 255, 0, 0, 255 ) );
    pen.setWidthF( 2 );
    painter.setPen( pen );
    painter.drawPolygon( polygon, Qt::OddEvenFill );

    pen.setWidthF(4);
    painter.setPen( pen );
    for (int i = 0; i < m_points.length(); ++i)
    {
        painter.drawPoint( m_points[i] );
    }

}

void Canvas::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        m_points << ev->pos();
        if (m_points.length() < 2)
        {
            m_lastLength = 0;
        }
        else
        {
            int n = m_points.length();
            QPointF diff = m_points[n-1] - m_points[n-2];
            m_lastLength = qSqrt( QPointF::dotProduct( diff, diff ) );
        }
    }
    else
    {
        m_points.clear();
        m_lastLength = 0;
    }
    emit pointsChanged();
    update();
}

double Canvas::area() const
{
    if (m_points.isEmpty())
    {
        return 0;
    }

    double a1 = 0;
    double a2 = 0;

    for ( int i = 1; i < m_points.length(); ++i )
    {
        a1 += m_points[i-1].x() * m_points[i].y();
        a2 += m_points[i-1].y() * m_points[i].x();
    }
    a1 += m_points.last().x() * m_points.first().y();
    a2 += m_points.last().y() * m_points.first().x();
    return qAbs(a1 - a2) / 2.0 * m_zoom * m_zoom;
}

void Canvas::reload()
{
    openPDF( m_filename );
}

double Canvas::zoom() const
{
    return m_zoom * 100.0 / m_dpi;
}

void Canvas::setDPI(double dpi)
{
    m_dpi = dpi;
}
