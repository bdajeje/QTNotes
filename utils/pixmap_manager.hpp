#ifndef PIXMAP_MANAGER_HPP
#define PIXMAP_MANAGER_HPP

#include <QLabel>

#include "utils/resources_manager.hpp"

namespace utils {

namespace pixmap {
  static const QString CategoryAdd  = "add.png";
  static const QString CategoryDel  = "delete.png";
  static const QString LabelEdit    = "text_edit.png";
  static const QString ValidateEdit = "validate.png";

  static const std::map<QString, QSize> _sizes = {
    {CategoryAdd,  QSize(20, 20)},
    {CategoryDel,  QSize(20, 20)},
    {LabelEdit,    QSize(20, 20)},
    {ValidateEdit, QSize(20, 20)}
  };
}

class PixmapManager : public ResourcesManager<QPixmap>
{
  public:

    static QPixmap& get(const QString& id)
    {
      auto& resource = ResourcesManager<QPixmap>::get(id);
      resource = resource.scaled( pixmap::_sizes.find(id)->second );
      return resource;
    }

    static void setLabelPixmap(QLabel* label, const QString& pixmap_id)
    {
      const QPixmap& pixmap = get(pixmap_id);
      label->setPixmap( pixmap );
      label->setFixedSize( pixmap.size() );
    }
};

} // namespace utils

#endif // PIXMAP_MANAGER_HPP
