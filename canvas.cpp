#include "canvas.h"
#include <QPoint>
#include <QMouseEvent>
#include <QPen>
#include <QBrush>
#include <QDrag>
#include <QGraphicsItem>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>
#include <QDir>

Canvas::Canvas() : QGraphicsView(), m_selected_tool {0}
{
} // should probably add canvas dimensions later
//Also what gets setup here is the tool thing.

void Canvas::change_rect()
{
  m_selected_tool = 0;
}

void Canvas::change_circle()
{
  m_selected_tool = 1;
}

void Canvas::change_mov()
{
  m_selected_tool = 3;
}

void Canvas::change_del()
{
  m_selected_tool = 6;
}


void Canvas::mousePressEvent(QMouseEvent *event)
{
	QPoint start = event->pos();
	QPointF q = mapToScene(start);
	qreal x = q.x();
	qreal y = q.y();
	QPen drawPen(Qt::black);
	drawPen.setWidth(2);
	switch(m_selected_tool)
	{
		case 0: // Rectangle tool.
			{
				QRectF rect(x-60, y-40, 120, 80);
				QGraphicsRectItem* r = scene()->addRect(rect, drawPen, QBrush(Qt::black));
				r->setFlag(QGraphicsItem::ItemIsSelectable, true);
				r->setFlag(QGraphicsItem::ItemIsMovable, true);
				r->setCursor(Qt::PointingHandCursor);
				break;
			}
		case 1: // Circle tool.
			{
				QRectF rect(x-60, y-60, 120, 120);
				QGraphicsEllipseItem* r = scene()->addEllipse(rect, drawPen, QBrush(Qt::black));
				r->setFlag(QGraphicsItem::ItemIsSelectable, true);
				r->setFlag(QGraphicsItem::ItemIsMovable, true);
				r->setCursor(Qt::PointingHandCursor);
				break;
			}
		case 3: //Selection tool.
			{
				break; //Yeah, this literally does nothing except free up the cursor.
			}

		case 6: //Delete tool.
			{
				QList<QGraphicsItem*> items = scene()->selectedItems();
				for(QGraphicsItem* i : items) {
					scene()->removeItem(i);
				}
				break;
			}
		default:
			{
				break;
			}
	} // This switch statement sets up a bunch of cases based on what the currently selected tool is.
	//Right now there are two cases. It draws a rectangle or a circle. Either way the first thing it does is establish mouse location.
	//For additional cases, add a new int, and then go add another slot in the window.cpp class.
	show();	

}
