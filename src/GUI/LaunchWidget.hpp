#pragma once
#include <QStackedWidget>
#include "GreetingWidget.hpp"
#include "CreationDialog.hpp"
#include "LoadDialog.hpp"

class SetUpWindowsWrapper final : public QStackedWidget
{
    Q_OBJECT
private: // Data
    GreetingWindow* pGreetingWidget = nullptr;
    CreationDialog* pCreationDialog = nullptr;
    LoadDialog*     pLoadDialog     = nullptr;

private: // Methods
    /// @brief Connects slots and singals.
    void AttachConnections();
    /// @brief Disconnects slots and signals.
    void DetachConnections();
public:
    SetUpWindowsWrapper(QWidget* parent = nullptr);

private:
    /// @brief Initialize `GreetingWindow`, `CreationDialog`, `LoadDialog`.
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
