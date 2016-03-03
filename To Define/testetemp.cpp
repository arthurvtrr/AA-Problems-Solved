#include <iostream>
#include <string>

using namespace std;

template < class type1, class type2 >

void troca(type1 x, type2 y) {
    type1 aux = x;
    x = y;
    y = aux;
    cout << x << " " << y << " " << "\n";
}

int main() {
    string s = "abacate";
    float f = 0.32542135;
    troca(s, f);
    return 0;
}
