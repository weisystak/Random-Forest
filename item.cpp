#include "item.h"
Item::Item()
{

}
/* input: selAttr, attrColumn (attrVal, class) */
Item::Item(int selAttr, vector<pair<string,string>> attrCol)
    :selAttr(selAttr)
{
    //cout<<"    constructing Item..."<<endl;
    /* convert attrCol to attrVals */
    /* string -> double */
    /* set Samples */
    /* vector<<double,string>> */
    vector<double> attrVals;
    for (auto x: attrCol)
    {
        double tmp;
        stringstream ss;
        ss<<x.first;
        ss>>tmp;
        attrVals.push_back(tmp);
        samples.push_back(make_pair(tmp, x.second));
    }
    sort(attrVals.begin(), attrVals.end());

    /* set thresholdVals */
    for (int i = 1; i < attrVals.size(); i++){
        /* discard threshold determined by 2 same values                  */
        /* because it can't classify samples whose value equals threshold */
        if(attrVals[i - 1] != attrVals[i])
        {
            double tmp = (attrVals[i - 1] + attrVals[i]) / 2.0;
            //cout<<"        threshold val: "<<tmp<<endl;
            thresholdVals.push_back(tmp);
        }
    }
    //cout<<"    X constructing Item..."<<endl;
}

/*------------------*/
/*  main operations */
/*------------------*/
void Item::decideThreshold()
{
    //cout<<"    deciding threshold..."<<endl;
    /* biggest double */
    double min_impurity = DBL_MAX;

    /* R, L temp best Rsamples, Lsamples */
    vector<int> R, L;
    //cout<<"     samples' size: "<<samples.size()<<endl;
    assert(samples.size() != 0);
    for (double x: thresholdVals)
    {

        Rsamples.clear();
        Lsamples.clear();

        for (int i = 0; i < samples.size(); i++)
        {
            if(x < samples[i].first)
                Rsamples.push_back(i);
            else
                Lsamples.push_back(i);
        }
        if(GiniImpurity() < min_impurity){
            threshold = x;
            min_impurity = GiniImpurity();
            R = Rsamples;
            L = Lsamples;

        }
    }
    Rsamples = R;
    Lsamples = L;
    //cout<<"         Rsamples.size(): "<<Rsamples.size()<<endl;
    //cout<<"         Lsamples.size(): "<<Lsamples.size()<<endl;
    //cout<<"         Gini: "<<min_impurity<<endl;

    Gini = min_impurity;
    //cout<<"    X deciding threshold..."<<endl;
}


double Item::getFinalGini()
{
    return Gini;
}

vector<int> Item::getFinalRsamples()
{
    return Rsamples;
}
vector<int> Item::getFinalLsamples()
{
    return Lsamples;
}
/*------------------*/
/* helper function */
/*------------------*/
/* require Rsamples and Lsamples values */
double Item::GiniImpurity()
{
    double nR = Rsamples.size(), nL = Lsamples.size();
    double GR = 1, GL = 1;

    /* ********** */
    /*   R Gini   */
    /* ********** */
    /* cnt each class's num */
    map<string, double> cnt;
    for (auto idx: Rsamples)
        cnt[samples[idx].second]++;

    /* compute each pk */
    vector<double> ratios;
    for (auto nk: cnt)
        ratios.push_back(nk.second / nR);
    /* compute Gini Index */
    for (auto pk: ratios)
        GR -= pk * pk;

    /* ********** */
    /*   L Gini   */
    /* ********** */
    cnt.clear();
    /* cnt each class's num */
    for (auto idx: Lsamples)
        cnt[samples[idx].second]++;
    /* compute each pk */
    ratios.clear();
    for (auto nk: cnt)
        ratios.push_back(nk.second / nL);
    /* compute Gini Index */
    for (auto pk: ratios)
        GL -= (pk * pk);
    //cout<<"              nR: "<<nR<<endl;
    //cout<<"              nL: "<<nL<<endl<<endl;
    //cout<<"                    GR: "<<GR<<endl;
    //cout<<"                    GL: "<<GL<<endl;
    //cout<<"                    nR*GR + nL*GL:  "<<nR * GR + nL * GL<<endl;
    return nR * GR + nL * GL;

}


/*-----------------------------*/
/*   functions for debugging   */
/*-----------------------------*/
void outputSamples(vector<vector<string>> s, string filename)
{
    ofstream fout("output_" + filename);
    for (auto sample: s)
    {
        for (auto data: sample)
            fout<<data<<" ";
        fout<<endl;
    }
}

void printSamples(vector<vector<string>> s, string name)
{
    cout<<"    "<<name<<endl;
    for (auto sample: s)
    {
        for (auto data: sample)
            cout<<data<<" ";
        cout<<endl;
    }
}










