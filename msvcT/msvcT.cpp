// msvcT.cpp: 定义应用程序的入口点。
//
#include "msvcT.h"
#include <qrc_lib.h>
#include <QHboxLayout>
#include <QPixmap>

void initQRC() {
	Q_INIT_RESOURCE(qrc); // Initialize the resource system
	// Initialize QRC resources if needed
}

TestWidget::TestWidget(QWidget* parent) : QWidget(parent)
{
    resize(800, 600);
    initQRC();
	m_label = new QLabel(this);
	m_label->setText("Hello, World!");
	m_label->setFixedSize(this->size());
    
    QPixmap pixmap(QRC::LOGO_IMG); 
    m_label->setPixmap(pixmap);
    m_label->setScaledContents(true);
    m_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_label->setAlignment(Qt::AlignCenter); 
    
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_label);
    layout->setContentsMargins(0, 0, 0, 0);  // 去除边距
    setLayout(layout);
}
