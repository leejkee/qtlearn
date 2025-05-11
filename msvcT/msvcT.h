// msvcT.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <QWidget>
#include <QLabel>
#include <QApplication>

class TestWidget final : public QWidget {
public:
	TestWidget(QWidget* parent = nullptr);
	~TestWidget() override = default;
private:

	QLabel* m_label;

};
