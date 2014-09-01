#ifndef JLABEL_HPP
#define JLABEL_HPP

#include <QLabel>

class JLabel final : public QLabel
{
  Q_OBJECT

  public:

    explicit JLabel(QWidget *parent = 0);
    explicit JLabel(const QString& label, QWidget *parent = 0);

    void setClickable(bool value);

  protected:

    void mousePressEvent( QMouseEvent * event );
    void mouseDoubleClickEvent( QMouseEvent * event );

  signals:

    void clicked();
    void doubleClicked();

  public slots:

     void slotClicked();

  protected:

   bool m_clickable {true};
};

#endif // JLABEL_HPP
