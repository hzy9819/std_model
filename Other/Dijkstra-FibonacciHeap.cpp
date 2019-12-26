#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<math.h>
#include<ctime>

using namespace std;

const int N=1005;
const int INF=1e9;

int tot=0;
int n;
int edge[N][N];
int dis[N];
bool flag[N];

class Fibnode
{
public:
  int num;
  int id;

  int degree;
  Fibnode *left;
  Fibnode *right;
  Fibnode *child;
  Fibnode *fa;
  bool flag;
  Fibnode();
  Fibnode(int num_,int id_);
};
Fibnode::Fibnode()
{num=0;id=0;degree=0;left=this;right=this;child=NULL;fa=NULL;flag=false;}
Fibnode::Fibnode(int num_,int id_)
{num=num_;id=id_;degree=0;left=this;right=this;child=NULL;fa=NULL;flag=false;}
class Fibheap
{
public:
  int tot;
  int maxdegree;
  Fibnode *nowmin;
  Fibnode **cons;

  Fibheap();
  ~Fibheap();
  void add(Fibnode *node,Fibnode *root);
  void remove(Fibnode *node);
  void insert(int num,int id);
  void insert(Fibnode *node);
  void link(Fibnode *node,Fibnode *root);
  Fibnode* extractmin();
  void consolidate();
  void delmin();
  int getminid();
  int getmin();
}a;
Fibheap::Fibheap()
{
  tot=0;
  maxdegree=0;
  nowmin=NULL;
  cons=NULL;
}
Fibheap::~Fibheap(){}
void Fibheap::add(Fibnode *node,Fibnode *root)
{
  node->left=root->left;
  root->left->right=node;
  node->right=root;
  root->left=node;
}
void Fibheap::remove(Fibnode *node)
{
  node->left->right=node->right;
  node->right->left=node->left;
}
void Fibheap::insert(Fibnode *node)
{ 
  if(tot==0)
    nowmin=node;
  else
  {
    
    add(node,nowmin);
    if(node->num<nowmin->num)
      nowmin=node;
  }
  tot++;
}
void Fibheap::insert(int num,int id)
{ 
  Fibnode *node;
  node=new Fibnode(num,id);
  if(node==NULL)
    return;
  insert(node);
}
Fibnode* Fibheap::extractmin()
{
  Fibnode *p=nowmin;
  if(p==p->right)
    nowmin=NULL;
  else
  {
    remove(p);
    nowmin=p->right;
  }
  p->left=p->right=p;
  return p;
}
void Fibheap::link(Fibnode *node,Fibnode *root)
{
  remove(node);
  if(root->child==NULL)
    root->child=node;
  else
    add(node,root->child);
  node->fa=root;
  root->degree++;
  node->flag=false;
}
void Fibheap::consolidate()
{
  int d,D;
  Fibnode *x,*y,*tmp;
  cons =(Fibnode **)realloc(cons,sizeof(Fibheap *)*N);
  D=N;  
  for(int i=0;i<D;i++)
    cons[i]=NULL;
  while(nowmin!=NULL)
  {
    x=extractmin();
    d=x->degree;
    while(cons[d]!=NULL)
    {
        y=cons[d];
        if(x->num>y->num)
          swap(x,y);
        link(y,x);
        cons[d]=NULL;
        d++;
    }
    cons[d]=x;
  }
 
  nowmin=NULL;
  for(int i=0;i<D;i++)
  {
    if(cons[i]!=NULL)
    {
      if(nowmin==NULL)
        nowmin=cons[i];
      else
      {
        add(cons[i],nowmin);
        if(cons[i]->num<nowmin->num)
          nowmin=cons[i];
      }
    }
  }
}
void Fibheap::delmin()
{ 
  if(nowmin==NULL)
    return;
  Fibnode *child=NULL;
  Fibnode *m=nowmin;
  while(m->child!=NULL)
  {
    child=m->child;
    remove(child);
    if(child->right==child)
      m->child=NULL;
    else
      m->child=child->right; 
    add(child,nowmin); 
    child->fa=NULL;
  }

  remove(m);
  if(m->right==m)
    nowmin=NULL;
  else
  {
    nowmin=m->right; 
    consolidate();
  }
  tot--; 
  delete m;
}
int Fibheap::getminid()
{
  if(nowmin==NULL)
    return 0;
  return nowmin->id;
}
int Fibheap::getmin()
{
  int minid;
  do
  {
    minid=getminid();
    if(minid!=0)
      delmin();
  }while(flag[minid]!=0);
  return minid;
}

void init()
{
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
      scanf("%d",&edge[i][j]);
  for(int i=1;i<=n;i++)
    dis[i]=INF;
  dis[1]=0;
  a.insert(0,1);
  for(int i=1;i<=n;i++)
  {
    int now=a.getmin();
    flag[now]=1;
    for(int j=1;j<=n;j++)
      if(dis[j]>dis[now]+edge[now][j])
      {
        dis[j]=dis[now]+edge[now][j];
        a.insert(dis[j],j);
      }
  }
  for(int i=1;i<=n;i++)
    printf("%d\n",dis[i]);
}
int main()
{
  double start,end;
  start=clock();
  init();
  end=clock();
  printf("%lf\n",end-start);
  return 0;
}