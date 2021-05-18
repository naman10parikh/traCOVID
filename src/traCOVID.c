#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
  
struct covidnode 
{ 
    char data[50]; 
    struct covidnode *left; 
    struct covidnode *right; 
}; 
  
struct covidnode * createNode(char *data) 
{ 
    struct covidnode *covidnode = (struct covidnode *)malloc(sizeof(struct covidnode)); 
    strcpy(covidnode->data, data); 
    covidnode->left = NULL; 
    covidnode->right = NULL; 
    return covidnode; 
} 

void addNode(struct covidnode* insert, char* received, struct covidnode* head)
{
    if (strcmp(head->data, received)!=0)
    {
        if (head->left!=NULL)
        {
            addNode(insert, received, head->left);
        }
        if (head->right!=NULL)
        {
            addNode(insert, received, head->right);
        }
    }
    else
    {
        if (head->left!=NULL)
        {
            if (strcmp(head->left->data, insert->data)<0)
            {
                head->right=insert;
            }
            else
            {
                head->right=head->left;
                head->left=insert;
            }
        }
        else if (head->right!=NULL)
        {
            if (strcmp(head->right->data, insert->data)>0)
            {
                head->left=insert;
            }
            else
            {
                head->left=head->right;
                head->right=insert;
            }
        }
        else
        {
            head->left=insert;
        }
    }

}

void clearOut(struct covidnode* head) 
{ 
    if (head != NULL) 
    {
        clearOut(head->left);
        clearOut(head->right);
        free(head);
    }
}

void printOut(struct covidnode* head) 
{ 
    if (head != NULL) 
    {
        printf("%s\n", head->data);
        printOut(head->left);
        printOut(head->right);
    }
}

int main(int argc, char* argv[]) 
{ 
    char compare[100];
    char received[100];
    char infected[100];
    FILE *f;
    f=fopen(argv[1], "rt");
    char bluedevil[80];
    strcpy(bluedevil, "BlueDevil");
    strcpy(compare, "DONE");
    struct covidnode* misc;
    struct covidnode* head;
    head=createNode(bluedevil);
    while(10)
    {
        fscanf(f, "%s", received);
        if (strcmp(received, compare)==0)
        {
            break;
        }
        fscanf(f, "%s", infected);
        misc=createNode(received);
        addNode(misc, infected, head);
    }
    fclose(f);
    printOut(head); 
    clearOut(head);
    return 0;
}
