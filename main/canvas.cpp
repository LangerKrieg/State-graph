#include "canvas.h"
#include "ui_canvas.h"

#include <QMessageBox>
#include <QDir>

Canvas::Canvas(eventGraph *graph, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Canvas),
    _graph(graph)
{
    ui->setupUi(this);
    this->setMouseTracking(true);

    QStringList nameFilter;
    QDir dir("../l6");
    nameFilter.clear();
    nameFilter << "*.csv";

    QFileInfoList list = dir.entryInfoList( nameFilter, QDir::Files );

    for (QFileInfo file: list)
        ui->listWidget->addItem(file.fileName());
}

Canvas::~Canvas() {
    delete ui;
}

void Canvas::paintEvent(QPaintEvent *) {
    QPainter p;
    p.begin(this);
    _graph->draw(&p);
    p.end();
}

void Canvas::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Right)
        _graph->changeActive(eventDirection::rigth);
    else if (event->key() == Qt::Key_Left)
        _graph->changeActive(eventDirection::left);
    else if (event->key() == Qt::Key_Up)
        _graph->changeActive(eventDirection::up);
    else if (event->key() == Qt::Key_Down)
        _graph->changeActive(eventDirection::down);
    this->repaint();
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    QPoint pos = event->pos();
    _graph->changeMousePositionNode(pos);
    this->repaint();
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    _graph->changeActive();
    this->repaint();
}

void Canvas::on_listWidget_itemDoubleClicked(QListWidgetItem *item) {
    if (!_graph->readCVS(item->text())) {
        QMessageBox msgBox;
        msgBox.setText("Ошибка чтения файла!");
        msgBox.exec();
    } else {
        this->repaint();
    }
    this->setFocus();
}
