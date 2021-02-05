#ifndef MSGRAPHICSSCENE_H 
#define MSGRAPHICSSCENE_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QSound>
#include <QApplication>
#include "msdefine.h"
#include "msgrid.h"

enum MSDirection {
	NODIR = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class MSGraphicsScene : public QGraphicsScene {
    Q_OBJECT

public:
	MSGraphicsScene(QWidget * parent = 0);
	~MSGraphicsScene();

	void drawGrid(MSGrid grid);
	void undoMoving();
	void clearUndoData();

signals:
	void gameOver();

protected slots:
	void slotEmitGameOver();

private:
	MSGrid mGrid;
	MSDirection mDirection;
	QList<MSCell *> mMovingItemsList;
	QSound * mSoundBang;
	QSound * mSoundMove;
	QSound * mSoundGameOver;
	QList<MSGrid> mUndoGrids;

protected:
	void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent );
	void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent );
	void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
	void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent );

	QList<MSCell *> getMovingCells(MSImageItem * item, MSDirection dir);
	int checkAndSelectSameTypeCells(MSGrid &grid, bool checkOnly);
	int checkAndSelectSameTypeCells(MSGrid &grid, QList<MSCell *> &list, bool checkOnly);
	int checkAndSelectSameTypeCells(MSGrid &grid, MSCell * cell, bool checkOnly);
	int checkAndSelectSameTypeCells(MSCell * cell, MSCell * ccell, bool checkOnly);
	void eraseSameTypeCells(MSGrid &grid, MSCell * cell);
	void eraseCell(MSCell * cell);
	void checkGameOver();
};

#endif // MSGRAPHICSSCENE_H