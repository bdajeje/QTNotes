#include "jlabel.hpp"

JLabel::JLabel(QWidget *parent)
  : JLabel("", parent)
{}

JLabel::JLabel(const QString& label, QWidget *parent)
  : QLabel(label, parent)
{
  setClickable(m_clickable);

  connect( this, SIGNAL( clicked() ), this, SLOT( slotClicked() ) );
}

void JLabel::setClickable(bool value)
{
  m_clickable = value;

  if( value )
    setCursor(Qt::PointingHandCursor);
  else
    setCursor(Qt::ArrowCursor);
}

void JLabel::slotClicked()
{
  // No specific behavior here, but could be override by child class.
}

void JLabel::mousePressEvent(QMouseEvent*)
{
  emit clicked();
}

void JLabel::mouseDoubleClickEvent(QMouseEvent*)
{
    emit doubleClicked();
}
