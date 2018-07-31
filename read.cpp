#include<iostream>
#include<fstream>

using namespace std;

int main()
{
    ifstream fp;
    ofstream f;
    f.open("Img2_B.jpg.txt");
    fp.open("T2_B.txt");    
    int a,b;
    while(fp>>a>>b)
        f<<b<<" "<<a<<"\n";
    return 0;
}
