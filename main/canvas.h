#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QListWidgetItem>
#include <QKeyEvent>
#include <QMouseEvent>
#include "eventGraph.h"

namespace Ui {
    class Canvas;
}

class Canvas : public QWidget {
    Q_OBJECT

    public:
        Canvas(eventGraph* graph, QWidget *parent = nullptr);
        ~Canvas();

    private:
        Ui::Canvas *ui;
        eventGraph* _graph;

    protected:
        void paintEvent(QPaintEvent*);
        void keyPressEvent(QKeyEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);

    private slots:
        void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
};

#endif // CANVAS_H
