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
#define LMS_TITLE			"麻将接龙"

#define LMS_MENU_GAME		"游戏(&G)"
#define LMS_MENU_START		"新游戏(&N)"
#define LMS_MENU_RESTART	"重新开始(&R)"
#define LMS_MENU_UNDO		"撤销(&U)"
#define LMS_MENU_REDO		"恢复(&D)"
#define LMS_MENU_SCORE		"成绩表(&S)..."
#define LMS_MENU_EXIT		"退出(&E)"
#define LMS_MENU_OPTION		"选项(&O)"
#define LMS_MENU_MUSIC		"音乐(&M) On/Off"
#define LMS_MENU_SOUND		"音效(&S) On/Off"
#define LMS_MENU_PREFERENCES	"个人设置(&P)..."
#define LMS_MENU_HELP		"帮助(&H)"
#define LMS_MENU_INTRODUCTION	"游戏方法(&P)..." 
#define LMS_MENU_ABOUT		"关于(&A)..." 

#define LMS_STATUS_MSG		"游戏时间 : "

#define LMS_SCOREDLG_MSG		"<h3>恭喜您 !</h3>您的成绩为 %1."
#define LMS_SCOREDLG_ADDSCORE	"添加成绩"
#define LMS_SCOREDLG_CLEARSCORE	"清空成绩表"
#define LMS_SCOREDLG_CLOSE		"关闭"
#define LMS_SCOREDLG_SCORENAME	"Player"

#endif
// Returevalue Define
#define R_NORMAL	0

// Macro Define
#define MABS(x)		(x>=0?x:-x)

#endif // MSDEFINE_H