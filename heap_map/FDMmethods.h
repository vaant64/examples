#ifndef FDMMETHODS_H
#define FDMMETHODS_H

#include <QtGlobal>
#include <QtMath>
#include <fstream>

using namespace std;

#define LOAD1 200
#define LOAD2 20
#define LOAD3 0

struct FDMNode {
    qint32 x;
    qint32 y;
    uint index;

    /* тип узла:
     * 0 - ось симметрии
     * 1 - ограничение 1-го рода 200
     * 2 - ограничение 1-го рода 20
     * 3 - ограничение 2-го рода 0
     * 4 - внутренний узел
     */
    uint type;

    /* индексы соседей */
    uint right;
    uint left;
    uint top;
    uint bottom;
};

template <typename T>
void freeMatrix(T **matrix, uint n) {
    for (uint i = 0; i < n; i++)
        delete [] matrix[i];
    delete [] matrix;
}

template <typename T>
void freeVector(T *vector) {
    delete [] vector;
}

/* Решатель расширенной матрицы */
qreal* methodGauss(qreal**, qreal*, uint);

/* Вектор узлов сетки */
FDMNode* createFDMVector(uint, uint*);

/* Расширенная матрица СЛАУ */
qreal** createFDMMatrix(FDMNode*, uint);

/* Экстраполяция Ричардсона */
qreal* methodRichard(qreal*, uint, qreal*, uint);

/* Численный вывод результата */
void FDMDecisionWrite(qreal*, uint, string);

#endif // FDMMETHODS_H
