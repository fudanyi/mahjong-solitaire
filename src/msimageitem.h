#ifndef MSIMAGEITEM_H 
#define MSIMAGEITEM_H

#include <QPixmap>
#include <QGraphicsRectItem>
#include <QTextCodec>
#include <QSize>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "msdefine.h"

class MSImageItem : public QGraphicsRectItem {

public:
	MSImageItem(QString image);
	~MSImageItem();

protected:
    void paint( QPainter *, const QStyleOptionGraphicsItem *option, QWidget *widget );
	QPixmap getImage(QString image);


private:
    QPixmap mPixmap;
};

#endif // MSIMAGEITEM_H