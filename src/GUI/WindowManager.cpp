#include <QFileInfo>
#include <QApplication>

#include "../Logger.hpp"
#include "../Unsorted.hpp"
#include "../Convert.hpp"
#include "../Registry.hpp"

#include "ImageManager.hpp"
#include "WindowManager.hpp"

WindowManager::WindowManager()
{
    Language = Convert::ToLangEnum(Registry::GetCurrentUserLanguage());
    SetTranslator(Language);

    qApp->setWindowIcon(QIcon(QPixmap::fromImage(ImageManager::DecodeEditorWebpIcon())));
    
    LOGMSG("Loading \"" + PROGRAM_CONSTANTS->STYLES_SHEET + "\"...");
    QFile css{PROGRAM_CONSTANTS->STYLES_SHEET};
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
    pLaunchWidget = std::make_unique<LaunchWidget>();
    pLaunchWidget->setWindowTitle(strWindowName);
    LOGMSG("Launch window has been loaded");
}

void WindowManager::LaunchWidget_AcceptConfiguration(const QVariant& cfg)
{
    // 2nd init protection 
    if (pHotkeysEditor != nullptr) return;

    LOGMSG("Loading editor window...");
    pHotkeysEditor = std::make_unique<HotkeysMainWindow>(cfg);
    pHotkeysEditor->setWindowTitle(strWindowName);
    pHotkeysEditor->show();
    pLaunchWidget->close();
    bEditorInitialized = true;
    LOGMSG("Editor window has been loaded");
}

void WindowManager::SetTranslator(Languages lngType)
{
    if (pAppTranslator != nullptr) 
        qApp->removeTranslator(pAppTranslator);
    
    QString lngShortName = Unsorted::GetLanguageShortName(lngType);
    LOGMSG("Set editor language to " + lngShortName.toUpper());

    Language       = lngType;
    pAppTranslator = new QTranslator();
    pAppTranslator->load(lngShortName, PROGRAM_CONSTANTS->TRANSLATIONS_FOLDER);
    qApp->installTranslator(pAppTranslator);
}

void WindowManager::Show()             { pLaunchWidget->show(); }
Languages WindowManager::GetLanguage() { return Language; }
