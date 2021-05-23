#include <iostream>
#include <vector>
#include <string>
 

struct BNode{
  std::string val;   
  BNode* left;  
  BNode* right;
};
 
// you can define here other functions to use in the code below
 
// you can also define here other 
// structured data types or classes 
// (including member data and member functions) 
// to use in the code below
 
// do not alter the following line that begins the function build_bt

BNode* cons_tree(int layer_depth, int layer_count){
  BNode* tree;
  tree = new BNode;
  if(layer_count == layer_depth){
    tree-> left = NULL;
    tree-> right = NULL;
    tree->val = "0";
    return tree; 
  }
  else{
    tree-> val = "x" + std::to_string(layer_count+1);
    tree-> left = cons_tree(layer_depth,layer_count+1);
    tree-> right =cons_tree(layer_depth,layer_count+1);
    return tree;
  }
}

BNode* cons_value(BNode* tree, std::string input, int layer_depth, int layer_count){

  if (layer_count == layer_depth){
    tree->val = "1";
    return tree;
  }
  else if (input[layer_count] =='0'){
    return cons_value(tree->left,  input, layer_depth, layer_count+1); 
  }
  else{
    return cons_value(tree-> right, input, layer_depth, layer_count+1); 
  }
}

void deallocate_tree(BNode* tree){
  if (tree != NULL){
    deallocate_tree(tree->left);
    deallocate_tree(tree->right);
    delete tree;
  }
}


bool compare_nodes(BNode* left_subtree,BNode* right_subtree){
  
  if (left_subtree == right_subtree){
    return true;
  }  
  
  if ((left_subtree == NULL) || (right_subtree == NULL)){
    return false;
  }
  
  return ((left_subtree->val == right_subtree->val) && compare_nodes (left_subtree->left,  right_subtree->left) && compare_nodes (left_subtree->right, right_subtree->right));

}


BNode* simplify_tree(BNode* tree){
  
  if (tree->left ==NULL || tree->right ==NULL){
    return tree;
  }

  if (compare_nodes(tree->left, tree->right)){
    BNode* rootnode;
    rootnode = tree;
    tree= tree->left;
    rootnode->left = NULL;
    deallocate_tree(rootnode);
    return tree;
  }

  else{
    tree->left = simplify_tree(tree->left);
    
    tree->right = simplify_tree(tree->right);
    
    return tree;
  }
}


BNode* build_bt(const std::vector<std::string>& fvalues){
  BNode* tree;
  int layer_count=0;
  int layer_depth = fvalues[0].length();
  //construct entire tree first
  tree = cons_tree(layer_depth,layer_count);
  for (int i=0; i<fvalues.size(); i++){
    //change the value of required nodes from 0 to 1
    cons_value(tree, fvalues[i],layer_depth,layer_count);
  }
  for (int i=0; i<fvalues[0].size(); i++){
    tree=simplify_tree(tree);
  }
  return tree;
}
 
// do not alter the following function
// this function converts e.g. std::string "x3" to int 2
int label_to_idx(const std::string& label){
 
  std::string out;

  for(int i = 1; i < label.size(); i++){
    out.push_back(label[i]);
  }

  return std::stoi(out) - 1;
}
 
// do not alter the following function
std::string eval_bt(BNode* bt, const std::string& input){
 
    if( (bt->left == NULL) && (bt->right == NULL) ){
        return bt->val;
    }
    else{
        int idx = label_to_idx(bt->val);
        std::string input_idx;
        input_idx.push_back(input[idx]);
 
        if(input_idx == "0"){
            return eval_bt(bt->left, input); 
        }
        else{
            return eval_bt(bt->right, input); 
        }
    }
}
 
// do not alter the following function
int n_nodes_bt(BNode* t){
    if(t == NULL){
        return 0;
    }
    else{
        return 1 + n_nodes_bt(t->left) + n_nodes_bt(t->right);
    }
}
 
class BoolTree{
public:
 
    BoolTree(const std::vector<std::string>& fvalues){
       t = build_bt(fvalues);
    }
 
    std::string eval(const std::string& s){
        return eval_bt(t, s);
    }
 
    int n_nodes(){
        return n_nodes_bt(t);
    }
 
    ~BoolTree(){
      deallocate_tree(t);
        // complete this function 
        // (do not alter in any other way class BoolTree)
 
        // keep in mind that you can include in this function 
        // calls to functions defined outside class BoolTree
        // (as done in the member functions above)
        // and that you can define other functions
        // above and outside this class

    }
 
private:
    BNode* t;
};
 
// the main provided below must work correctly
// with your implementation for the code above
// however you can change it as you wish for your own testing 
// and your changes won't be considered for the assessment
// (in your submission you can also have an empty main or no main at all)
 
int main(){
   	std::vector<std::string> fv;
    std::string row;
 
    row = "00";
    fv.push_back(row);
    row = "01";
    fv.push_back(row);
    row = "10";
    fv.push_back(row);
    row = "11";
    fv.push_back(row);
 
    BoolTree ft2(fv);

	std::cout << ft2.n_nodes() << std::endl;

	std::cout << "ft2 truth table" << std::endl;
    std::cout << ft2.eval("00") << std::endl;
    std::cout << ft2.eval("01") << std::endl;
    std::cout << ft2.eval("10") << std::endl;
    std::cout << ft2.eval("11") << std::endl;

}