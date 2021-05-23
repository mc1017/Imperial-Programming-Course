 BNode* rootnode;
    rootnode = tree;
    tree= tree->left;
    rootnode->left = NULL;
    deallocate_tree(rootnode);
  
    std::cout<<tree->val<<std::endl;
    simplify_tree(tree->left,layer_depth,layer_count+1);
    simplify_tree(tree->right,layer_depth,layer_count+1);
    return tree;
  