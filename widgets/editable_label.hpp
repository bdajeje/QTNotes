#ifndef EDITABLE_LABEL_HPP
#define EDITABLE_LABEL_HPP

#include <QHBoxLayout>
#include <QLineEdit>

#include "widgets/jlabel.hpp"

class EditableLabel : public QWidget
{
  Q_OBJECT

  public:

    EditableLabel(const QString& text, bool show_label, QWidget *parent = 0);

    JLabel* label() { return m_label; }
    QLineEdit* input() { return m_input; }

    void showIcon(bool show);

  protected:

    void updateVisibility();

  protected:

    JLabel* m_label;
    QLineEdit* m_input;
    QHBoxLayout* m_layout_edit;
    QHBoxLayout* m_layout_text;
    QHBoxLayout* m_main_layout;
    JLabel* m_icon_edit;
    JLabel* m_icon_validate;
    bool m_label_shown;

  public slots:

    void showInput();
    void showLabel();
    void updateText();
};

#endif // EDITABLE_LABEL_HPP
