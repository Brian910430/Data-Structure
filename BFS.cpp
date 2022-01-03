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
        queue<Node> q;
        q.push(graph[start]);
        while (q.size())
        {
            Node now = q.front();
            int data = now.data;
            if (graph[data].notPassed)
            {
                fout << data << " ";
                graph[data].notPassed = false;
            }
            q.pop();

            for (int i = 0; i < length; i++)
            {
                if (matrix[data][i] && graph[i].notPassed)
                {
                    q.push(graph[i]);
                }
            }
        }
        fout << endl;
    }
    fin.close();
    fout.flush();
    fout.close();
}