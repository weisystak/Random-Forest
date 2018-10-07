#ifndef DTREE_H
#define DTREE_H
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "bag.h"

using namespace std;




class dtree
{
    public:
        dtree();
        ~dtree();
        /*------------------*/
        /*  main operations */
        /*------------------*/
        /* input: testSample, validationSample */
        void init(vector<vector<string>>, vector<vector<string>>);
        void buildTree();
        /* oob error */
        /* output error rate */
        double oob_error();
        /* input: attrs */
        /* output the result class */
        string classify(vector<double>);

        /*------------------*/
        /* helper function */
        /*------------------*/

        /* input: node to be expanded, Samples */
        /* expand nodes */
        void splitting(node*, vector<vector<string>>);
        /* input: samples */
        double GiniImpurity(vector<vector<string>>);
        /* input: cur node, attrs  */
        /* output: class    */
        string traverse(node*, vector<double>);

        /*-----------------------*/
        /*  functions for debug  */
        /*-----------------------*/

        node* root;
        vector<vector<string>> testSamples;
        vector<vector<string>> validationSamples;

        /* unused */
        double AttrBaggingRatio;

};

#endif // DTREE_H

