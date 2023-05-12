#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    ifstream fin("newmap.map");
    int w, h;
    fin >> w >> h;
    int arr[h][w];
    char tmp;
    for (int i  = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j )
        {
            fin >> arr[i][j];
            fin >> tmp;
        }
    }

    ofstream fout("game_map.map");

    for (int i = 0; i < h; ++i )
    {
        for (int j = 0; j < w; ++j )
        {
            fout << fixed << setw(3) << arr[i][j]  << " ";
        }
        fout << endl;
    }
    fin.close();
    fout.close();
}