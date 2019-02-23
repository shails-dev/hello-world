#include <iostream>
using namespace std;



//BST BstNode class
class BstNode 
{
	BstNode *left;
    int data;
    BstNode *right;

    public:
        BstNode() {};
        void setLeft(BstNode* aleft) { left = aleft; };
        void setData(int aData) { data = aData; };
        void setRight(BstNode* aright) { right = aright; };
        BstNode* getLeft() { return left; };
        int getData() { return data; };
        BstNode* getRight() { return right; };
};

class BstList
{
   BstNode *root;

   public:
       BstList() { root = NULL; };//constructor
       BstNode *getRoot(){ return(root); };
       BstNode *createBstNode(int data);

       void insertElementIterative(int element);
       void disposeTree();//uses removeTreeFromMemory(BstNode *ptr).
       void removeTreeFromMemory(BstNode *ptr);

       void preOrderRec(BstNode *ptr);
       void postOrderRec(BstNode *ptr);
       void inOrderRec(BstNode *ptr);
       void levelOrder(BstNode *cBstNode);

       int bstHeightRec(BstNode *tree);
       int totalNodeRec(BstNode *tree);
       int totalInternalNodesRec(BstNode *tree);
       int totalLeafNodeRec(BstNode *tree);
       void findMirrorImage(BstNode *tree);
       BstNode* searchElementRec(BstNode *tree, int value);
       BstNode* smallestElementRec(BstNode *tree);
       BstNode* largestElementRec(BstNode *tree);
       void deleteElementRec(BstNode *parentNode, BstNode *cNode, int value);




       void Exit();

};





/*----------------------------------------------*/
// Queue Node class
class QNode 
{
    //int Data;
    BstNode *Data;
    QNode* Next;

    public:
        QNode() {};
        void setData(BstNode *aData) { Data = aData; };
        void setNext(QNode* aNext) { Next = aNext; };
        BstNode* data() { return Data; };
        QNode* next() { return Next; };
};

// List class
class LinearQueueList 
{
    QNode *front;
    QNode *rear;
    int size;

    public:
        LinearQueueList(){front=NULL;rear=NULL;size=0;};
        void setFront(QNode *nodePtr){front=nodePtr;};
        void setRear(QNode *nodePtr){rear=nodePtr;};

        QNode *createNode(BstNode *data);
        bool isEmpty();
        void enqueue(BstNode *value);
        BstNode* dequeue();
        int frontElement();
        int qSize();
        void viewQueue();
        void viewQueueR();//uses viewQueueRec().
        void viewQueueRec(QNode *ptr);
        bool clearQueue();

};

/* Creating Node */
QNode* LinearQueueList::createNode(BstNode* data)
{
    QNode *newNode = new QNode();
    if (newNode == NULL)
    {
        cout<<"Memory not allocated "<<endl;
        return 0;
    }
    else
    {
        newNode->setData(data);
        newNode->setNext(NULL);
        return newNode;
    }
}

bool LinearQueueList::isEmpty()
{
    if(front==NULL)
        return true;
    else
        return false;
}

void LinearQueueList::enqueue(BstNode* value)
{
    QNode *newNode = createNode(value);//to create a new node
    if(newNode!=NULL)
    {
        if (front == NULL)
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->setNext(newNode);
            rear = newNode;
        }
        size++;
        
    }
}

BstNode* LinearQueueList::dequeue()
{
    QNode *tmpPtr = front;
    BstNode* temp = front->data();
    front = front->next();
    delete tmpPtr;
    size--;
    return temp;
}

bool LinearQueueList::clearQueue()
{
    //Node *ptr = front;
    QNode *tmp;
    while(front!=NULL)
    {
        tmp = front->next();
        delete front;
        front = tmp;
        size--;
    }
    if(front==NULL)
    {
        rear = NULL;
        return true;
    }
    else
        return false;
}
/*----------------------------------------------*/









