/* ********************** */
/*                        */
/*    the item in bag     */
/*                        */
/*                        */
/* ********************** */
#ifndef ITEM_H
#define ITEM_H
#include <vector>
#include <string>
#include <algorithm>
#include <cfloat> //DBL_MAX
#include <utility>
#include <sstream>
#include <map>
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

class Item
{
    public:
        Item();
        /* input: selAttr, attrColumn (attrVal, class) */
        Item(int, vector<pair<string,string>>);

        /*------------------*/
        /*  main operations */
        /*------------------*/
        void decideThreshold();
        double getFinalGini();
        vector<int> getFinalRsamples();
        vector<int> getFinalLsamples();

        /*------------------*/
        /* helper function */
        /*------------------*/
        /* require Rsamples and Lsamples values */
        double GiniImpurity();


        vector<int> Rsamples, Lsamples;
        /* <value, class> */
        vector<pair<double, string>> samples;
        /* candidate Threshold vals */
        vector<double> thresholdVals;

        int selAttr;
        double threshold;
        double Gini;
};

/*-----------------------------*/
/*   functions for debugging   */
/*-----------------------------*/
void outputSamples(vector<vector<string>>, string);


void printSamples(vector<vector<string>>, string);

#endif // ITEM_H
