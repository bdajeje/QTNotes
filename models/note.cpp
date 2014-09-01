#include "note.hpp"

#include <iostream>

#include <QFile>
#include <QMessageBox>
#include <QStringList>
#include <QTextStream>

namespace model {

Note::Note(const QString& filepath)
  : m_filepath(filepath)
{
  QFile file{filepath};
  if(!file.open(QIODevice::ReadOnly))
  {
    QMessageBox::warning(nullptr, "Error", QString{"Can't read note: "} + filepath + "\n" + file.errorString());
    return;
  }

  QString file_content{file.readAll()};
  file.close();

  QStringList lines = file_content.split("\n");
  if( lines.empty() )
  {
    QMessageBox::warning(nullptr, "Error", QString{"Can't read note title: "} + filepath);
    m_name = "undefined";
    return;
  }

  m_name = lines[0];

  if( lines.size() >= 2 )
    m_content = lines[1];
}

void Note::remove( const Note& note )
{
  QFile(note.m_filepath).remove();
}

} // model
