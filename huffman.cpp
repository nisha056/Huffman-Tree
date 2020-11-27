# include<bits/stdc++.h>
using namespace std;
# define Max_tree 100
# define SIZE 26
// node for huffmann tree
class QueueNode
{
public:
    char data;
    unsigned freq;
    QueueNode *left,*right;
};
// structure for queue
class Queue
{
public:
    int front,rear;
    int capacity;
    QueueNode** array;
};
// A utility function to create a new Queuenode
QueueNode* newNode(char data,unsigned freq)
{
    QueueNode* temp= new QueueNode[(sizeof(QueueNode))];
    temp->left = temp->right=NULL;
    temp->data= data;
    temp->freq=freq;
    return temp;
}
// A utility function to create a queue of given capacity
Queue* createQueue(int capacity)
{
    Queue* queue= new Queue[(sizeof(Queue))];
    queue->front=queue->rear= -1;
    queue->capacity =capacity;
    queue->array = new QueueNode*[(queue->capacity* sizeof(QueueNode*))];
    return queue;
}
// A utility function to check if the size of given queue is 1
int isSizeOne(Queue* queue)
{
    return queue->front == queue->rear && queue->front != -1;

}
// A utility function to check if given queue is empty
int isEmpty(Queue* queue)
{
    return queue->front == -1;
}
// A utility function to check if given queue is full
int isFull( Queue* queue)
{
    return queue->rear == queue->capacity -1;

}
// A utility function to add an item to queue
void enQueue(Queue* queue, QueueNode* item)
{
    if(isFull(queue))
        return;
    queue->array[++queue->rear] = item;
    if(queue-> front == -1)
        ++ queue->front;
}
// A utility function to remove an item from queue
QueueNode* deQueue(Queue* queue)
{
    if(isEmpty(queue))
        return NULL;
    QueueNode* temp = queue->array[queue->front];
    if(queue->front == queue->rear)// if there is only one item in queue
        queue->front =queue->rear = -1;
    else
        ++queue->front;
    return temp;
}
// A utility function to get front of queue
QueueNode* getFront(Queue* queue)
{
    if(isEmpty(queue))
        return NULL;
    return queue->array[queue->front];
}
//A utility function to get minimum item from two queues
QueueNode* findMin(Queue* firstQueue, Queue* secondQueue)
{
    // if first queue is empty dequeue from second queue
    if(isEmpty(firstQueue))
        return deQueue(secondQueue);
    // if second queue is empty dequeue from first queue
    if(isEmpty(secondQueue))
        return deQueue(firstQueue);
    // else compare the front of two queues and dequeue the minimum
    if(getFront(firstQueue)->freq < getFront(secondQueue)->freq)
        return deQueue (firstQueue);

    return deQueue(secondQueue);

}
// utility function to check if this node is leaf
int isLeaf(QueueNode* root)
{
    return !(root->left) && !(root->right);
}
// A utility function to print an array of size n
void printArr(int arr[],int n)
{
    for(int i=0;i<n;i++)
        cout<< arr[i];
    cout<<endl;
}
// main function that builds huffmann tree
QueueNode* buildHuffmanTree(char data[],int freq[],int size)
{
    QueueNode *left, *right,*top;
    // create two empty queues
    Queue* firstQueue = createQueue(size);
    Queue* secondQueue = createQueue(size);
    //create a leaf node , enqueue it to non decreasing order to first queue. initially second queue is empty
    for(int i=0;i<size;++i)
        enQueue(firstQueue , newNode(data[i],freq[i]));
    // run while queues contain more than one node. Finally,first queue will be empty and second queue will contain only one node
    while(!(isEmpty(firstQueue) && isSizeOne(secondQueue))){
        // dequeue two nodes with minimum frequencies
        //by examining the front of both queues
        left = findMin(firstQueue , secondQueue);
        right = findMin(firstQueue, secondQueue);
        // create a new internal node with frequency equal to
        // sum of two nodes frequencies
        // Enqueue this node to second queue
        top= newNode('$', left->freq + right-> freq);
        top->left = left;
        top->right = right;
        enQueue(secondQueue , top);
}
return deQueue(secondQueue);
}

// print huffamnn code from root of Huffmann tree
// uses arr[] to store codes
void printCodes(QueueNode* root,int arr[],int top)
{
    // Assign 0 to left edge and recur
    if(root->left)
    {
        arr[top]=0;
        printCodes(root->left, arr,top+1);
    }
    // Assign 1 to right edge and recur
    if(root->right)
    {
        arr[top]=1;
        printCodes(root->right,arr,top+1);
    }
// if this is a leaf node, then it contains one of the input characters
// print the character and its code
if(isLeaf(root))
{
    cout<< root->data<<":";
    printArr(arr,top);
}
}
// main function that builds huffmann tree and
//codes by traversing the built huffmann tree
void HuffmanCodes(char data[],int freq[],int size)
{
    // construct huffman tree
    QueueNode* root = buildHuffmanTree(data,freq,size);
    // print huffman codes using the huffman tree built above
    int arr[Max_tree], top=0;
    printCodes(root,arr,top);
}

/*int main()
{
    char arr[]={'a','b','c','d','e','f'};
    int freq[]={5,9,12,13,16,45};
    int size= sizeof(arr)/ sizeof(arr[0]);
    HuffmanCodes(arr,freq,size);
    return 0;
}*/
int main()
{
    int characterFrequency [128];
    string input;
    std::vector<char> arr;
    std::vector<int> freq;
    for(int i=0 ;i<128;i++){
        characterFrequency[i] = 0;
    }
    cout<< " Enter the string ";

    cin>>input;
    for(int i=0;i<input.size();i++){
        characterFrequency[(int)input[i]]++;
    }
    for(int i=0 ;i<128;i++){
        if(characterFrequency[i]>0){
            arr.push_back((char)i);
            freq.push_back(characterFrequency[i]);
        }
    }
    HuffmanCodes(&arr[0],&freq[0],arr.size());
    return 0;
}
