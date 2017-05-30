#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
/*
struct Node
{
    int row;
    int col;
    
    Node *left;
    Node *right;
    
    Node()
    : row(-1)
    , col(-1)
    , left(nullptr)
    , right(nullptr)
    {}
};

class BTree
{
    public:
        BTree() : m_root(nullptr) {}
        
        ~BTree() { clear(); }
        
        
        std::string preorder_traverse()
        {
            std::string out;
            if (m_root)
            {
                out = preorder_traverse_impl(m_root);
            }
            return out;
        }
        

        void clear()
        {
            if (m_root)
            {
                std::queue<Node*> q;
                q.push(m_root);
                
                while (!q.empty())
                {
                    Node *top = q.front();
                    q.pop();
                    
                    if (top->left){
                        q.push(top->left);   
                    }
                    if (top->right){
                        q.push(top->right);   
                    }
                }
            }
        }
        
    protected:
    
    
    std::string preorder_traverse_impl(Node *root)
    {
        if (!root){
            return "";
        }
        
        std::string out(std::to_string(root->col) + " " + std::to_string(root->row) + " " );
        
        out += preorder_traverse_impl(root->right);
        out += preorder_traverse_impl(root->left);
        
        return out;
    }
    //private:
    public:
        Node *m_root;
};

Node* init2dArray(int **array, int height, int width, int row, int col)
{            
    if (!array || (row < 0 || row == height) || (col < 0 || col == width)){
        return nullptr;   
    }
            
    if (array[row][col] == -1) { return nullptr; }
    
    
    Node *curr = new Node();
    curr->row = row;
    curr->col = col;
    
    array[row][col] = -1; // mark as visited
    
    curr->right = init2dArray(array, height, width, row, col + 1);
    curr->left  = init2dArray(array, height, width, row + 1, col);
    
    return curr;        
}


std::vector<std::string> split(const std::string &str, char split_ch)
{
    std::vector<std::string> out;
    
    size_t pos = 0, pos_prev = 0;
    while((pos = str.find(split_ch, pos)) != std::string::npos)
    {
        std::string token = str.substr(pos_prev, pos);
        
        //cerr << token << endl;
        
        pos_prev = pos++;
    }
    return out;
}

*/
void fill_row(int **array, int rows, int cols, int row, std::string &str)
{
    if (!array || (row < 0 || row >= rows)) { 
        return;
    }
    
    for (int i = 0; i < cols; i++)
    {
        array[row][i] = (i >= str.size() || str[i] == '.') ? -1 : 0;
        
        //cerr << array[row][i];
    }
       cerr << endl;
}

std::string trim(std::string&& str)
{
    str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
    str.erase(str.find_last_not_of(' ')+1);         //surfixing spaces
    return str;
}


void findNeigbours(int **array, int rows, int cols, int row, int col)
{
    int r = row;
    int c = col;
    
    int right_neib_row = -1;
    int right_neib_col = -1;
    
    int bottom_neib_row = -1;
    int bottom_neib_col = -1;
    
    // go right
    for (int i = col + 1; i < cols; i++)
    {
        if (array[row][i] == 0)
        {
            right_neib_row = row;
            right_neib_col = i;
            break;
        }
    }
    
    // down
    for (int i = row + 1; i < rows; i++)
    {
        if (array[i][col] == 0)
        {
            bottom_neib_row = i;
            bottom_neib_col = col;
            break;
        }
    }
    cout << col << " " << row << " " <<
        right_neib_col << " " << right_neib_row << " " << 
        bottom_neib_col << " " << bottom_neib_row << endl;
}

int main()
{
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();
   // cerr << height << " " << width << endl;
    
    int **array = new int* [height];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            array[i] = new int[width];
            std::memset((void*)array[i], -1, sizeof(array[i])/sizeof(int));
        }
    }

    for (int i = 0; i < height; i++) {
        string line; // width characters, each either 0 or .
        getline(cin, line);
       // cerr << line << endl;
        
        fill_row(array, height, width, i, line);
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (array[i][j] == -1){
                continue;   
            }
            
            findNeigbours(array, height, width, i, j);
        }
    }
    

    //BTree tree;
    
    //tree.m_root = init2dArray(array, height, width, 0, 0);

   // cout << trim(tree.preorder_traverse()) << endl;

    for (int j = 0; j < width; j++){
        delete [] array[j];    
    }
    delete [] array;

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;


    // Three coordinates: a node, its right neighbor, its bottom neighbor
   // cout << "0 0 1 0 0 1 1 0 -1 -1 -1 -1 0 1 -1 -1 -1 -1" << endl;
}
