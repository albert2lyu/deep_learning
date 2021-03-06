#include "TrainModel.h"
#include "MultiLayerRBM.h"
#include "Utility.h"
#include "Logistic.h"
#include "DeepAutoEncoder.h"
#include "mkl.h"

void testPancanTraining_11cancer_479feature(){
    SVMDataset data;
    data.loadData("../data/TCGA/11cancer_479feature/Pancan-GAM-train.txt", "../data/TCGA/11cancer_479feature/Pancan-GAM-valid.txt");

    //one layer no pretrain
    if(0){
        MLP mlp; 
        MLPLayer *firstLayer = new TanhLayer(data.getFeatureNumber(), 500);
        Logistic *secondLayer = new Logistic(500, data.getLabelNumber());
        mlp.addLayer(firstLayer);
        mlp.addLayer(secondLayer);

        TrainModel mlpModel(mlp);
        mlpModel.train(&data, 0.01, 10, 1000, 20, -0.02);
    }

    //two layer no pretrain
    if(0){
        MLP mlp; 
        MLPLayer *firstLayer = new TanhLayer(data.getFeatureNumber(), 500);
        MLPLayer *secondLayer = new TanhLayer(data.getFeatureNumber(), 500);
        Logistic *thirdLayer = new Logistic(500, data.getLabelNumber());
        mlp.addLayer(firstLayer);
        mlp.addLayer(secondLayer);
        mlp.addLayer(thirdLayer);

        TrainModel mlpModel(mlp);
        mlpModel.train(&data, 0.01, 10, 1000, 20);
    }

    //one layer pretrain
    if(0){
        int rbmLayerSize[] = { data.getFeatureNumber(), 500};
        MultiLayerRBM multirbm(1, rbmLayerSize);
        multirbm.setPersistent(false);
        multirbm.setModelFile("result/DBN-Pancan-GAM-onelayer-pretrain.dat");

        MultiLayerTrainModel pretrainModel(multirbm);
        pretrainModel.train(&data, 0.01, 5, 100);

        /*
        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-onelayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 5, 1000, 40, -0.02);
        */
    }

    //two layer pretrain
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-onelayer-pretrain.dat");
        multirbm.setPersistent(false);
        multirbm.addLayer(500);
        multirbm.setLayerToTrain(0, false);
        multirbm.setModelFile("result/DBN-Pancan-GAM-twolayer-pretrain.dat");

        MultiLayerTrainModel pretrainModel(multirbm);
        pretrainModel.train(&data, 0.01, 5, 29);

        /*
        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-twolayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 5, 1000, 40);
        */
    }

    //three layer pretrain
    if(1){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-twolayer-pretrain.dat");
        multirbm.setPersistent(false);
        multirbm.addLayer(500);
        multirbm.setLayerToTrain(0, false);
        multirbm.setLayerToTrain(1, false);
        multirbm.setModelFile("result/DBN-Pancan-GAM-threelayer-pretrain.dat");

        MultiLayerTrainModel pretrainModel(multirbm);
        pretrainModel.train(&data, 0.01, 5, 30);

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-threelayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 5, 118, 40);
    }

    //one layer train
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-onelayer-pretrain.dat");

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-onelayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.005, 5, 1000, 40, -0.01);
    }

    //two layer train
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-twolayer-pretrain.dat");

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-twolayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.005, 3, 1000, 40);
    }

    //three layer train
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-threelayer-pretrain.dat");

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-threelayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 5, 118, 40);
    }

    // logistic
    if(0){
        Logistic logi(data.getFeatureNumber(), data.getLabelNumber());
        TrainModel logisticModel(logi);
        logisticModel.train(&data, 0.01, 10, 1000, 30, -0.02);
    }
}

