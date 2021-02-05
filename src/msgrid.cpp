#include "msgrid.h"
#include "msimageitem.h"

extern QTextCodec * codec;

MSCell::MSCell()
{
	mId = LCO_NONEID;
	mType = -1;
	mImage = "";
	mIndex = -1;
	mRow = -1;
	mCol = -1;
	mItem = NULL;
	mPos.setX(0);
	mPos.setY(0);
}

MSCell::~MSCell()
{
}

void MSCell::setValue(int index, int id, int type, QString image)
{
	mId = id;
	mType = type;
	mImage = image;
	mItem = NULL;

	mIndex = index;
	mRow = mIndex / LCO_GRIDHNUM;
	mCol = mIndex % LCO_GRIDHNUM;
	mPos.setX(LCO_GRIDLEFT + mCol * LCO_CELLWIDTH);
	mPos.setY(LCO_GRIDTOP + mRow * LCO_CELLHEIGHT);
}

void MSCell::setValue(int id, int type, QString image, MSImageItem * item)
{
	mId = id;
	mType = type;
	mImage = image;
	mItem = item;
}

void MSCell::setPos(int r, int c)
{
	mRow = r;
	mCol = c;
	mIndex = mRow * LCO_GRIDHNUM + mCol;

	mPos.setX(LCO_GRIDLEFT + mCol * LCO_CELLWIDTH);
	mPos.setY(LCO_GRIDTOP + mRow * LCO_CELLHEIGHT);
}

void MSCell::setItem(MSImageItem * item)
{
	mItem = item;
}

int MSCell::id()
{
	return mId;
}

int MSCell::type()
{
	return mType;
}

QString MSCell::image()
{
	return mImage;
}

MSImageItem * MSCell::item()
{
	return mItem;
}

QPointF MSCell::pos()
{
	return mPos;
}

QPointF MSCell::rightBottomPos()
{
	return mPos + QPointF(LCO_CELLWIDTH-1, LCO_CELLHEIGHT-1);
}

int MSCell::row()
{
	return mRow;
}

int MSCell::col()
{
	return mCol;
}

int MSCell::index()
{
	return mIndex;
}

void MSCell::exchange(MSCell * cell)
{
	int id = cell->id();
	int type = cell->type();
	QString image = cell->image();
	MSImageItem * item = cell->item();

	cell->setValue(mId, mType, mImage, mItem);
	setValue(id, type, image, item);
}

void MSCell::init()
{
	mId = LCO_NONEID;
	mType = -1;
	mImage = "";
	mItem = NULL;
}

MSGrid::MSGrid()
{
	
}

MSGrid::~MSGrid()
{
}

void MSGrid::initGrid()
{
	QString path;
	// init all cells
	for(int i = 0,j = 0;i < 136;i++,j++) {
		if(j == 34) {
			j = 0;
		}
		path.sprintf("%s%.2d%s", LCO_IMAGEPATH, j, LCO_IMAGEEXT);
		mCell[i].setValue(i, j, j, path);
	}
	for(int i = 136,j = 34;i < 140;i++,j++) {
		path.sprintf("%s%.2d%s", LCO_IMAGEPATH, j, LCO_IMAGEEXT);
		mCell[i].setValue(i, j, 34, path);
	}
	for(int i = 140,j = 38;i < 144;i++,j++) {
		path.sprintf("%s%.2d%s", LCO_IMAGEPATH, j, LCO_IMAGEEXT);
		mCell[i].setValue(i, j, 34, path);
	}
}

void MSGrid::createGrid()
{
	// init all cells
	initGrid();

	// random all cells
	for(int i = 0;i < count();i++) {
		int r = qrand() % LCO_CELLNUM;
		mCell[i].exchange(&mCell[r]);
	}
}

int MSGrid::count()
{
	return LCO_CELLNUM;
}

MSCell * MSGrid::cell(int index)
{
	return &mCell[index];
}

MSCell * MSGrid::cell(int row, int col)
{
	int index = row * LCO_GRIDHNUM + col;
	return &mCell[index];
}

MSCell * MSGrid::cell(MSImageItem * item)
{
	MSCell * cell = NULL;
	// find the cell
	int i = 0;
	for(i = 0;i < count();i++) {
		if(mCell[i].item() == item) {
			cell = &mCell[i];
			break;
		}
	}

	return cell;
}

MSCell * MSGrid::cell(QPointF p)
{
	MSCell * cell = NULL;
	// find the cell
	int i = 0;
	for(i = 0;i < count();i++) {
		if(p.x() >= mCell[i].pos().x() && p.x() <= mCell[i].rightBottomPos().x()
		&& p.y() >= mCell[i].pos().y() && p.y() <= mCell[i].rightBottomPos().y()) {
			cell = &mCell[i];
			break;
		}
	}

	return cell;
}
