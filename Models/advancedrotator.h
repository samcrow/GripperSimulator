#ifndef ADVANCEDROTATOR_H
#define ADVANCEDROTATOR_H
#include <QObject>
#include <QPointF>
#include "linearvaluechanger.h"

/**
 * Calculates the rotation of the gripper around a point
 */
class AdvancedRotator : public QObject
{
	Q_OBJECT
public:
	AdvancedRotator();

	QPointF center() const;
	void setCenter(const QPointF& center);
	double angle() const;
	void setAngle(double angle);
	double radius() const;
	void setRadius(double radius);
	void setRate(double newRate);

	QPointF position() const;
	void setPosition(const QPointF& position);

signals:

	void newPosition(const QPointF& newPosition);

public slots:

	void start();
	void pause();

private slots:
	void angleChanged(double newAngle);

private:
	QPointF center_;
	double angle_ = 0;
	double radius_ = 0;

	LinearValueChanger angleChanger_;
};

#endif // ADVANCEDROTATOR_H
