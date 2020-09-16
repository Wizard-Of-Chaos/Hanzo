#include <QGraphicsView>

#ifndef __CANVAS_H
#define __CANVAS_H
class Canvas : public QGraphicsView
{
  	Q_OBJECT
	private:
		int m_selected_tool; //Pointer to the int in the Window class determining tool
	
	private slots: //The slots are functions that get connected to each of the options on the toolbar.
	  void change_rect();
	  void change_circle();

	public:
		Canvas();
		void mousePressEvent(QMouseEvent* event);
};

#endif
