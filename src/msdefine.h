#ifndef MSDEFINE_H
#define MSDEFINE_H

#include <stdlib.h>
#include <time.h>

// General Define
#define LCO_SOUNDPATH			"wavs\\"
#define LCO_SOUND_MOVE			"move.wav"
#define LCO_SOUND_BANG			"bang.wav"
#define LCO_SOUND_GAMEOVER		"gameover.wav"
#define LCO_MUSIC_BACKGROUND		"background.wav"

#define LCO_IMAGEPATH		"images\\"
#define LCO_IMAGEEXT		".bmp"
#define LCO_IMAGEZ			256
#define LCO_BACKGROUNDZ		0

#define LCO_GRIDLEFT		0
#define LCO_GRIDTOP			0
#define LCO_GRIDHNUM		18
#define LCO_GRIDVNUM		8
#define LCO_CELLWIDTH		54
#define LCO_CELLHEIGHT		72
#define LCO_GRIDWIDTH		LCO_CELLWIDTH * LCO_GRIDHNUM
#define LCO_GRIDHEIGTH		LCO_CELLHEIGHT * LCO_GRIDVNUM
#define LCO_CELLNUM			LCO_GRIDHNUM * LCO_GRIDVNUM
#define LCO_IDNUM			42
#define LCO_TYPENUM			36
#define LCO_IMAGESPACE		2

#define LCO_NONEID			-1

// Literals Define
#define LMS_SCOREDLG_FILE		"score.mss"

#if 0
#define LMS_TITLE			"MahjongSolitaire"

#define LMS_MENU_GAME		"&Game"
#define LMS_MENU_START		"&New Game"
#define LMS_MENU_RESTART	"&Restart"
#define LMS_MENU_UNDO		"&Undo"
#define LMS_MENU_REDO		"Re&do"
#define LMS_MENU_SCORE		"&Score..."
#define LMS_MENU_EXIT		"&Exit"
#define LMS_MENU_OPTION		"&Option"
#define LMS_MENU_MUSIC		"&Music On/Off"
#define LMS_MENU_SOUND		"&Sound On/Off"
#define LMS_MENU_PREFERENCES	"&Preferences..."
#define LMS_MENU_HELP		"&Help"
#define LMS_MENU_INTRODUCTION	"How to &play..." 
#define LMS_MENU_ABOUT		"&About..." 

#define LMS_STATUS_MSG		"Used Time : "

#define LMS_SCOREDLG_FILE		"score.mss"
#define LMS_SCOREDLG_MSG		"<h3>Congratuations !</h3>You finished the game in %1."
#define LMS_SCOREDLG_ADDSCORE	"Add Score"
#define LMS_SCOREDLG_CLEARSCORE	"Clear Score"
#define LMS_SCOREDLG_CLOSE		"Close"
#define LMS_SCOREDLG_SCORENAME	"Player"

#else
#define LMS_TITLE			"�齫����"

#define LMS_MENU_GAME		"��Ϸ(&G)"
#define LMS_MENU_START		"����Ϸ(&N)"
#define LMS_MENU_RESTART	"���¿�ʼ(&R)"
#define LMS_MENU_UNDO		"����(&U)"
#define LMS_MENU_REDO		"�ָ�(&D)"
#define LMS_MENU_SCORE		"�ɼ���(&S)..."
#define LMS_MENU_EXIT		"�˳�(&E)"
#define LMS_MENU_OPTION		"ѡ��(&O)"
#define LMS_MENU_MUSIC		"����(&M) On/Off"
#define LMS_MENU_SOUND		"��Ч(&S) On/Off"
#define LMS_MENU_PREFERENCES	"��������(&P)..."
#define LMS_MENU_HELP		"����(&H)"
#define LMS_MENU_INTRODUCTION	"��Ϸ����(&P)..." 
#define LMS_MENU_ABOUT		"����(&A)..." 

#define LMS_STATUS_MSG		"��Ϸʱ�� : "

#define LMS_SCOREDLG_MSG		"<h3>��ϲ�� !</h3>���ĳɼ�Ϊ %1."
#define LMS_SCOREDLG_ADDSCORE	"��ӳɼ�"
#define LMS_SCOREDLG_CLEARSCORE	"��ճɼ���"
#define LMS_SCOREDLG_CLOSE		"�ر�"
#define LMS_SCOREDLG_SCORENAME	"Player"

#endif
// Returevalue Define
#define R_NORMAL	0

// Macro Define
#define MABS(x)		(x>=0?x:-x)

#endif // MSDEFINE_H