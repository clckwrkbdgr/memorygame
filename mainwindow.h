#pragma once
#include <QtGui/QWidget>
#include <QtCore/QVector>

class QTableWidget;

class MemoryWidget : public QWidget {
	Q_OBJECT
	Q_DISABLE_COPY(MemoryWidget)
public:
	MemoryWidget(QWidget * parent = 0);
	virtual ~MemoryWidget();
public slots:
	void turnOver(int row, int column);
private:
	QTableWidget * view;
	QVector<bool> opened;
	QVector<QChar> table;
};
