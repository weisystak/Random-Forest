/* ------------------------------------------------------------------------------------------------------- */
/* can ¡§splitting attribute¡¨ appear many times in decision tree?                                           */
/* https://stackoverflow.com/questions/19993139/can-splitting-attribute-appear-many-times-in-decision-tree */
/* ------------------------------------------------------------------------------------------------------- */
#include <cstdlib> //rand
#include <ctime>
#include <iomanip>
#include "randomforest.h"

using namespace std;


int main()
{
    /* seed */
    //srand( time(NULL) );
    srand( 0 );
    vector<string> filename = {"optical-digits.txt", "cross200.txt", "iris.txt"};
    vector<double> validationRatio = {1.0/2.0, 1.0/4.0, 1.0/7.0 }, baggingRatio = {0.63, 0.63, 0.63};
    vector<int> Num_dTrees = {5, 500, 1000};


    /* validation Ratio */
    for (int i = 0; i < 3; i++){
        cout<<"#"<<i+1<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"| filename:        "<<setw(25)<<filename[0]<<" |"<<endl;
        cout<<"| Num_dTrees:      "<<setw(25)<<Num_dTrees[0]<<" |"<<endl;
        cout<<"| validationRatio: "<<setw(25)<< validationRatio[i]<<" |"<<endl;
        cout<<"| baggingRatio:    "<<setw(25)<<baggingRatio[0]<<" |"<<endl;
        cout<<"----------------------------------------------"<<endl;
        RandomForest a( "sample_data/" + filename[0], Num_dTrees[0], validationRatio[i],  baggingRatio[0]);
        cout<<"Num of All Samples: "<<a.AllSample.size()<<endl;
        cout<<"Num of training Samples: "<<a.testSamplePool.size()<<endl<<endl;
        a.validate();
        a.oobEachTree();
        cout<<endl;
    }

}
