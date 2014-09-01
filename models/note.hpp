#ifndef NOTE_HPP
#define NOTE_HPP

#include <QString>

namespace model {

class Note final
{
  public:

    Note(const QString& filepath);

    const QString& name() const { return m_name; }
    const QString& content() const { return m_content; }

    static void remove( const Note& note );

  protected:

    QString m_filepath;
    QString m_name;
    QString m_content;
};

} // model

#endif // NOTE_HPP