void testPancanTraining_22cancer_479feature(){
    SVMDataset data;
    data.loadData("../data/TCGA/Pancan-GAM-train.txt", "../data/TCGA/Pancan-GAM-valid.txt");

    //one layer no pretrain
    if(0){
        MLP mlp; 
        MLPLayer *firstLayer = new TanhLayer(data.getFeatureNumber(), 500);
        Logistic *secondLayer = new Logistic(500, data.getLabelNumber());
        mlp.addLayer(firstLayer);
        mlp.addLayer(secondLayer);

        TrainModel mlpModel(mlp);
        mlpModel.train(&data, 0.01, 10, 1000, 20, -0.02);
    }

    //two layer no pretrain
    if(0){
        MLP mlp; 
        MLPLayer *firstLayer = new TanhLayer(data.getFeatureNumber(), 500);
        MLPLayer *secondLayer = new TanhLayer(data.getFeatureNumber(), 500);
        Logistic *thirdLayer = new Logistic(500, data.getLabelNumber());
        mlp.addLayer(firstLayer);
        mlp.addLayer(secondLayer);
        mlp.addLayer(thirdLayer);

        TrainModel mlpModel(mlp);
        mlpModel.train(&data, 0.01, 10, 1000, 20);
    }

    //one layer pretrain
    if(0){
        int rbmLayerSize[] = { data.getFeatureNumber(), 500};
        MultiLayerRBM multirbm(1, rbmLayerSize);
        multirbm.setPersistent(false);
        multirbm.setModelFile("result/DBN-Pancan-GAM-onelayer-pretrain.dat");

        MultiLayerTrainModel pretrainModel(multirbm);
        pretrainModel.train(&data, 0.01, 5, 100);

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-onelayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 5, 1000, 40);
    }

    //two layer pretrain
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-onelayer-pretrain.dat");
        multirbm.setPersistent(false);
        multirbm.addLayer(500);
        multirbm.setLayerToTrain(0, false);
        multirbm.setModelFile("result/DBN-Pancan-GAM-twolayer-pretrain.dat");

        MultiLayerTrainModel pretrainModel(multirbm);
        pretrainModel.train(&data, 0.01, 5, 20);

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-twolayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 5, 1000, 40);
    }

    //three layer pretrain
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-twolayer-pretrain.dat");
        multirbm.setPersistent(false);
        multirbm.addLayer(500);
        multirbm.setLayerToTrain(0, false);
        multirbm.setLayerToTrain(1, false);
        multirbm.setModelFile("result/DBN-Pancan-GAM-threelayer-pretrain.dat");

        MultiLayerTrainModel pretrainModel(multirbm);
        pretrainModel.train(&data, 0.01, 5, 16);

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-threelayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 5, 1000, 40);
    }

    //one layer train
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-onelayer-pretrain.dat");

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-onelayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.005, 5, 1000, 40, -0.01);
    }

    //two layer train
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-twolayer-pretrain.dat");

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-twolayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.005, 3, 1000, 40);
    }

    // logistic
    if(0){
        Logistic logi(data.getFeatureNumber(), data.getLabelNumber());
        TrainModel logisticModel(logi);
        logisticModel.train(&data, 0.01, 10, 1000, 30, -0.02);
    }
}

void testPancanAutoEncoder_11cancer_479feature(){
    SVMDataset data;
    data.loadData("../data/TCGA/11cancer_479feature/Pancan-GAM-all.txt", "../data/TCGA/11cancer_479feature/Pancan-GAM-valid.txt");

    // DBN pretrain
    if(0){
        double lr[] = { 0.01, 0.01, 0.005 };
        int rbmLayerSize[] = { data.getFeatureNumber(), 500, 200, 30};

        MultiLayerRBM multirbm(3, rbmLayerSize);
        multirbm.setModelFile("result/DBN-Pancan-GAM-AutoEncoder-pretrain.dat");
        multirbm.setPersistent(false);
        multirbm.setGaussianHidden(2, true);

        MultiLayerTrainModel pretrainModel(multirbm);
        pretrainModel.train(&data, lr, 1, 100);
    }
    
    // deep autoencoder fine tune
    if(0){
        MultiLayerRBM* multirbm = new MultiLayerRBM("result/DBN-Pancan-GAM-AutoEncoder-pretrain.dat");
        DeepAutoEncoder dad(*multirbm); 
        delete multirbm;
        dad.setModelFile("result/DBN-Pancan-GAM-AutoEncoder.dat");
        TrainModel model(dad);
        model.train(&data, 0.01, 10, 200);
    }

    // dump reduced dim data
    if(1){
        DeepAutoEncoder dad("result/DBN-Pancan-GAM-AutoEncoder.dat");
        TransmissionDataset out(data, dad);
        out.dumpTrainingData("result/DBN-Pancan-GAM-AutoEncoder-30dim.bin");
    }
}

