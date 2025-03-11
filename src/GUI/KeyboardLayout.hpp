#pragma once
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTreeWidgetItem>

/// @brief Creates line of buttons-keys as keyboard layout.
class KeyboardLayout : public QVBoxLayout
{
    Q_OBJECT
private: // Data
    QHBoxLayout* pFirstLine;
    QHBoxLayout* pSecondLine;
    QHBoxLayout* pThirdLine;
private: // Methods
    QHBoxLayout* CreateKeysOnKeyboard(const QString& str);
public:
    KeyboardLayout(QWidget* parent = nullptr);
    /// @brief Set key's styles on keyboard block to property `status=null`.
    KeyboardLayout* Nullify();
    KeyboardLayout* Update(const QTabWidget& tab, int id);
    
};
