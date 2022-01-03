#include <bits/stdc++.h>
using namespace std;

struct treeNode
{
    treeNode *lchild = nullptr, *rchild = nullptr;
    int data;
};
int index;
ofstream fout;

// function announcement
treeNode *preorderBuild(int pre[], int in[], int start, int end);
int findData(int in[], int start, int end, int data);
void postorderShow(treeNode *root);
treeNode *postorderBuild(int post[], int in[], int start, int end);
void preorderShow(treeNode *root);

int main()
{
    int times;
    int len;
    treeNode *root = nullptr;
    string file;
    string pattern;
    ifstream fin;

    cout << "Please enter the filename:";
    cin >> file;
    fin.open(file, ios::binary);
    file = "output" + file.substr(5);
    fout.open(file);
    fin >> times;
    for (int i = 0; i < times; i++)
    {
        fin >> pattern;
        fin >> len;
        int first[len], second[len];
        for (int j = 0; j < len; j++)
            fin >> first[j];
        for (int j = 0; j < len; j++)
            fin >> second[j];
        if (pattern == "preorder-inorder")
        {
            index = 0;
            root = preorderBuild(first, second, 0, len - 1);
            postorderShow(root);
        }
        else if (pattern == "postorder-inorder")
        {
            index = len - 1;
            root = postorderBuild(first, second, 0, len - 1);
            preorderShow(root);
        }
        delete[] first;
        delete[] second;
        root = nullptr;
        fout << endl;
    }
    fin.close();
    fout.flush();
    fout.close();
}

treeNode *preorderBuild(int pre[], int in[], int start, int end)
{
    if (start > end)
        return nullptr;
    treeNode *Node = new treeNode();
    Node->data = pre[index++];
    if (start == end)
        return Node;
    int in_index = findData(in, start, end, Node->data);
    Node->lchild = preorderBuild(pre, in, start, in_index - 1);
    Node->rchild = preorderBuild(pre, in, in_index + 1, end);
}

void postorderShow(treeNode *root)
{
    if (root == nullptr)
        return;
    postorderShow(root->lchild);
    postorderShow(root->rchild);
    fout << root->data << " ";
}

treeNode *postorderBuild(int post[], int in[], int start, int end)
{
    if (start > end)
        return nullptr;
    treeNode *Node = new treeNode();
    Node->data = post[index--];
    if (start == end)
        return Node;
    int in_index = findData(in, start, end, Node->data);
    Node->rchild = postorderBuild(post, in, in_index + 1, end);
    Node->lchild = postorderBuild(post, in, start, in_index - 1);
}

void preorderShow(treeNode *root)
{
    if (root == nullptr)
        return;
    fout << root->data << " ";
    preorderShow(root->lchild);
    preorderShow(root->rchild);
}

int findData(int in[], int start, int end, int data)
{
    for (int i = start; i < end; i++)
        if (in[i] == data)
            return i;
}