#pragma once

#include <QImage>
#include <QRgb>
#include <queue>
#include <QDir>
#include <QString>
#include <list>
#include <array>
#include <algorithm>

struct node
{
public:
	int x{ 0 }, y{ 0 }, z{ 0 };
	float real{ 0.0 };
	float distance{ 0.0 };
	bool white = false;
	bool blue = false;
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

	Algorithm_base(int current_search_type = 0);
	
	~Algorithm_base() ;

	int choice_calculation{ 0 };
	QRgb pixel_color;
	node queue_top;

	float heuristics{ 0.0 };
	float deltax{ 0.0 }, deltay{ 0.0 }, deltaz{ 0.0 };
	int images_number{ 0 };
	int width, height;

	unsigned long int NumberOfVisitedNodes{ 0 };

	QString result_path = "Result_1";
	QString file_path = "Dane";

	QStringList files;
	node* auxiliary = nullptr;
	node *** nodes;


	QImage* images = nullptr;

	std::priority_queue<node, std::deque<node>, std::greater<node>> nodes_queue; // to do testów jeszcze z t¹ kolejk¹ 
	node begin;
	node end;

	void(Algorithm_base::* Search_type)(int& z, int& x, int& y, float& real);
	void Executive();
	void Nodes_calculation(int dz, int dx, int dy, float dreal);

	void CalculationForForZEqualsZero(int deltaz);
	void CalculationForZUpAndDownValue(int deltaz);

	void Searching_for_real_value(int& z, int& x, int& y, float& real); // Dijkstra algorithm - real
	void Searching_for_total_value(int& z, int& x, int& y, float& real); // A* algorithm - euclidean + real
	void Searching_for_euclidean_value(int& z, int& x, int& y, float& real); // A* algorithm - euclidean
	bool Reload(int* begin, int* end);
	
};