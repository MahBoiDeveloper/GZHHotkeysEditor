#include "../Logger.hpp"
#include "ImageManager.hpp"
#include "CreationDialog.hpp"
#include "LoadDialog.hpp"
#include "WindowManager.hpp"
#include "LaunchWidget.hpp"

LaunchWidget::LaunchWidget(QWidget* parent) : QStackedWidget(parent)
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

void LaunchWidget::AttachConnections()
{
    connect(pGreetingWidget, &GreetingWindow::languageChanged,
            this,            &LaunchWidget::GreetingWidget_LanguageChanged);

    connect(pGreetingWidget, &GreetingWindow::pressed,
            this,            &LaunchWidget::BtnNewProjectOrBtnLoadProject_Clicked);

    connect(pLoadDialog,     &LoadDialog::btnBackClicked,
            this,            &LaunchWidget::BtnBack_Clicked);

    connect(pCreationDialog, &CreationDialog::btnBackClicked,
            this,            &LaunchWidget::BtnBack_Clicked);
    
    connect(pCreationDialog, &CreationDialog::btnStartClicked,
            this,            &LaunchWidget::CreationDialog_AcceptConfiguration);
}

void LaunchWidget::DetachConnections()
{
    disconnect(pGreetingWidget, &GreetingWindow::languageChanged,
               this,            &LaunchWidget::GreetingWidget_LanguageChanged);

    disconnect(pGreetingWidget, &GreetingWindow::pressed,
               this,            &LaunchWidget::BtnNewProjectOrBtnLoadProject_Clicked);
    
    disconnect(pLoadDialog,     &LoadDialog::btnBackClicked,
               this,            &LaunchWidget::BtnBack_Clicked);

    disconnect(pCreationDialog, &CreationDialog::btnBackClicked,
               this,            &LaunchWidget::BtnBack_Clicked);

    disconnect(pCreationDialog, &CreationDialog::btnStartClicked,
               this,            &LaunchWidget::CreationDialog_AcceptConfiguration);
}

void LaunchWidget::AddWidgets()
{
    pGreetingWidget = new GreetingWindow(this);
    pCreationDialog = new CreationDialog(pGreetingWidget);
    pLoadDialog     = new LoadDialog(pGreetingWidget);

    pGreetingWidget->setFixedSize(size());
    pCreationDialog->setFixedSize(size());
    pLoadDialog->setFixedSize(size());

    addWidget(pGreetingWidget);
    addWidget(pCreationDialog);
    addWidget(pLoadDialog);
}

void LaunchWidget::GreetingWidget_LanguageChanged(int intLngIndex)
{
    Languages lngType = static_cast<Languages>(intLngIndex);

    WINDOW_MANAGER->SetTranslator(lngType);

    DetachConnections();
    pGreetingWidget->deleteLater();
    pCreationDialog->deleteLater();
    pLoadDialog->deleteLater();

    AddWidgets();
    AttachConnections();
    setCurrentWidget(pGreetingWidget);
}

void LaunchWidget::BtnNewProjectOrBtnLoadProject_Clicked(GreetingWindow::StandartButtons standartButton)
{
    switch (standartButton)
    {
        case GreetingWindow::StandartButtons::NewProject:
            setCurrentWidget(pCreationDialog);
            break;
        case GreetingWindow::StandartButtons::LoadProject:
            setCurrentWidget(pLoadDialog);
            break;
        default:
            setCurrentWidget(pCreationDialog);
            break;
    }
}

void LaunchWidget::BtnBack_Clicked() { setCurrentWidget(pGreetingWidget); }

void LaunchWidget::CreationDialog_AcceptConfiguration() { QVariant cfg; WINDOW_MANAGER->LaunchWidget_AcceptConfiguration(cfg); }
