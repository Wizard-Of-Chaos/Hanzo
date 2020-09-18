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
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>
#include <QDir>


Window::Window() : QMainWindow()
{	
    m_selected_tool = 0; 
	//m_menubar = new QMenuBar(this);
    	m_menu = menuBar()->addMenu(tr("&File"));
	m_toolbar = new QToolBar(this);  //Morgan Magner
	addToolBar(m_toolbar);
	m_newmenu = new QAction(tr("New"));
	m_importmenu = new QAction(tr("Import"));
	m_printmenu = new QAction(tr("Print"));
	m_savemenu = new QAction(tr("Save"));
	m_scene = new QGraphicsScene(this);
	m_canvas = new Canvas;

	m_canvas->setScene(m_scene);
        
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

	
	m_menu->addAction(m_newmenu);
	m_menu->addAction(m_importmenu);
	m_menu->addAction(m_printmenu);
	m_menu->addAction(m_savemenu);

	m_menu->addSeparator();	
	
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
    	connect(m_circle, SIGNAL(triggered()), m_canvas, SLOT(change_circle()));
	connect(m_rect, SIGNAL(triggered()), m_canvas, SLOT(change_rect()));
	connect(m_move, SIGNAL(triggered()), m_canvas, SLOT(change_mov()));
	connect(m_delete, SIGNAL(triggered()), m_canvas, SLOT(change_del()));
	connect(m_savemenu, SIGNAL(triggered()), this, SLOT(save_file()));
	//This is a sloppy way of handling it right now requiring some duplication of effort; refactor if we have the time
    //Alexander Wiecking, 9/15
	
	setCentralWidget(m_canvas);
	
	//this->setLayout(m_layout);
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

void Window::save_file()
{
	bool ok;
	QString filename = QInputDialog::getText(this, tr("Save"), tr("Enter a file name:"), QLineEdit::Normal, QDir::home().dirName(), &ok); //Opens dialogue box
	QList<QGraphicsItem*> items = m_canvas->scene()->items(); //Gets a list of all items on the scene
	filename = filename += tr(".hzo"); //Sets up the filename as a file.hzo file
	QFile file(filename); //Opens up a new file using the QFile format
	file.open(QIODevice::WriteOnly); //Gets ready to write
	QDataStream out(&file); //Sets up the out-stream
	for (QGraphicsItem* i : items) { //This loop grabs all the various data about the items on the list
		QPointF pos = i->pos();
		qreal height = i->boundingRect().height();
		qreal width = i->boundingRect().width();
		int type = i->type();
	}
}

void Window::load_file()
{
	bool ok;
	QString filename = QInputDialog::getText(this, tr("Load"), tr("Enter a file name:"), QLineEdit::Normal, QDir::home().dirName(), &ok);
}
