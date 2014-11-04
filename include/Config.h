#ifndef _CONFIG_H
#define _CONFIG_H

const int maxLayer = 5;
const int maxUnit = 1000;
const int maxBatchSize = 20;

typedef double RBMBuffer[maxUnit*maxBatchSize];

#endif
