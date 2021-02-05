#include "msmainwindow.h"
#include "msgraphicsscene.h"
#include "msscoredialog.h"

extern QTextCodec * codec;

bool MSMainWindow::sMusic = TRUE;
bool MSMainWindow::sSound = TRUE;

MSMainWindow::MSMainWindow(QWidget * parent, Qt::WindowFlags flags)
 : QMainWindow(parent, flags)
{
	// create main window
    setWindowTitle( codec->toUnicode(LMS_TITLE) );
	mGameZoneScene = new MSGraphicsScene(this);
	mGameZoneScene->setSceneRect(0, 0, LCO_GRIDWIDTH, LCO_GRIDHEIGTH);
	connect(mGameZoneScene, SIGNAL(gameOver()), this, SLOT(slotGameOver()));
	mGameZone = new QGraphicsView(mGameZoneScene, this);

	QLinearGradient gradient(QPointF(0, 0), QPointF(LCO_GRIDWIDTH, LCO_GRIDHEIGTH));
	gradient.setSpread(QGradient::PadSpread);
	gradient.setColorAt (0, QColor(255,128,0) );
	gradient.setColorAt (1, Qt::black );
	
	mGameZoneScene->setBackgroundBrush(gradient);
	setCentralWidget( mGameZone );
	resize(1024,768);

	// create menubar
    QMenuBar* menu = menuBar();

	QMenu* game = new QMenu( codec->toUnicode(LMS_MENU_GAME), menu );
	mMenuStart = game->addAction( codec->toUnicode(LMS_MENU_START), this, SLOT(slotNewGame()), Qt::Key_F2);
	mMenuRestart = game->addAction( codec->toUnicode(LMS_MENU_RESTART), this, SLOT(slotRestartGame()), Qt::Key_F3);
	game->addSeparator();
	mMenuUndo = game->addAction( codec->toUnicode(LMS_MENU_UNDO), this, SLOT(slotUndo()), QKeySequence::Undo);
	//mMenuRedo = game->addAction( codec->toUnicode(LMS_MENU_REDO), this, SLOT(slotRedo()), QKeySequence::Redo);
	game->addSeparator();
	mMenuScore = game->addAction( codec->toUnicode(LMS_MENU_SCORE), this, SLOT(slotScore()), Qt::Key_F4);
	game->addSeparator();
	mMenuExit = game->addAction( codec->toUnicode(LMS_MENU_EXIT), this, SLOT(slotExit()), QKeySequence::Close);
	menu->addMenu(game);

	QMenu* option = new QMenu( codec->toUnicode(LMS_MENU_OPTION), menu );
	mMenuMusic = option->addAction( codec->toUnicode(LMS_MENU_MUSIC), this, SLOT(slotMusic()), Qt::CTRL+Qt::Key_M);
	mMenuMusic->setCheckable(TRUE);
	mMenuMusic->setChecked(TRUE);
	mMenuSound = option->addAction( codec->toUnicode(LMS_MENU_SOUND), this, SLOT(slotSound()), Qt::CTRL+Qt::Key_S);
	mMenuSound->setCheckable(TRUE);
	mMenuSound->setChecked(TRUE);
	//mMenuPreferences = option->addAction( codec->toUnicode(LMS_MENU_PREFERENCES), this, SLOT(slotPreferences()), Qt::CTRL+Qt::Key_P);
	menu->addMenu(option);

	QMenu* help = new QMenu( codec->toUnicode(LMS_MENU_HELP), menu );
	mMenuHelp = help->addAction( codec->toUnicode(LMS_MENU_INTRODUCTION), this, SLOT(slotHelp()), QKeySequence::HelpContents);
	mMenuAbout = help->addAction( codec->toUnicode(LMS_MENU_ABOUT), this, SLOT(slotAbout()), Qt::CTRL+Qt::Key_A);
	menu->addMenu(help);

	// create statusbar
    statusBar();

	// others
	mTimer = new QTimer(this);
	connect(mTimer, SIGNAL(timeout()), this, SLOT(slotTimeOut()));
	slotChangeMenuStatus();

	QString path;
	path.sprintf("%s%s", LCO_SOUNDPATH, LCO_MUSIC_BACKGROUND);
	mMusic = new QSound(path, this);
	mMusic->play();

	// init
	mStatus = NORMAL;
	mUsedTime = 0;
	slotChangeMenuStatus();
}

