#pragma once

#include <QImage>
#include <QRgb>
#include <queue>
#include <QDir>
#include <QString>

struct node
{
public:
	int x{ 0 }, y{ 0 }, z{ 0 };
	float real{ 0.0 };
	float distance{ 0.0 };
	node* next = nullptr;

	node(int x, int y, int z, float real, float distance) :x(x), y(y), z(z), real(real), distance(distance) {};

	node() {};

	bool operator>(const node& right) const
	{
		return distance > right.distance;
	}
};

class Algorithm_base
{
public:

	Algorithm_base()
	{
		QDir folder_data("Dane");
		file_path = folder_data.absolutePath();
		file_path = file_path + "//";

		files = folder_data.entryList(QDir::Files | QDir::NoDotAndDotDot);
		files.erase(files.begin());
	};

	~Algorithm_base() {};

	int choice_calculation{ 0 };
	QRgb pixel_color;
	node queue_top;

	float h{ 0.0 };
	double deltax{ 0.0 }, deltay{ 0.0 }, deltaz{ 0.0 };
	int images_number{ 0 };

	QString result_path = "Result_1";
	QString file_path = "Dane";

	QStringList files;
	node* auxiliary = nullptr;
	node nodes[208][200][200];

	QImage* images = nullptr;

	std::priority_queue<node, std::vector<node>, std::greater<node>> nodes_queue;
	node begin;
	node end;

	void Executive();
	virtual void Nodes_calculation(int dz, int dx, int dy, float dreal) {};
	bool Reload(int* begin, int* end);
};

class Algorithm_dijkstra :public Algorithm_base
{
public:
	Algorithm_dijkstra() :Algorithm_base() {};

	virtual void Nodes_calculation(int dz, int dx, int dy, float dreal) override;
};

class Algorithm_total :public Algorithm_base
{
public:

	Algorithm_total() :Algorithm_base() {};
	virtual void Nodes_calculation(int dz, int dx, int dy, float dreal) override;
};

class Algorithm_euclidean : public Algorithm_base
{
public:

	Algorithm_euclidean() :Algorithm_base() {};

	virtual void Nodes_calculation(int dz, int dx, int dy, float dreal) override;
};