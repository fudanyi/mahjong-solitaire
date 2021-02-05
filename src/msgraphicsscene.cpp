#include "msgraphicsscene.h"
#include "msimageitem.h"
#include "msmainwindow.h"
 
extern QTextCodec * codec;

MSGraphicsScene::MSGraphicsScene(QWidget * parent)
 : QGraphicsScene(parent)
{
	mDirection = NODIR;

	QString path;
	path.sprintf("%s%s", LCO_SOUNDPATH, LCO_SOUND_BANG);
	mSoundBang = new QSound(path, this);
	path.sprintf("%s%s", LCO_SOUNDPATH, LCO_SOUND_MOVE);
	mSoundMove = new QSound(path, this);
	path.sprintf("%s%s", LCO_SOUNDPATH, LCO_SOUND_GAMEOVER);
	mSoundGameOver = new QSound(path, this);
}

MSGraphicsScene::~MSGraphicsScene()
{
}

void MSGraphicsScene::drawGrid(MSGrid grid)
{
	mGrid = grid;
	MSCell * cell = NULL;
	MSImageItem * item = NULL;

	clear();
	int c = mGrid.count();
	for(int i = 0;i < c;i++) {
		cell = mGrid.cell(i);
		if(cell->id() == LCO_NONEID) {
			continue;
		}
		item = new MSImageItem(cell->image());
		item->setPos(cell->pos());
		addItem(item);
		cell->setItem(item);
	}

	checkAndSelectSameTypeCells(mGrid, FALSE);
}

void MSGraphicsScene::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent ) 
{
	if( (mouseEvent->buttons() & Qt::LeftButton) != 0) {
		MSImageItem * item = NULL;
		MSCell * cell = NULL;
		QPointF p = mouseEvent->scenePos() - mouseEvent->lastScenePos();
		QPointF checkP;
		
		// init moving
		if(mDirection == NODIR) {
			// get moving item
			item = (MSImageItem *)itemAt(mouseEvent->lastScenePos());
			if(item == NULL) {
				// click out of range
				return;
			}
			// check moving direction
			if(MABS(p.y()) > MABS(p.x())) {
				if(p.y() > 0) {
					mDirection = DOWN;
				}
				else {
					mDirection = UP;
				}
			}
			else {
				if(p.x() > 0) {
					mDirection = RIGHT;
				}
				else {
					mDirection = LEFT;
				}
			}
			// get moving cells
			mMovingItemsList.clear();
			mMovingItemsList = getMovingCells(item, mDirection);
		}
		else {
			bool redo = FALSE;
			// get movingcells again when move direction changes
			if(mMovingItemsList.count() == 0) {
				// no moving cells 
				return;
			}
			cell = mMovingItemsList.at(0);
			checkP = cell->pos();
			// check whether move direction changes
			if(mDirection == UP) {
				if(cell->item()->pos().y() >= checkP.y()) {
					redo = TRUE;
				}
			}
			else if(mDirection == DOWN) {
				if(cell->item()->pos().y() <= checkP.y()) {
					redo = TRUE;
				}
			}
			else if(mDirection == LEFT) {
				if(cell->item()->pos().x() >= checkP.x()) {
					redo = TRUE;
				}
			}
			else if(mDirection == RIGHT) {
				if(cell->item()->pos().x() <= checkP.x()) {
					redo = TRUE;
				}
			}
			else {
				// no such case
				return;
			}
			if(redo == TRUE) {
				// recover all moving cells
				for(int i = 0;i < mMovingItemsList.count();i++) {
					cell = mMovingItemsList.at(i);
					cell->item()->setPos(cell->pos());
				}
				// get movingcells again
				// check moving direction
				if(MABS(p.y()) > MABS(p.x())) {
					if(p.y() > 0) {
						mDirection = DOWN;
					}
					else {
						mDirection = UP;
					}
				}
				else {
					if(p.x() > 0) {
						mDirection = RIGHT;
					}
					else {
						mDirection = LEFT;
					}
				}
				// get moving cells
				cell = mMovingItemsList.at(0);
				mMovingItemsList.clear();
				mMovingItemsList = getMovingCells(cell->item(), mDirection);
			}
		}
		// set offset
		MSDirection curDir = NODIR;
		if(mDirection == UP || mDirection == DOWN) {
			if(p.y() > 0) {
				curDir = DOWN;
			}
			else {
				curDir = UP;
			}
			p.setX(0);
		}
		else { // HORIZONTAL
			if(p.x() > 0) {
				curDir = RIGHT;
			}
			else {
				curDir = LEFT;
			}
			p.setY(0);
		}
		// check movable
		for(int i = 0;i < mMovingItemsList.count();i++) {
			cell = mMovingItemsList.at(i);
			if(curDir == UP || curDir == LEFT) {
				checkP = cell->item()->pos() + p;
			}
			else {
				checkP = cell->item()->pos() + QPointF(LCO_CELLWIDTH-1, LCO_CELLHEIGHT-1) + p;
			}
			cell = mGrid.cell(checkP);
			if(cell == NULL) {
				// out of grid range
				return;
			}
			if(cell->id() != LCO_NONEID && mMovingItemsList.count(cell) == 0) {
				// unmovable then return
				return;
			}
		}
		// move
		for(int i = 0;i < mMovingItemsList.count();i++) {
			cell = mMovingItemsList.at(i);
			cell->item()->moveBy(p.x(), p.y());
		}
	}
	else {
		// set cursor shape
		MSImageItem * citem = (MSImageItem *)itemAt(mouseEvent->scenePos());
		if(citem != NULL) {
			((MSMainWindow *)parent())->setCursor(Qt::OpenHandCursor);
		}
		else {
			((MSMainWindow *)parent())->setCursor(Qt::ArrowCursor);
		}
	}
}