void testPancanTraining_11cancer_Merge500Mutation(){
    SVMDataset data;
    data.loadData("../data/TCGA/Pancan-GAM-train.txt", "../data/TCGA/Pancan-GAM-valid.txt");

    //one layer no pretrain
    if(0){
        MLP mlp; 
        MLPLayer *firstLayer = new TanhLayer(data.getFeatureNumber(), 1000);
        Logistic *secondLayer = new Logistic(1000, data.getLabelNumber());
        mlp.addLayer(firstLayer);
        mlp.addLayer(secondLayer);

        TrainModel mlpModel(mlp);
        mlpModel.train(&data, 0.01, 10, 1000, 20);
    }

    //two layer no pretrain
    if(0){
        MLP mlp; 
        MLPLayer *firstLayer = new TanhLayer(data.getFeatureNumber(), 500);
        MLPLayer *secondLayer = new TanhLayer(data.getFeatureNumber(), 500);
        Logistic *thirdLayer = new Logistic(500, data.getLabelNumber());
        mlp.addLayer(firstLayer);
        mlp.addLayer(secondLayer);
        mlp.addLayer(thirdLayer);

        TrainModel mlpModel(mlp);
        mlpModel.train(&data, 0.01, 10, 1000, 20);
    }

    //one layer pretrain
    if(0){
        int rbmLayerSize[] = { data.getFeatureNumber(), 1000};
        MultiLayerRBM multirbm(1, rbmLayerSize);
        multirbm.setPersistent(false);
        multirbm.setModelFile("result/DBN-Pancan-GAM-onelayer-pretrain.dat");

        MultiLayerTrainModel pretrainModel(multirbm);
        pretrainModel.train(&data, 0.01, 5, 100);

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-onelayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 5, 1000, 40);
    }

    //two layer pretrain
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-onelayer-pretrain.dat");
        multirbm.setPersistent(false);
        multirbm.addLayer(1000);
        multirbm.setLayerToTrain(0, false);
        multirbm.setModelFile("result/DBN-Pancan-GAM-twolayer-pretrain.dat");

        MultiLayerTrainModel pretrainModel(multirbm);
        pretrainModel.train(&data, 0.01, 5, 20);

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-twolayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 5, 1000, 40);
    }

    //three layer pretrain
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-twolayer-pretrain.dat");
        multirbm.setPersistent(false);
        multirbm.addLayer(500);
        multirbm.setLayerToTrain(0, false);
        multirbm.setLayerToTrain(1, false);
        multirbm.setModelFile("result/DBN-Pancan-GAM-threelayer-pretrain.dat");

        MultiLayerTrainModel pretrainModel(multirbm);
        pretrainModel.train(&data, 0.01, 5, 16);

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-threelayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 5, 1000, 40);
    }

    //one layer train
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-onelayer-pretrain.dat");

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-onelayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 10, 1000, 40, -0.02);
    }

    //two layer train
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-twolayer-pretrain.dat");

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-twolayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 10, 1000, 40);
    }

    // logistic
    if(1){
        Logistic logi(data.getFeatureNumber(), data.getLabelNumber());
        TrainModel logisticModel(logi);
        logisticModel.train(&data, 0.01, 10, 1000, 30, -0.04);
    }
}

