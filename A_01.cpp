#include "A_01.h"

//A_01::A_01(int *start, int* docelowy): A_00()
//{
//
//    QDir folder("E://Inzynierka//Dane");
//    QString path = folder.absolutePath();
//   
//    path = path + "//";
//
//    QStringList files = folder.entryList(QDir::Files | QDir::NoDotAndDotDot);
//    files.erase(files.begin());
//
//    
//    this->docelowy.x = docelowy[0];
//    this->docelowy.y = docelowy[1];
//    this->docelowy.z = docelowy[2];
//
//    this->start.x = start[0];
//    this->start.y = start[1];
//    this->start.z = start[2];
//    
//        this->n = this->docelowy.z + 1;
//
//        this->image = new QImage[this->n];
//
//        for (size_t i{ 0 }; i < this->n; i++)
//        {
//
//            this->image[i] = QImage(path + files[i]);
//
//            this->pixel_color = qRgb(0, 0, 0);
//            this->image[i].setColor(0, this->pixel_color);
//
//            //Bia³y
//            this->pixel_color = qRgb(255, 255, 255);
//            this->image[i].setColor(1, this->pixel_color);
//
//            //Niebieski
//            this->pixel_color = qRgb(0, 0, 255);
//            this->image[i].setColor(2, this->pixel_color);
//
//            //Zielony
//            this->pixel_color = qRgb(0, 255, 0);
//            this->image[i].setColor(3, this->pixel_color);
//
//            //Czerwony
//            this->pixel_color = qRgb(255, 0, 0);
//            this->image[i].setColor(4, this->pixel_color);
//
//        }
//
//        QRgb value_begin = this->image[this->docelowy.z].color(this->image[this->docelowy.z].pixelIndex(this->docelowy.x, this->docelowy.y));
//        QRgb value_end = this->image[this->start.z].color(this->image[this->start.z].pixelIndex(this->start.x, this->start.y));
//
//        if (255 != qRed(value_begin) && 255 != qBlue(value_begin) && 255 != qGreen(value_begin)
//            || 255 != qRed(value_end) && 255 != qBlue(value_end) && 255 != qGreen(value_end))
//        {
//            //qDebug() << "Wprowadzono nieprawidlowe dane";
//            this->nodes[this->docelowy.z][this->docelowy.x][this->docelowy.y].real = -1.0;
//            return;
//        }
//
//
//        this->image[this->start.z].setPixel(this->start.x, this->start.y, 4);
//        this->start.real = 0.0;
//        this->deltax = this->start.x - this->docelowy.x;
//        this-> deltay = this->start.y - this->docelowy.y;
//        this->deltaz = this->start.z - this->docelowy.z;
//      
//
//        this->kolejka.push(this->start);
//}

void A_01::Nodes_calculation(int z ,int x, int y, float real)
{
    x = this->x + x;
    y = this->y + y;
    z = this->z + z;
    real = this->real + real;

    if (x >= 0 && x <= 199 && y >= 0 && y <= 199 && z < this->n)
    {
        this->pixel_color = this->image[z].color(this->image[z].pixelIndex(x, y));
       
        if (255 == qRed(this->pixel_color) && 255 == qGreen(this->pixel_color) && 255 == qBlue(this->pixel_color))
        {
            /*this->deltax = x - this->end.x;
            this->deltay = y - this->end.y;
            this->deltaz = z - this->end.z;*/
            this->nodes[z][x][y].x = this->x;
            this->nodes[z][x][y].y = this->y;
            this->nodes[z][x][y].z = this->z;
            this->nodes[z][x][y].real = real;

            //this->h = std::sqrt((this->deltax * this->deltax) + (this->deltay * this->deltay) + (this->deltaz * this->deltaz));
            this->image[z].setPixel(x, y, 2);
            this->nodes[z][x][y].next = &this->nodes[this->z][this->x][this->y];


            this->nodes_queue.push(data(x, y, z, real));
        }
     
    }
}

//A_01::~A_01()
//{
//    this->pom = &this->nodes[this->docelowy.z][this->docelowy.x][this->docelowy.y];
//
//    while (this->pom->next)
//    {
//        this->image[this->pom->z].setPixel(this->pom->x, this->pom->y, 3);
//        this->pom = pom->next;
//    }
//
//
//    this->image[this->start.z].setPixel(this->start.x, this->start.y, 4);
//    this->image[this->docelowy.z].setPixel(this->docelowy.x, this->docelowy.y, 4);
//
//
//    if (!this->kolejka.empty())
//    {
//        for (size_t i = 0; i < n; i++)
//        {
//            //QString filename = QString("testy_%1.bmp").arg(i, 4, 10, QChar('0'));
//            this->image[i].save(this->wyniki + "//" + QString("testy_%1.bmp").arg(i, 4, 10, QChar('0')));
//
//        }
//    }
//
//    qDebug() << "Koszt: " << this->nodes[this->docelowy.z][this->docelowy.x][this->docelowy.y].real;
//
//    delete[] image;
//}

//#############################################################

void A_02::Nodes_calculation(int z, int x, int y, float real)
{
    x = this->x + x;
    y = this->y + y;
    z = this->z + z;
    real = this->real + real;

    if (x >= 0 && x <= 199 && y >= 0 && y <= 199 && z < this->n)
    {
        this->pixel_color = this->image[z].color(this->image[z].pixelIndex(x, y));

        if (255 == qRed(this->pixel_color) && 255 == qGreen(this->pixel_color) && 255 == qBlue(this->pixel_color))
        {
            this->deltax = x - this->end.x;
            this->deltay = y - this->end.y;
            this->deltaz = z - this->end.z;
            this->nodes[z][x][y].x = this->x;
            this->nodes[z][x][y].y = this->y;
            this->nodes[z][x][y].z = this->z;
            this->nodes[z][x][y].real = real;

            this->h = std::sqrt((this->deltax * this->deltax) + (this->deltay * this->deltay) + (this->deltaz * this->deltaz));
            this->image[z].setPixel(x, y, 2);
            this->nodes[z][x][y].next = &this->nodes[this->z][this->x][this->y];


            this->nodes_queue.push(data_1(x, y, z, real, (h+real)));
        }

    }
}

//#############################################################
void A_03::Nodes_calculation(int z, int x, int y, float real)
{
    x = this->x + x;
    y = this->y + y;
    z = this->z + z;
    real = this->real + real;


    if (x >= 0 && x <= 199 && y >= 0 && y <= 199 && z < this->n)
    {
        this->pixel_color = this->image[z].color(this->image[z].pixelIndex(x, y));

        if (255 == qRed(this->pixel_color) && 255 == qGreen(this->pixel_color) && 255 == qBlue(this->pixel_color))
        {
            this->deltax = x - this->end.x;
            this->deltay = y - this->end.y;
            this->deltaz = z - this->end.z;
            this->nodes[z][x][y].x = this->x;
            this->nodes[z][x][y].y = this->y;
            this->nodes[z][x][y].z = this->z;
            this->nodes[z][x][y].real = real;

            this->h = std::sqrt((this->deltax * this->deltax) + (this->deltay * this->deltay) + (this->deltaz * this->deltaz));
            this->image[z].setPixel(x, y, 2);
            this->nodes[z][x][y].next = &this->nodes[this->z][this->x][this->y];

            this->nodes_queue.push(data_2(x, y, z, real, h));
        }

    }
}