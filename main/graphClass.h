#ifndef GRAPHCLASS_H
#define GRAPHCLASS_H

#include <QVector>
#include <QPainter>
#include <QFile>
#include <QList>
#include <QTextStream>
#include <math.h>

enum eventDirection {
    rigth,
    left,
    up,
    down
};

class GraphClass {
    public:
        GraphClass();
        GraphClass(QVector<QVector<int>> points);

        bool readCVS(QString fileName);
        bool checkCorrectness();

        void draw(QPainter *p);
        void drawLine(int i, int j, QPainter *p);

    protected:
        QVector<QVector<int>> _points;
        QVector<QPoint>       _positions;

        int                   _count;
};

#endif // GRAPHCLASS_H
