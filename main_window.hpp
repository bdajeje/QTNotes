#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QLabel>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QTextEdit>
#include <QTreeView>

#include "models/note.hpp"
#include "widgets/editable_label.hpp"
#include "widgets/jlabel.hpp"
#include "widgets/window_add_note.hpp"

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:

    MainWindow(QWidget *parent = 0);

  protected:

    void createWidgets();
    void loadNotes(const QString& directory_path, QStandardItem* parent);
    void selectNote(const model::Note& note);

  protected:

    std::map<QModelIndex, model::Note> m_notes;
    QStandardItemModel* m_notes_model;
    QTreeView* m_notes_view;
    EditableLabel* m_note_title;
    QTextEdit* m_note_edit;
    JLabel* m_notes_action_add;
    JLabel* m_notes_action_del;
    WindowAddNote* m_window_new_note;

  public slots:

    void noteSelected(QModelIndex index);
    void addNewNote();
    void deleteSelectedNote();
};

#endif // MAIN_WINDOW_HPP
