#ifndef MSMAINWINDOW_H 
#define MSMAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QTextCodec>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QTimer>
#include <QTime>
#include <QStatusBar>
#include <QSound>
#include "msdefine.h"
#include "msgrid.h"

class MSGraphicsScene;

enum MSStatus {
	NORMAL = 0,
	GAMING
};

class MSMainWindow : public QMainWindow {
    Q_OBJECT

public:
	MSMainWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0);
	~MSMainWindow();

	static bool sMusic;
	static bool sSound;

protected slots:
	void slotNewGame();
	void slotRestartGame();
	void slotUndo();
	void slotRedo();
	void slotScore();
	void slotExit();
	void slotMusic();
	void slotSound();
	void slotPreferences();
	void slotHelp();
	void slotAbout();
	void slotTimeOut();
	void slotGameOver();

	void slotChangeMenuStatus();

private:
	MSGraphicsScene * mGameZoneScene;
	QGraphicsView * mGameZone;
	QAction * mMenuStart;
	QAction * mMenuRestart;
	QAction * mMenuUndo;
	QAction * mMenuRedo;
	QAction * mMenuScore;
	QAction * mMenuExit;
	QAction * mMenuMusic;
	QAction * mMenuSound;
	QAction * mMenuPreferences;
	QAction * mMenuHelp;
	QAction * mMenuAbout;
	QTimer * mTimer;
	QSound * mMusic;

	MSStatus mStatus;
	MSGrid mGrid;
	QTime mStartTime;
	int mUsedTime;
};

#endif // MSMAINWINDOW_H