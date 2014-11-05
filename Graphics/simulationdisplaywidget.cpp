#include "simulationdisplaywidget.h"
#include <QPainter>
#include <QTransform>
#include <QDebug>

SimulationDisplayWidget::SimulationDisplayWidget(QWidget *parent) :
    QWidget(parent)
{
}

void SimulationDisplayWidget::setSimulation(Simulation *simulation) {
    this->simulation = simulation;
    connect(this->simulation, SIGNAL(changed()), this, SLOT(repaint()));
}

void SimulationDisplayWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // Draw black background
    painter.setBrush(Qt::black);
    painter.fillRect(this->rect(), Qt::SolidPattern);

    if(simulation) {
        painter.setRenderHints(QPainter::TextAntialiasing | QPainter::Antialiasing | QPainter::HighQualityAntialiasing);

        // Scale: 0.15 m = smallest dimension of widget
        const double smallerDimension = qMin(this->width(), this->height());
        const double centerX = this->width() / 2;
        const double centerY = this->height() / 2;
        const double SCALE = smallerDimension / 0.15;

        const QTransform transform = QTransform().translate(centerX, centerY).scale(SCALE, SCALE);

        // Draw the object information bitmap
        const QImage& objectBitmap = simulation->objectInformation().bitmap();
        const QRect bitmapRegion = transform.map(QRectF(-0.1, -0.1, 0.2, 0.2)).boundingRect().toRect();
        painter.drawImage(bitmapRegion, objectBitmap);

        // Draw points for the fingertip locations
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::green);
        painter.drawEllipse(transform.map(simulation->gripper().fingertip1Position()), 2, 2);
        painter.drawEllipse(transform.map(simulation->gripper().fingertip2Position()), 2, 2);


        // Draw the fingertips
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::gray);
        painter.drawPolygon(transform.map(simulation->gripper().fingertip1Polygon()));
        painter.drawPolygon(transform.map(simulation->gripper().fingertip2Polygon()));

        // Draw the object
        painter.setBrush(Qt::red);
        painter.drawPolygon(transform.map(simulation->object().polygon()));

        // Draw the infrared beam
        painter.setPen(Qt::red);
        painter.drawLine(transform.map(simulation->gripper().infraredBeamLine()));
    }
}
