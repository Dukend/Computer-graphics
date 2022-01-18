#include "ellipsoid.h"
#include <vector>
#include <cmath>
#include <QVector4D>
#include <QTextStream>

Ellipsoid::Ellipsoid() {
    a = 4;
    b = 3;
    c = 2;
    step = 0.1;
    lamp = new Lamp(70, 0, 0, 100);

    fullTransformation = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

Ellipsoid::Ellipsoid(const Ellipsoid &e) {
    polygons = e.polygons;
    a = e.a;
    b = e.b;
    c = e.c;
    step = e.step;
}

void Ellipsoid::clear_polygons() {
    polygons.clear();
}

void Ellipsoid::change_ellipsoid(const QMatrix4x4 &mtrx) {
    for (auto &polygon: polygons) {
        polygon.change_vertices(mtrx);
    }
}

void Ellipsoid::set_step(double s) {
    step = s;
}

void Ellipsoid::create() {
    std::vector<QVector4D> prevPoints{};
    QVector4D firstIter{0, 0, static_cast<float>(c * cos(0)), 1};
    QVector4D lastIter{0, 0, static_cast<float>(c * cos(M_PI)), 1};
    bool connectToOnePoint = true;
    for (double theta = step / 2.; theta < M_PI; theta += step / 2.) {
        if (connectToOnePoint && theta + step < M_PI) {
            QVector4D prevVertex;
            QVector4D firstVertex;
            for (double phi = 0.; phi < 2 * M_PI; phi += step) {
                if (phi == 0.) {
                    firstVertex = {
                        static_cast<float>(a * sin(theta) * cos(phi)),
                        static_cast<float>(b * sin(theta) * sin(phi)),
                        static_cast<float>(c * cos(theta)),
                        1
                    };
                    prevVertex = firstVertex;
                    prevPoints.push_back(prevVertex);
                    continue;
                }
                std::vector<QVector4D> toPushBack;
                QVector4D newVertex;
                newVertex = {
                    static_cast<float>(a * sin(theta) * cos(phi)),
                    static_cast<float>(b * sin(theta) * sin(phi)),
                    static_cast<float>(c * cos(theta)),
                    1
                };
                toPushBack = {
                    firstIter,
                    prevVertex,
                    newVertex
                };
                polygons.push_back(toPushBack);
                prevVertex = newVertex;
                prevPoints.push_back(prevVertex);
                if (phi + step >= 2 * M_PI) {
                    toPushBack = {
                        firstIter,
                        prevVertex,
                        firstVertex
                    };
                    polygons.push_back(toPushBack);
                    prevPoints.push_back(firstVertex);
                    connectToOnePoint = false;
                }
            }
        } else {
            QVector4D prevVertex;
            QVector4D firstVertex;
            std::vector<QVector4D> newPrevPoints{};
            size_t cnt = 0;
            for (double phi = 0; phi < 2 * M_PI; phi += step, cnt++) {
                if (phi == 0.) {
                    firstVertex = {
                        static_cast<float>(a * sin(theta) * cos(phi)),
                        static_cast<float>(b * sin(theta) * sin(phi)),
                        static_cast<float>(c * cos(theta)),
                        1
                    };
                    prevVertex = firstVertex;
                    newPrevPoints.push_back(prevVertex);
                    continue;
                }
                std::vector<QVector4D> toPushBack;
                QVector4D newVertex;
                newVertex = {
                    static_cast<float>(a * sin(theta) * cos(phi)),
                    static_cast<float>(b * sin(theta) * sin(phi)),
                    static_cast<float>(c * cos(theta)),
                    1
                };
                toPushBack = {
                    prevPoints[cnt - 1],
                    prevVertex,
                    newVertex
                };
                polygons.push_back(toPushBack);
                toPushBack = {
                    prevPoints[cnt - 1],
                    newVertex,
                    prevPoints[cnt]
                };
                polygons.push_back(toPushBack);
                prevVertex = newVertex;
                newPrevPoints.push_back(prevVertex);
                if (phi + step > 2 * M_PI) {
                    cnt++;
                    toPushBack = {
                        prevPoints[cnt - 1],
                        prevVertex,
                        firstVertex
                    };
                    polygons.push_back(toPushBack);
                    toPushBack = {
                        prevPoints[cnt - 1],
                        firstVertex,
                        prevPoints[cnt]
                    };
                    polygons.push_back(toPushBack);
                    newPrevPoints.push_back(firstVertex);
                    prevPoints = newPrevPoints;
                    if (theta + step / 2. > M_PI) {
                        connectToOnePoint = true;
                    }
                }
            }
        }
    }
    std::vector<QVector4D> toPushBack;
    for (size_t i = 0; i < prevPoints.size() - 1; i++) {
        toPushBack = {
            prevPoints[i + 1],
            prevPoints[i],
            lastIter
        };
        polygons.push_back(toPushBack);
    }
}

void Ellipsoid::draw(QPainter *ptr, int center_x, int center_y, double step_pixels,
                     int window_center_x, int window_center_y) {
    for (auto &polygon: polygons) {
        auto normal = polygon.get_normal();
        if (normal.z() > 0) {
            polygon.draw(ptr, center_x, center_y, step_pixels,
                         window_center_x, window_center_y, lamp, displayCarcass);
        }
    }
}
