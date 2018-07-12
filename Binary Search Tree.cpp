#include<iostream>
#include <fstream>
#include <string>
using namespace std;

struct node{
	int id, x, num;
	char dir;
	node* left;
	node* right;
	void change_dir(){
		if (dir == 'L')
			dir = 'R';
		else if (dir == 'R')
			dir = 'L';
	}
	void num_init(){
		num = x;
	}
};

int main(int argc, char* argv[]){
	ifstream fin;
	ofstream fout;
	fin.open(argv[1]);
	fout.open(argv[2]);
	//fin.open("case.txt");
	//fout.open("ans.txt");
	string instruction;
	int tree_num = 0;
	node* root;
	node* n;
	node* pre_now;
	node* now;
	node* delete_node;
	while (fin >> instruction){
		if (instruction == "add"){
			if (tree_num == 0){
				n = new node;
				fin >> n->id >> n->dir >> n->x;
				n->num_init();
				n->left = NULL;
				n->right = NULL;
				root = n;
				tree_num++;
			}
			else{
				char dir_record;
				n = new node;
				fin >> n->id >> n->dir >> n->x;
				n->num_init();
				n->left = NULL;
				n->right = NULL;
				now = root;
				while (now != NULL){
					pre_now = now;
					if (n->id < now->id){//left
						now = now->left;
						dir_record = 'L';
					}
					else if (n->id > now->id){//right
						now = now->right;
						dir_record = 'R';
					}
					else{//¾쩘
						now->dir = n->dir;
						now->x = n->x;
						dir_record = 'N';
						now->num_init();
						tree_num--;
						break;
					}
				}
				if (dir_record == 'L')
					pre_now->left = n;
				else if (dir_record == 'R')
					pre_now->right = n;
				tree_num++;
			}
		}
		else if (instruction == "deleteR"){
			int id;
			char dir_record;
			bool found = false;
			fin >> id;
			now = root;
			while (now != NULL){
				if (id == now->id){
					found = true;
					break;
				}
				else if (id < now->id){
					pre_now = now;
					dir_record = 'L';
					now = now->left;
				}
				else if (id > now->id){
					pre_now = now;
					dir_record = 'R';
					now = now->right;
				}
			}
			if (found){
				if (now->right != NULL &&now->left != NULL){//┳ⅹ쩵쨖언
					delete_node = now;
					now = now->right;
					pre_now = now;
					while (now->left != NULL){
						pre_now = now;
						now = now->left;
					}
					if (pre_now != now){
						if (now->right != NULL){
							pre_now->left = now->right;
						}
						else{
							pre_now->left = NULL;
						}
						delete_node->id = now->id;
						delete_node->x = now->x;
						delete_node->num = now->num;
						delete_node->dir = now->dir;
					}
					else{
						delete_node->id = now->id;
						delete_node->x = now->x;
						delete_node->num = now->num;
						delete_node->dir = now->dir;
						delete_node->right = now->right;
					}	
				}
				else if (now->right != NULL &&now->left == NULL){//쪀┳쩵쨖언
					if (now != root){
						if (dir_record == 'L'){
							pre_now->left = now->right;
						}
						else if (dir_record == 'R'){
							pre_now->right = now->right;
						}
					}
					else
						root = now->right;
				}
				else if (now->right == NULL &&now->left != NULL){//쪀┳ⅹ쨖언
					if (now != root){
						if (dir_record == 'L'){
							pre_now->left = now->left;
						}
						else if (dir_record == 'R'){
							pre_now->right = now->left;
						}
					}
					else
						root = now->left;
				}
				else{//쮁┳쨖언
					if (now != root){
						if (dir_record == 'L'){
							pre_now->left = NULL;
						}
						else if (dir_record == 'R'){
							pre_now->right = NULL;
						}
					}
					else
						root = NULL;
				}
				tree_num--;
			}
			else
				fout << "Deletion failed." << endl;
		}
		else if (instruction == "deleteL"){
			int id;
			char dir_record;
			bool found = false;
			fin >> id;
			now = root;
			while (now != NULL){
				if (id == now->id){
					found = true;
					break;
				}
				else if (id < now->id){
					pre_now = now;
					dir_record = 'L';
					now = now->left;
				}
				else if (id > now->id){
					pre_now = now;
					dir_record = 'R';
					now = now->right;
				}
			}
			if (found){
				if (now->right != NULL &&now->left != NULL){//┳ⅹ쩵쨖언
					delete_node = now;
					now = now->left;
					pre_now = now;
					while (now->right != NULL){
						pre_now = now;
						now = now->right;
					}
					if (pre_now != now){
						if (now->left != NULL){
							pre_now->right = now->left;
						}
						else{
							pre_now->right = NULL;
						}
						delete_node->id = now->id;
						delete_node->x = now->x;
						delete_node->num = now->num;
						delete_node->dir = now->dir;
					}
					else{
						delete_node->id = now->id;
						delete_node->x = now->x;
						delete_node->num = now->num;
						delete_node->dir = now->dir;
						delete_node->left = now->left;
					}
				}
				else if (now->right != NULL &&now->left == NULL){//쪀┳쩵쨖언
					if (now != root){
						if (dir_record == 'L'){
							pre_now->left = now->right;
						}
						else if (dir_record == 'R'){
							pre_now->right = now->right;
						}
					}
					else
						root = now->right;
				}
				else if (now->right == NULL &&now->left != NULL){//쪀┳ⅹ쨖언
					if (now != root){
						if (dir_record == 'L'){
							pre_now->left = now->left;
						}
						else if (dir_record == 'R'){
							pre_now->right = now->left;
						}
					}
					else
						root = now->left;
				}
				else{//쮁┳쨖언
					if (now != root){
						if (dir_record == 'L'){
							pre_now->left = NULL;
						}
						else if (dir_record == 'R'){
							pre_now->right = NULL;
						}
					}
					else
						root = NULL;
				}
				tree_num--;
			}
			else
				fout << "Deletion failed." << endl;
		}
		else if (instruction == "drop"){
			int id;
			char dir_record;
			fin >> id;
			if (tree_num != 0){
				for (int i = 1; i < id; i++){
					now = root;
					while (now != NULL){
						dir_record = now->dir;
						if (now->num == 1){
							now->change_dir();
							now->num_init();
						}
						else if (now->num == 0);
						else
							now->num--;
						if (dir_record == 'L')
							now = now->left;
						else if (dir_record == 'R')
							now = now->right;
					}
				}
				now = root;
				while (now != NULL){
					fout << now->id << ' ';
					dir_record = now->dir;
					if (now->num == 1){
						now->change_dir();
						now->num_init();
					}
					else if (now->num == 0);
					else
						now->num--;
					if (dir_record == 'L')
						now = now->left;
					else if (dir_record == 'R')
						now = now->right;
				}
				fout << endl;
			}
			else
				fout << "Tree is empty." << endl;
		}
	}
	fin.close();
	fout.close();
	return 0;
}