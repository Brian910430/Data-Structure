#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    bool notPassed = true;
};

int main()
{
    int times;
    int length, start;
    string file;
    ifstream fin;
    ofstream fout;
    cout << "Please enter the filename:";
    cin >> file;
    fin.open(file, ios::binary);
    file = "output" + file.substr(5);
    fout.open(file);

    fin >> times;
    for (int t = 0; t < times; t++)
    {
        fin >> length >> start;
        int matrix[length][length];
        Node graph[length];
        for (int i = 0; i < length; i++)
        {
            graph[i].data = i;
            for (int j = 0; j < length; j++)
                fin >> matrix[i][j];
        }
        stack<Node> s;
        s.push(graph[start]);
        while (s.size())
        {
            Node now = s.top();
            int data = now.data;
            if (graph[data].notPassed)
            {
                fout << data << " ";
                graph[data].notPassed = false;
            }
            s.pop();

            for (int i = length - 1; i >= 0; i--)
            {
                if (matrix[data][i] && graph[i].notPassed)
                {
                    s.push(graph[i]);
                }
            }
        }
        fout << endl;
    }
    fin.close();
    fout.flush();
    fout.close();
}