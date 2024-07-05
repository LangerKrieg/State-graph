#include "eventGraph.h"

eventGraph::eventGraph(QVector<QVector<int>> points) :
    GraphClass(points)
  , _active(0)
  , _mousePositionNode(-1)
{
}

eventGraph::eventGraph() :
    GraphClass()
  , _active(0)
  , _mousePositionNode(-1)
{
}

void eventGraph::draw(QPainter *p) {
    GraphClass::draw(p);
    p->setBrush(QBrush(Qt::red));
    double f = 2.0 / _count * M_PI;
    QPoint position = QPoint(735 + 300 * sin(f*_active), 400 + 300 * cos(f*_active));
    p->drawEllipse(position.x() - 25, position.y() - 25, 50, 50);
    p->drawText(position.x(), position.y(), QString().number(_active + 1));

    if (_mousePositionNode != -1) {
        p->setBrush(QBrush(Qt::gray));
        position = QPoint(735 + 300 * sin(f*_mousePositionNode), 400 + 300 * cos(f*_mousePositionNode));
        p->drawEllipse(position.x() - 25, position.y() - 25, 50, 50);
        p->drawText(position.x(), position.y(), QString().number(_mousePositionNode + 1));
    }
}

void eventGraph::changeActive(eventDirection direction) {
    if (_points.length() == 0)
        return;

    switch (int(direction)) {
        case eventDirection::rigth:
            if (_points[_active][0] != 0)
                _active = _points[_active][0] - 1;

            break;
        case eventDirection::left:
            if (_points[_active][1] != 0)
                _active = _points[_active][1] - 1;

            break;
        case eventDirection::up:
            if (_points[_active][2] != 0)
                _active = _points[_active][2] - 1;

            break;
        case eventDirection::down:
            if (_points[_active][3] != 0)
                _active = _points[_active][3] - 1;

            break;
    }
}

void eventGraph::changeActive() {
    if (_mousePositionNode == -1)
        return;

    _active            = _mousePositionNode;
    _mousePositionNode = -1;
}

void eventGraph::changeMousePositionNode(QPoint &mosePosition) {
    for(int i = 0; i < _positions.length(); i++) {
        QPoint node = _positions[i];
        if (abs(mosePosition.x() - node.x()) <= 25 && abs(mosePosition.y() - node.y()) <= 25) {
            _mousePositionNode = i;
            return;
        }
    }
    _mousePositionNode = -1;
}
