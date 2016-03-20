#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct tree{
  int data;
  struct tree *left;
  struct tree *right;
} *root;

int size_tree = 0, height_tree = 0, sdp_tree = 0, summ_tree = 0;

void print(struct tree *root){
  if(root!=NULL){
    print(root->left);
    printf("%d ",root->data);
    print(root->right);
  }
}

//Размер
int size(struct tree *root){
  if(root==NULL) return 0;
  else  return 1 + size(root->left) + size(root->right);
}

//Высота
int height(struct tree *root){
  if(root==NULL) return 0;
  else return 1 + (size(root->left) > size(root->right) ? size(root->left) : size(root->right));
}

//Сумма Длин Путей
int sdp(struct tree **root,int L){
  if(*root==NULL) sdp_tree = 0;
  else sdp_tree = L + sdp(&(*root)->left,L+1) + sdp(&(*root)->right,L+1);
}

//Контрольная сумма
int summ(struct tree **root){
  if(*root==NULL) return 0;
  else return (**root).data + summ(&(*root)->left) + summ(&(*root)->right);
}

//Дабавление
void add(struct tree **root,int data){
  struct tree **p=root;
  while(*p!=NULL){
    if(data < (*p)->data) p = &((*p)->left);
    else if(data > (*p)->data) p = &((*p)->right);
    else break;
  }
  if(*p==NULL){
    *p = (struct tree*) malloc(sizeof(struct tree));
    (*p)->data = data;
    (*p)->right = NULL;
    (*p)->left = NULL;
  }
}

//Удаление
struct tree* del(struct tree *root, int x){
  struct tree *p,*v;
  if(root==NULL){}
  else if (x < root->data) root->left = del(root->left,x);
  else if(x > root->data) root->right = del(root->right,x);
  else {
    p=root;
    if(root->right==NULL) root = root->left;
    else if(root->left ==NULL) root = root->right;
    else {
      v = root->left;
      if(v->right!=NULL){
        while(v->right->right!=NULL) v = v->right;
        root->data = v->right->data;
        p = v->right;
      } else {
        root->data = v->data;
        p=v;
        root->left = root->left->left;
      }
    }
    p = NULL;
  }
  return root;
}

//Поиск
int search(struct tree *root, int x){
  if(root!=NULL){
    if(search(root->left,x) == 1) return 1;
    if(root->data == x) return 1;
    if(search(root->right,x) == 1) return 1;
  }
  return 0;
}

int main(){
  int i,x;
  for( i=1; i<=5; i++){
    scanf("%d",&x);
    add(&root,x);
  }
  print(root);
  printf("\n");
  scanf("%d",&x);
  del(root,x);
  //printf("\n%d\n",search(root,x));
  print(root);
  free(root);
  return 0;
}
