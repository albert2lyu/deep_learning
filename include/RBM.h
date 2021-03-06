#include "Config.h"
#include "Dataset.h"
#include "Utility.h"
#include "TrainModel.h"
#include <cstring>
#include <ctime>
#include <cstdio>

#ifndef _RBM_H
#define _RBM_H

class MultiLayerRBM;

class RBM : public UnsuperviseTrainComponent {
    public:
        RBM(int, int);
        RBM(const char *);
        RBM(FILE *);
        ~RBM();

        void setWeightFile(const char *);
        void dumpWeight(int, int);

        void beforeTraining(int);
        void afterTraining(int);
        void trainBatch(int);
        void runBatch(int);
        void setLearningRate(double lr);
        void setPersistent(bool p) { persistent = p; };
        double* getOutput() { return h1; }
        double* getTransOutput() { return ph1; }
        int getOutputNumber() { return numHid; }
        int getInputNumber() { return numVis; }
        double* getHBias() { return hbias; }
        double* getVBias() { return vbias; }
        double getTrainingCost(int, int);
        void operationPerEpoch();
        void setInput(double* in);
        void setSparsity(bool b, double p = 0.0, double numda = 0.9, double slr = 0.01) 
        { 
            this->sparsity = b;
            this->p = p; 
            this->numda = numda; 
            this->q = 1.0;
            this->slr = slr;
        }

        void saveModel(FILE* modelFileFd);
        void getWeightTrans(double *weight);

        void generateSample(const char*, double*, int);
        void dumpSample(FILE*, double*, int);
        void dumpSampleBinary(FILE*, double*, int);

        void setGaussianVisible(bool b) {
            this->binVis = !b;
        }
        void setGaussianHidden(bool b) {
            this->binHid = !b;
        }
    private:
        void getHProb(const double *v, double *ph, const int size);
        void getHSample(const double *ph, double *h, const int size);
        void getVProb(const double *h, double *pv, const int size);
        void getVSample(const double *pv, double *v, const int size);
        void gibbsSampleHVH(double *hStart, double *h, double *ph, 
                                  double *v, double *pv, const int step, const int size);
        void getFE(const double *v, double *FE, const int size);
        double getPL(double *v, const int size);
        double getReconstructCost(double *v, double *pv, int size);
        double getSquareReconstructCost(double *v1, double *v2, int size);

        void runChain(int, int);
        void updateWeight(int);
        void updateBias(int);

        void loadModel(FILE*);
        void allocateBuffer(int);
        void freeBuffer();
        void getAMDelta(int, double*);
        void updateAMSample(int, double);

        int numVis, numHid;
        double *weight;
        double *hbias, *vbias;
        double *v1, *v2, *h1, *h2;
        double *ph1, *ph2, *pv;
        double *chainStart;
        double *AMdelta;    //activation maximization
        double *AMSample;

        double learningRate;
        bool persistent;

        char *weightFile;
        friend class MultiLayerRBM;

        double p, q, numda, slr;
        bool sparsity;
        double *hderiv;

        bool gaussian;
        bool binVis, binHid;    //whether is binary visible unit and hidden unit
};

#endif
