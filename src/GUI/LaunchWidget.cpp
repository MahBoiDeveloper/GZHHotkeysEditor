#include "../Logger.hpp"
#include "ImageManager.hpp"
#include "CreationDialog.hpp"
#include "LoadDialog.hpp"
#include "WindowManager.hpp"
#include "LaunchWidget.hpp"

LaunchWidget::LaunchWidget(QWidget* parent) : QStackedWidget(parent)
{
    // MainLaunchWidget settings
    setFixedSize(795, 440);
    setWindowFlags(windowFlags() |  Qt::MSWindowsFixedSizeDialogHint);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint &
                                   ~Qt::WindowMinimizeButtonHint);
    
    pGreetingWidget = new GreetingWidget(this);
    addWidget(pGreetingWidget);
    AttachConnections();
}

void LaunchWidget::AttachConnections()
{
    connect(pGreetingWidget, &GreetingWidget::languageChanged,
            this,            &LaunchWidget::GreetingWidget_LanguageChanged);

    connect(pGreetingWidget, &GreetingWidget::pressed,
            this,            &LaunchWidget::BtnNewProjectOrBtnLoadProject_Clicked);
}

void LaunchWidget::DetachConnections()
{
    disconnect(pGreetingWidget, &GreetingWidget::languageChanged,
               this,            &LaunchWidget::GreetingWidget_LanguageChanged);

    disconnect(pGreetingWidget, &GreetingWidget::pressed,
               this,            &LaunchWidget::BtnNewProjectOrBtnLoadProject_Clicked);
}

void LaunchWidget::GreetingWidget_LanguageChanged(int intLngIndex)
{
    // Find language type by its code.
    Languages lngType = static_cast<Languages>(intLngIndex);

    // Change class' translator.
    WINDOW_MANAGER->SetTranslator(lngType);

    // Recreate StartWidget and update connections.
    DetachConnections();
    removeWidget(pGreetingWidget);
    pGreetingWidget->deleteLater();

    pGreetingWidget = new GreetingWidget(this);
    addWidget(pGreetingWidget);
    setCurrentWidget(pGreetingWidget);
    AttachConnections();
}

void LaunchWidget::BtnNewProjectOrBtnLoadProject_Clicked(GreetingWidget::StandartButtons standartButton)
{
    BaseConfigurationDialog* pConfigurationWidget = nullptr;

    switch (standartButton)
    {
        case GreetingWidget::StandartButtons::NewProject:
            pConfigurationWidget = new CreationDialog();
            break;
        case GreetingWidget::StandartButtons::LoadProject:
            pConfigurationWidget = new LoadDialog();
            break;
        default:
            pConfigurationWidget = new CreationDialog();
            break;
    }
    addWidget(pConfigurationWidget);
    setCurrentWidget(pConfigurationWidget); // next window (creator)

    // if accepted -> send signal with configuration
    connect(pConfigurationWidget, &CreationDialog::acceptConfiguration, this, &LaunchWidget::CreationDialog_AcceptConfiguration);
}

void LaunchWidget::CreationDialog_AcceptConfiguration(const QVariant& cfg) { WINDOW_MANAGER->LaunchWidget_AcceptConfiguration(cfg); }
