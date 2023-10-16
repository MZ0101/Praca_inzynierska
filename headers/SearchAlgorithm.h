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

	Algorithm_base(int current_alhorithm = 0)
	{
		QDir folder_data("Dane");
		this->file_path = folder_data.absolutePath();
		this->file_path = file_path + "//";

		this->files = folder_data.entryList(QDir::Files | QDir::NoDotAndDotDot);
		this->files.erase(files.begin());

		if (current_alhorithm == 0) Nodes_claculation = &Algorithm_base::Nodes_calculation_dijkstra;
		else if (current_alhorithm == 1) Nodes_claculation = &Algorithm_base::Nodes_calculation_total;
		else if (current_alhorithm == 2) Nodes_claculation = &Algorithm_base::Nodes_calculation_euclidean;
	};

	~Algorithm_base() {};

	int choice_calculation{ 0 };
	QRgb pixel_color;
	node queue_top;

	float heuristics{ 0.0 };
	float deltax{ 0.0 }, deltay{ 0.0 }, deltaz{ 0.0 };
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

	void(Algorithm_base::* Nodes_claculation)(int dz, int dx, int dy, float dreal);
	void Executive();
	void Nodes_calculation_dijkstra(int dz, int dx, int dy, float dreal);
	void Nodes_calculation_total(int dz, int dx, int dy, float dreal);
	void Nodes_calculation_euclidean(int dz, int dx, int dy, float dreal);
	bool Reload(int* begin, int* end);
	
};