void MSGraphicsScene::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent ) 
{
	if( mouseEvent->button() == Qt::LeftButton) {
		// set cursor shape
		MSImageItem * citem = (MSImageItem *)itemAt(mouseEvent->scenePos());
		if(citem != NULL) {
			((MSMainWindow *)parent())->setCursor(Qt::ClosedHandCursor);
		}
		else {
			((MSMainWindow *)parent())->setCursor(Qt::ArrowCursor);
		}

		mDirection = NODIR;
		mMovingItemsList.clear();
	}
}

void MSGraphicsScene::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent ) 
{
	if( mouseEvent->button() == Qt::LeftButton) {
		// set cursor shape
		MSImageItem * citem = (MSImageItem *)itemAt(mouseEvent->scenePos());
		if(citem != NULL) {
			((MSMainWindow *)parent())->setCursor(Qt::OpenHandCursor);
		}
		else {
			((MSMainWindow *)parent())->setCursor(Qt::ArrowCursor);
		}

		if(mDirection == NODIR) {
			mMovingItemsList.clear();
			return;
		}

		MSCell * cell = NULL;
		MSCell * tmpCell = NULL;
		MSGrid tmpGrid = mGrid;
		QList<MSCell *> tmpMovingItemsList;

		// save current items into tmpgrid
		for(int i = 0;i < mMovingItemsList.count();i++) {
			cell = mMovingItemsList.at(i);
			tmpGrid.cell(cell->index())->init();
		}
		for(int i = 0;i < mMovingItemsList.count();i++) {
			cell = mMovingItemsList.at(i);
			tmpCell = tmpGrid.cell(cell->item()->pos() + QPointF(LCO_CELLWIDTH/2, LCO_CELLHEIGHT/2));
			tmpCell->init();
			tmpCell->setValue(cell->id(), cell->type(), cell->image(), cell->item());
			tmpMovingItemsList << tmpCell;
		}
		if(tmpMovingItemsList.count() != 0) {
			// check cells with same type
			if(checkAndSelectSameTypeCells(tmpGrid, tmpMovingItemsList.at(0), TRUE) > 0) {
				// line up moving cells
				for(int i = 0;i < tmpMovingItemsList.count();i++) {
					cell = tmpMovingItemsList.at(i);
					cell->item()->setPos(cell->pos());
				}
				// get undogrid
				mUndoGrids << mGrid;
				mGrid = tmpGrid;
				mDirection = NODIR;
				// do erase cells
				cell = mGrid.cell(tmpMovingItemsList.at(0)->index());
				if(checkAndSelectSameTypeCells(mGrid, cell, FALSE) == 1) {
					eraseSameTypeCells(mGrid, cell);
					checkGameOver();
				}
				else {
					mSoundMove->play();
				}
				checkAndSelectSameTypeCells(mGrid, FALSE);
			}
			else {
				// check failure then recover moving cells
				for(int i = 0;i < mMovingItemsList.count();i++) {
					cell = mMovingItemsList.at(i);
					cell->item()->setPos(cell->pos());
				}
				mDirection = NODIR;
				checkAndSelectSameTypeCells(mGrid, FALSE);
			}
		}

		mDirection = NODIR;
		mMovingItemsList.clear();
	}
}

