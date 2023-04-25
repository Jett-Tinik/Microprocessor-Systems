/*
if(key==fast value)
  if(fast->left == NULL && fast -> right ==NULL){
    cout <<"============"<< endl;
    cout <<"Case I delete"<< endl;
    if(slow -> left == fast){
      slow ->left =NULL;
      cout <<"About to delete"<<ednl;
    }
    else {
      slow -> right = NULL;
      cout <<"About to delete"<<endl;
      delete fast
    }
  }
  else if (fast->left ==NULL && fast->right !=NULL){
    cout <<"-------------"<< endl;
    cout <<"Case II delete"<< endl;
    if(slow->left = fast){
      slow->left = fast->right;
    }
    else{
    slow->right = fast ->right;
    }
    cout<<"About to delete"<<endl;
    delete fast;
  }
  else if(fast -> left != NULL & fast->right == NULL){
    cout<<"----------------"<< endl;
    cout<<"Case II delete"<< endl;
    if(slow->left ==fast){
      slow->left = fast->left
    }
    else{
      slow->right=fast left;

    }
  }

  int minValTRee(TreeChunk *start){
    if(start==NULL){
      retrun -1;
    }
    while(start->left !=NULL)
      start = start->left;
    return start->value;
  }

  else{
    cout<<"========="<<endl;
    cout<<"CAse III delete. Fun fun fun"<<endl;
    int swap = minValTree(fast->right);
    fast->value=swap;
    deleteNode(swap, fast->right);
  }

*/