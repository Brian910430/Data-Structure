#include <bits/stdc++.h> //include all library
using namespace std;

struct Node // element of stack
{
    int x;
    int y;
};

int main()
{
    string name;
    cout << "enter filename:";
    cin >> name;    // input the file name
    ifstream fin;   // input stream
    fin.open(name); // load the file
    string mp[17];
    if (fin)
    {
        for (int i = 0; i < 17; i++)
        {
            fin >> mp[i];
        }
        for (int i = 0; i < 17; i++)
        {
            cout << mp[i] << endl;
        }
    }

    while (1)
    {
        bool unvisit[17][17];                   // has the rat been to
        int step = 0;                           // count the steps
        int startx = 0, starty = 0;             // start
        int endx, endy;                         // end
        int roads = 0;                          // record how many roads are there in the start
        int count = 0;                          // record how many times the rat steps on the start
        bool flag = false;                      // whether the rat reach the end
        memset(unvisit, true, sizeof(unvisit)); // initialize

        // s means points the rat is going to go
        // back means points the rat has been to
        stack<Node> s;
        stack<Node> back;

        // input the coordinate of start and end
        // if input -1, end the program
        cout << "enter start position:";
        cin >> startx >> starty;
        if (startx == -1 || starty == -1)
            break;
        cout << "enter exit position:";
        cin >> endx >> endy;
        if (endx == -1 || endy == -1)
            break;

        Node A = {startx, starty}; // the start
        s.push(A);

        if (mp[A.x][A.y - 1] == '0')
            roads++;
        if (mp[A.x][A.y + 1] == '0')
            roads++;
        if (mp[A.x - 1][A.y] == '0')
            roads++;
        if (mp[A.x + 1][A.y] == '0')
            roads++;

        while (!s.empty()) // if there's still ways to go
        {
            A = s.top();
            int i = A.x, j = A.y;
            int f = 0; // fork in the coordinate

            s.pop();
            unvisit[i][j] = false;

            // reach the end
            if (i == endx && j == endy)
            {
                flag = true;
                break;
            }

            // stack is FILO
            // so check left first
            // then up,down,right follow the sequence
            if (mp[i][j - 1] == '0' && unvisit[i][j - 1])
            {
                Node temp;
                temp.x = i;
                temp.y = j - 1;
                f++;
                s.push(temp);
            }
            if (mp[i - 1][j] == '0' && unvisit[i - 1][j])
            {
                Node temp;
                temp.x = i - 1;
                temp.y = j;
                f++;
                s.push(temp);
            }
            if (mp[i + 1][j] == '0' && unvisit[i + 1][j])
            {
                Node temp;
                temp.x = i + 1;
                temp.y = j;
                f++;
                s.push(temp);
            }
            if (mp[i][j + 1] == '0' && unvisit[i][j + 1])
            {
                Node temp;
                temp.x = i;
                temp.y = j + 1;
                f++;
                s.push(temp);
            }

            if (A.x == startx && A.y == starty)
                count++;
            // if the rat passes the start once more than roads(the step0 count)
            // there is no way out
            if (count == roads + 1)
                break;

            cout << step << ":" << A.x << "," << A.y << endl;
            step++;

            // when it is a dead end
            // push the previous step in s to check if there is any other way to go
            // then pop it out
            // if the point is not a dead end, mark it down in back
            if (f == 0)
            {
                s.push(back.top());
                back.pop();
            }
            else
                back.push(A);
        }
        if (flag)
        {
            // program normally output the coordinate at the buttom of loop
            // so it is needed to output endpoint coordinate here
            cout << step << ":" << endx << "," << endy << endl;
            cout << "successfully escaped!!" << endl;
        }
        else
        {
            // when escape failed the rat need to walk backward
            // so startpoint also needs to output here
            cout << step << ":" << startx << "," << starty << endl;
            cout << "Failed to escape." << endl;
        }
    }
    return 0;
}
