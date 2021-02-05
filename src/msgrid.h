#ifndef MSGRID_H 
#define MSGRID_H

#include <QTextCodec>
#include <QPointF>
#include "msdefine.h"

class MSImageItem;

class MSCell {
public:
	MSCell();
	~MSCell();

	void setValue(int index, int id, int type, QString image);
	void setValue(int id, int type, QString image, MSImageItem * item);
	void setPos(int r, int c);
	void setItem(MSImageItem * item);
	int id();
	int type();
	QString image();
	MSImageItem * item();
	QPointF pos();
	QPointF rightBottomPos();
	int row();
	int col();
	int index();
	void exchange(MSCell * cell);
	void init();

private:
	int mId;
	int mType;
	QString mImage;
	int mIndex;
	int mRow;
	int mCol;
	QPointF mPos;
	MSImageItem * mItem;
};

class MSGrid {

public:
	MSGrid();
	~MSGrid();

	void initGrid();
	void createGrid();
	int count();
	MSCell * cell(int index);
	MSCell * cell(int row, int col);
	MSCell * cell(MSImageItem * item);
	MSCell * cell(QPointF p);

private:
	MSCell mCell[LCO_CELLNUM];
};

#endif // MSGRID_H