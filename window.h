#include <QMainWindow>
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

class Window : public QMainWindow
{
  	Q_OBJECT
	private:
		QGraphicsScene* m_scene;
		Canvas* m_canvas;
		QMenu* m_menu;
		QToolBar* m_toolbar;
		QAction* m_filemenu;
		QAction* m_savemenu;
		QAction* m_printmenu;
		QAction* m_importmenu;
		QAction* m_newmenu;
		QAction* m_rect;
		QAction* m_circle;
		QAction* m_triangle;
		QAction* m_line;
		QAction* m_move;
		QAction* m_delete;

        int m_selected_tool;
	private slots:

	void save_file();
	void load_file();
	void print_file();
	
	public:
		Window();
		~Window();
        int tool();
};

#endif
