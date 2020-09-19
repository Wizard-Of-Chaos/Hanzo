#include <iostream>
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
#include <QPrinter>
#include <QTextStream>
#include <QGraphicsPolygonItem>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <string>

//You ever wonder how many of these includes are unnecessary?
//So do I, but I fear to remove them.
//Are you ready to face your own #include demons?
//It has... little bearing on the following code, I'm more just inquiring.
//-Alexander Wiecking

Window::Window() : QMainWindow()
{	
    m_selected_tool = 0; 
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
	m_toolbar->addSeparator();  //marks the end of the toolbar
    
    //Adding some connections to a few of the widgets
    	connect(m_circle, SIGNAL(triggered()), m_canvas, SLOT(change_circle()));
	connect(m_rect, SIGNAL(triggered()), m_canvas, SLOT(change_rect()));
	connect(m_triangle, SIGNAL(triggered()), m_canvas, SLOT(change_triangle()));
	connect(m_line, SIGNAL(triggered()), m_canvas, SLOT(change_line()));
	connect(m_move, SIGNAL(triggered()), m_canvas, SLOT(change_mov()));
	connect(m_delete, SIGNAL(triggered()), m_canvas, SLOT(change_del()));
	connect(m_savemenu, SIGNAL(triggered()), this, SLOT(save_file()));
	connect(m_importmenu, SIGNAL(triggered()), this, SLOT(load_file()));
	connect(m_printmenu, SIGNAL(triggered()), this, SLOT(print_file()));
	connect(m_newmenu, SIGNAL(triggered()), this, SLOT(new_file()));
	//This is a sloppy way of handling it right now requiring some duplication of effort; refactor if we have the time
    //Alexander Wiecking, 9/15
	
	setCentralWidget(m_canvas);
	
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
	QTextStream out(&file); //Sets up the out-stream
	for (QGraphicsItem* i : items) { //This loop grabs all the various data about the items on the list
		qreal height = i->boundingRect().height();
		qreal width = i->boundingRect().width();
		
		QGraphicsRectItem* rect = dynamic_cast<QGraphicsRectItem *>(i);
		if (rect != nullptr)
		{
			//I'm a rectangle!
		  	out << QString("Rect ");
			out << height << QString(" ");
			out << width << QString(" ");
			out << rect->rect().x() << QString(" ") << rect->rect().y() << QString("\n");
		}
		
		
		QGraphicsEllipseItem* circle = dynamic_cast<QGraphicsEllipseItem *>(i);
		if (circle != nullptr)
		{
			//I'm a circle!
		  	out << QString("Circle ");
			out << height << QString(" ");
			out << width << QString(" ");
			out << circle->rect().x() << QString(" ") << circle->rect().y() <<  QString("\n");

		}

		QGraphicsLineItem* line = dynamic_cast<QGraphicsLineItem *>(i);
		if (line != nullptr)
		{
			//I'm a line!
			QPointF p1 = line->line().p1();
			QPointF p2 = line->line().p2();
		  	out << QString("Line ");
			out << p1.x() << QString(" ") <<  p1.y() << QString(" ") << p2.x() << QString(" ") << p2.y();
			out << QString("\n");
		}


		QGraphicsPolygonItem* triangle = dynamic_cast<QGraphicsPolygonItem *>(i);
		if (triangle != nullptr)
		{
			//I'm a triangle!
		  	out << QString("Triangle ");
			for(int i = 0; i < triangle->polygon().size(); ++i) {
				QPointF p = triangle->polygon()[i];
				out << p.x() << QString(" ") << p.y() << QString(" ");
			}
			out << QString("\n");
		}

			
	}
			  
}


void Window::load_file()
{
	bool ok;
	QString filename = QInputDialog::getText(this, tr("Load"), tr("Enter a file name:"), QLineEdit::Normal, QDir::home().dirName(), &ok);
	filename += QString(".hzo");
	QList<QGraphicsItem*> items = m_canvas->scene()->items();
	for (QGraphicsItem* i : items) {
		m_canvas->scene()->removeItem(i);
	} //Clears the old canvas.
	QList<QGraphicsItem*> new_items;

	std::ifstream in(filename.toStdString());
	if (!in.fail()) {
		std::string line;
		QPen drawPen(Qt::black);
		drawPen.setWidth(2);
		while (getline(in, line)) {
			std::stringstream ss(line);
			std::string chunk;
			ss >> chunk;
			if (chunk == "Rect") {
				int height, width, x, y;
				ss >> height >> width >> x >> y;
				QRectF rect(x, y, width, height);
				QGraphicsRectItem* r = m_canvas->scene()->addRect(rect, drawPen, QBrush(Qt::black));
				r->setFlag(QGraphicsItem::ItemIsSelectable, true);
				r->setFlag(QGraphicsItem::ItemIsMovable, true);
				r->setCursor(Qt::PointingHandCursor);
			} else if (chunk == "Circle") {
				int height, width, x, y;
				ss >> height >> width >> x >> y;
				QRectF rect(x, y, width, height);
				QGraphicsEllipseItem* r = m_canvas->scene()->addEllipse(rect, drawPen, QBrush(Qt::black));
				r->setFlag(QGraphicsItem::ItemIsSelectable, true);
				r->setFlag(QGraphicsItem::ItemIsMovable, true);
				r->setCursor(Qt::PointingHandCursor);
			} else if (chunk == "Line") {
				int x1, y1, x2, y2;
				ss >> x1 >> y1 >> x2 >> y2;
				QLineF line(x1, y1, x2, y2);
				QGraphicsLineItem* l = m_canvas->scene()->addLine(line, drawPen);
				l->setFlag(QGraphicsItem::ItemIsSelectable, true);
				l->setFlag(QGraphicsItem::ItemIsMovable, true);
				l->setCursor(Qt::PointingHandCursor);
			} else if (chunk == "Triangle") {
				int x1, y1, x2, y2, x3, y3;
				ss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
				QPolygonF poly;
				poly << QPointF(x1, y1) << QPointF(x2, y2) << QPointF(x3, y3);
				QGraphicsPolygonItem* p = m_canvas->scene()->addPolygon(poly, drawPen, QBrush(Qt::black));
				p->setFlag(QGraphicsItem::ItemIsSelectable, true);
				p->setFlag(QGraphicsItem::ItemIsMovable, true);
				p->setCursor(Qt::PointingHandCursor);
			}
		}
	} else {
		QMessageBox errormsg;
                errormsg.setWindowTitle("Error opening file");
                errormsg.setText("Could not open file. Make sure you didn't add a file extension.");
                errormsg.exec();
	}
	//filename 
}

void Window::print_file() //Michael Eddins
{
	bool ok; 
	
	QPainter myPainter;
	QString pdfname = QInputDialog::getText(this, tr("Print to PDF"), tr("Enter name to save PDF as:"), QLineEdit::Normal, "" , &ok); //Dialogue box for getting name to save PDF as.
	QPrinter printer(QPrinter::HighResolution); //Sets pdf as being a high resolution image
	printer.setOutputFormat(QPrinter::PdfFormat); //Ensures that QPrinter knows that it is a PDF
	printer.setOutputFileName(QDir::currentPath() + tr("/") + pdfname + tr(".pdf")); // Sets the pdf to be saved in the current directory as the previously submitted name.
	myPainter.begin(&printer);
	m_canvas->scene()->render(&myPainter); //Draw stuff
	myPainter.end();
}

void Window::new_file()
{
	QList<QGraphicsItem*> items = m_canvas->scene()->items();
	for (QGraphicsItem* i : items) {
		m_canvas->scene()->removeItem(i);
	} //Clears the old canvas.
}


