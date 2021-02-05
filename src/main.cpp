#include <QApplication>
#include <QTextCodec>
#include <QDesktopWidget>
#include <QStyleFactory>
#include "msdefine.h"
#include "msmainwindow.h"

QTextCodec * codec = NULL;

int main(int argc, char** argv)
{
	qsrand(time(NULL));
#ifdef _DEBUG // debug
	QList<QByteArray> ba = QTextCodec::availableCodecs() ;
	for(int i = 0;i < ba.count();i++) {
		printf("%3d : %s\n", i, ba[i].data () );
	}
	QStringList sf = QStyleFactory::keys ();
	for(int i = 0;i < sf.count();i++) {
		printf("%3d : %s\n", i, sf[i].toAscii().data() );
	}
#endif // debug

	codec = QTextCodec::codecForName("System");
	if(codec == NULL) {
		printf("No codec !!\n");
		return 0;
	}
	
    QApplication app(argc,argv);
	QApplication::setStyle("Plastique");
		
    MSMainWindow m;
    if ( QApplication::desktop()->width() > m.width() + 10
	&& QApplication::desktop()->height() > m.height() +30 )
	m.show();
    else
	m.showMaximized();
    
    QObject::connect( qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()) );
    return app.exec();
}



