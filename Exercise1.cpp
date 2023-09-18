#include <iostream>

using namespace std;

int inverse(int e, int phi) {
    int d = 0;
    int x1 = 0;
    int x2 = 1;
    int tempPhi = phi;

    while (e > 0) {
        int temp1 = phi / e;
        int temp2 = tempPhi - temp1 * e;
        tempPhi = e;
        e = temp2;
        int d = x1 - x2 * temp1;
        int raw = d;
        x1 = x2;
        x2 = raw;
    }
    
    if (tempPhi == 1)
        return x2;

    return x2;
}


int main() {
    cout << inverse(3, 20);
    return 0;
}