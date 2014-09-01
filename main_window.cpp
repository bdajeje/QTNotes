#include "main_window.hpp"

#include <iostream>

#include <QApplication>
#include <QDir>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QStringList>
#include <QVBoxLayout>

#include "utils/icons_manager.hpp"
#include "utils/pixmap_manager.hpp"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  // Window icon
  setWindowIcon( utils::IconsManager::get("icon.png") );

  // Create widgets
  createWidgets();

  // Create notes tree
  loadNotes(QApplication::applicationDirPath() + "/resources/data/", m_notes_model->invisibleRootItem());
}

void MainWindow::createWidgets()
{
  auto central_widget = new QWidget(this);
  auto main_layout    = new QVBoxLayout();

  // notes layout
  auto notes_layout = new QVBoxLayout();

  // notes title
  auto notes_title = new QLabel("Notes");

  // Notes list
  m_notes_model = new QStandardItemModel();
  m_notes_view  = new QTreeView;
  m_notes_view->setModel(m_notes_model);
  m_notes_view->header()->hide();

  // Notes actions layout
  auto notes_actions_layout = new QHBoxLayout();
  notes_actions_layout->setAlignment(Qt::AlignLeft);

  // Notes action add button
  m_notes_action_add = new JLabel();
  utils::PixmapManager::setLabelPixmap(m_notes_action_add, utils::pixmap::CategoryAdd);

  // Notes action del button
  m_notes_action_del = new JLabel();
  utils::PixmapManager::setLabelPixmap(m_notes_action_del, utils::pixmap::CategoryDel);

  // Note layout
  auto note_layout = new QVBoxLayout();

  // Note title
  m_note_title = new EditableLabel("", true);

  // Text edit
  m_note_edit = new QTextEdit();

  // HLayout for list and note
  auto hlayout = new QHBoxLayout();

  // Widgets placement
  notes_actions_layout->addWidget(m_notes_action_add);
  notes_actions_layout->addWidget(m_notes_action_del);
  notes_layout->addWidget(notes_title);
  notes_layout->addWidget(m_notes_view);
  note_layout->addWidget(m_note_title);
  note_layout->addWidget(m_note_edit);
  hlayout->addLayout(notes_layout);
  hlayout->addLayout(note_layout);
  main_layout->addLayout(hlayout);
  main_layout->addLayout(notes_actions_layout);

  central_widget->setLayout(main_layout);
  setCentralWidget(central_widget);

  // Widgets not related to this view
  m_window_new_note = new WindowAddNote(this, Qt::Dialog);
  m_window_new_note->setWindowModality(Qt::ApplicationModal);

  // Connections
  connect( m_notes_view, SIGNAL(clicked(QModelIndex)), this, SLOT(noteSelected(QModelIndex)) );
  connect( m_notes_action_add, SIGNAL(clicked()), this, SLOT(addNewNote()) );
  connect( m_notes_action_del, SIGNAL(clicked()), this, SLOT(deleteSelectedNote()) );
}

void MainWindow::loadNotes(const QString& directory_path, QStandardItem* parent)
{
  QDir data_directory{ directory_path };
  QFileInfoList files_info = data_directory.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

  for( const QFileInfo& file_info : files_info )
  {
    if( file_info.isDir() )
    {
      auto category = new QStandardItem( file_info.fileName() );
      parent->appendRow( category );
      loadNotes( file_info.filePath(), category );
    }
    else if( file_info.isFile() )
    {
      model::Note note{ file_info.filePath() };
      auto item = new QStandardItem( note.name() );
      parent->appendRow( item );
      m_notes.emplace( m_notes_model->indexFromItem(item), std::move(note) );
    }
  }
}

void MainWindow::noteSelected(QModelIndex index)
{
  auto found = m_notes.find(index);
  if( found != m_notes.end() )
    selectNote( found->second );
}

void MainWindow::selectNote(const model::Note& note)
{
  m_note_title->label()->setText( note.name() );
  m_note_edit->setText( note.content() );
}

void MainWindow::addNewNote()
{
  m_window_new_note->show();
}

void MainWindow::deleteSelectedNote()
{
  auto found = m_notes.find(m_notes_view->currentIndex());
  if( found == m_notes.end() )
    return;

  // Remove note from list
  // todo

  // Remove note from system
  model::Note::remove( found->second );
}