void testPancanTraining_11cancer_MergeHCDCD(){
    SVMDataset data;
    data.loadData("../data/TCGA/Pancan-GAM-train.txt", "../data/TCGA/Pancan-GAM-valid.txt");

    //one layer no pretrain
    if(0){
        MLP mlp; 
        MLPLayer *firstLayer = new TanhLayer(data.getFeatureNumber(), 1000);
        Logistic *secondLayer = new Logistic(1000, data.getLabelNumber());
        mlp.addLayer(firstLayer);
        mlp.addLayer(secondLayer);

        TrainModel mlpModel(mlp);
        mlpModel.train(&data, 0.01, 10, 1000, 20);
    }

    //two layer no pretrain
    if(0){
        MLP mlp; 
        MLPLayer *firstLayer = new TanhLayer(data.getFeatureNumber(), 500);
        MLPLayer *secondLayer = new TanhLayer(data.getFeatureNumber(), 500);
        Logistic *thirdLayer = new Logistic(500, data.getLabelNumber());
        mlp.addLayer(firstLayer);
        mlp.addLayer(secondLayer);
        mlp.addLayer(thirdLayer);

        TrainModel mlpModel(mlp);
        mlpModel.train(&data, 0.01, 10, 1000, 20);
    }

    //one layer pretrain
    if(0){
        int rbmLayerSize[] = { data.getFeatureNumber(), 1000};
        MultiLayerRBM multirbm(1, rbmLayerSize);
        multirbm.setPersistent(false);
        multirbm.setModelFile("result/DBN-Pancan-GAM-onelayer-pretrain.dat");

        MultiLayerTrainModel pretrainModel(multirbm);
        pretrainModel.train(&data, 0.01, 5, 100);

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-onelayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 5, 1000, 40);
    }

    //two layer pretrain
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-onelayer-pretrain.dat");
        multirbm.setPersistent(false);
        multirbm.addLayer(1000);
        multirbm.setLayerToTrain(0, false);
        multirbm.setModelFile("result/DBN-Pancan-GAM-twolayer-pretrain.dat");

        MultiLayerTrainModel pretrainModel(multirbm);
        pretrainModel.train(&data, 0.01, 5, 20);

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-twolayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 5, 1000, 40);
    }

    //three layer pretrain
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-twolayer-pretrain.dat");
        multirbm.setPersistent(false);
        multirbm.addLayer(500);
        multirbm.setLayerToTrain(0, false);
        multirbm.setLayerToTrain(1, false);
        multirbm.setModelFile("result/DBN-Pancan-GAM-threelayer-pretrain.dat");

        MultiLayerTrainModel pretrainModel(multirbm);
        pretrainModel.train(&data, 0.01, 5, 16);

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-threelayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 5, 1000, 40);
    }

    //one layer train
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-onelayer-pretrain.dat");

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-onelayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 10, 1000, 40, -0.02);
    }

    //two layer train
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-twolayer-pretrain.dat");

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-twolayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 10, 1000, 40);
    }

    // logistic
    if(1){
        Logistic logi(data.getFeatureNumber(), data.getLabelNumber());
        TrainModel logisticModel(logi);
        logisticModel.train(&data, 0.01, 10, 1000, 30, -0.01);
    }
}

void testPancanAM(){
    SVMDataset data;
    data.loadData("../data/TCGA/11cancer_479feature/Pancan-GAM-train.txt", "../data/TCGA/11cancer_479feature/Pancan-GAM-valid.txt");
    
    double avgNorm = squareNorm(data.getTrainingData(0), data.getFeatureNumber(), 2000);
    MLP* mlp = new MLP("result/DBN-Pancan-GAM-threelayer.dat");
    MultiLayerRBM multirbm(*mlp);
    delete mlp;

    multirbm.activationMaxization(0, 500, avgNorm, 1000, "result/Pancan-GAM-FirstLayer-AM.bin", true);
    multirbm.activationMaxization(1, 500, avgNorm, 1000, "result/Pancan-GAM-SecondLayer-AM.bin", true);
    multirbm.activationMaxization(2, 500, avgNorm, 1000, "result/Pancan-GAM-ThirdLayer-AM.bin", true);
}

void testPancanDumpHidden(){
    SVMDataset data;
    data.loadData("../data/TCGA/11cancer_479feature/Pancan-GAM-all.txt", "../data/TCGA/11cancer_479feature/Pancan-GAM-valid.txt");

    MLP* mlp = new MLP("result/DBN-Pancan-GAM-threelayer.dat");
    MultiLayerRBM multirbm(*mlp);
    delete mlp;
    TrainComponent& firstLayer = multirbm.getLayer(0);
    TrainComponent& secondLayer = multirbm.getLayer(1);
    TrainComponent& thirdLayer = multirbm.getLayer(2);

    // dump first layer weight
    //firstLayer.setModelFile("result/20NewsgroupDBN_FirstLayer.dat");
    //firstLayer.saveModel();

    // dump first layer hidden layer output
    TransmissionDataset h1out(data, firstLayer);
    h1out.dumpTrainingData("result/Pancan-GAM-FirstLayer-Hidden.bin");

    // dump second layer hidden layer output
    TransmissionDataset h2out(h1out, secondLayer);
    h2out.dumpTrainingData("result/Pancan-GAM-SecondLayer-Hidden.bin");

    TransmissionDataset h3out(h2out, thirdLayer);
    h3out.dumpTrainingData("result/Pancan-GAM-ThirdLayer-Hidden.bin");
}

