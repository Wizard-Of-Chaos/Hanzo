#include "window.h"
#include "canvas.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QRectF>
#include <QGraphicsRectItem>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QToolButton>
#include <QAction>

Window::Window() : QWidget()
{	
    m_selected_tool = 0; 
	m_menubar = new QMenuBar(this);
	m_toolbar = new QToolBar(this);  //Morgan Magner
	m_filemenu = new QMenu(tr("File"), this);
	m_newmenu = new QMenu(tr("New"), this);
	m_importmenu = new QMenu(tr("Import"), this);
	m_printmenu = new QMenu(tr("Print"), this);
	m_savemenu = new QMenu(tr("Save"), this);
	m_layout = new QHBoxLayout;
	m_scene = new QGraphicsScene(this);
	m_canvas = new Canvas(&m_selected_tool);
        
/*	m_rect = new QToolButton();  //Morgan Magner   -- start of QToolBar
	m_rect->setIcon(Rectangle.png);  //change to setIcon(_____.png); later
        m_circle = new QToolButton();
	m_circle->setIcon(Rectangle.png);  //Change Later
        m_triangle = new QToolButton();
	m_triangle->setIcon(Rectangle.png); //Change Later 
        m_line = new QToolButton();
	m_line->setIcon(Rectangle.png);  //Change Later
        m_move = new QToolButton();
	m_move->setIcon(Rectangle.png);
        m_delete = new QToolButton();
	m_delete->setIcon(Rectangle.png);
*/
	m_rect = new QAction(tr("Rectangle"));
	m_circle = new QAction(tr("Circle")); 
	m_triangle = new QAction(tr("Triangle"));
	m_line = new QAction(tr("Line"));
	m_move = new QAction(tr("Move"));
	m_delete = new QAction(tr("Delete"));

	
	m_menubar->addMenu(m_filemenu);
	m_menubar->addMenu(m_newmenu);
	m_menubar->addMenu(m_importmenu);
	m_menubar->addMenu(m_printmenu);
	m_menubar->addMenu(m_savemenu);

	m_menubar->addSeparator();	
	
	//Morgan Magner     9/15
	//m_toolbar will be the "second menu" if you will. It is used to hold options such as
	//circle, rectangle, line as well as move and delete. I hope to also add color to this
	//section.
	//
	//addWidget actually adds the items to the toolbar
	
	m_toolbar->setMovable(false);   //where the toolbar appears in main window
	m_toolbar->setGeometry(0,0,1400,800);
	m_toolbar->addAction(m_rect);
	m_toolbar->addAction(m_circle);
	m_toolbar->addAction(m_triangle);
	m_toolbar->addAction(m_line);
	m_toolbar->addAction(m_move);
	m_toolbar->addAction(m_delete);
/*	m_toolbar->addWidget(m_rect);
	m_toolbar->addWidget(m_circle);
	m_toolbar->addWidget(m_triangle);
	m_toolbar->addWidget(m_line);
	m_toolbar->addWidget(m_move);
	m_toolbar->addWidget(m_delete); */
	m_toolbar->addSeparator();  //marks the end of the toolbar
    
    //Adding some connections to a few of the widgets
    connect(m_circle, SIGNAL(triggered()), this, SLOT(change_circle()));
	connect(m_rect, SIGNAL(triggered()), this, SLOT(change_rect()));
	//This is a sloppy way of handling it right now requiring some duplication of effort; refactor if we have the time
    //Alexander Wiecking, 9/15
	
	m_canvas->setScene(m_scene);	
	m_layout->addWidget(m_menubar);
	m_layout->addWidget(m_canvas);
	this->setLayout(m_layout);
	this->show();
	
}

Window::~Window()
{
	delete m_scene;
	delete m_canvas;
}

int Window::tool()
{
	return m_selected_tool;
}

void Window::change_rect()
{
	m_selected_tool = 0;
}

void Window::change_circle()
{
	m_selected_tool = 1;
}
