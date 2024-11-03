#include "../Logger.hpp"
#include "ImageManager.hpp"
#include "CreationDialog.hpp"
#include "LoadDialog.hpp"
#include "WindowManager.hpp"

LaunchWidget::LaunchWidget(Languages lngType, QWidget* parent) : QStackedWidget(parent)
{
    // MainLaunchWidget settings
    setFixedSize(795, 440);
    setWindowFlags(windowFlags() |  Qt::MSWindowsFixedSizeDialogHint);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint &
                                   ~Qt::WindowMinimizeButtonHint);
    
    WINDOW_MANAGER->SetTranslator(lngType);
    pStartWidget = new GreetingWidget{lngType};
    addWidget(pStartWidget);
    UpdateConnectionsToSignals();
}

void LaunchWidget::UpdateConnectionsToSignals()
{
    connect(pStartWidget, &GreetingWidget::languageChanged,
            this,         &LaunchWidget::OnChangeLanguage);
    connect(pStartWidget, &GreetingWidget::pressed,
            this,         &LaunchWidget::OnStartButtonClicked);
}

void LaunchWidget::OnChangeLanguage(int intLngIndex)
{
    // Find language type by its code.
    Languages lngType = static_cast<Languages>(intLngIndex);

    // Change class' translator.
    WINDOW_MANAGER->SetTranslator(lngType);

    // Recreate StartWidget and update connections.
    pStartWidget->deleteLater();
    pStartWidget = new GreetingWidget{lngType};
    addWidget(pStartWidget);
    UpdateConnectionsToSignals();
}

void LaunchWidget::OnStartButtonClicked(GreetingWidget::StandartButtons standartButton)
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
    connect(pConfigurationWidget, &CreationDialog::AcceptedConfiguration, this, &LaunchWidget::AcceptedConfiguration);
}
