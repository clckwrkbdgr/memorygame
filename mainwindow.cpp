#include <QtDebug>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include "mainwindow.h"

const int WIDTH = 6;
const int HEIGHT = 6;

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
			view->setItem(y, x, new QTableWidgetItem(table[x + y * WIDTH]));
		}
	}
}

MemoryWidget::~MemoryWidget()
{
}

void MemoryWidget::turnOver(int row, int column)
{
}