MSMainWindow::~MSMainWindow()
{
}

void MSMainWindow::slotNewGame()
{
	mGrid.createGrid();
	mGameZoneScene->clearUndoData();
	mGameZoneScene->drawGrid(mGrid);

	mStatus = GAMING;
	mUsedTime = 0;
	mStartTime = QTime::currentTime ();
	mTimer->start(1000);
	slotChangeMenuStatus();
}

void MSMainWindow::slotRestartGame()
{
	mGameZoneScene->clearUndoData();
	mGameZoneScene->drawGrid(mGrid);

	mStatus = GAMING;
	mUsedTime = 0;
	mStartTime = QTime::currentTime ();
	mTimer->start(500);
	slotChangeMenuStatus();
}

void MSMainWindow::slotUndo()
{
	mGameZoneScene->undoMoving();
}

void MSMainWindow::slotRedo()
{
}

void MSMainWindow::slotScore()
{
	MSScoreDialog sdlg(this);
	sdlg.showViewMode();
}

void MSMainWindow::slotExit()
{
	close();
}

void MSMainWindow::slotMusic()
{
	if( mMenuMusic->isChecked()	) {
		MSMainWindow::sMusic = TRUE;
	}
	else {
		MSMainWindow::sMusic = FALSE;
		mMusic->stop();
	}
}

void MSMainWindow::slotSound()
{
	if( mMenuSound->isChecked()	) {
		MSMainWindow::sSound = TRUE;
	}
	else {
		MSMainWindow::sSound = FALSE;
	}
}

void MSMainWindow::slotPreferences()
{
}

void MSMainWindow::slotHelp()
{
    static QMessageBox * about = new QMessageBox( QMessageBox::Information, codec->toUnicode(LMS_TITLE),
	    "<h3>The Mahjong Solitaire Game</h3>"
	    "<ul>"
		"<li> Press CTRL-N for new game."
		"<li> Press F5 for restart."
		"<li> Press F1 for help."
		"<li> Press CTRL+P for prefences."
	    "</ul>", QMessageBox::Ok, this );
    about->show();
}

void MSMainWindow::slotAbout()
{
    static QMessageBox * about = new QMessageBox( QMessageBox::Information, codec->toUnicode(LMS_TITLE),
	    "<h3>The Mahjong Solitaire Game 0.9beta</h3>"
	    , QMessageBox::Ok, this );
    about->show();
}

void MSMainWindow::slotTimeOut()
{
	mUsedTime = mStartTime.secsTo(QTime::currentTime());
	QTime t(0,0,0);
	statusBar()->showMessage(codec->toUnicode(LMS_STATUS_MSG) + t.addSecs(mUsedTime).toString("HH:mm:ss"));
}

void MSMainWindow::slotChangeMenuStatus()
{
	switch(mStatus) {
	case NORMAL:
		mMenuRestart->setEnabled(FALSE);
		mMenuUndo->setEnabled(FALSE);
		//mMenuRedo->setEnabled(FALSE);
		break;
	case GAMING:
		mMenuRestart->setEnabled(TRUE);
		mMenuUndo->setEnabled(TRUE);
		//mMenuRedo->setEnabled(FALSE);
		break;
	default:
		break;
	}
}

void MSMainWindow::slotGameOver()
{
	mTimer->stop();

	MSScoreDialog sdlg(this);
	sdlg.showWinMode(mUsedTime);

	mGameZoneScene->clearUndoData();
	mStatus = NORMAL;
	mUsedTime = 0;
	mStartTime = QTime::currentTime ();
	slotChangeMenuStatus();
}
