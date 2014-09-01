#include "editable_label.hpp"

#include "utils/pixmap_manager.hpp"

EditableLabel::EditableLabel(const QString& text, bool show_label, QWidget *parent)
  : QWidget(parent)
  , m_label_shown(show_label)
{
  // Widgets creation
  m_label         = new JLabel(text);
  m_input         = new QLineEdit;
  m_icon_edit     = new JLabel("edit");
  m_icon_validate = new JLabel("valid");
  m_layout_edit   = new QHBoxLayout();
  m_layout_text   = new QHBoxLayout();
  m_main_layout   = new QHBoxLayout(this);

  utils::PixmapManager::setLabelPixmap(m_icon_edit, utils::pixmap::LabelEdit);
  utils::PixmapManager::setLabelPixmap(m_icon_validate, utils::pixmap::ValidateEdit);

  // Widgets placement
  m_layout_text->addWidget(m_icon_edit);
  m_layout_text->addWidget(m_label);
  m_layout_edit->addWidget(m_icon_validate);
  m_layout_edit->addWidget(m_input);
  m_main_layout->addLayout(m_layout_text);
  m_main_layout->addLayout(m_layout_edit);
  setLayout(m_main_layout);

  // Show correct widget
  updateVisibility();

  // Connections
  connect( m_label, SIGNAL(doubleClicked()), this, SLOT(showInput()) );
  connect( m_icon_edit, SIGNAL(clicked()), this, SLOT(showInput()) );
  connect( m_input, SIGNAL(editingFinished()), this, SLOT(updateText()) );
  connect( m_icon_validate, SIGNAL(clicked()), this, SLOT(updateText()) );
}

void EditableLabel::showIcon(bool show)
{
  if(show)
  {
    m_icon_edit->show();
    m_icon_validate->show();
  }
  else
  {
    m_icon_edit->hide();
    m_icon_validate->hide();
  }
}

void EditableLabel::updateVisibility()
{
  if( m_label_shown )
  {
    m_icon_edit->show();
    m_label->show();
    m_icon_validate->hide();
    m_input->hide();
  }
  else
  {
    m_icon_edit->hide();
    m_label->hide();
    m_icon_validate->show();
    m_input->show();
  }
}

void EditableLabel::showLabel()
{
  m_label_shown = true;
  updateVisibility();
}

void EditableLabel::showInput()
{
  m_label_shown = false;
  updateVisibility();
  m_input->setFocus();
}

void EditableLabel::updateText()
{
  m_label->setText( m_input->text() );
  showLabel();
}
