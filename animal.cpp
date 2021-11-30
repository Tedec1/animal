/*
	animal.cpp

	author: L. Henke and C. Painter-Wakefield
	date: 04 November 2019

	Animal/20 questions program for CSCI 262, starter code.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <queue>
#include <utility>

using namespace std;

class node {
public:
    node(){
        data = "";
        left = nullptr;
        right = nullptr;
    }
    explicit node(string d){
        data = std::move(d);
        left = nullptr;
        right = nullptr;
    }
    string data;
    node* left;
    node* right;
};

#include <bits/stdc++.h>
#define COUNT 10
void print2DUtil(node *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->data<<"\n";

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(node *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}


void play_game(node*);
node* read_game_tree();
void write_game_tree(node*);
void delete_game_tree(node*);
void build_tree_req(node* &cur, ifstream &fin);
bool valid_response(string& s);


/**
 * Handles showing the main menu/basic UI
 */
int main() {
	node* root = read_game_tree();
	if (root == nullptr) return -1;

	while (true) {
		string tmp;
		int choice;

		cout << "Welcome to 20 questions!" << endl;
		cout << "  1) Play the game" << endl;
		cout << "  2) Save the game file" << endl;
		cout << "  3) Quit" << endl;
		cout << "Please make your selection: ";
		getline(cin, tmp);
		choice = atoi(tmp.c_str());

		switch (choice) {
    		case 1:
    			play_game(root);
    			break;
    		case 2:
    			write_game_tree(root);
    			break;
    		case 3:
    			break;
    		default:
    			cout << "Sorry, I don't understand." << endl << endl;
		}
		if (choice == 3) break;
	}

	delete_game_tree(root);
	return 0;
}

/**
 * Sets up the recursive call to the read_preorder
 * @return root of the tree
 */
node* read_game_tree() {
    ifstream fin("animal_game_tree.txt");
    string s;
    node* head = new node;
    getline(fin,s);
    head->data = s.substr(3);
    build_tree_req(head, fin);
    return head;
}

void build_tree_req(node* &cur, ifstream &fin){
    if(fin.eof()){
        return;
    }
    string s;
    getline(fin,s);
    if(!cur->left){
        cur->left = new node(s.substr(3));
        if(s[1] == 'Q'){
            build_tree_req(cur->left, fin);
        }
    }
    getline(fin,s);
    if(!cur->right){
        cur->right = new node(s.substr(3));
        if(s[1] == 'Q'){
            build_tree_req(cur->right, fin);
        }
    }
}


/**
 * Plays the game
 * @param root Root of the game tree
 */
void play_game(node* root) {
    string s;
    while(root != nullptr){
        try {
            cout << root->data << "(y/n)" << endl;
            cin >> s;
            if(valid_response(s)){
                root = root->left;
                if(root == nullptr){
                    cout << "YAY! I won!!" << endl;
                }
            } else {
                if(root->right == nullptr){
                    cout << "I lost, boo!" << endl;
                    write_game_tree(root);
                } else {
                    root = root->right;
                }
            }
        } catch (runtime_error& e){
            cout << e.what();
            continue;
        }
    }
}



/**
 * Writes the game tree, sets up a recursive call to write_preorder();
 * @param root The root of the tree
 */
void write_game_tree(node* root) {
    string s;
    cout <<"would you like to expand the game tree? (y/n)";
    cin >> s;
//    while(){
//
//    }
//

}

/**
 * Deletes the game tree
 * @param root Root of the game tree
 */
void delete_game_tree(node* root) {
    // Optional. Do a post-order deletion of the game tree.
    // This isn't strictly needed as the program exits after this is called,
    // which frees up all the memory anyway.
}


bool valid_response(string& s){
    const vector<string> yes_tests = {"Y", "y", "yes", "Yes", "YES"};
    const vector<string> no_tests = { "N", "n", "no", "No", "NO"};
    for (const string& test:yes_tests) {
        if(s == test){
            return true;
        }
    }
    for (const string& test:no_tests) {
        if(s == test){
            return false;
        }
    }
    throw runtime_error("Sorry, I didn't recognize your input, please type again");
}