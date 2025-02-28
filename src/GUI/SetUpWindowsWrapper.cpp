#include <QLineEdit>
#include <QFile>
#include <QMessageBox>

#include "../Logger.hpp"
#include "../Registry.hpp"
#include "WindowManager.hpp"
#include "ImageManager.hpp"
#include "LoadFromTheGameWindow.hpp"
#include "SetUpWindowsWrapper.hpp"

SetUpWindowsWrapper::SetUpWindowsWrapper(QWidget* parent) : QStackedWidget(parent)
{
    // Makes window unresizeable and equal to the size of the background
    setFixedSize(795, 440);
    setWindowFlags(windowFlags() |  Qt::MSWindowsFixedSizeDialogHint);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint &
                                   ~Qt::WindowMinimizeButtonHint);

    AddWidgets();
    setCurrentWidget(pGreetingWidget);
    AttachConnections();
}

void SetUpWindowsWrapper::AttachConnections()
{
    connect(pGreetingWidget,        &GreetingWindow::languageChanged,
            this,                   &SetUpWindowsWrapper::GreetingWidget_LanguageChanged);

    connect(pGreetingWidget,        &GreetingWindow::btnLoadFromFileClicked,
            this,                   &SetUpWindowsWrapper::BtnLoadFromFile_Clicked);
    
    connect(pGreetingWidget,        &GreetingWindow::btnLoadFromGameClicked,
            this,                   &SetUpWindowsWrapper::BtnLoadFromGame_Clicked);

    connect(pGreetingWidget,        &GreetingWindow::btnSettingsClicked,
            this,                   &SetUpWindowsWrapper::BtnSettings_Clicked);

    connect(pLoadFromTheFileWindow, &LoadFromTheFileWindow::btnBackClicked,
            this,                   &SetUpWindowsWrapper::BtnBack_Clicked);
    
    connect(pLoadFromTheFileWindow, &LoadFromTheFileWindow::btnStartClicked,
            this,                   &SetUpWindowsWrapper::LoadFromTheFileWindow_AcceptConfiguration);

    connect(pLoadFromTheGameWindow, &LoadFromTheGameWindow::btnBackClicked,
            this,                   &SetUpWindowsWrapper::BtnBack_Clicked);
    
    connect(pLoadFromTheGameWindow, &LoadFromTheGameWindow::btnStartClicked,
            this,                   &SetUpWindowsWrapper::LoadFromTheGameWindow_AcceptConfiguration);

    connect(pSettingsWindow,        &SettingsWindow::btnBackClicked,
            this,                   &SetUpWindowsWrapper::BtnBack_Clicked);
}

void SetUpWindowsWrapper::DetachConnections()
{
    disconnect(pGreetingWidget,        &GreetingWindow::languageChanged,
               this,                   &SetUpWindowsWrapper::GreetingWidget_LanguageChanged);

    disconnect(pGreetingWidget,        &GreetingWindow::btnLoadFromFileClicked,
               this,                   &SetUpWindowsWrapper::BtnLoadFromFile_Clicked);
        
    disconnect(pGreetingWidget,        &GreetingWindow::btnLoadFromGameClicked,
               this,                   &SetUpWindowsWrapper::BtnLoadFromGame_Clicked);

    disconnect(pGreetingWidget,        &GreetingWindow::btnSettingsClicked,
               this,                   &SetUpWindowsWrapper::BtnBack_Clicked);
    
    disconnect(pLoadFromTheFileWindow, &LoadFromTheFileWindow::btnBackClicked,
               this,                   &SetUpWindowsWrapper::BtnBack_Clicked);

    disconnect(pLoadFromTheFileWindow, &LoadFromTheFileWindow::btnStartClicked,
               this,                   &SetUpWindowsWrapper::LoadFromTheFileWindow_AcceptConfiguration);

    disconnect(pLoadFromTheGameWindow, &LoadFromTheGameWindow::btnBackClicked,
               this,                   &SetUpWindowsWrapper::BtnBack_Clicked);

    disconnect(pLoadFromTheGameWindow, &LoadFromTheGameWindow::btnStartClicked,
               this,                   &SetUpWindowsWrapper::LoadFromTheGameWindow_AcceptConfiguration);

    disconnect(pSettingsWindow,        &SettingsWindow::btnBackClicked,
               this,                   &SetUpWindowsWrapper::BtnBack_Clicked);
}

void SetUpWindowsWrapper::AddWidgets()
{
    pGreetingWidget        = new GreetingWindow(this);
    pLoadFromTheGameWindow = new LoadFromTheGameWindow(pGreetingWidget);
    pLoadFromTheFileWindow = new LoadFromTheFileWindow(pGreetingWidget);
    pSettingsWindow        = new SettingsWindow(pGreetingWidget);

    pGreetingWidget->setFixedSize(size());
    pLoadFromTheGameWindow->setFixedSize(size());
    pLoadFromTheFileWindow->setFixedSize(size());
    pSettingsWindow->setFixedSize(size());

    addWidget(pGreetingWidget);
    addWidget(pLoadFromTheGameWindow);
    addWidget(pLoadFromTheFileWindow);
    addWidget(pSettingsWindow);
}

void SetUpWindowsWrapper::GreetingWidget_LanguageChanged(int intLngIndex)
{
    Languages lngType = static_cast<Languages>(intLngIndex);

    WINDOW_MANAGER->SetTranslator(lngType);

    DetachConnections();
    pGreetingWidget->deleteLater();
    pLoadFromTheGameWindow->deleteLater();
    pLoadFromTheFileWindow->deleteLater();
    pSettingsWindow->deleteLater();

    AddWidgets();
    AttachConnections();
    setCurrentWidget(pGreetingWidget);
}

void SetUpWindowsWrapper::BtnLoadFromFile_Clicked() { setCurrentWidget(pLoadFromTheFileWindow); }
void SetUpWindowsWrapper::BtnLoadFromGame_Clicked() { setCurrentWidget(pLoadFromTheGameWindow); }
void SetUpWindowsWrapper::BtnSettings_Clicked()     { setCurrentWidget(pSettingsWindow); }
void SetUpWindowsWrapper::BtnBack_Clicked()         { WINDOW_MANAGER->SetCSFFilePath(""); setCurrentWidget(pGreetingWidget); }

void SetUpWindowsWrapper::LoadFromTheGameWindow_AcceptConfiguration()
{ 
    // TODO: Make it load vanila Generals
    //       Also as work with non-ascii paths
    //       Also as search in big-archives (see more at GZH source code)
    //       Also as if-protection when `Game\English` doesnt have `generals.csf`
    QString path = QString::fromStdString(Registry::GetPathToGame(Registry::Games::GeneralsZeroHour)) + "\\Data\\English\\generals.csf";
    
    if (!QFile::exists(path))
    {
        QMessageBox::critical(nullptr, L10N(PROGRAM_CONSTANTS->CSF_ERROR_HEADER),
                                       L10N(PROGRAM_CONSTANTS->CSF_EMPTY_DATA_ENGLISH));
        return;
    }
    
    WINDOW_MANAGER->SetCSFFilePath(path);
    WINDOW_MANAGER->LaunchWidget_AcceptConfiguration();
}

void SetUpWindowsWrapper::LoadFromTheFileWindow_AcceptConfiguration() 
{
    WINDOW_MANAGER->SetCSFFilePath(pLoadFromTheFileWindow->findChild<QLineEdit*>("lneFilePath", Qt::FindChildrenRecursively)->text());
    WINDOW_MANAGER->LaunchWidget_AcceptConfiguration();
}
