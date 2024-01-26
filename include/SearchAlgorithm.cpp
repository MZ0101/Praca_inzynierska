#include "SearchAlgorithm.h"

Algorithm_base::Algorithm_base(int current_search_type)
{
	//QDir folder_data("C:\\Users\\mateu\\Downloads\\3values");
	QDir folder_data("Dane");
	this->file_path = folder_data.absolutePath();
	this->file_path = file_path + "//";

	this->files = folder_data.entryList(QDir::Files | QDir::NoDotAndDotDot);
	//this->files.erase(files.begin());

	if (current_search_type == 0) Search_type = &Algorithm_base::Searching_for_real_value;
	else if (current_search_type == 1) Search_type = &Algorithm_base::Searching_for_total_value;
	else if (current_search_type == 2) Search_type = &Algorithm_base::Searching_for_euclidean_value;

	int depth = files.size();
	this->nodes = new node **[depth];
	QImage image = QImage(this->file_path + this->files[0]);

	this->width = image.width();
	this->height = image.height();


	for (int z = 0; z < depth; z++)
	{
		this->nodes[z] = new node * [this->width];

		for (int x = 0; x < this->width; x++) 
		{
			this->nodes[z][x] = new node[this->height];
		}
	}


	};


bool Algorithm_base::Reload(int* begin, int* end)
{
	this->end.x = end[0];
	this->end.y = end[1];
	this->end.z = end[2];

	this->begin.x = begin[0];
	this->begin.y = begin[1];
	this->begin.z = begin[2];

	this->NumberOfVisitedNodes = 0;

	this->images_number = files.size();

	this->images = new QImage[this->images_number]; 


	for (size_t z{ 0 }; z < this->images_number; z++)
	{
		this->images[z] = QImage(this->file_path + this->files[z]);
		for (size_t x{ 0 }; x < this->width; x++)
		{
			for (size_t y{ 0 }; y < this->height; y++)
			{
				this->pixel_color = this->images[z].color(this->images[z].pixelIndex(x, y));
				if (255 == qRed(this->pixel_color) && 255 == qGreen(this->pixel_color) && 255 == qBlue(this->pixel_color))
				{
					this->nodes[z][x][y].white = true;
				}
			}
		}
		//Niebieski
		this->pixel_color = qRgb(0, 0, 255);
		this->images[z].setColor(6, this->pixel_color);

		////Zielony
		this->pixel_color = qRgb(0, 255, 0);
		this->images[z].setColor(7, this->pixel_color);
	}

	if (!this->nodes[this->begin.z][this->begin.x][this->begin.y].white || !this->nodes[this->end.z][this->end.x][this->end.y].white)
	{
		delete[] images;
		this->nodes[this->end.z][this->end.x][this->end.y].real = -1.0;
		return false;
	}

	this->pixel_color = qRgb(255, 0, 0);
	this->images[this->begin.z].setColor(8, this->pixel_color);
	this->images[this->end.z].setColor(8, this->pixel_color);

	this->nodes[this->begin.z][this->begin.x][this->begin.y].white = false;
	this->begin.real = 0.0;

	this->deltax = this->begin.x - this->end.x;
	this->deltay = this->begin.y - this->end.y;
	this->deltaz = this->begin.z - this->end.z;

	this->nodes_queue.push(this->begin);


	return true;
}

void Algorithm_base::Executive() {
	while (!(this->queue_top.x == this->end.x && this->queue_top.y == this->end.y && this->queue_top.z == this->end.z))
	{
		if (this->nodes_queue.empty())
		{

			return;
		}

		this->queue_top.x = nodes_queue.top().x;
		this->queue_top.y = nodes_queue.top().y;
		this->queue_top.z = nodes_queue.top().z;

		this->queue_top.real = nodes_queue.top().real;
		this->nodes_queue.pop();

		this->CalculationForForZEqualsZero(0);
		this->CalculationForZUpAndDownValue(1);
		this->CalculationForZUpAndDownValue(-1);

	}

	this->auxiliary = &this->nodes[this->end.z][this->end.x][this->end.y];

	int z_max{ 0 };
	int z_min = this->begin.z > this->end.z ? this->end.z : this->begin.z;


	while (this->auxiliary->next)
	{
		this->images[this->auxiliary->z].setPixel(this->auxiliary->x, this->auxiliary->y, 7);
		this->nodes[this->auxiliary->z][this->auxiliary->x][this->auxiliary->y].blue = false;
		z_max = this->auxiliary->z > z_max ? this->auxiliary->z : z_max;
		z_min = this->auxiliary->z < z_min ? this->auxiliary->z : z_min;
		this->auxiliary = this->auxiliary->next;
	}

	for (size_t z = 0; z < this->images_number; z++) {
		for (size_t x = 0; x < this->width; x++) {
			for (size_t y = 0; y < this->height; y++) {
				this->nodes[z][x][y].next = nullptr;
				if (this->nodes[z][x][y].blue) this->images[z].setPixel(x, y, 6);

				this->nodes[z][x][y].blue = false;
			}
		}
	}

	//Czerwony
	this->images[this->begin.z].setPixel(this->begin.x, this->begin.y, 8);
	this->images[this->end.z].setPixel(this->end.x, this->end.y, 8);

	if (z_max < end.z) z_max = end.z;

	for (size_t i = z_min; i <= z_max; i++)
	{
		
		QString filename = QString("Image_%1.bmp").arg(i, 4, 10, QChar('0'));

		images[i].save(this->result_path + "//" + QString("Image_%1.bmp").arg(i, 4, 10, QChar('0')));

	}
	qDebug() << "Koszt: " << this->nodes[this->end.z][this->end.x][this->end.y].real ;

	while (!nodes_queue.empty()) {
		nodes_queue.pop();
	}

	delete[] images;
};
void Algorithm_base::CalculationForForZEqualsZero(int deltaz) {

	this->Nodes_calculation(deltaz, 1, 0, 1.0);


	this->Nodes_calculation(deltaz, 0, 1, 1.0);


	this->Nodes_calculation(deltaz, -1, 0, 1.0);


	this->Nodes_calculation(deltaz, 0, -1, 1.0);


	this->Nodes_calculation(deltaz, 1, 1, 1.41);


	this->Nodes_calculation(deltaz, -1, -1, 1.41);


	this->Nodes_calculation(deltaz, 1, -1, 1.41);


	this->Nodes_calculation(deltaz, -1, 1, 1.41);
}

