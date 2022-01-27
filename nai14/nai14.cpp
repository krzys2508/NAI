#include "iostream"
#include "vector"
#include "string"

using namespace std;

pair<string, bool> decide(vector<string> decisionToMake){
    pair<string, bool> decision;
    string day = decisionToMake.at(0);
    string outlook = decisionToMake.at(1);
    string temperature = decisionToMake.at(2);
    string humidity = decisionToMake.at(3);
    string wind = decisionToMake.at(4);

    decision.first = day;

    if (outlook == "Overcast"){
        decision.second = 1;
        return decision;
    } else if (outlook == "Sunny"){
        if (humidity == "High"){
            decision.second = 0;
            return decision;
        } else {
           decision.second = 1;
            return decision;
        }
    } else if (outlook == "Rain") {
        if (wind == "Strong"){
            decision.second = 0;
            return decision;
        } else {
            decision.second = 1;
            return decision;
        }
    }
}

int main(int argc, char* argv[]){
    vector<vector<string>> decisionsToMake = {
            {"D1", "Sunny", "Hot", "High", "Weak"},
            {"D2", "Sunny", "Hot", "High", "Strong"},
            {"D3", "Overcast", "Hot", "High", "Weak"},
            {"D4", "Rain", "Mild", "High", "Weak"},
            {"D5", "Rain", "Cool", "Normal", "Weak"},
            {"D6", "Rain", "Cool", "Normal", "Strong"},
            {"D7", "Overcast", "Cool", "Normal", "Strong"},
            {"D8", "Sunny", "Mild","High", "Weak"},
            {"D9", "Sunny", "Cool", "Normal", "Weak"},
            {"D10", "Rain", "Mild", "Normal", "Weak"},
            {"D11", "Sunny", "Mild", "Normal", "Strong"},
            {"D12", "Overcast", "Mild", "High", "Strong"},
            {"D13", "Overcast", "Hot","Normal", "Weak"},
            {"D14", "Rain", "Mild", "High", "Strong"}
    };
    vector<string> decisionsExpected = {
    {"cannot play"},
    {"Cannot play"},
    {"Can play"},
    {"Can play"},
    {"Can play"},
    {"Cannot play"},
    {"Can play"},
    {"Cannot play"},
    {"Can play"},
    { "Can play"},
    { "Can play"},
    { "Can play"},
    { "Can play"}
};

    pair<string, bool> decision;
    int check;
    for (int i = 0; i<decisionsToMake.size();i++){
        decision = decide(decisionsToMake[i]);
        cout <<"Day "<<i << " : ";
        if (decision.second == true){
             check = 1;
        cout<<"Can play ";
        }
        else {
             check =0;
            cout<<"Cannot play ";
        }
        cout<<" "<<" Expected: "<<decisionsExpected[i];
        if (check==1){
            cout << " Its a match!";
        }
        else if (check ==0){
            cout<<"Something went wrong!";
        }
        cout << endl;
    }

    return 0;
}