void testMKL(){
    printf("%d\n", mkl_get_max_threads());    
}

void testPancanTraining_11cancer_199mutation(){
    SVMDataset data;
    data.loadData("../data/TCGA/11cancer_199mutation/Pancan-GAM-train.txt", "../data/TCGA/11cancer_199mutation/Pancan-GAM-valid.txt");

    //one layer no pretrain
    if(0){
        MLP mlp; 
        MLPLayer *firstLayer = new TanhLayer(data.getFeatureNumber(), 500);
        Logistic *secondLayer = new Logistic(500, data.getLabelNumber());
        mlp.addLayer(firstLayer);
        mlp.addLayer(secondLayer);

        TrainModel mlpModel(mlp);
        mlpModel.train(&data, 0.01, 10, 1000, 20, -0.02);
    }

    //two layer no pretrain
    if(0){
        MLP mlp; 
        MLPLayer *firstLayer = new TanhLayer(data.getFeatureNumber(), 500);
        MLPLayer *secondLayer = new TanhLayer(data.getFeatureNumber(), 500);
        Logistic *thirdLayer = new Logistic(500, data.getLabelNumber());
        mlp.addLayer(firstLayer);
        mlp.addLayer(secondLayer);
        mlp.addLayer(thirdLayer);

        TrainModel mlpModel(mlp);
        mlpModel.train(&data, 0.01, 10, 1000, 20);
    }

    //one layer pretrain
    if(0){
        int rbmLayerSize[] = { data.getFeatureNumber(), 200};
        MultiLayerRBM multirbm(1, rbmLayerSize);
        multirbm.setPersistent(false);
        multirbm.setModelFile("result/DBN-Pancan-GAM-onelayer-pretrain.dat");

        MultiLayerTrainModel pretrainModel(multirbm);
        pretrainModel.train(&data, 0.01, 5, 100);

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-onelayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 5, 1000, 40);
    }

    //two layer pretrain
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-onelayer-pretrain.dat");
        multirbm.setPersistent(false);
        multirbm.addLayer(200);
        multirbm.setLayerToTrain(0, false);
        multirbm.setModelFile("result/DBN-Pancan-GAM-twolayer-pretrain.dat");

        MultiLayerTrainModel pretrainModel(multirbm);
        pretrainModel.train(&data, 0.01, 5, 29);

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-twolayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 5, 1000, 40);
    }

    //three layer pretrain
    if(1){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-twolayer-pretrain.dat");
        multirbm.setPersistent(false);
        multirbm.addLayer(200);
        multirbm.setLayerToTrain(0, false);
        multirbm.setLayerToTrain(1, false);
        multirbm.setModelFile("result/DBN-Pancan-GAM-threelayer-pretrain.dat");

        MultiLayerTrainModel pretrainModel(multirbm);
        pretrainModel.train(&data, 0.01, 5, 30);

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-threelayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 5, 1000, 40);
    }

    //one layer train
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-onelayer-pretrain.dat");

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-onelayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.005, 5, 1000, 40, -0.01);
    }

    //two layer train
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-twolayer-pretrain.dat");

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-twolayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.005, 3, 1000, 40);
    }

    //three layer train
    if(0){
        MultiLayerRBM multirbm("result/DBN-Pancan-GAM-threelayer-pretrain.dat");

        MLP mlp;
        multirbm.toMLP(&mlp, data.getLabelNumber());
        mlp.setModelFile("result/DBN-Pancan-GAM-threelayer.dat");

        TrainModel supervisedModel(mlp);
        supervisedModel.train(&data, 0.01, 5, 118, 40);
    }

    // logistic
    if(0){
        Logistic logi(data.getFeatureNumber(), data.getLabelNumber());
        TrainModel logisticModel(logi);
        logisticModel.train(&data, 0.01, 10, 1000, 30);
    }
}

int main(){
    //testPancanTraining_11cancer_479feature();
    //testPancanTraining_22cancer_479feature();
    //testPancanAutoEncoder_11cancer_479feature();
    //testPancanTraining_11cancer_Merge500Mutation();
    //testPancanTraining_11cancer_MergeHCDCD();
    //testPancanAM();
    //testPancanDumpHidden();
    testPancanTraining_11cancer_199mutation();
}
