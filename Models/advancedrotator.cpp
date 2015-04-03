#include "advancedrotator.h"
#include <cmath>

AdvancedRotator::AdvancedRotator() {
	connect(&angleChanger_, &LinearValueChanger::valueChanged, this, &AdvancedRotator::angleChanged);
}

QPointF AdvancedRotator::center() const
{
	return center_;
}

void AdvancedRotator::setCenter(const QPointF& center)
{
	center_ = center;
}
double AdvancedRotator::angle() const
{
	return angle_;
}

void AdvancedRotator::setAngle(double angle)
{
	angle_ = angle;
}
double AdvancedRotator::radius() const
{
	return radius_;
}

void AdvancedRotator::setRadius(double radius)
{
	radius_ = radius;
}
void AdvancedRotator::setRate(double newRate) {
	angleChanger_.setRate(newRate);
}

QPointF AdvancedRotator::position() const {
	const double x = center_.x() + radius_ * std::cos(angle_);
	const double y = center_.y() + radius_ * std::sin(angle_);
	return QPointF(x, y);
}

void AdvancedRotator::setPosition(const QPointF& position) {
	const double dy = position.y() - center_.y();
	const double dx = position.x() - center_.x();
	angle_ = std::atan2(dy, dx);
	radius_ = std::hypot(dy, dx);
}

void AdvancedRotator::start() {
	angleChanger_.setValue(angle_);
	angleChanger_.start();
}

void AdvancedRotator::pause() {
	angleChanger_.pause();
}

void AdvancedRotator::angleChanged(double newAngle) {
	angle_ = newAngle;
	emit newPosition(position());
}
