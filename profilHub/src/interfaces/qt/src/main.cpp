#include <c_application.h>
#include <QSettings>
#include <QLocale>
#include <QTranslator>
#include <iostream>

using namespace pH;

int	main(int argc, char** argv)
{
	c_application	application(argc, argv);
	QSettings       settings("profilHubTeam", "profilHub");
	QString         locali;
	QTranslator	translator;

    if (settings.value("lang", "").toString() == "")
    {
        locali = QLocale::system().name().section('_', 0, 0);
    }
    else
    {
        locali = settings.value("lang").toString();
    }
    if (locali != "en")
    {
        std::cout << locali.toStdString() << std::endl;
        if (translator.load("./" + locali, QApplication::applicationDirPath()) == false)
            return 12;
        application.installTranslator(&translator);
    }
	if (application.f_init() == false)
		return 0;
	return application.exec();
}
