#include<stdio.h>
#include<stdlib.h>
#include<string.h>

  #define MAX 4
  #define MIN 2

  struct btreeNode 
  {
        int val[MAX + 1], count;
		char z[5][20];
        struct btreeNode *link[MAX + 1];
  };

  struct btreeNode *root;

  
  struct btreeNode * createNode(int val,char *p ,struct btreeNode *child)
  {
        struct btreeNode *newNode;
	    newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
        newNode->val[1] = val;
		strcpy(newNode->z[1],p);
        newNode->count =1;
        newNode->link[0] = root;
        newNode->link[1] = child;
        return newNode;
  }

  void addValToNode(int val,char *p, int pos, struct btreeNode *node,struct btreeNode *child)
{
        int j = node->count;
        while (j > pos) 
		{      strcpy(node->z[j+1],node->z[j]);
                node->val[j + 1] = node->val[j];
                node->link[j + 1] = node->link[j];
                j--;
        }
        node->val[j + 1] = val;
		strcpy(node->z[j+1],p);
        node->link[j + 1] = child;
        node->count++;
  }

  
  void splitNode (int val, int *pval,char *p ,char *pnme, int pos, struct btreeNode *node,struct btreeNode *child, struct btreeNode **newNode)
 {
        int median, j;

        if (pos > MIN)
                median = MIN + 1;
        else
                median = MIN;

        *newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
        j = median + 1;
        while (j <= MAX) 
		{
                (*newNode)->val[j - median] = node->val[j];
				strcpy((*newNode)->z[j - median],node->z[j]);
                (*newNode)->link[j - median] = node->link[j];
                j++;
        }
        node->count = median;
        (*newNode)->count = MAX - median;

        if (pos <=MIN)
		{
                addValToNode(val, p,pos, node, child);
        }
		else {
                addValToNode(val, p,pos - median, *newNode, child);
        }
        *pval = node->val[node->count];
		strcpy(pnme,node->z[node->count]);
		(*newNode)->link[0] = node->link[node->count];
        node->count--;
  }

  int setValueInNode(int val, int *pval,char *pnme,char *p,struct btreeNode *node, struct btreeNode **child) 
  {

        int pos;
		if (!node) 
		{
                *pval = val;
				pnme=p;
				*child = NULL;
                return 1;
        }

        if (val < node->val[1]) ///
		{
                pos = 0;
        }
		else 
		{
                for (pos = node->count;(val < node->val[pos] && pos > 1); pos--);//

                if (val == node->val[pos])//
				{
                        return 0;
                }
        }
        if (setValueInNode(val, pval,pnme,p, node->link[pos], child))
		{
                if (node->count < MAX) 
				{
                        addValToNode(*pval, p,pos, node, *child);
                } 
				else
				{
                        splitNode(*pval, pval,p,pnme, pos, node, *child, child);
                        return 1;
                }
        }
        return 0;
  }

  void insertion(int val,char *p) 
  {
        int flag, i;
		char *pnme;
        struct btreeNode *child;
		pnme=p;
        flag = setValueInNode(val, &i,pnme,p, root, &child);
		
        if (flag)
             {   root = createNode(i,p, child);
		
		}
  }

  void searching(int val, int *pos, struct btreeNode *myNode) 
  {
        if (!myNode) 
		{
                return;
        }

        if (val < myNode->val[1]) 
		{
                *pos = 0;
        } 
		else
		{
			for (*pos = myNode->count; (val < myNode->val[*pos] && *pos > 1); (*pos)--);
              
			if (val == myNode->val[*pos]) 
			{
                        printf("Given data %d is present in B-Tree,%s", val,myNode->z[*pos]);
                        return;
            }
        }
        searching(val, pos, myNode->link[*pos]);
        return;
  }

  void traversal(struct btreeNode *myNode) 
  {
        int i;
        if (myNode)
		{
                for (i = 0; i < myNode->count; i++) 
				{traversal(myNode->link[i]);
                       printf("\n\n%d  %s\n", myNode->val[i + 1],myNode->z[i+1]);
                }
		
                traversal(myNode->link[i]);
        }
  }
  int main()
  {
        int val, ch;
		char nme[20];
		FILE *fp,*fp1;
		fp=fopen("recfile.txt","r");
		fp1=fopen("btreefile.txt","a+");
		while(1)
		{
			if(feof(fp))
				break;
			else
				{
					fscanf(fp,"%d|%s\n",&val,&nme);
					insertion(val,nme); 
				//	traversal(root);
				}

		}
		printf("Enter the element to search:");
        scanf("%d", &val);
        searching(val, &ch, root);
        fcloseall();
  }

