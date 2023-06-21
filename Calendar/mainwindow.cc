#include "mainwindow.h"

#include <QMenu>
#include <QWidgetAction>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  QPushButton *button = new QPushButton("Выбрать дату", this);
  button->setStyleSheet("QPushButton::menu-indicator{image:none;}");
  QMenu *menu = new QMenu(button);
  QWidgetAction *w_action = new QWidgetAction(menu);

  // Создаем календарь
  QCalendarWidget *calendar = new QCalendarWidget(menu);
  calendar->setWindowFlags(Qt::Popup);
  calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
  calendar->setSelectionMode(QCalendarWidget::SingleSelection);

  // обновляем lineEdit
  connect(calendar, &QCalendarWidget::selectionChanged, this,
          &MainWindow::updateLineEdit);

  // закрываем меню после выбора даты
  connect(calendar, &QCalendarWidget::selectionChanged, menu, &QMenu::close);

  // устанавливаем календарь в action
  w_action->setDefaultWidget(calendar);
  menu->addAction(w_action);
  button->setMenu(menu);

  // Создаем qLineEdit
  QLineEdit *lineEdit = new QLineEdit(this);
  lineEdit->setObjectName("line_calendar");

  // Создаем вертикальный лейаут и добавляем в него кнопку и qLineEdit
  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(button);
  layout->addWidget(lineEdit);

  // Создаем виджет для центральной области окна, устанавливаем наш лейаут в
  // качестве его лейаута
  QWidget *centralWidget = new QWidget(this);
  centralWidget->setLayout(layout);
  setCentralWidget(centralWidget);
}

void MainWindow::updateLineEdit() {
  QCalendarWidget *calendar = qobject_cast<QCalendarWidget *>(sender());
  if (findChild<QLineEdit *>("line_calendar")) {
    findChild<QLineEdit *>("line_calendar")
        ->setText(calendar->selectedDate().toString("dd.MM.yyyy"));
  }
}
