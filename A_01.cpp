﻿#include "A_01.h"

bool A_00::Reload(int* begin, int* end)
{
	this->end.x = end[0];
	this->end.y = end[1];
	this->end.z = end[2];

	this->begin.x = begin[0];
	this->begin.y = begin[1];
	this->begin.z = begin[2];
	this->images_number = this->end.z + 1;

	this->images = new QImage[this->images_number];

	for (size_t i{ 0 }; i < this->images_number; i++)
	{
		this->images[i] = QImage(file_path + files[i]);

		this->pixel_color = qRgb(0, 0, 0);
		this->images[i].setColor(0, this->pixel_color);

		//Bia³y
		this->pixel_color = qRgb(255, 255, 255);
		this->images[i].setColor(1, this->pixel_color);

		//Niebieski
		this->pixel_color = qRgb(0, 0, 255);
		this->images[i].setColor(2, this->pixel_color);

		//Zielony
		this->pixel_color = qRgb(0, 255, 0);
		this->images[i].setColor(3, this->pixel_color);
	}

	QRgb value_begin = this->images[this->end.z].color(this->images[this->end.z].pixelIndex(this->end.x, this->end.y));
	QRgb value_end = this->images[this->begin.z].color(this->images[this->begin.z].pixelIndex(this->begin.x, this->begin.y));

	if (255 != qRed(value_begin) && 255 != qBlue(value_begin) && 255 != qGreen(value_begin)
		|| 255 != qRed(value_end) && 255 != qBlue(value_end) && 255 != qGreen(value_end))
	{
		//qDebug() << "Wprowadzono nieprawidlowe dane";
		delete[] images;
		this->nodes[this->end.z][this->end.x][this->end.y].real = -1.0;
		return false;
	}

	this->pixel_color = qRgb(255, 0, 0);
	this->images[this->begin.z].setColor(4, this->pixel_color);

	this->images[this->end.z].setColor(4, this->pixel_color);

	this->images[this->begin.z].setPixel(this->begin.x, this->begin.y, 4);
	this->begin.real = 0.0;
	this->deltax = this->begin.x - this->end.x;
	this->deltay = this->begin.y - this->end.y;
	this->deltaz = this->begin.z - this->end.z;

	this->queue_top.x = 0;
	this->queue_top.y = 0;
	this->queue_top.z = 0;

	this->nodes_queue.push(this->begin);
	return true;
}

void A_00::Executive() {
	while (!(this->queue_top.x == this->end.x && this->queue_top.y == this->end.y && this->queue_top.z == this->end.z))
	{
		if (this->nodes_queue.empty()) { return; }
		this->queue_top.x = nodes_queue.top().x;

		this->queue_top.y = nodes_queue.top().y;
		this->queue_top.z = nodes_queue.top().z;

		this->queue_top.real = nodes_queue.top().real;
		this->nodes_queue.pop();

		for (int i{ 0 }; i < 2; i++)
		{
			this->Nodes_calculation(i, 1, 0, 1.0);


			this->Nodes_calculation(i, 0, 1, 1.0);


			this->Nodes_calculation(i, -1, 0, 1.0);


			this->Nodes_calculation(i, 0, -1, 1.0);


			this->Nodes_calculation(i, 1, 1, 1.41);


			this->Nodes_calculation(i, -1, -1, 1.41);


			this->Nodes_calculation(i, 1, -1, 1.41);


			this->Nodes_calculation(i, -1, 1, 1.41);
		}
		this->Nodes_calculation(1, 0, 0, 1.0);

	}

	this->auxiliary = &this->nodes[this->end.z][this->end.x][this->end.y];

	while (this->auxiliary->next)
	{
		this->images[this->auxiliary->z].setPixel(this->auxiliary->x, this->auxiliary->y, 3);
		this->auxiliary = this->auxiliary->next;
	}

	for (int i = 0; i < 208; ++i) {
		for (int j = 0; j < 200; ++j) {
			for (int k = 0; k < 200; ++k) {
				nodes[i][j][k].next = nullptr;
			}
		}
	}

	//Czerwony

	this->images[this->begin.z].setPixel(this->begin.x, this->begin.y, 4);
	this->images[this->end.z].setPixel(this->end.x, this->end.y, 4);

	if (!this->nodes_queue.empty())
	{
		for (size_t i = this->begin.z; i < images_number; i++)
		{
			QString filename = QString("testy_%1.bmp").arg(i, 4, 10, QChar('0'));
			this->images[i].save(this->result_path + "//" + QString("testy_%1.bmp").arg(i, 4, 10, QChar('0')));

		}
	}

	qDebug() << "Koszt: " << this->nodes[this->end.z][this->end.x][this->end.y].real;

	while (!nodes_queue.empty()) {
		nodes_queue.pop();
	}

	delete[] images;
};

