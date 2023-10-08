


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
	float real{0.0};
	node* next = nullptr;
};

struct data
{
public:
	int x{ 0 }, y{ 0 }, z{0};
	float real = { 0.0 };
	
	data(int x, int y, int z, float real) :x(x), y(y), z(z), real(real) {};
	
	data() {};

    bool operator>(const data&right) const
	{
		return real > right.real;
	}
	
};
struct data_1 : public data
{
public:
	float total = { 0.0 };

	data_1(int x, int y, int z, float real, float total) :
		data(x, y, z, real), total(total) {}


	data_1() {};

	  bool operator>(const data_1& right) const
	{
		return total > right.total;
	}
};

struct data_2 :public data
{
public:
	float h = { 0.0 };

	data_2(int x, int y, int z, float real, float h) :
		data(x, y, z, real), h(h) {}

	data_2() {};

	bool operator>(const data_2& right) const
	{
		return h > right.h;
	}
};



template<class T>
	class A_00
	{
	public:

		A_00() 
		{
			QDir folder_data("Dane");
			file_path = folder_data.absolutePath();
			file_path = file_path + "//";

			files = folder_data.entryList(QDir::Files | QDir::NoDotAndDotDot);
			files.erase(files.begin());
		};

		~A_00() {};
		
		QRgb pixel_color;
		int x{ 0 }, y{ 0 }, z{ 0 };
		float real{ 0 };

		float h{ 0.0 };
		double deltax{ 0.0 }, deltay{ 0.0 }, deltaz{ 0.0 };
		int n{ 0 };

		QString result_path = "Result_1//Result_D";
		QString file_path = "Dane";
		
		QStringList files;
		node* aux = nullptr;
		node nodes[208][200][200];

		QImage* image = nullptr;

		std::priority_queue<T, std::vector<T>, std::greater<T>> nodes_queue;
		T begin;
		T end;

		virtual void Executive() {
			while (!(this->x == this->end.x && this->y == this->end.y && this->z == this->end.z))
				    {
				
				        if (this->nodes_queue.empty()) { return; }
				        this->x = nodes_queue.top().x;
				
				        this->y = nodes_queue.top().y;
				        this->z = nodes_queue.top().z;
				
				        this->real = nodes_queue.top().real;
				
				        this->nodes_queue.pop();

				        this->Nodes_calculation(0, 1, 0, 1.0);
				
				
				        this->Nodes_calculation(0, 0, 1, 1.0);
				
				
				        this->Nodes_calculation(0, -1, 0, 1.0);
				
				
				        this->Nodes_calculation(0, 0, -1, 1.0);
				
				
				        this->Nodes_calculation(0, 1, 1, 1.41);
				
				
				        this->Nodes_calculation(0, -1, -1, 1.41);
				
				
				        this->Nodes_calculation(0, 1, -1, 1.41);
				
				
				        this->Nodes_calculation(0, -1, 1, 1.41);
				
				
				        this->Nodes_calculation(1, 0, 0, 1.0);
				
				
				        this->Nodes_calculation(1, 1, 0, 1.41);
				
				
				        this->Nodes_calculation(1, 0, 1, 1.41);
				
				
				        this->Nodes_calculation(1, -1, 0, 1.41);
				
				
				        this->Nodes_calculation(1, 0, -1, 1.41);
				
				
				        this->Nodes_calculation(1, 1, 1, 1.41);
				
				
				        this->Nodes_calculation(1, -1, 1, 1.41);
				
				
				        this->Nodes_calculation(1, 1, -1, 1.41);
				
				
				        this->Nodes_calculation(1, -1, -1, 1.41);
				    }

			    this->aux = &this->nodes[this->end.z][this->end.x][this->end.y];
			
				while (this->aux->next)
				{
					this->image[this->aux->z].setPixel(this->aux->x, this->aux->y, 3);
					this->aux = this->aux->next;
				}


				for (int i = 0; i < 208; ++i) {
					for (int j = 0; j < 200; ++j) {
						for (int k = 0; k < 200; ++k) {
							nodes[i][j][k].next = nullptr;
						}
					}
				}
				

				//Czerwony
				
			
			    this->image[this->begin.z].setPixel(this->begin.x, this->begin.y, 4);
			    this->image[this->end.z].setPixel(this->end.x, this->end.y, 4);
			
			    if (!this->nodes_queue.empty())
			    {
			        for (size_t i = this->begin.z; i < n; i++)
			        {
			            //QString filename = QString("testy_%1.bmp").arg(i, 4, 10, QChar('0'));
			            this->image[i].save(this->result_path + "//" + QString("testy_%1.bmp").arg(i, 4, 10, QChar('0')));
			
			        }
			    }
			
			    qDebug() << "Koszt: " << this->nodes[this->end.z][this->end.x][this->end.y].real;

				while (!nodes_queue.empty()) {
					nodes_queue.pop();
				}

			    delete[] image;

		};
		virtual void Nodes_calculation(int z, int x, int y, float real) {};

		virtual bool reload(int* begin, int* end )
		{
			    this->end.x = end[0];
				this->end.y = end[1];
				this->end.z = end[2];

				//this->nodes[this->end.z][this->end.x][this->end.y].next = nullptr;
			
			    this->begin.x = begin[0];
			    this->begin.y = begin[1];
			    this->begin.z = begin[2];
			    
			        this->n = this->end.z + 1;
			
			        this->image = new QImage[this->n];

			        for (size_t i{ 0 }; i < this->n; i++)
			        {
			            this->image[i] = QImage(file_path + files[i]);
			
			            this->pixel_color = qRgb(0, 0, 0);
			            this->image[i].setColor(0, this->pixel_color);
			
			            //Bia³y
			            this->pixel_color = qRgb(255, 255, 255);
			            this->image[i].setColor(1, this->pixel_color);
			
			            //Niebieski
			            this->pixel_color = qRgb(0, 0, 255);
			            this->image[i].setColor(2, this->pixel_color);

						//Zielony
						this->pixel_color = qRgb(0, 255, 0);
						this->image[i].setColor(3, this->pixel_color);

			          
			        }

					QRgb value_begin = this->image[this->end.z].color(this->image[this->end.z].pixelIndex(this->end.x, this->end.y));
					QRgb value_end = this->image[this->begin.z].color(this->image[this->begin.z].pixelIndex(this->begin.x, this->begin.y));

					if (255 != qRed(value_begin) && 255 != qBlue(value_begin) && 255 != qGreen(value_begin)
						|| 255 != qRed(value_end) && 255 != qBlue(value_end) && 255 != qGreen(value_end))
					{
						//qDebug() << "Wprowadzono nieprawidlowe dane";
						delete[] image;
						this->nodes[this->end.z][this->end.x][this->end.y].real = -1.0;
						return false;
					}

					this->pixel_color = qRgb(255, 0, 0);
					this->image[this->begin.z].setColor(4, this->pixel_color);

			
					this->image[this->end.z].setColor(4, this->pixel_color);
			
			        this->image[this->begin.z].setPixel(this->begin.x, this->begin.y, 4);
			        this->begin.real = 0.0;
			        this->deltax = this->begin.x - this->end.x;
			        this->deltay = this->begin.y -this->end.y;
			        this->deltaz = this->begin.z - this->end.z;
			      
			        this->nodes_queue.push(this->begin);

					this->x = 0;
					this->y = 0;
					this->z = 0;
					this->real = 0;

					return true;
		}
	};

class A_01:public A_00<data>
{
public:
	A_01() :A_00() {};

	virtual void Nodes_calculation(int z, int x, int y, float real) override;
};

class A_02 :public A_00<data_1>
{
public:
	
	A_02() :A_00() {};
	virtual void Nodes_calculation(int z, int x, int y, float real) override;
};

class A_03 : public A_00<data_2>
{
public:

	A_03() :A_00() {};

	virtual void Nodes_calculation(int z, int x, int y, float real) override;
};