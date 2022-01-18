#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "polygon.h"
#include <QMatrix4x4>
#include <QPainter>
#include "lamp.h"

class Ellipsoid
{
public:
    std::vector<Polygon> polygons;
    QMatrix4x4 fullTransformation;
    double a, b, c;
    double step;
    Lamp *lamp;
    bool displayCarcass = false;

    Ellipsoid();
    Ellipsoid(const Ellipsoid &e);
    void clear_polygons();
    void change_ellipsoid(const QMatrix4x4 &mtrx);
    void set_step(double s);
    void create();
    void draw(QPainter *ptr, int center_x, int center_y, double step_pixels,
              int window_center_x, int window_center_y);
};

#endif // ELLIPSOID_H
