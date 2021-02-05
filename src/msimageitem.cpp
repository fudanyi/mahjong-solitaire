#include "msimageitem.h"

extern QTextCodec * codec;

MSImageItem::MSImageItem(QString image)
{
	mPixmap.load(image);
	mPixmap = mPixmap.scaled( QSize(LCO_CELLWIDTH-LCO_IMAGESPACE, LCO_CELLHEIGHT-LCO_IMAGESPACE) );
	setRect(0, 0, LCO_CELLWIDTH, LCO_CELLHEIGHT);
    setFlag(ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
	setZValue(LCO_IMAGEZ);
}

MSImageItem::~MSImageItem()
{
}

void MSImageItem::paint( QPainter *p, const QStyleOptionGraphicsItem *option, QWidget * )
{
    p->drawPixmap( option->exposedRect, mPixmap, option->exposedRect );
	if (isSelected())
	{
		QPen pen( QBrush(QColor(0,128,0), Qt::Dense3Pattern), 6, Qt::SolidLine);
		p->setPen(pen);
		p->drawRect(QRect(rect().x()+3,rect().y()+3,rect().width()-6,rect().height()-6));
	}
}

QPixmap MSImageItem::getImage(QString image)
{
	QString path;
	QPixmap img;

	path.sprintf("%s%s", LCO_IMAGEPATH, image);
	img.load(path);
	
	return img;
}