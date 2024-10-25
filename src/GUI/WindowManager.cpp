#include <QApplication>

#include "../Logger.hpp"
#include "../Registry.hpp"
#include "GUIConfig.hpp"
#include "WindowManager.hpp"

WindowManager::WindowManager()
{
    WindowName = "C&C: Generals Zero Hour Hotkey Editor";
    qApp->setWindowIcon(QIcon(QPixmap::fromImage(GUIConfig::DecodeEditorWebpIcon())));
    
    LOGMSG("Loading loading \"" + GUIConfig::STYLES_SHEET + "\"...");
    QFile css{GUIConfig::STYLES_SHEET};
    if (css.open(QIODevice::ReadOnly))
    {
        qApp->setStyleSheet(css.readAll());
        css.close();
        LOGMSG("Styles sheet has been loaded");
    }
    else
    {
        LOGMSG("Unable to read the style file");
    }

    LOGMSG("Loading launch window...");
    pLaunchWidget = std::make_unique<LaunchWidget>(Config::GetLangEnumByLocale(Registry::GetCurrentUserLanguage()));
    pLaunchWidget->setWindowTitle(WindowName);
    LOGMSG("Launch window has been loaded");

    QObject::connect(pLaunchWidget.get(), &LaunchWidget::AcceptedConfiguration, pLaunchWidget.get(), [=, this](const QVariant& cfg)
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

void WindowManager::SetTranslator(Config::Languages lngType)
{
    // Delete old translator
    if (pAppTranslator != nullptr) qApp->removeTranslator(pAppTranslator);

    QString lngShortName = Config::GetLanguageShortName(lngType);
    LOGMSG("Set editor language to " + lngShortName.toUpper());

    // Create new translator
    if (lngType != Config::Languages::English)
    {
        pAppTranslator = new QTranslator();
        pAppTranslator->load(lngShortName, Config::TRANSLATIONS_FOLDER);
        qApp->installTranslator(pAppTranslator);
    }
}