/* Creating BstNode */
BstNode* BstList::createBstNode(int data)
{
    BstNode *newBstNode = new BstNode();
    if (newBstNode == NULL)
    {
        cout<<"Memory not allocated "<<endl;
        return 0;
    }
    else
    {
        newBstNode->setData(data);
        newBstNode->setLeft(NULL);
        newBstNode->setRight(NULL);
        return newBstNode;
    }
}

void BstList::insertElementIterative(int element)
{
    BstNode *newBstNode,*BstNodePtr,*parentPtr;
    newBstNode = createBstNode(element);

    if(root==NULL)
        root = newBstNode;
    else
    {
        parentPtr = NULL;
        BstNodePtr = root;
        while(BstNodePtr!=NULL)
        {
            parentPtr = BstNodePtr;
            if(element<BstNodePtr->getData())
                BstNodePtr=BstNodePtr->getLeft();
            else
                BstNodePtr=BstNodePtr->getRight();
        }
        if(element < parentPtr->getData())
            parentPtr->setLeft(newBstNode);
        else
            parentPtr->setRight(newBstNode);
    }
}

void BstList::disposeTree()
{
    removeTreeFromMemory(root);
}

void BstList::removeTreeFromMemory(BstNode *ptr)
{
    if (ptr!=NULL)
    {
        removeTreeFromMemory(ptr->getLeft());
        removeTreeFromMemory(ptr->getRight());
        delete ptr;
    }
    root = NULL;
}

void BstList::preOrderRec(BstNode *ptr)
{
    if (ptr!=NULL)
    {
        cout<< ptr->getData()<<", ";
        preOrderRec(ptr->getLeft());
        preOrderRec(ptr->getRight());
    }
}

void BstList::postOrderRec(BstNode *ptr)
{
    if (ptr!=NULL)
    {
        postOrderRec(ptr->getLeft());
        postOrderRec(ptr->getRight());
        cout<< ptr->getData()<<", ";
    }
}

void BstList::inOrderRec(BstNode *ptr)
{
    if (ptr!=NULL)
    {
        inOrderRec(ptr->getLeft());
        cout<< ptr->getData()<<", ";
        inOrderRec(ptr->getRight());
    }
}

void BstList::levelOrder(BstNode *cBstNode)
{
    LinearQueueList q;
    BstNode *ptr;
    q.enqueue(cBstNode);
    while( !q.isEmpty())
    {
        ptr = q.dequeue();
        if(ptr->getLeft() != NULL)
            q.enqueue(ptr->getLeft());
        if(ptr->getRight() != NULL)
            q.enqueue(ptr->getRight());
        cout << ptr->getData() <<", ";
    }
    q.clearQueue();
}

int BstList::bstHeightRec(BstNode *tree)
{
    //BstNode *tree = root;
    int leftHeight,rightHeight;
    if(tree==NULL)
        return 0;
    else
    {
        leftHeight = bstHeightRec(tree->getLeft());
        rightHeight = bstHeightRec(tree->getRight());
        if(leftHeight > rightHeight)
            return ++leftHeight;
        else
            return ++rightHeight;
    }
}

int BstList::totalNodeRec(BstNode *tree)
{
    if(tree == NULL)
        return 0;
    else
        return( totalNodeRec(tree->getLeft()) + totalNodeRec(tree->getRight()) +1 );
}

int BstList::totalInternalNodesRec(BstNode *tree)
{
    if((tree == NULL) || ((tree->getLeft()==NULL) && (tree->getRight()==NULL)) )
        return 0;
    else
        return( totalInternalNodesRec(tree->getLeft()) + 
                totalInternalNodesRec(tree->getRight()) +1 );
}

int BstList::totalLeafNodeRec(BstNode *tree)
{
    if(tree == NULL)
        return 0;
    else if((tree->getLeft()==NULL) && (tree->getRight()==NULL))
        return 1;
    else
        return( totalLeafNodeRec(tree->getLeft()) + 
                totalLeafNodeRec(tree->getRight()) );
}

