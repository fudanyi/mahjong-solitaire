#include "msscoredialog.h"

extern QTextCodec * codec;

MSScoreDialog::MSScoreDialog( QWidget * parent, Qt::WindowFlags f )
: QDialog(parent, f)
{
	// create the dialog
	QVBoxLayout * layout = new QVBoxLayout(this);

	mScoreMsg = new QLabel(this);
	QString msg = codec->toUnicode(LMS_SCOREDLG_MSG);
	msg = msg.arg(convSecs2Time(0));
	mScoreMsg->setText(msg);
	layout->addWidget(mScoreMsg);

	mScoreList = new QListWidget(this);
	layout->addWidget(mScoreList);

	mScoreName = new QLineEdit(this);
	mScoreName->setMaxLength ( 32 );
	layout->addWidget(mScoreName);

	QHBoxLayout * buttonlayout = new QHBoxLayout();

	mCloseButton = new QPushButton(codec->toUnicode(LMS_SCOREDLG_CLOSE), this);
	connect(mCloseButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
	mAddScoreButton = new QPushButton(codec->toUnicode(LMS_SCOREDLG_ADDSCORE), this);
	connect(mAddScoreButton, SIGNAL(clicked(bool)), this, SLOT(slotAddScore()));
	mClearScoreButton = new QPushButton(codec->toUnicode(LMS_SCOREDLG_CLEARSCORE), this);
	connect(mClearScoreButton, SIGNAL(clicked(bool)), this, SLOT(slotClearScore()));

	buttonlayout->addWidget(mAddScoreButton);
	buttonlayout->addWidget(mClearScoreButton);
	buttonlayout->addWidget(mCloseButton);

	layout->addLayout(buttonlayout);
	// init
	mScoreTime = 0;
	loadScoreData();
}

MSScoreDialog::~MSScoreDialog()
{
}

void MSScoreDialog::loadScoreData()
{
	QFile file(LMS_SCOREDLG_FILE);
	if(!file.open(QIODevice::ReadOnly)) {
		return;
	}
	QDataStream in(&file);
	QString name;
	int time;
	
	while(!in.atEnd()) {
		in >> name >> time;
		mScoreList->addItem(name + "  \t" + convSecs2Time(time));
	}
	file.close();
}

void MSScoreDialog::saveScoreData(QString name, int time)
{
	QFile file(LMS_SCOREDLG_FILE);
	if(!file.open(QIODevice::Append)) {
		return;
	}
	QDataStream out(&file);
	
	out << name << time;
	file.close();
}

void MSScoreDialog::showViewMode()
{
	mScoreMsg->hide();
	mScoreName->hide();
	mAddScoreButton->hide();

	exec();
}

void MSScoreDialog::showWinMode(int usedTime)
{
	mScoreTime = usedTime;

	QString msg = codec->toUnicode(LMS_SCOREDLG_MSG);
	msg = msg.arg(convSecs2Time(mScoreTime));
	mScoreMsg->setText(msg);

	mScoreName->setText(codec->toUnicode(LMS_SCOREDLG_SCORENAME));
	mScoreName->setFocus();
	mScoreName->selectAll();

	exec();
}

void MSScoreDialog::slotAddScore()
{
	mScoreList->addItem(mScoreName->text() + "  \t" + convSecs2Time(mScoreTime));
	saveScoreData(mScoreName->text(), mScoreTime);

	mScoreName->setEnabled(FALSE);
	mAddScoreButton->setEnabled(FALSE);
}

void MSScoreDialog::slotClearScore()
{
	mScoreList->clear();
	QFile::remove(LMS_SCOREDLG_FILE);

	mScoreName->setEnabled(TRUE);
	mAddScoreButton->setEnabled(TRUE);
}

QString MSScoreDialog::convSecs2Time(int secs)
{
	QTime t(0,0,0);
	return t.addSecs(secs).toString("HH:mm:ss");
}


