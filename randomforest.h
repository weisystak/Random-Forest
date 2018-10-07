#ifndef RANDOMFOREST_H
#define RANDOMFOREST_H
#include "dtree.h"
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <cstdlib> /* rand */
#include <ctime>   /* time */
#include <utility> /* pair */
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

class RandomForest
{
    public:
        RandomForest();
        /* set sample by filename,  NumOfdTree,  validation Ratio, baggingRatio*/
        RandomForest(string, int, double, double);
        ~RandomForest();
        /*------------------*/
        /*  main operations */
        /*------------------*/
        /* print the error rate */
        void validate();
        /* print each tree's oob rate */
        void oobEachTree();

        /*------------------*/
        /* helper function */
        /*------------------*/
        /* build dtrees  */
        void buildForest();
        void setAllSample();
        /* divide sample into testSamplePool and validationSample */
        void divideSample();
        /* random select testSample from testSamplePool */
        /* output: Lsamples, Rsamples */
        pair<vector<vector<string>>, vector<vector<string>>> baggingSample();
        /* set all sample sizes */
        void setSampleSize();
        /* return final class */
        string vote(vector<double>);

        /* ------------------------------ */
        /*          NOT   Used            */
        /* ------------------------------ */
        void setNumOfAttrs();

        /*-----------------------*/
        /*  functions for debug  */
        /*-----------------------*/
        /* print each tree's result and the consensus result */
        void classifyOneSample(vector<double>);
        /* output file: output_[filename].txt */
        void outputSamples(vector<vector<string>>, string);

        vector<dtree> trees;
        vector<vector<string>> AllSample;
        vector<vector<string>> testSamplePool;
        vector<vector<string>> validationSample;
        double validationRatio, baggingRatio;
        int NumOfAttrs;
        int NumOfdTrees;
        int NumOfSamples, NumOfValidationSamples, NumOftestSamples;
        int num_bagging_Samples, num_oob_Samples;
        string filename;
};

#endif // RANDOMFOREST_H
