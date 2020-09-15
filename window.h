#include <QWidget>
#include <QToolBar>
#include <QAction>
#include "canvas.h"

#ifndef __WINDOW_H
#define __WINDOW_H

class QGraphicsScene;
class QHBoxLayout;
class QPoint;
class QMouseEvent;
class QMenuBar;
class QMenu;

class Window : public QWidget
{
	Q_OBJECT
	private:
		QGraphicsScene* m_scene;
		Canvas* m_canvas;
		QHBoxLayout* m_layout;
		QMenuBar* m_menubar;
		QToolBar* m_toolbar;
		QMenu* m_filemenu;
		QMenu* m_savemenu;
		QMenu* m_printmenu;
		QMenu* m_importmenu;
		QMenu* m_newmenu;
		QAction* m_rect;
		QAction* m_circle;
		QAction* m_triangle;
		QAction* m_line;
		QAction* m_move;
		QAction* m_delete;
        
        int m_selected_tool;
    private slots: //The slots are functions that get connected to each of the options on the toolbar.
        void change_rect();
        void change_circle();
	public:
		Window();
		~Window();
        int tool();

};

#endif
