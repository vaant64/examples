#include "FDMmethods.h"

/* геометрические ограничения */
#define X1 (qint32)(0)
#define X2 (qint32)(0.5*qPow(2, n))
#define X3 (qint32)(4*qPow(2, n))
#define Y1 (qint32)(0.5*qPow(2, n))
#define Y2 (qint32)(3*qPow(2, n))

/* размеры объекта */
#define LX1 (qint32)(X3 + 1)
#define LX2 (qint32)(X2)
#define LY1 (qint32)(2*Y2 + 1)
#define LY2 (qint32)(2*Y1 - 1)

qreal* methodGauss(qreal **matrix, qreal *vector, uint n) {
    qreal factor;
    uint m = n + 1;

    /* прямой ход */
    for (uint i = 0; i < n; i++) {
        factor = matrix[i][i];

        for (uint j = i; j < m; j++)
            matrix[i][j] /= factor;

        for (uint j = i+1; j < n; j++) {
            factor = matrix[j][i];

            for (uint k = i; k < m; k++)
                matrix[j][k] -= factor * matrix[i][k];
        }
    }

    /* обратный ход */
    vector[n-1] = matrix[n-1][n];

    for (uint i = 2; i < n+1; i++) {
        vector[n-i] = matrix[n-i][n];

        for (uint j = n-i+1; j < n; j++)
            vector[n-i] -= matrix[n-i][j] * vector[j];
    }

    return vector;
}

FDMNode* createFDMVector(uint n, uint *count) {
    uint FDMLength = LX1*LY1 - LX2*LY2;
    FDMNode *FDMVector = new FDMNode[FDMLength];
    uint FDMCount = 0;

    for (qint32 x = 0; x <= X3; x++) {
        for (qint32 y = Y2; y >= -Y2; y--) {
            if (y == Y2)
                FDMVector[FDMCount].type = 2;
            else if (y == -Y2) {
                FDMVector[FDMCount].type = 3;
                FDMVector[FDMCount].top = FDMCount-1;
            }
            else if ((x >= X1) && (x < X2)) {
                if (qAbs(y) < Y1) {
                    continue;
                }
                else if (qAbs(y) == Y1)
                    FDMVector[FDMCount].type = 1;
                else if (x == X1) {
                    FDMVector[FDMCount].type = 0;

                    if ((x == X2-1) && (y < Y1))
                        FDMVector[FDMCount].right = FDMCount + LY1;
                    else
                        FDMVector[FDMCount].right = FDMCount + (LY1-LY2);

                    FDMVector[FDMCount].top = FDMCount-1;
                    FDMVector[FDMCount].bottom = FDMCount+1;
                }
                else {
                    FDMVector[FDMCount].type = 4;

                    if ((x == X2-1) && (y < Y1))
                        FDMVector[FDMCount].right = FDMCount + LY1;
                    else
                        FDMVector[FDMCount].right = FDMCount + (LY1-LY2);

                    FDMVector[FDMCount].left = FDMCount - (LY1-LY2);
                    FDMVector[FDMCount].top = FDMCount-1;
                    FDMVector[FDMCount].bottom = FDMCount+1;
                }
            }
            else {
                if (x == X2) {
                    if (qAbs(y) < Y1)
                        FDMVector[FDMCount].type = 1;
                    else {
                        FDMVector[FDMCount].type = 4;
                        FDMVector[FDMCount].right = FDMCount+LY1;

                        if (y >= Y1)
                            FDMVector[FDMCount].left = FDMCount - (LY1-LY2);
                        else if (y <= -Y1)
                            FDMVector[FDMCount].left = FDMCount-LY1;

                        FDMVector[FDMCount].top = FDMCount-1;
                        FDMVector[FDMCount].bottom = FDMCount+1;
                    }
                }
                else if (x == X3)
                    FDMVector[FDMCount].type = 2;
                else {
                    FDMVector[FDMCount].type = 4;
                    FDMVector[FDMCount].right = FDMCount+LY1;
                    FDMVector[FDMCount].left = FDMCount-LY1;
                    FDMVector[FDMCount].top = FDMCount-1;
                    FDMVector[FDMCount].bottom = FDMCount+1;
                }
            }
            FDMVector[FDMCount].x = x;
            FDMVector[FDMCount].y = y;
            FDMVector[FDMCount].index = FDMCount;
            FDMCount++;
        }
    }

    *count = FDMCount;
    return FDMVector;
}

