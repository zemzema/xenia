#include "xenia/ui/qt/widgets/nav.h"
#include "xenia/ui/qt/widgets/tab.h"

#include <QLabel>

namespace xe {
namespace ui {
namespace qt {

XNav::XNav() { 
  Build(); 
};

void XNav::Build() {
  // Set Styling (TODO: Themeable)
  this->setStyleSheet("background-color: #282828;");
  this->setFixedHeight(60);  // TODO: Scalable

  // Build Main Layout
  layout_ = new QHBoxLayout();
  this->setLayout(layout_);

  // Build Components
  BuildXeniaIcon();
  BuildTabs();

  layout_->addStretch(1);
}

void XNav::BuildXeniaIcon() {
  xenia_icon_ = new QLabel();
  xenia_icon_->setFixedSize(40, 40);
  xenia_icon_->setScaledContents(true);
  xenia_icon_->setPixmap(QPixmap(":/resources/graphics/icon64x64.png"));

  QHBoxLayout* icon_layout = new QHBoxLayout();
  icon_layout->setContentsMargins(0, 0, 70, 0);
  icon_layout->addWidget(xenia_icon_, 0, Qt::AlignLeft);
  layout_->addLayout(icon_layout);
}

void XNav::BuildTabs() {
  std::vector<XTab*> tabs{
      new XTab("Home"),
      new XTab("Library"),
      new XTab("Settings"),
  };
  tab_selector_ = new XTabSelector(tabs);
  layout_->addWidget(tab_selector_);

  connect(tab_selector_, SIGNAL(TabChanged), SLOT(TabChangedSlot));
}

void XNav::TabChangedSlot(XTab* tab) {
  emit TabChanged(tab);
}

}  // namespace qt
}  // namespace ui
}  // namespace xe