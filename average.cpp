#include<iostream>

using namespace std;

int main(int argc, char *argv[]) {
    float sum;
    if (argc >1) {
        for (int i = 1; i < argc; i++) sum += stof(argv[i]);
        cout << "---------------------------------" << endl;
        cout << "Average of " << argc-1 << " numbers = " << sum/(argc-1) << endl;
        cout << "---------------------------------" << endl;
    } else cout << "Please input numbers to find average." << endl;
    return 0;
}