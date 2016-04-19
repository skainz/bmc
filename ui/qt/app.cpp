#include "mainwindow.h"
#include <QApplication>
#include "windows.h"
#include <locale>
#include <bmc/braille/text2braille.hpp>

#include <QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)


int main(int argc, char *argv[])
{
  std::locale::global(std::locale(""));
  bmc::braille::set_default_table_from_locale();

    FreeConsole();
    QApplication app(argc, argv);
	QApplication::setOrganizationName("3dots, Ltd.");
	QApplication::setOrganizationDomain("blind.guru");
    QApplication::setApplicationName("Braille Music Compiler");
    QApplication::setApplicationVersion(BMC_VERSION);
    BrailleMusicEditor window;
    window.show();

    return app.exec();
}
