#include <QtDebug>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include "mainwindow.h"

const int WIDTH = 3;
const int HEIGHT = 4;

MemoryWidget::MemoryWidget(QWidget * parent)
	: QWidget(parent), view(0), opened(WIDTH * HEIGHT, false), table(WIDTH * HEIGHT, QChar())
{
	Q_ASSERT((WIDTH * HEIGHT) % 2 = 0);
	for(int i = 0; i < table.size() / 2; ++i) {
		QString alphabet = "QWERTYUIOPASDFGHJKLZXCVBNM";
		QChar ch = alphabet[qrand() % alphabet.size()];

		QPoint a, b;
		for(int j = 0; j < 10000; ++j) {
			a = QPoint(qrand() % WIDTH, qrand() % HEIGHT);
			if(table[a.x() + a.y() * WIDTH].isNull()) {
				break;
			}
		}
		Q_ASSERT(table[a.x() + a.y() * WIDTH].isNull());
		table[a.x() + a.y() * WIDTH] = ch;
		for(int j = 0; j < 10000; ++j) {
			b = QPoint(qrand() % WIDTH, qrand() % HEIGHT);
			if(table[b.x() + b.y() * WIDTH].isNull()) {
				break;
			}
		}
		Q_ASSERT(table[b.x() + b.y() * WIDTH].isNull());
		table[b.x() + b.y() * WIDTH] = ch;
	}

	view = new QTableWidget();
	view->setRowCount(HEIGHT);
	view->setColumnCount(WIDTH);
	QVBoxLayout * vbox = new QVBoxLayout();
	vbox->addWidget(view);
	setLayout(vbox);
	connect(view, SIGNAL(cellClicked(int, int)), this, SLOT(turnOver(int, int)));

	for(int x = 0; x < WIDTH; ++x) {
		for(int y = 0; y < HEIGHT; ++y) {
			view->setItem(y, x, new QTableWidgetItem());
		}
	}
	for(int x = 0; x < WIDTH; ++x) {
		for(int y = 0; y < HEIGHT; ++y) {
			if(opened[x + y * WIDTH]) {
				view->item(y, x)->setText(table[x + y * WIDTH]);
			} else {
				view->item(y, x)->setText("");
			}
		}
	}
}

MemoryWidget::~MemoryWidget()
{
}

void MemoryWidget::turnOver(int row, int column)
{
	if(!opened[column + row * WIDTH]) {
		opened[column + row * WIDTH] = true;
	}

	QList<QChar> paired;
	QList<QChar> unpaired;
	for(int i = 0; i < table.size(); ++i) {
		if(opened[i]) {
			QChar ch = table[i];
			if(unpaired.contains(ch)) {
				unpaired.removeAt(unpaired.indexOf(ch));
				paired << ch;
			} else {
				unpaired << ch;
			}
		}
	}
	if(paired.size() == table.size() / 2) {
		view->setEnabled(false);
	}

	if(unpaired.size() > 1) {
		for(int i = 0; i < table.size(); ++i) {
			opened[i] = false;
		}
	}

	for(int x = 0; x < WIDTH; ++x) {
		for(int y = 0; y < HEIGHT; ++y) {
			if(opened[x + y * WIDTH]) {
				view->item(y, x)->setText(table[x + y * WIDTH]);
			} else {
				view->item(y, x)->setText("");
			}
		}
	}
}

