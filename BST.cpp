#include <bits/stdc++.h>
using namespace std;

struct treeNode
{
    treeNode *lchild = nullptr, *rchild = nullptr;
    int data;
};

// function announcement
treeNode *insertNode(treeNode *root, int token);
bool deleteNode(treeNode *root, int token);
bool search(treeNode *root, int token);
void inorder(treeNode *root);
void preorder(treeNode *root);
void postorder(treeNode *root);
void levelorder(treeNode *root);
void BST();

treeNode *mapInsert(treeNode *root, int token);
void searchBroccoli(treeNode *root, int broccoli);
void goCapooGo(treeNode *root, int sword, int meaty);
void FindMeaty();

// because original searchBroccoli funtion cannot delete leaf nodes
// so I let MeatyMap be a global variable
treeNode *MeatyMap = nullptr;

int main()
{
    // all variables need to be initialized or bad things might happen
    int mainManuSelect = 3;
    // main menu here
    while (mainManuSelect != 0)
    {
        if (mainManuSelect == 1)
            BST();
        if (mainManuSelect == 2)
            FindMeaty();
        cout << "(1)Binary searching Tree." << endl;
        cout << "(2)Finding Meaty." << endl;
        cout << "(0)Escape." << endl;
        cin >> mainManuSelect;
    }
}

void BST()
{
    char mode = 'A';
    int input;
    // initialize the root is very important
    treeNode *root = nullptr;
    while (mode != 'R' && mode != 'r')
    {
        if (mode == 'I' || mode == 'i')
        {
            // insert treeNode
            cout << "Enter numbers to insert : ";
            cin >> input;
            while (input != -1)
            {
                root = insertNode(root, input);
                cin >> input;
            }
        }
        if (mode == 'D' || mode == 'd')
        {
            // delete treeNode
            cout << "Enter numbers to delete : ";
            cin >> input;
            while (input != -1)
            {
                if (deleteNode(root, input))
                    cout << "Number " << input << " is deleted." << endl;
                else
                    cout << "Number " << input << " is not exist." << endl;
                cin >> input;
            }
        }
        if (mode == 'S' || mode == 's')
        {
            // search specific number
            cout << "Enter numbers to search : ";
            cin >> input;
            while (input != -1)
            {
                if (search(root, input))
                    cout << "Number " << input << " is found." << endl;
                else
                    cout << "Number " << input << " is not found." << endl;
                cin >> input;
            }
        }
        if (mode == 'P' || mode == 'p')
        {
            // print all the treeNode data by preorder, inorder, postorder and levelorder
            cout << "The tree in prefix order : ";
            preorder(root);
            cout << endl
                 << "The tree in infix order : ";
            inorder(root);
            cout << endl
                 << "The tree in postfix order : ";
            postorder(root);
            cout << endl
                 << "The tree in level order : ";
            levelorder(root);
            cout << endl;
        }
        // second menu
        cout << "(I)nsert numbers." << endl;
        cout << "(D)elete numbers." << endl;
        cout << "(S)earch numbers." << endl;
        cout << "(P)rint 4 kinds of orders" << endl;
        cout << "(R)eturn" << endl;
        cin >> mode;
    }
}

// return treeNode pointer root otherwise root will point to nothing even insertNode function active normally
treeNode *insertNode(treeNode *root, int token)
{
    if (root == nullptr)
    {
        root = new treeNode();
        root->data = token;
        cout << "Number " << token << " is inserted." << endl;
        return root;
    }
    else if (root->data < token)
    {
        root->rchild = insertNode(root->rchild, token);
    }
    else if (root->data > token)
    {
        root->lchild = insertNode(root->lchild, token);
    }
    else if (root->data == token)
    {
        root->data = token;
        cout << "Error. Number " << token << " exists." << endl;
        return root;
    }
}

// return bool to check if treeNode was successfully deleted
bool deleteNode(treeNode *root, int token)
{
    if (root == nullptr)
        return false;
    treeNode *now = root, *next;
    // use two pointer to ensure leaf nodes can be deleted smoothly by changing parent node's pointer
    if (root->data > token)
        next = now->lchild;
    else if (root->data < token)
        next = now->rchild;
    else
        next = now;
    while (1)
    {
        if (next == nullptr)
            return false;
        else if (next->data > token)
        {
            now = next;
            next = next->lchild;
        }
        else if (next->data < token)
        {
            now = next;
            next = next->rchild;
        }
        else
            break;
    }
    if (next->lchild == nullptr && next->rchild == nullptr)
    {
        if (now->lchild == next)
            now->lchild = nullptr;
        else if (now->rchild == next)
            now->rchild = nullptr;
        delete next;
    }
    else if (next->lchild == nullptr)
    {
        treeNode *temp = next->rchild;
        next->data = temp->data;
        next->lchild = temp->lchild;
        next->rchild = temp->rchild;
        delete temp;
    }
    else if (next->rchild == nullptr)
    {
        treeNode *temp = next->lchild;
        next->data = temp->data;
        next->lchild = temp->lchild;
        next->rchild = temp->rchild;
        delete temp;
    }
    else
    {
        now = next;
        next = next->rchild;
        treeNode *temp = now;
        while (next->lchild)
        {
            temp = next;
            next = next->lchild;
        }
        now->data = next->data;
        if (now == temp)
            now->rchild = next->rchild;
        else
            temp->lchild = next->rchild;
        delete next;
    }
    return true;
}