void BstList::findMirrorImage(BstNode *tree)
{
    BstNode *temp;
    if (tree != NULL)
    {
        findMirrorImage(tree->getLeft());
        findMirrorImage(tree->getRight());
        temp = tree->getLeft();
        tree->setLeft(tree->getRight());
        tree->setRight(temp);
    }
}

BstNode* BstList::searchElementRec(BstNode *tree, int value)
{
    if((tree == NULL) || (tree->getData()==value))
        return tree;
    else if(value < tree->getData())
        return searchElementRec(tree->getLeft(),value);
    else
        return searchElementRec(tree->getRight(),value);
}

BstNode* BstList::smallestElementRec(BstNode *tree)
{
    if( (tree==NULL) || (tree->getLeft()==NULL) )
        return tree;
    else
        return smallestElementRec(tree->getLeft());
}

BstNode* BstList::largestElementRec(BstNode *tree)
{
    if( (tree==NULL) || (tree->getRight()==NULL) )
        return tree;
    else
        return largestElementRec(tree->getRight());
}


void BstList::deleteElementRec(BstNode *parentNode, BstNode *cNode, int value)
{
    if(cNode == NULL)
    {
        cout<<"Element "<<value<<" not found in BST"<<endl;
        return;
    }
    else if(value < cNode->getData())
        deleteElementRec(cNode,cNode->getLeft(),value);
    else if(value > cNode->getData())
        deleteElementRec(cNode,cNode->getRight(),value);
    else if(cNode->getLeft()!=NULL && cNode->getRight()!=NULL)
    {
        cout<<"Have two childeren."<<endl;
/*        if(parentNode!=NULL)
            cout<<"parent:" <<parentNode->getData()<<endl;
        else
            cout<<"parent:NULL"<<endl;
        cout<<"cNode:" <<cNode->getData()<<endl;*/
        BstNode *temp;
        temp = largestElementRec( cNode->getLeft() );
        cNode->setData( temp->getData() );
        deleteElementRec(cNode,cNode->getLeft(),temp->getData());

    }
    else
    {
        BstNode *child;
        if( cNode->getLeft()==NULL && cNode->getRight()==NULL )//leaf child.
        {
            cout<<"No Child."<<endl;
            if(parentNode==NULL)
                root = NULL;
            else
            {
                if(cNode == parentNode->getLeft())//cNode is left child.
                    parentNode->setLeft(NULL);
                else
                    parentNode->setRight(NULL);
                delete cNode;
            }
        }
        else//either left or right child.
        {   //identify child pointer.
            if(cNode->getLeft()!=NULL)//Only Left Child.
            {
                cout<<"Only Left Child."<<endl;
                child = cNode->getLeft();
            }
            else if(cNode->getRight()!=NULL)//Only Right Child.
            {
                cout<<"Only Right Child."<<endl;
                child = cNode->getRight();
            }

            //assigning child to parent.
            if(cNode == root)
                root = child;
            else if(cNode == parentNode->getLeft())//cNode is left child.
                parentNode->setLeft(child);
            else
                parentNode->setRight(child);
            delete cNode;
            
        }



    }
        
}



/*
void BstList::preOrderIterative()
{
    
}
*/




