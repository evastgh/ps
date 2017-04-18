#include <iostream>

using namespace std;
int main(){
    double TWD_to_USD = 1;
    double CAD_to_USD = 1;
    double MXN_to_USD = 1;

    double twd, cad, mxn;
    // double twd(0), cad, mxn;
    cout << "How much Taiwanese dollars do you wish to exchange? ";
    cin >> twd;
    // cin << twd;
    // cin >> twd >> cad >> mxn;
    // cout << twd << endl;
    cout << "How much Canadian dollars do you wish to exchange? ";
    // cout << "How much Cana" + "dian dollars do you wish to exchange? ";
    // cout << "How much Cana" "dian dollars do you wish to exchange? ";
    // cout << "How much Cana"     "dian dollars do you wish to exchange? ";
    cin >> cad;
    cout << "How much Mexican pesos do you wish to exchange? ";
    cin >> mxn;

    double usd = twd*TWD_to_USD + cad*CAD_to_USD + mxn*MXN_to_USD;
    cout << "Here\'s " << usd << " dollars. Have a good day!" << endl;
    return 0;
}
