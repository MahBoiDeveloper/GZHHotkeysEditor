#include "EditorWindowWrapper.hpp"
#include "WindowManager.hpp"

EditorWindowWrapper::EditorWindowWrapper(QWidget* parent) : QStackedWidget(parent)
{
    resize(PROGRAM_CONSTANTS->EDITOR_WINDOW_SIZE);
    AddWidgets();
    setCurrentWidget(pEditorWindow);
    AttachConnections();
}

void EditorWindowWrapper::AddWidgets()
{
    pEditorWindow = new EditorWindow();
    addWidget(pEditorWindow);
}

void EditorWindowWrapper::AttachConnections()
{
    connect(pEditorWindow, &EditorWindow::languageChanged, 
            this,          &EditorWindowWrapper::EditorWindow_LanguageChanged);
}

void EditorWindowWrapper::DetachConnections()
{
    disconnect(pEditorWindow, &EditorWindow::languageChanged, 
               this,          &EditorWindowWrapper::EditorWindow_LanguageChanged);
}

void EditorWindowWrapper::EditorWindow_LanguageChanged()
{
    WINDOW_MANAGER->SetTranslator();

    DetachConnections();
    pEditorWindow->deleteLater();

    AddWidgets();
    AttachConnections();
    setCurrentWidget(pEditorWindow);
}
