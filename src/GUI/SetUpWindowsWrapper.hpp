#pragma once
#include <QStackedWidget>
#include "GreetingWindow.hpp"
#include "LoadFromTheGameWindow.hpp"
#include "LoadFromTheFileWindow.hpp"

class SetUpWindowsWrapper final : public QStackedWidget
{
    Q_OBJECT
private: // Data
    GreetingWindow* pGreetingWidget = nullptr;
    LoadFromTheGameWindow* pCreationDialog = nullptr;
    LoadFromTheFileWindow*     pLoadDialog     = nullptr;

private: // Methods
    /// @brief Connects slots and singals.
    void AttachConnections();
    /// @brief Disconnects slots and signals.
    void DetachConnections();
public:
    SetUpWindowsWrapper(QWidget* parent = nullptr);

private:
    /// @brief Initialize `GreetingWindow`, `LoadFromTheGameWindow`, `LoadFromTheFileWindow`.
    void AddWidgets();

private slots:
    /// @brief Show `GreetingWindow`, if button `Back` has been clicked.
    void BtnBack_Clicked();
    /// @brief Change language by its index if language has been changed via select list.
    void GreetingWidget_LanguageChanged(int intLngIndex);
    /// @brief Open create/loader widget if start button has been clicked.
    void BtnNewProjectOrBtnLoadProject_Clicked(GreetingWindow::StandartButtons standartButton);
    /// @brief Returns checked configuration of user preferences.
    void CreationDialog_AcceptConfiguration();
};