qreal** createFDMMatrix(FDMNode* FDMVector, uint FDMCount) {
    qreal **FDMMatrix = new qreal*[FDMCount];

    for (uint i = 0; i < FDMCount; i++) {
        FDMMatrix[i] = new qreal[FDMCount + 1];
        for (uint j = 0; j < FDMCount; j++)
            FDMMatrix[i][j] = 0;
    }

    uint index;
    for (uint i = 0; i < FDMCount; i++) {
        index = FDMVector[i].index;
        switch (FDMVector[i].type) {
        case 0:
            FDMMatrix[index][index] = -4;
            FDMMatrix[index][FDMVector[i].right] = 2;
            FDMMatrix[index][FDMVector[i].top] = 1;
            FDMMatrix[index][FDMVector[i].bottom] = 1;
            break;

        case 1:
            FDMMatrix[index][index] = 1;
            FDMMatrix[index][FDMCount] = LOAD1;
            break;

        case 2:
            FDMMatrix[index][index] = 1;
            FDMMatrix[index][FDMCount] = LOAD2;
            break;

        case 3:
            FDMMatrix[index][FDMVector[i].index] = 1;
            FDMMatrix[index][FDMVector[i].top] = -1;
            FDMMatrix[index][FDMCount] = LOAD3;
            break;

        case 4:
            FDMMatrix[index][index] = -4;
            FDMMatrix[index][FDMVector[i].right] = 1;
            FDMMatrix[index][FDMVector[i].left] = 1;
            FDMMatrix[index][FDMVector[i].top] = 1;
            FDMMatrix[index][FDMVector[i].bottom] = 1;
            break;
        }
    }

    return FDMMatrix;
}

qreal* methodRichard(qreal *FDMLow, uint FDMCount, qreal *FDMHight, uint n) {
    qreal *FDMSparse  = new qreal[FDMCount];
    uint count = 0;

    for (qint32 x = 0; x < LX1; x += 2) {
        if (x < X2) {
            for (qint32 y = 0; y < (LY1-LY2)/2; y += 2)
                FDMSparse[count++] = FDMHight[x*(LY1-LY2) + y];

            for (qint32 y = (LY1-LY2)/2; y < (LY1-LY2); y += 2)
                FDMSparse[count++] = FDMHight[x*(LY1-LY2) + y];
        }
        else {
            for (qint32 y = 0; y < LY1; y += 2)
                FDMSparse[count++] = FDMHight[(x*LY1-X2*LY2) + y];
        }
    }

    // FDMDecisionWrite(FDMLow, n-1, "result1.txt");
    // FDMDecisionWrite(FDMSparse, n-1, "result2.txt");
    for (uint i = 0; i < count; i++)
        FDMLow[i] = (4*FDMSparse[i] - FDMLow[i]) / 3;

    freeVector(FDMSparse);
    return FDMLow;
}

void FDMDecisionWrite(qreal *FDMDecision, uint n, string filname) {
    qreal **matrix = new qreal*[LY1];

    for (uint i = 0; i < (uint)LY1; i++) {
        matrix[i] = new qreal[LX1];
        for (uint j = 0; j < (uint)LX1; j++)
            matrix[i][j] = 0;
    }

    uint count = 0;
    for (qint32 x = 0; x <= X3; x++) {
        for (qint32 y = Y2; y >= -Y2; y--) {
            if ((x < X2) && (qAbs(y) < Y1)) {
                continue;
            }
            matrix[-(y-Y2)][x] = FDMDecision[count++];
        }
    }

    ofstream fout;
    fout.open(filname);
    for (uint i = 0; i < (uint)LY1; i++) {
        for (uint j = 0; j < (uint)LX1; j++) {
            fout.width(8);
            fout.precision(2);
            fout << fixed << matrix[i][j];
        }
        fout << endl;
    }
    fout.close();

    freeMatrix(matrix, LY1);
}
