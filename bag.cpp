#include "bag.h"

/* input: Samples, proportion of Bagging attr */
Bag::Bag( vector<vector<string>> samples, double attr)
{

}
Bag::~Bag()
{
    //cout<<"destructing Bag..."<<endl;
    delete bestItem;
}
/* input: Samples */
/* default num of Bagging attr: sqrt(Num_attr) */
/* not use for small num_attr */
Bag::Bag(vector<vector<string>> Samples)
    :samples(Samples)
{
    bestItem = new Item;

    //cout<<"constructing bag..."<<endl;

    //assert(samples.size() != 0);
    //cout<<"samples' size: "<<samples.size()<<endl;
    int num_attrs = samples.back().size()-1;

    int num_attr_bagging = sqrt(num_attrs);

    if (num_attrs < 10)
        num_attr_bagging = num_attrs;

    for (int i = 0; i < num_attr_bagging; i++){
        int sel_attr = rand() % num_attrs;

        /* (attrVal, class) */
        vector<pair<string,string>> attrCol;
        for (auto s: samples)
            attrCol.push_back(make_pair(s[sel_attr], s.back()));

        Item t(sel_attr, attrCol);
        t.decideThreshold();
        items.push_back(t);
    }
    //cout<<"X constructing bag..."<<endl;
}
/*------------------*/
/*  main operations */
/*------------------*/
/* select best Item */
node Bag::getNode()
{
    //cout<<"getting node..."<<endl;
    /* infinte big */
    double min_Gini = DBL_MAX;
    for (auto& item: items)
    {
        if(item.getFinalGini() < min_Gini)
        {
            *bestItem = item;
            min_Gini = item.getFinalGini();
        }
    }
    if(bestItem->getFinalLsamples().size() == 0)
    {
        bestItem->Lsamples.push_back(0);
        bestItem->selAttr = items[0].selAttr;
    }
    if(bestItem->getFinalRsamples().size() == 0 )
    {
        bestItem->Rsamples.push_back(0);
        bestItem->selAttr = items[0].selAttr;
    }

    node n;
    n.attr = bestItem -> selAttr;
    n.threshold = bestItem -> threshold;
    //cout<<"    best Gini: "<<min_Gini<<endl;
    //cout<<"X getting node..."<<endl;
    return n;
}
vector<vector<string>> Bag::getLsamples()
{
    vector<vector<string>> Lsamples;
    vector<int> L = bestItem->getFinalLsamples();
    for (auto idx: L)
        Lsamples.push_back(samples[idx]);
    return Lsamples;
}
vector<vector<string>> Bag::getRsamples()
{
    vector<vector<string>> Rsamples;
    vector<int> R = bestItem->getFinalRsamples();
    for (auto idx: R)
        Rsamples.push_back(samples[idx]);
    return Rsamples;

}
/*------------------*/
/* helper function */
/*------------------*/



