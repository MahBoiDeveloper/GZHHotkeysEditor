#pragma once
#include <QStackedWidget>
#include "EditorWindow.hpp"

class EditorWindowWrapper final : public QStackedWidget
{
    Q_OBJECT
private: // Data
    EditorWindow* pEditorWindow = nullptr;

private: // Methods
    /// @brief Connects slots and singals.
    void AttachConnections();
    /// @brief Disconnects slots and signals.
    void DetachConnections();
public:
    EditorWindowWrapper(QWidget* parent = nullptr);
};