void MSGraphicsScene::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent ) 
{	
	if( mouseEvent->button() == Qt::LeftButton) {
		MSImageItem * item = NULL;
		MSCell * cell = NULL;
		int found = 0;

		mDirection = NODIR;
		mMovingItemsList.clear();

		item = (MSImageItem *)itemAt(mouseEvent->scenePos());
		if(item == NULL || item->isSelected() == FALSE) {
			// logical error
			return;
		}
		cell = mGrid.cell(item);
		found = checkAndSelectSameTypeCells(mGrid, cell, FALSE);
		if(found == 1) {
			// get undogrid
			mUndoGrids << mGrid;
			// do erase cells
			eraseSameTypeCells(mGrid, cell);
			checkGameOver();
			checkAndSelectSameTypeCells(mGrid, FALSE);
		}
	}
}

QList<MSCell *> MSGraphicsScene::getMovingCells(MSImageItem * item, MSDirection dir)
{
	QList<MSCell *> list;
	MSCell * curCell = mGrid.cell(item);
	if(curCell == NULL) {
		// logical error
		return list;
	}

	// find movable cells
	switch(dir) {
	case UP:
		for(int j = curCell->row();j >= 0;j--) {
			if(mGrid.cell(j, curCell->col())->id() != LCO_NONEID) {
				list << mGrid.cell(j, curCell->col());
			}
			else {
				break;
			}
		}
		break;
	case DOWN:
		for(int j = curCell->row();j < LCO_GRIDVNUM;j++) {
			if(mGrid.cell(j, curCell->col())->id() != LCO_NONEID) {
				list << mGrid.cell(j, curCell->col());
			}
			else {
				break;
			}
		}
		break;
	case LEFT:
		for(int j = curCell->col();j >= 0;j--) {
			if(mGrid.cell(curCell->row(), j)->id() != LCO_NONEID) {
				list << mGrid.cell(curCell->row(), j);
			}
			else {
				break;
			}
		}
		break;
	case RIGHT:
		for(int j = curCell->col();j < LCO_GRIDHNUM;j++) {
			if(mGrid.cell(curCell->row(), j)->id() != LCO_NONEID) {
				list << mGrid.cell(curCell->row(), j);
			}
			else {
				break;
			}
		}
		break;
	default:
		break;
	}

	return list;
}

int MSGraphicsScene::checkAndSelectSameTypeCells(MSGrid &grid, bool checkOnly)
{
	MSCell * cell = NULL;
	int found = 0;

	for(int i = 0;i < grid.count();i++) {
		cell = grid.cell(i);
		if(cell->id() == LCO_NONEID) {
			continue;
		}
		found += checkAndSelectSameTypeCells(grid, cell, checkOnly);
		if(found > 0 && checkOnly == TRUE) {
			return found;
		}
	}
	
	return found;
}

int MSGraphicsScene::checkAndSelectSameTypeCells(MSGrid &grid, QList<MSCell *> &list, bool checkOnly)
{
	MSCell * cell = NULL;
	int found = 0;

	for(int i = 0;i < list.count();i++) {
		cell = list.at(i);
		if(cell->id() == LCO_NONEID) {
			continue;
		}
		found += checkAndSelectSameTypeCells(grid, cell, checkOnly);
		if(found > 0 && checkOnly == TRUE) {
			return found;
		}
	}
	
	return found;
}

int MSGraphicsScene::checkAndSelectSameTypeCells(MSGrid &grid, MSCell * cell, bool checkOnly)
{
	MSCell * ccell = NULL;
	int found = 0;

	if(cell == NULL || cell->id() == LCO_NONEID) {
		return found;
	}
	// find same type cell 
	if(mDirection == LEFT || mDirection == RIGHT || mDirection == NODIR) {
		// UP
		for(int j = cell->row()-1;j >= 0;j--) {
			ccell = grid.cell(j, cell->col());
			if(cell == NULL) {
				break;
			}
			if(ccell->id() != LCO_NONEID) {
				found += checkAndSelectSameTypeCells(cell, ccell, checkOnly);
				if(found > 0 && checkOnly == TRUE) {
					return found;
				}
				break;
			}
		}
		// DOWN
		for(int j = cell->row()+1;j < LCO_GRIDVNUM;j++) {
			ccell = grid.cell(j, cell->col());
			if(cell == NULL) {
				break;
			}
			if(ccell->id() != LCO_NONEID) {
				found += checkAndSelectSameTypeCells(cell, ccell, checkOnly);
				if(found > 0 && checkOnly == TRUE) {
					return found;
				}
				break;
			}
		}
	}
	if(mDirection == UP || mDirection == DOWN || mDirection == NODIR) {
		// LEFT
		for(int j = cell->col()-1;j >= 0;j--) {
			ccell = grid.cell(cell->row(), j);
			if(cell == NULL) {
				break;
			}
			if(ccell->id() != LCO_NONEID) {
				found += checkAndSelectSameTypeCells(cell, ccell, checkOnly);
				if(found > 0 && checkOnly == TRUE) {
					return found;
				}
				break;
			}
		}
		// RIGHT
		for(int j = cell->col()+1;j < LCO_GRIDHNUM;j++) {
			ccell = grid.cell(cell->row(), j);
			if(cell == NULL) {
				break;
			}
			if(ccell->id() != LCO_NONEID) {
				found += checkAndSelectSameTypeCells(cell, ccell, checkOnly);
				if(found > 0 && checkOnly == TRUE) {
					return found;
				}
				break;
			}
		}
	}

	if(found == 0) {
		cell->item()->setSelected(FALSE);
	}

	return found;
}

