#include <iostream>

using namespace std;

int main() {
    int a[3][5]={
    {1,2,3,4,5},
    {6,7,8,9,10}, 
    {11,12,13,14,15}
    };
    int sum=0, j = 0;
    for(j=0; j<3; j++){
        for (int i=0; i<5; i++){
            sum+=a[j][i];
        }
    }
    cout<<sum;

    return 0;
}
