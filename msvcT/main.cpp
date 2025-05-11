#include "msvcT.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	TestWidget w; // Ensure TestWidget is instantiated correctly
	w.show();     // Ensure TestWidget inherits from QWidget or a derived class
	return QApplication::exec();
}
