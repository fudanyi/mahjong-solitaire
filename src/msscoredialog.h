#ifndef MSSCOREDIALOG_H
#define MSSCOREDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QTextCodec>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTime>
#include <QFile>
#include "msdefine.h"

class MSScoreDialog : public QDialog {
	Q_OBJECT

public:
	MSScoreDialog( QWidget * parent = 0, Qt::WindowFlags f = 0 );
	~MSScoreDialog();

	void loadScoreData();
	void saveScoreData(QString name, int time);
	void showViewMode();
	void showWinMode(int usedTime);
	QString convSecs2Time(int secs);

public slots:
	void slotAddScore();
	void slotClearScore();

private:
	QListWidget * mScoreList;
	QLineEdit * mScoreName;
	QPushButton * mAddScoreButton;
	QPushButton * mClearScoreButton;
	QPushButton * mCloseButton;
	QLabel * mScoreMsg;

	int	mScoreTime;
};

#endif // MSSCOREDIALOG_H