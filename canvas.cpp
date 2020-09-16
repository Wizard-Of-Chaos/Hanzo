#include "canvas.h"
#include <QPoint>
#include <QMouseEvent>
#include <QPen>
#include <QBrush>
#include <QDrag>

Canvas::Canvas() : QGraphicsView(), m_selected_tool {0}
{

} // should probably add canvas dimensions later
//Also what gets setup here is the tool thing.

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
		case 0:
			{
				QRectF rect(x-60, y-40, 120, 80);
				scene()->addRect(rect, drawPen, QBrush(Qt::black));
				break;
			}
		case 1:
			{
				QRectF rect(x-60, y-60, 120, 120);
				scene()->addEllipse(rect, drawPen, QBrush(Qt::black));
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
