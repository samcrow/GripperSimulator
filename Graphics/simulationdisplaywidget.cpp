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
}

void SimulationDisplayWidget::paintEvent(QPaintEvent *)
{
    if(simulation) {
        QPainter painter(this);
        painter.setRenderHints(QPainter::TextAntialiasing | QPainter::Antialiasing | QPainter::HighQualityAntialiasing);

        // Scale: 0.15 m = smallest dimension of widget
        const double smallerDimension = qMin(this->width(), this->height());
        const double centerX = this->width() / 2;
        const double centerY = this->height() / 2;
        const double SCALE = smallerDimension / 0.15;
        // Make the vertical scale negative so that everything is flipped vertically
        // to translate from the model coordinate system with the origin at bottom left
        // to the widget coordinate system with the origin at top left
        const QTransform transform = QTransform().translate(centerX, centerY).scale(SCALE, -SCALE);

        // Create a transform that incorporates the gripper position offsets
        const QTransform gripperTransform = QTransform(transform).translate(simulation->gripper()->xOffset(), simulation->gripper()->yOffset());
        // Draw points for the fingertip locations
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::black);
        painter.drawEllipse(gripperTransform.map(simulation->gripper()->fingertip1Position()), 2, 2);
        painter.drawEllipse(gripperTransform.map(simulation->gripper()->fingertip2Position()), 2, 2);


        // Draw the fingertips
        painter.setPen(Qt::green);
        painter.drawPolyline(gripperTransform.map(simulation->gripper()->fingertip1Polygon()));
        painter.drawPolyline(gripperTransform.map(simulation->gripper()->fingertip2Polygon()));

        // Draw the object
        painter.setPen(Qt::black);
        painter.drawPolyline(transform.map(simulation->object()->polygon()));
    }
}
