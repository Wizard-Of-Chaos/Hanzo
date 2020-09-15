#include <QGraphicsView>

#ifndef __CANVAS_H
#define __CANVAS_H
class Canvas : public QGraphicsView
{
	private:
		int* m_selected_tool; //Pointer to the int in the Window class determining tool
	public:
		Canvas(int* tool);
		void mousePressEvent(QMouseEvent* event);
};

#endif
