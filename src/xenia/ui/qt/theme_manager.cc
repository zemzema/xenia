/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2018 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include <QCoreApplication>
#include <QDebug>
#include <QDirIterator>

#include "theme_manager.h"
#include "xenia/base/logging.h"
#include "xenia/vfs/devices/host_path_device.h"

namespace xe {
namespace ui {
namespace qt {

ThemeManager::ThemeManager() {}

ThemeManager& ThemeManager::SharedManager() {
  static ThemeManager* manager = nullptr;
  if (!manager) {
    manager = new ThemeManager();
    manager->LoadThemes();
  }
  return *manager;
}

const QString& ThemeManager::base_style() const {
  QFile file(":/themes/base.css");
  file.open(QFile::ReadOnly | QFile::Text);

  static QString* style = nullptr;
  if (!style) {
    style = new QString(file.readAll());
    style->remove(QRegExp("[\\n\\t\\r]"));
  }

  return *style;
}

void ThemeManager::LoadThemes() {
  QString theme_dir = ":/resources/themes/";
  QDirIterator iter(theme_dir, QDir::Dirs | QDir::NoDotAndDotDot);

  while (iter.hasNext()) {
    Theme t(iter.next());
    t.LoadTheme();
    themes_.push_back(t);
  }
}

}  // namespace qt
}  // namespace ui
}  // namespace xe