void Algorithm_base::CalculationForZUpAndDownValue(int deltaz) {
	this->Nodes_calculation(deltaz, 1, 0, 1.41);


	this->Nodes_calculation(deltaz, 0, 1, 1.41);


	this->Nodes_calculation(deltaz, -1, 0, 1.41);


	this->Nodes_calculation(deltaz, 0, -1, 1.41);


	this->Nodes_calculation(deltaz, 1, 1, 1.73);


	this->Nodes_calculation(deltaz, -1, -1, 1.73);


	this->Nodes_calculation(deltaz, 1, -1, 1.73);


	this->Nodes_calculation(deltaz, -1, 1, 1.73);

	this->Nodes_calculation(deltaz, 0, 0, 1.0);
}

void Algorithm_base::Nodes_calculation(int dz, int dx, int dy, float dreal)
{
	int x = this->queue_top.x + dx;
	int y = this->queue_top.y + dy;
	int z = this->queue_top.z + dz;
	float real = this->queue_top.real + dreal;

	if (x >= 0 && x < this->width && y >= 0 && y < this->height && z >= 0 && z < this->images_number)
	{

		if (this->nodes[z][x][y].white)
		{
			this->nodes[z][x][y].x = this->queue_top.x;
			this->nodes[z][x][y].y = this->queue_top.y;
			this->nodes[z][x][y].z = this->queue_top.z;
			this->nodes[z][x][y].real = real;
			this->nodes[z][x][y].blue = true;
			this->nodes[z][x][y].white = false;
			this->nodes[z][x][y].next = &this->nodes[this->queue_top.z][this->queue_top.x][this->queue_top.y];

			this->NumberOfVisitedNodes++;

			(this->*Search_type)(z, x, y, real);
		}
		else if (this->nodes[z][x][y].blue)
		{
			if (real < this->nodes[z][x][y].real)
			{
				this->nodes[z][x][y].x = this->queue_top.x;
				this->nodes[z][x][y].y = this->queue_top.y;
				this->nodes[z][x][y].z = this->queue_top.z;
				this->nodes[z][x][y].real = real;

				this->nodes[z][x][y].next = &this->nodes[this->queue_top.z][this->queue_top.x][this->queue_top.y];

				(this->*Search_type)(z, x, y, real);
			}

		}
	}
}

void  Algorithm_base::Searching_for_real_value(int &z, int &x, int &y, float &real)
{
	this->nodes_queue.push(node(x, y, z, real, real));
}

void  Algorithm_base::Searching_for_total_value(int& z, int& x, int& y, float& real)
{
	this->deltax = x - this->end.x;
	this->deltay = y - this->end.y;
	this->deltaz = z - this->end.z;
	this->heuristics = std::sqrt((this->deltax * this->deltax) + (this->deltay * this->deltay) + (this->deltaz * this->deltaz));

	this->nodes_queue.push(node(x, y, z, real, (heuristics + real)));
}

void  Algorithm_base::Searching_for_euclidean_value(int& z, int& x, int& y, float& real)
{
	this->deltax = x - this->end.x;
	this->deltay = y - this->end.y;
	this->deltaz = z - this->end.z;
	this->heuristics = std::sqrt((this->deltax * this->deltax) + (this->deltay * this->deltay) + (this->deltaz * this->deltaz));
	this->nodes_queue.push(node(x, y, z, real, heuristics ));
}

Algorithm_base::~Algorithm_base()
{
	for (int z = 0; z < this->images_number; ++z) 
	{
		for (int x = 0; x < this->width; ++x) 
		{
			delete[] nodes[z][x];
		}
		delete[] nodes[z];
	}
	delete[] nodes;
}