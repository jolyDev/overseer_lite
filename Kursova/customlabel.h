#include <iostream>
class CustomLabel : public QLabel
{
Q_OBJECT
signals:
    void mousePressed( const QPoint& );

public:
    CustomLabel( QWidget* parent = 0, Qt::WindowFlags f = 0 );
    CustomLabel( const QString& text, QWidget* parent = 0, Qt::WindowFlags f = 0 );

    void mousePressEvent( QMouseEvent* ev );
};

void CustomLabel::mousePressEvent( QMouseEvent* ev )
{
    const QPoint p = ev->pos();
    emit mousePressed( p );
}

CustomLabel::CustomLabel( QWidget * parent, Qt::WindowFlags f )
    : QLabel( parent, f ) {}

CustomLabel::CustomLabel( const QString& text, QWidget* parent, Qt::WindowFlags f )
    : QLabel( text, parent, f ) {}

