#ifndef EVENTGRAPH_H
#define EVENTGRAPH_H

#include "graphClass.h"

class GraphClass;

class eventGraph : public GraphClass {
    public:
        eventGraph(QVector<QVector<int> > points);
        eventGraph();

        void draw(QPainter *p);

        void changeActive(eventDirection direction);
        void changeActive();
        void changeMousePositionNode(QPoint &mosePosition);

    private:
        int _active;
        int _mousePositionNode;
};

#endif // EVENTGRAPH_H
