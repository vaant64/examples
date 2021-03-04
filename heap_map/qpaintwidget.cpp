#include "qpaintwidget.h"
#include <QPainter>
#include <QtMath>

#define DEGREE 4  // dx = dy = (qPow(2, -DEGREE))

#define HSV_RED    0
#define HSV_BLUE 240

/* Базовые расчёты */
QPaintWidget::QPaintWidget(QWidget * parent) : QWidget(parent) {
    qreal **FDMMatrix;

    FDMCount = 0;
    FDMVector = createFDMVector(DEGREE, &FDMCount);

    FDMMatrix = createFDMMatrix(FDMVector, FDMCount);

    FDMDecision = new qreal[FDMCount];
    FDMDecision = methodGauss(FDMMatrix, FDMDecision, FDMCount);
    freeMatrix(FDMMatrix, FDMCount);

    /*
    // -----------------------------------------------------------------------

    uint FDMHighCount = 0;
    FDMNode *FDMHighVector = createFDMVector(DEGREE+1, &FDMHighCount);

    FDMMatrix = createFDMMatrix(FDMHighVector, FDMHighCount);

    qreal *FDMHighDecision = new qreal[FDMHighCount];
    FDMHighDecision = methodGauss(FDMMatrix, FDMHighDecision, FDMHighCount);
    freeMatrix(FDMMatrix, FDMHighCount);
    freeVector(FDMHighVector);

    // -----------------------------------------------------------------------

    FDMDecision = methodRichard(FDMDecision, FDMCount, FDMHighDecision, DEGREE+1);
    freeVector(FDMHighDecision);
    */

    FDMDecisionWrite(FDMDecision, DEGREE, "result.txt");
}

QPaintWidget::~QPaintWidget() {
    freeVector(FDMDecision);
    freeVector(FDMVector);
}

/* Визуализация */
void QPaintWidget::paintEvent(QPaintEvent *) {
    uint pHSV;
    QColor pRGB;
    uint pSize = qPow(2, 6 - DEGREE);
    qreal toHSV = (LOAD1 - LOAD2)/(double)HSV_BLUE;

    QPainter painter(this);

    qint32 x, y;
    qint32 xc = this->width()/2 - pSize/2;
    qint32 yc = this->height()/2 - pSize/2;

    painter.setPen(QPen(QColor(0,0,0,0)));
    painter.setBrush(QBrush(Qt::black));
    painter.drawRect(0, 0, this->width(), this->height());

    for (uint i = 0; i < FDMCount; i++) {
        pHSV = HSV_BLUE - (FDMDecision[i]-LOAD2)/toHSV;
        pRGB = QColor::fromHsv(pHSV,255,255);
        painter.setBrush(QBrush(pRGB));

        x = FDMVector[i].x*pSize;
        y = FDMVector[i].y*pSize;
        painter.drawRect(xc + x, yc - y, pSize, pSize);
        painter.drawRect(xc - x, yc - y, pSize, pSize);
    }

    painter.setPen(QPen(QColor(255,255,255,255)));
    painter.setBrush(QBrush(QColor(0,0,0,0)));
    painter.drawRect(20, 20, this->width() - 40, this->height() - 40);
}