void A_01::Nodes_calculation(int dz, int dx, int dy, float dreal)
{
	int x = this->queue_top.x + dx;
	int y = this->queue_top.y + dy;
	int z = this->queue_top.z + dz;
	float real = this->queue_top.real + dreal;

	if (x >= 0 && x <= 199 && y >= 0 && y <= 199 && z < this->images_number)
	{
		this->pixel_color = this->images[z].color(this->images[z].pixelIndex(x, y));

		if (255 == qRed(this->pixel_color) && 255 == qGreen(this->pixel_color) && 255 == qBlue(this->pixel_color))
		{

			this->nodes[z][x][y].x = this->queue_top.x;
			this->nodes[z][x][y].y = this->queue_top.y;
			this->nodes[z][x][y].z = this->queue_top.z;
			this->nodes[z][x][y].real = real;
			this->images[z].setPixel(x, y, 2);
			this->nodes[z][x][y].next = &this->nodes[this->queue_top.z][this->queue_top.x][this->queue_top.y];

			this->nodes_queue.push(node(x, y, z, real, real));
		}
	}
}

//#############################################################

void A_02::Nodes_calculation(int dz, int dx, int dy, float dreal)
{
	int x = this->queue_top.x + dx;
	int y = this->queue_top.y + dy;
	int z = this->queue_top.z + dz;
	float real = this->queue_top.real + dreal;

	if (x >= 0 && x <= 199 && y >= 0 && y <= 199 && z < this->images_number)
	{
		this->pixel_color = this->images[z].color(this->images[z].pixelIndex(x, y));

		if (255 == qRed(this->pixel_color) && 255 == qGreen(this->pixel_color) && 255 == qBlue(this->pixel_color))
		{
			this->deltax = x - this->end.x;
			this->deltay = y - this->end.y;
			this->deltaz = z - this->end.z;
			this->nodes[z][x][y].x = this->queue_top.x;
			this->nodes[z][x][y].y = this->queue_top.y;
			this->nodes[z][x][y].z = this->queue_top.z;
			this->nodes[z][x][y].real = real;

			this->h = std::sqrt((this->deltax * this->deltax) + (this->deltay * this->deltay) + (this->deltaz * this->deltaz));
			this->images[z].setPixel(x, y, 2);
			this->nodes[z][x][y].next = &this->nodes[this->queue_top.z][this->queue_top.x][this->queue_top.y];


			this->nodes_queue.push(node(x, y, z, real, (h + real)));
		}
	}
}

//#############################################################
void A_03::Nodes_calculation(int dz, int dx, int dy, float dreal)
{
	int x = this->queue_top.x + dx;
	int y = this->queue_top.y + dy;
	int z = this->queue_top.z + dz;
	float real = this->queue_top.real + dreal;

	if (x >= 0 && x <= 199 && y >= 0 && y <= 199 && z < this->images_number)
	{
		this->pixel_color = this->images[z].color(this->images[z].pixelIndex(x, y));

		if (255 == qRed(this->pixel_color) && 255 == qGreen(this->pixel_color) && 255 == qBlue(this->pixel_color))
		{
			this->deltax = x - this->end.x;
			this->deltay = y - this->end.y;
			this->deltaz = z - this->end.z;
			this->nodes[z][x][y].x = this->queue_top.x;
			this->nodes[z][x][y].y = this->queue_top.y;
			this->nodes[z][x][y].z = this->queue_top.z;
			this->nodes[z][x][y].real = real;

			this->h = std::sqrt((this->deltax * this->deltax) + (this->deltay * this->deltay) + (this->deltaz * this->deltaz));
			this->images[z].setPixel(x, y, 2);
			this->nodes[z][x][y].next = &this->nodes[this->queue_top.z][this->queue_top.x][this->queue_top.y];

			this->nodes_queue.push(node(x, y, z, real, h));
		}

	}
}