// return bool to check if data exists
bool search(treeNode *root, int token)
{
    if (root == nullptr)
        return false;
    else
    {
        if (token < root->data)
            return search(root->lchild, token);
        else if (token > root->data)
            return search(root->rchild, token);
        else
            return true;
    }
}

// left->middle->right
void inorder(treeNode *root)
{
    if (root == nullptr)
        return;
    inorder(root->lchild);
    cout << root->data << " ";
    inorder(root->rchild);
}

// middle->left->right
void preorder(treeNode *root)
{
    if (root == nullptr)
        return;
    cout << root->data << " ";
    preorder(root->lchild);
    preorder(root->rchild);
}

// left->right->middle
void postorder(treeNode *root)
{
    if (root == nullptr)
        return;
    postorder(root->lchild);
    postorder(root->rchild);
    cout << root->data << " ";
}

// parent->children->leaf
void levelorder(treeNode *root)
{
    if (root == nullptr)
        return;
    queue<treeNode *> level;
    level.push(root);
    while (level.size())
    {
        if (level.front() == nullptr)
            continue;
        if (level.front()->lchild != nullptr)
            level.push(level.front()->lchild);
        if (level.front()->rchild != nullptr)
            level.push(level.front()->rchild);
        cout << level.front()->data << " ";
        level.pop();
    }
}

void FindMeaty()
{
    int sword, meaty, broccoli;
    string map;
    int input = 0;
    cout << "Please enter the map file : ";
    cin >> map;
    ifstream fin;
    fin.open(map);
    while (fin >> input)
    {
        MeatyMap = mapInsert(MeatyMap, input);
    }
    cout << "Please enter the sword's location : ";
    cin >> sword;
    cout << "Please enter Meaty's location : ";
    cin >> meaty;
    cout << "Please enter the broccoli traps' index(0~9) : ";
    cin >> broccoli;
    cout << endl;
    searchBroccoli(MeatyMap, broccoli);
    cout << endl;
    cout << "Capoo successfully found his favorite Meaty<3" << endl;
    cout << endl;
    cout << "Shortest path to find Meaty : " << endl;
    goCapooGo(MeatyMap, sword, meaty);
    // prepare for next loop
    MeatyMap = nullptr;
}

// basically same as inserNode
treeNode *mapInsert(treeNode *root, int token)
{
    if (root == nullptr)
    {
        root = new treeNode();
        root->data = token;
        return root;
    }
    else if (root->data < token)
    {
        root->rchild = mapInsert(root->rchild, token);
    }
    else if (root->data > token)
    {
        root->lchild = mapInsert(root->lchild, token);
    }
    else if (root->data == token)
    {
        root->data = token;
        return root;
    }
}

// search broccoli traps' location and call deleteNode function
void searchBroccoli(treeNode *root, int broccoli)
{
    if (root == nullptr)
        return;
    searchBroccoli(root->lchild, broccoli);
    searchBroccoli(root->rchild, broccoli);
    int number = root->data;
    while (number)
    {
        int single = number % 10;
        if (single == broccoli)
        {
            cout << "Number " << root->data << " is deleted." << endl;
            deleteNode(MeatyMap, root->data);
        }
        number /= 10;
    }
}

// the output path is a collage
void goCapooGo(treeNode *root, int sword, int meaty)
{
    treeNode *now = root;
    stack<treeNode *> stack;
    // if sword and meaty both on the left or right subtree there is no need to push treeNode into stack
    while ((now->data < sword && now->data < meaty) || (now->data > sword && now->data > meaty))
    {
        cout << now->data << "->";
        if (now->data < sword)
            now = now->rchild;
        if (now->data > sword)
            now = now->lchild;
    }
    // while facing the fork, find sword first
    while (1)
    {
        cout << now->data << "->";
        if (now->data < sword)
        {
            stack.push(now);
            now = now->rchild;
        }
        else if (now->data > sword)
        {
            stack.push(now);
            now = now->lchild;
        }
        else
            break;
    }
    if (stack.size() != 1)
    {
        while (stack.size() > 1)
        {
            now = stack.top();
            stack.pop();
            cout << now->data << "->";
        }
    }
    if (!stack.empty())
        now = stack.top();
    while (1)
    {
        if (now->data < meaty)
        {
            if (now->data != sword)
                cout << now->data << "->";
            now = now->rchild;
        }
        else if (now->data > meaty)
        {
            if (now->data != sword)
                cout << now->data << "->";
            now = now->lchild;
        }
        else
        {
            cout << now->data << endl;
            break;
        }
    }
}