#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H
#include <QObject>
#include "gripper.h"
#include "objectinformation.h"

/**
 * Calculates the score of a gripper movement program.
 *
 * The score has two components:
 * The movement score starts at zero and decreases as the gripper moves.
 * Because translation is more expensive than rotation, translation
 * decreases the movement score more quickly than rotation.
 *
 * The information score starts at zero and increases as the robot
 * finds areas that are clear.
 *
 */
class ScoreCalculator : public QObject
{
    Q_OBJECT
public:
	ScoreCalculator(Gripper& gripper, ObjectInformation& objectInfo, QObject* parent = 0);

    /// Returns the movement score
    int movementScore() const;
    /// Returns the information score
    int informationScore() const;
    /// Returns the result of subtracting the movement score from the information score
    int netScore() const;

	int pixels() const;

signals:

    void scoreChanged();

public slots:

    void gripperGeometryChanged();

private:
    /// Cost of moving the gripper, in points per meter
    static constexpr double MOVE_COST = 1000;
    /// Cost of rotating the gripper, in points per radian
    static constexpr double ROTATE_COST = 30;

    /**
     * The current implementation scores information by counting
     * the number of pixels in the ObjectInformation that are confirmed clear.
     * This constant is the number of points received per pixel.
     */
    static constexpr double PIXEL_SCORE = 0.1;

    double oldGripperX = 0;
    double oldGripperY = 0;
    double oldGripperAngle = 0;

	Gripper& gripper;
	ObjectInformation& objectInfo;

    double movementScore_ = 0;
    double informationScore_ = 0;
	double contPixels_ = 0;

    void updateMovmementScore();
    void updateInformationScore();
	void updatePixels();


	bool isWhite(QRgb color);
};

#endif // SCORECALCULATOR_H