int main()
{
    // New list
    BstList bst,output;
    BstNode *tmp;
    int choice;
    int value,pos;//position of new BstNode to be inserted/deleted.

    while (1)
    {
        cout<<endl<<"---------------------------------"<<endl;
        cout<<endl<<"Operations on Binary Search Tree "<<endl;
        cout<<endl<<"---------------------------------"<<endl;
        cout<<"1.Insert an Element "<<endl;
        cout<<"2.Pre-order Traversal "<<endl;
        cout<<"3.Post-order Traversal "<<endl;
        cout<<"4.In-order Traversal "<<endl;
        cout<<"5.Level-order Traversal "<<endl;
        cout<<"6.Determine Height of Binary Search Tree "<<endl;
        cout<<"7.Determine Numbers of Nodes "<<endl;
        cout<<"8.Determine Numbers of Internal Nodes "<<endl;
        cout<<"9.Determine Numbers of Leaf Nodes "<<endl;
        cout<<"10.Find Mirror Image of BST "<<endl;
        cout<<"11.Remove BST From Memory "<<endl;
        cout<<"12.Search an Element "<<endl;
        cout<<"13.Find Smallest Node "<<endl;
        cout<<"14.Find Largest Node "<<endl;
        cout<<"15.Delete a Node "<<endl;


        cout<<"31.Exit "<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            cout << "Enter the Element to be inserted:";
            cin >> value;
            bst.insertElementIterative(value);
            cout<<"Element has been successfully inserted."<<endl;
            break;
        case 2:
            cout << "Pre-Order Traversal of given BST:"<<endl;
            bst.preOrderRec(bst.getRoot());
            cout<<endl;
            break;
        case 3:
            cout << "Post-Order Traversal of given BST:"<<endl;
            bst.postOrderRec(bst.getRoot());
            cout<<endl;
            break;
        case 4:
            cout << "In-Order Traversal of given BST:"<<endl;
            bst.inOrderRec(bst.getRoot());
            cout<<endl;
            break;
        case 5:
            cout << "Level-Order Traversal of given BST:"<<endl;
            bst.levelOrder(bst.getRoot());
            cout<<endl;
            break;
        case 6:
            cout << "Height of Binary Search Tree:";
            cout<< bst.bstHeightRec(bst.getRoot());
            cout<<endl;
            break;
        case 7:
            cout << "Total Numbers of Nodes:";
            cout<< bst.totalNodeRec(bst.getRoot());
            cout<<endl;
            break;
        case 8:
            cout << "Total Numbers of Internal Nodes:";
            cout<< bst.totalInternalNodesRec(bst.getRoot());
            cout<<endl;
            break;
        case 9:
            cout << "Total Numbers of Leaf Nodes:";
            cout<< bst.totalLeafNodeRec(bst.getRoot());
            cout<<endl;
            break;
        case 10:
            cout << "Mirror Image of BST:";
            bst.findMirrorImage(bst.getRoot());
            cout<<endl;
            break;
        case 11:
            bst.removeTreeFromMemory(bst.getRoot());
            cout << "BST has been removed from memory.";
            cout<<endl;
            break;
        case 12:
            cout << "Enter the value to be searched:";
            cin >> value;
            tmp = bst.searchElementRec(bst.getRoot(),value);
            if(tmp==NULL)
                cout << "Element not found."<<endl;
            else
            {
                cout<< tmp <<endl;
                cout<< tmp->getData() <<endl;
            }
            break;
        case 13:
            tmp = bst.smallestElementRec(bst.getRoot());
            if(tmp==NULL)
                cout << "BST is Empty."<<endl;
            else
            {
                cout<< tmp <<endl;
                cout<< "Smallest Node is: " << tmp->getData() <<endl;
            }
            break;
        case 14:
            tmp = bst.largestElementRec(bst.getRoot());
            if(tmp==NULL)
                cout << "BST is Empty."<<endl;
            else
            {
                cout<< tmp <<endl;
                cout<< "Largest Node is: " <<tmp->getData() <<endl;
            }
            break;
        case 15:
            cout << "Enter the Element to be deleted:";
            cin >> value;
            bst.deleteElementRec(NULL,bst.getRoot(),value);
            cout<<"Element has been successfully deleted."<<endl;
            break;

        case 31:
            bst.disposeTree();

        	cout<<"Exiting..."<<endl;
        	//list.Exit();
        	return 0;    
    		//    break;  
    	default:
        	cout<<"Wrong choice"<<endl;
    	}
	}
}
