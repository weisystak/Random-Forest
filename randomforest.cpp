#include "randomforest.h"

RandomForest::RandomForest()
{
    //ctor
}
RandomForest::~RandomForest()
{
    //cout<<"destructing Forest..."<<endl;
}

/* set sample by filename, NumOfdTree,  validation Ratio, bagging Ratio  */
RandomForest::RandomForest(string filename, int NumOfdTrees, double validationRatio, double baggingRatio)
    :filename(filename),
    validationRatio(validationRatio),
    NumOfdTrees(NumOfdTrees),
    baggingRatio(baggingRatio)
{
    cout<<"constructing Forest..."<<endl;
    trees.resize(NumOfdTrees);
    setAllSample();
    setSampleSize();
    //outputSamples(AllSample, "AllSample.txt");
    buildForest();
    cout<<"X constructing Forest..."<<endl<<endl;
}


/* print the error rate */
void RandomForest::validate()
{
    cout<<"validation"<<endl;
    int correct = 0;
    vector<double> sample;
    double tmp;

    for (auto OneSample: validationSample)
    {
        string realClass = OneSample.back();
        stringstream ss;
        for (auto y = OneSample.begin(); y != OneSample.end()-1; ++y)
        {
            ss<<*y;
            ss>>tmp;
            sample.push_back(tmp);
            //cout<<tmp<<" ";
        }
        string res = vote(sample);
        //cout<<"    ans: "<<realClass<<endl;
        //cout<<"    res: "<<res;
        if(realClass == res)
        {
            correct++;
            //cout<<" O"<<endl;
        }
        //else
           // cout<<" X"<<endl;

        //cout<<realClass<<"       "<<res<<endl;
    }
    cout<<"    Num_validation_samples: "<<validationSample.size()<<endl;
    cout<<"    correct: "<<correct<<endl;
    cout<<"    correct rate: "<<(double)correct/(double)validationSample.size()<<endl;
    //cout<<"X validating..."<<endl;
}

/* print each tree's oob rate */
void RandomForest::oobEachTree()
{
    cout<<"oob error"<<endl;
    double acc = 0;
    for (auto& tree: trees)
    {
        double err = tree.oob_error();
        acc += err;
        //cout<<"    each err rate: "<<err<<endl;
    }
    cout<<"    avg oob error: "<<(double)acc/(double)trees.size()<<endl;
    //cout<<"X oobing..."<<endl;
}

/*------------------*/
/* helper function */
/*------------------*/
/* give trees the testSample */
void RandomForest::buildForest()
{
    //cout<<"building Forest..."<<endl;
    divideSample();
    for (int i = 0; i < NumOfdTrees; i++){
        auto t = baggingSample();
        //outputSamples(t.first, "testSample.txt");
        //outputSamples(t.second, "oobSample.txt");
        /* input: testSample, oob samples */
        trees[i].init(t.first, t.second);
        trees[i].buildTree();
    }
    //cout<<"X building Forest..."<<endl;
}
void RandomForest::setAllSample()
{
    /* set AllSample */
    ifstream fin(filename);
    string str;

    while(getline(fin, str)){
        assert(!str.empty());
        string tmp;
        vector<string> OneSample;

        for (int i = 0; i < str.size(); i++){
            if(str[i] != ',')
                tmp.push_back(str[i]);
            else{
                //cout<<tmp<<" ";
                OneSample.push_back(tmp);
                tmp.erase();
            }
            if(i == str.size()-1){
                OneSample.push_back(tmp);
                //cout<<tmp<<" ";
            }
        }
        //cout<<endl;
        AllSample.push_back(OneSample);
    }
}



/* divide sample into testSamplePool and validationSample */
void RandomForest::divideSample()
{
    //cout<<"dividing samples..."<<endl;

    vector<bool> selected(NumOfSamples, false);
    /* set testSamples */
    for (int i = 0; i < NumOftestSamples; i++){
        int Select;
        do{
            Select = rand() % NumOfSamples;
        }while(selected[Select]);

        selected[Select] = true;
        testSamplePool.push_back(AllSample[Select]);
        //cout<<"selected sample: "<<Select<<endl;
    }
    /* set validationSamples */
    for (int i = 0; i < NumOfSamples; i++){
        if(!selected[i])
            validationSample.push_back(AllSample[i]);
    }
    //outputSamples(testSamplePool, "testSamplePool");
}

/* random select testSample from testSamplePool */
pair<vector<vector<string>>, vector<vector<string>>> RandomForest::baggingSample()
{
    //cout<<"bagging samples..."<<endl;
    num_bagging_Samples = NumOftestSamples * baggingRatio;
    num_oob_Samples = NumOftestSamples - num_bagging_Samples;
    pair<vector<vector<string>>, vector<vector<string>>> t;


    vector<bool> selected(NumOftestSamples, false);
    /* set bagging samples */
    for (int i = 0; i < num_bagging_Samples; i++){
        int Select;
        do{
            Select = rand() % NumOftestSamples;
        }while(selected[Select]);

        selected[Select] = true;
        t.first.push_back(testSamplePool[Select]);
    }
    /* set oob Samples */
    for (int i = 0; i < NumOftestSamples; i++){
        if(!selected[i])
            t.second.push_back(testSamplePool[i]);
    }
    return t;
}

void RandomForest::setSampleSize()
{
    NumOfSamples = AllSample.size();
    NumOfValidationSamples = validationRatio * NumOfSamples;
    NumOftestSamples = NumOfSamples - NumOfValidationSamples;
    //cout<<"    NumOfSamples: "<< NumOfSamples<<endl;
    //cout<<"    NumOfValidationSamples"<<NumOfValidationSamples<<endl;
    //cout<<"    NumOftestSamples"<<NumOftestSamples<<endl;
}

/* input:  one sample  */
/* output: final class */
string RandomForest::vote(vector<double> sample)
{
    //cout<<"voting..."<<endl;
    map<string, int> m;
    for (int i = 0; i < NumOfdTrees; i++){
        m[trees[i].classify(sample)]++;
    }
    return max_element(m.begin(), m.end(), [](const pair<string, int>& a, const pair<string, int>& b)
                                            {
                                                return a.second < b.second;
                                            })->first;
    //cout<<"X voting..."<<endl;
}

/* ------------------------------ */
/*          NOT   Used            */
/* ------------------------------ */
void RandomForest::setNumOfAttrs()
{
    ifstream fin(filename);
    string str;
    getline(fin, str);
    int cnt = 0;

    for (auto x: str)
        if(x == ',')
            cnt++;
    NumOfAttrs = cnt;
}



/*-----------------------*/
/*  functions for debug  */
/*-----------------------*/
/* print each tree's result and the consensus result */
void RandomForest::classifyOneSample(vector<double> )
{

}

/* output file: output_[filename].txt */
void RandomForest::outputSamples(vector<vector<string>> s, string filename)
{
    ofstream fout("output_" + filename);
    for (auto sample: s)
    {
        for (auto data: sample)
            fout<<data<<" ";
        fout<<endl;
    }


}





