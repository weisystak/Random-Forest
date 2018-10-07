#include "dtree.h"

/*-----------------------*/
/*  functions for debug  */
/*-----------------------*/
void del(node * n)
{
    //cout<<"deleting node..."<<endl;
    if(n != nullptr)
    {
        del(n->left);
        del(n->right);
        delete n;
    }
    //cout<<"X deleting node..."<<endl;
}
dtree::dtree()
{
    //ctor
}
dtree::~dtree()
{
    //cout<<"destructing dtree..."<<endl;
    del(root);
    //cout<<"X destructing dtree..."<<endl;
}

/*------------------*/
/*  main operations */
/*------------------*/
/* input: testSample, validationSample */
void dtree::init(vector<vector<string>> t, vector<vector<string>> v)
{
    //cout<<"init tree..."<<endl;
    testSamples = t;
    //cout<<"   testSamples' size: "<< testSamples.size()<<endl;
    validationSamples = v;
    root = new node;
}
void dtree::buildTree()
{
    //cout<<"building tree..."<<endl;
    splitting(root, testSamples);
    //cout<<"X building tree..."<<endl;
}
/* oob error */
/* output error rate */
double dtree::oob_error()
{
    //cout<<"    dtree oobing..."<<endl;
    double X = 0;
    for (auto oneTest: validationSamples)
    {
        string ans = oneTest.back();
        oneTest.pop_back();
        vector<double> attrs;

        for (auto attr: oneTest)
        {
            double tmp;
            stringstream ss;
            ss<<attr;
            ss>>tmp;
            attrs.push_back(tmp);
        }
        //cout<<"    ans: "<<ans<<endl;
        //cout<<"    res: "<<classify(attrs);

        //cout<<"    before classify"<<endl;
        if(ans != classify(attrs))
        {
            X++;
            //cout<<" X"<<endl;
        }
        //else
           //cout<<" O"<<endl;
        //cout<<"    after classify"<<endl;
    }
    //cout<<"    X dtree oobing..."<<endl;
    return X/(double)validationSamples.size();

}
/* output the result class */
string dtree::classify(vector<double> attrs)
{
    //cout<<"classifying..."<<endl;
    return traverse(root, attrs);
    //cout<<"X classifying..."<<endl;
}

/*------------------*/
/* helper function */
/*------------------*/
/* input: node to be expanded, Samples */
/* expand nodes */
/* bug: when samples' size == 0 */
void dtree::splitting(node* cur, vector<vector<string>> samples)
{
    //cout<<"splitting tree..."<<endl;
    Bag bag(samples);
    *cur = bag.getNode();
    double GL = GiniImpurity(bag.getLsamples());
    double GR = GiniImpurity(bag.getRsamples());

    //cout<<"    GL "<<GL<<endl;
    //cout<<"    GR "<<GR<<endl;

    cur->left = new node;
    cur->right = new node;
    if(GL == 0)
    {
        cur->left->Class = bag.getLsamples().back().back();
    }
    else
    {
        splitting(cur->left, bag.getLsamples());
    }


    if(GR == 0)
        cur->right->Class = bag.getRsamples().back().back();
    else
        splitting(cur->right, bag.getRsamples());


    //cout<<"X splitting tree..."<<endl;
}
double dtree::GiniImpurity(vector<vector<string>> samples)
{
    double n = samples.size();
    double G = 1;

    /* ********** */
    /*    Gini    */
    /* ********** */
    /* cnt each class's num */
    map<string, int> cnt;
    for (auto oneSample: samples)
        cnt[oneSample.back()]++;

    /* compute each pk */
    vector<double> ratios;
    for (auto nk: cnt)
        ratios.push_back(nk.second / n);
    /* compute Gini Index */
    for (auto pk: ratios)
        G -= pk * pk;
    return G;
}


/* input: attrs  */
/* output: class */
string dtree::traverse(node* cur, vector<double> attrs)
{
    //cout<<"traversing..."<<endl;
    assert(cur != nullptr);
    if(cur->isLeaf())
    {
        //cout<<"    is Leaf!!"<<endl;
        return cur->Class;
    }
    else
    {
        if(attrs[cur->attr] > cur->threshold)
            return traverse(cur->right, attrs);
        else
            return traverse(cur->left, attrs);
    }
    //cout<<"X traversing..."<<endl;
}





