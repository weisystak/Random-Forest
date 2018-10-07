#ifndef BAG_H
#define BAG_H
#include "item.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <utility>
#include <cfloat> //DBL_MAX

using namespace std;


struct node{
    node(){
        left = nullptr;
        right = nullptr;
    }
    bool isLeaf()
    {
        if(left == nullptr && right == nullptr)
            return true;
        return false;
    }

    node *left, *right;
    int attr;
    /* Only leaf need result Class */
    string Class;
    /* threshold for splitting */
    double threshold;
};

class Bag
{
    public:
        /*------------------*/
        /* 2 constructors   */
        /*------------------*/
        /* input: Samples, proportion of Bagging attr */
        Bag(vector<vector<string>>, double);
        ~Bag();
        /* input: Samples */
        /* default num of Bagging attr: sqrt(Num_attr) */
        Bag(vector<vector<string>>);



        /*------------------*/
        /*  main operations */
        /*------------------*/
        /* select best Item in bag */
        node getNode();
        vector<vector<string>> getLsamples();
        vector<vector<string>> getRsamples();




        /*------------------*/
        /* helper function */
        /*------------------*/



        /* each item correspond to an attr */
        vector<Item> items;
        vector<vector<string>> samples;
        Item* bestItem;
};

#endif // BAG_H
