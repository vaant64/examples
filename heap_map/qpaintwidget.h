#ifndef QPAINTWIDGET_H
#define QPAINTWIDGET_H

#include <QWidget>
#include "FDMmethods.h"

class QPaintEvent;

class QPaintWidget : public QWidget
{
    Q_OBJECT

public:
    QPaintWidget(QWidget * parent = 0);
    ~QPaintWidget();

protected:
    void paintEvent(QPaintEvent *);

private:
    uint FDMCount;
    FDMNode *FDMVector;
    qreal *FDMDecision;
};

#endif // QPAINTWIDGET_H
