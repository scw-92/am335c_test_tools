#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>
#include "main_ui.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("cmi_at751_tools");
    QGuiApplication::setOrganizationName("QtProject");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //上述三行实现了支持高DPI等比缩放（不同的显示屏分辨率，显示效果一样）

    QGuiApplication app(argc, argv);

    QSettings settings;
    qputenv("QT_LABS_CONTROLS_STYLE", settings.value("style").toByteArray());

    main_ui ui ;

    return app.exec();
}
