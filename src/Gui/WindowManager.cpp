#include "../Logger.hpp"
#include "../Registry.hpp"
#include "WindowManager.hpp"

WindowManager::WindowManager()
{
    WindowName = "C&C: Generals Zero Hour Hotkey Editor";

    LOGMSG("Loading launch window...");
    pLaunchWidget = std::make_unique<StackedLaunchWidget>(Config::GetLangEnumByLocale(Registry::GetCurrentUserLanguage()));
    pLaunchWidget->setWindowTitle(WindowName);
    LOGMSG("Launch window has been loaded");

    QObject::connect(pLaunchWidget.get(), &StackedLaunchWidget::AcceptedConfiguration, pLaunchWidget.get(), [=](const QVariant& cfg)
    {
        LOGMSG("Loading editor window...");
        pHotkeysEditor = std::make_unique<HotkeysMainWindow>(cfg);
        pHotkeysEditor->setWindowTitle("C&C: Generals Zero Hour Hotkey Editor");
        pHotkeysEditor->show();
        LOGMSG("Editor window has been loaded");
        pLaunchWidget.reset();
    });
}

void WindowManager::Show()
{
    pLaunchWidget->show();
}