int MSGraphicsScene::checkAndSelectSameTypeCells(MSCell * cell, MSCell * ccell, bool checkOnly)
{
	int found = 0;

	if(cell == NULL || ccell == NULL) {
		return found;
	}
	if(cell->id() == LCO_NONEID || ccell->id() == LCO_NONEID) {
		return found;
	}

	if(cell->type() == ccell->type()) {
		// found same type cell
		found++;
		if(checkOnly == FALSE) {
			// select the cells and continue
			cell->item()->setSelected(TRUE);
			ccell->item()->setSelected(TRUE);
		}
	}

	return found;
}

void MSGraphicsScene::eraseSameTypeCells(MSGrid &grid, MSCell * cell)
{
	MSCell * ccell = NULL;
	int found = 0;

	// find same type cell 
	// UP
	for(int j = cell->row()-1;j >= 0;j--) {
		ccell = grid.cell(j, cell->col());
		if(cell == NULL) {
			break;
		}
		if(ccell->id() != LCO_NONEID) {
			found = checkAndSelectSameTypeCells(cell, ccell, TRUE);
			if(found > 0) {
				eraseCell(cell);
				eraseCell(ccell);
				return;
			}
			break;
		}
	}
	// DOWN
	for(int j = cell->row()+1;j < LCO_GRIDVNUM;j++) {
		ccell = grid.cell(j, cell->col());
		if(cell == NULL) {
			break;
		}
		if(ccell->id() != LCO_NONEID) {
			found = checkAndSelectSameTypeCells(cell, ccell, TRUE);
			if(found > 0) {
				eraseCell(cell);
				eraseCell(ccell);
				return;
			}
			break;
		}
	}
	// LEFT
	for(int j = cell->col()-1;j >= 0;j--) {
		ccell = grid.cell(cell->row(), j);
		if(cell == NULL) {
			break;
		}
		if(ccell->id() != LCO_NONEID) {
			found = checkAndSelectSameTypeCells(cell, ccell, TRUE);
			if(found > 0) {
				eraseCell(cell);
				eraseCell(ccell);
				return;
			}
			break;
		}
	}
	// RIGHT
	for(int j = cell->col()+1;j < LCO_GRIDHNUM;j++) {
		ccell = grid.cell(cell->row(), j);
		if(cell == NULL) {
			break;
		}
		if(ccell->id() != LCO_NONEID) {
			found = checkAndSelectSameTypeCells(cell, ccell, TRUE);
			if(found > 0) {
				eraseCell(cell);
				eraseCell(ccell);
				return;
			}
			break;
		}
	}
}

void MSGraphicsScene::eraseCell(MSCell * cell)
{
	mSoundBang->play();
	removeItem(cell->item());
	cell->init();
}

void MSGraphicsScene::checkGameOver()
{
	MSCell * cell = NULL;
	int found = 0;

	for(int i = 0;i < mGrid.count();i++) {
		cell = mGrid.cell(i);
		if(cell->id() != LCO_NONEID) {
			return;
		}
	}

	QTimer::singleShot(500, this, SLOT(slotEmitGameOver()));
}

void MSGraphicsScene::slotEmitGameOver()
{
	mSoundGameOver->play();
	emit gameOver();
}

void MSGraphicsScene::undoMoving()
{
	if(mUndoGrids.count() != 0) {
		mGrid = mUndoGrids.last();
		drawGrid(mGrid);
		mUndoGrids.removeLast();
	}
}

void MSGraphicsScene::clearUndoData()
{
	mUndoGrids.clear();
}