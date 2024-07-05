#include "graphClass.h"

GraphClass::GraphClass(QVector<QVector<int>> points) :
    _points(points)
    , _count(points.length())
{
    if (!checkCorrectness()) {
        _points = QVector<QVector<int>>(0);
        _count = 0;
    }
}

GraphClass::GraphClass() {
    _points = QVector<QVector<int>>(0);
    _count = 0;
}

bool GraphClass::readCVS(QString fileName) {
    if (!_points.empty())
        _points.clear();

    QFile* file = new QFile("../l6/" + fileName);

    if (!file->open(QIODevice::ReadOnly))
        return false;

    QTextStream in(file);
    while (!in.atEnd()) {
        QStringList elems = in.readLine().split(",");
        QVector<int> line;

        for (int i = 0; i < elems.size(); ++i)
            line.push_back(elems[i].toInt());

        _points.push_back(line);
    }
    file->close();
    _count = _points.length();
    for (int i = 0; i < _count; i++)
        _positions.push_back(QPoint(0,0));

    return true;
}

bool GraphClass::checkCorrectness() {
    if(_count == 0)
        return false;

    for(QVector<int> line : _points)
        if (line.length() != 4)
            return false;

    return true;
}

void GraphClass::draw(QPainter *p) {
    if (!checkCorrectness())
        return;

    p->setPen(QPen(Qt::black,3));
    p->setBrush(QBrush(Qt::green));

    double f = 2.0 / _count * M_PI;
    for(int i = 0; i < _count; i++) {
        _positions[i] = QPoint(735 + 300 * sin(f*i), 400 + 300 * cos(f*i));
        p->drawEllipse(_positions[i].x() - 25, _positions[i].y() - 25, 50, 50);
        p->drawText(_positions[i].x(), _positions[i].y(), QString().number(i + 1));
    }

    for(int i = 0; i < _points.length(); i++)
        for(int j = 0; j < _points[i].length(); j++)
            if(_points[i][j] != 0)
                drawLine(i,j,p);
}

void GraphClass::drawLine(int i, int j, QPainter *p) {
    int x2 = _positions[_points[i][j] - 1].x();
    int x1 = _positions[i].x();
    int y2 = _positions[_points[i][j] - 1].y();
    int y1 = _positions[i].y();

    int x = x2 - x1;
    int y = y2 - y1;

    double dx = x/sqrt(x*x + y*y)*25;
    double dy = y/sqrt(x*x + y*y)*25;
    x1 += dx;
    y1 += dy;
    x2 -= dx;
    y2 -= dy;

    double alpha = atan2(y2 - y1, x2 - x1) + M_PI;
    double arrowLenght = 20;
    double arrowAngle = 0.5;
    double f1x21 = x2 + arrowLenght * cos(alpha - arrowAngle);
    double f1y21 = y2 + arrowLenght * sin(alpha - arrowAngle);
    double f1x22 = x2 + arrowLenght * cos(alpha + arrowAngle);
    double f1y22 = y2 + arrowLenght * sin(alpha + arrowAngle);
    double dirx = x2 + arrowLenght * 2 * cos(alpha - arrowAngle);
    double diry = y2 + arrowLenght * 2 * sin(alpha - arrowAngle);

    p->drawLine(QPoint(x1,y1), QPoint(x2,y2));
    p->drawLine(QPoint(x2,y2), QPoint(f1x21,f1y21));
    p->drawLine(QPoint(x2,y2), QPoint(f1x22,f1y22));

    p->setPen(QPen(Qt::red));
    switch (j) {
    case eventDirection::rigth:
        p->drawText(dirx, diry, "-->");
        break;
    case eventDirection::left:
        p->drawText(dirx, diry, "<--");
        break;
    case eventDirection::up:
        p->drawText(dirx, diry, "^");
        p->drawText(dirx + 3, diry + 5, "|");
        break;
    case eventDirection::down:
        p->drawText(dirx + 2, diry - 7, "|");
        p->drawText(dirx, diry, "V");
        break;
    }
    p->setPen(QPen(Qt::black,3));
}
