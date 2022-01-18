#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <utility>

class coordinate_system_panel;

class view : public QWidget
{
    Q_OBJECT
public:
    explicit view(QWidget *parent = nullptr);
    coordinate_system_panel *cord_system() const;
    void set_cord_system_panel(coordinate_system_panel *c);
    void set_step(const int &, const int &);
    std::pair<int, int> get_step();
    void set_division(const int &x, const int &y);
    friend void draw_cord_system(view *);
    friend void draw_function(view *);
private:
    coordinate_system_panel *c_s;
//    int step;
    double step_x;
    double step_y;
    double center_x;
    double center_y;
    bool first;
    QPointF previousPoint;
protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
signals:

public slots:
};

#endif // VIEW_H
