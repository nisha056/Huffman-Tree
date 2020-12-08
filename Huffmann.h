#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
# define Max_tree 100
# define SIZE 26
// node for huffmann tree
class QueueNode
{
public:
    char data;
    unsigned freq;
    QueueNode* left, * right;
    sf::CircleShape body;
    QueueNode():body(100.f) {
        body.setFillColor(sf::Color::Green);

    }
    void draw(sf::RenderWindow& window ) {
        std::cout << "here" << std::endl;

    }
};
// structure for queue
class Queue
{
public:
    int front, rear;
    int capacity;
    QueueNode** array;
};
// A utility function to create a new Queuenode
class Huffmann {
private:
    sf::RenderWindow window;
    sf::RectangleShape OutlineBox1;
    sf::RectangleShape OutlineBox2;
    sf::RectangleShape rec;
    //sf::Font font;
    sf::Text text;
public:
    //Huffmann();
    int nodeRaduis = 20;
    sf::CircleShape body;
    std::vector<sf::CircleShape> tree;
    std::vector<sf::Text> nodeTexts;
    std::vector<sf::VertexArray> edges;
    sf::Font font;
    std::string comma = "";
    std::string separate = "";
    sf::RectangleShape drawingArea;
    QueueNode* root;

    Huffmann():body(100.f) {
        body.setFillColor(sf::Color::Green);
        if (!font.loadFromFile("DejaVuSans.ttf"))
        {
            //error
        }
    }
    void setDrawingArea(sf::RectangleShape drawingArea) {
        this->drawingArea = drawingArea;
    }
    QueueNode* newNode(char data, unsigned freq)
    {
        QueueNode* temp = new QueueNode[(sizeof(QueueNode))];
        temp->left = temp->right = NULL;
        temp->data = data;
        temp->freq = freq;
        return temp;
    }
    // A utility function to create a queue of given capacity
    Queue* createQueue(int capacity)
    {
        Queue* queue = new Queue[(sizeof(Queue))];
        queue->front = queue->rear = -1;
        queue->capacity = capacity;
        queue->array = new QueueNode * [(queue->capacity * sizeof(QueueNode*))];
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
    int isFull(Queue* queue)
    {
        return queue->rear == queue->capacity - 1;

    }
    // A utility function to add an item to queue
    void enQueue(Queue* queue, QueueNode* item)
    {
        if (isFull(queue))
            return;
        queue->array[++queue->rear] = item;
        if (queue->front == -1)
            ++queue->front;
    }
    // A utility function to remove an item from queue
    QueueNode* deQueue(Queue* queue)
    {
        if (isEmpty(queue))
            return NULL;
        QueueNode* temp = queue->array[queue->front];
        if (queue->front == queue->rear)// if there is only one item in queue
            queue->front = queue->rear = -1;
        else
            ++queue->front;
        return temp;
    }
    // A utility function to get front of queue
    QueueNode* getFront(Queue* queue)
    {
        if (isEmpty(queue))
            return NULL;
        return queue->array[queue->front];
    }
    //A utility function to get minimum item from two queues
    QueueNode* findMin(Queue* firstQueue, Queue* secondQueue)
    {
        // if first queue is empty dequeue from second queue
        if (isEmpty(firstQueue))
            return deQueue(secondQueue);
        // if second queue is empty dequeue from first queue
        if (isEmpty(secondQueue))
            return deQueue(firstQueue);
        // else compare the front of two queues and dequeue the minimum
        if (getFront(firstQueue)->freq < getFront(secondQueue)->freq)
            return deQueue(firstQueue);

        return deQueue(secondQueue);

    }
    // utility function to check if this node is leaf
    int isLeaf(QueueNode* root)
    {
        return !(root->left) && !(root->right);
    }
    // A utility function to print an array of size n
    void printArr(int arr[], int n)
    {
        for (int i = 0; i < n; i++)
            std::cout << arr[i];
        std::cout << std::endl;
    }
    // main function that builds huffmann tree
    QueueNode* buildHuffmanTree(char data[], int freq[], int size)
    {
        QueueNode* left, * right, * top;
        // create two empty queues
        Queue* firstQueue = createQueue(size);
        Queue* secondQueue = createQueue(size);
        //create a leaf node , enqueue it to non decreasing order to first queue. initially second queue is empty
        for (int i = 0; i < size; ++i)
            enQueue(firstQueue, newNode(data[i], freq[i]));
        // run while queues contain more than one node. Finally,first queue will be empty and second queue will contain only one node
        while (!(isEmpty(firstQueue) && isSizeOne(secondQueue))) {
            // dequeue two nodes with minimum frequencies
            //by examining the front of both queues
            left = findMin(firstQueue, secondQueue);
            right = findMin(firstQueue, secondQueue);
            // create a new internal node with frequency equal to
            // sum of two nodes frequencies
            // Enqueue this node to second queue
            top = newNode('$', left->freq + right->freq);
            top->left = left;
            top->right = right;
            enQueue(secondQueue, top);
        }
        return deQueue(secondQueue);
    }

    // print huffamnn code from root of Huffmann tree
    // uses arr[] to store codes
    void printCodes(QueueNode* root, int arr[], int top)
    {
        // Assign 0 to left edge and recur
        if (root->left)
        {
            arr[top] = 0;
            printCodes(root->left, arr, top + 1);
        }
        // Assign 1 to right edge and recur
        if (root->right)
        {
            arr[top] = 1;
            printCodes(root->right, arr, top + 1);
        }
        // if this is a leaf node, then it contains one of the input characters
        // print the character and its code
        if (isLeaf(root))
        {
            std::cout << root->data << ":";
            printArr(arr, top);
        }
    }
    // main function that builds huffmann tree and
    //codes by traversing the built huffmann tree
    void HuffmanCodes(char data[], int freq[], int size)
    {
        // construct huffman tree
        root = buildHuffmanTree(data, freq, size);
        // print huffman codes using the huffman tree built above
        int arr[Max_tree], top = 0;
        printCodes(root, arr, top);
        int treeHeight = getHeight(root);
        std::cout << treeHeight << std::endl;
        int yOffset = drawingArea.getSize().y / treeHeight;
        int xOffset =drawingArea.getSize().x*std::pow(2,treeHeight-2)/(2*(std::pow(2,treeHeight-1)+1));
        sf::Vector2f rootPosition = sf::Vector2f(drawingArea.getPosition().x + drawingArea.getSize().x / 2, drawingArea.getPosition().y);
        generateTreeShape(root, rootPosition, 0,xOffset,yOffset);

        std::cout << tree.size() << std::endl;

        ///
    }
    void draw(sf::RenderWindow& window) {
        //window.draw(body);
        for (const auto a : edges) {
            window.draw(a);
        }
        for (const auto a : tree) {
            window.draw(a);
        }
        for (const auto a : nodeTexts) {
            window.draw(a);
        }
    }
    int getHeight(QueueNode* node) {
        if (isLeaf(node)) {
            return 1;
        }
        else {
            return 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }
    void generateNodeShape(QueueNode* node,sf::Vector2f position) {
        sf::CircleShape temp(nodeRaduis);
        temp.setFillColor(sf::Color::Green);
        temp.setPosition(position);
        tree.push_back(temp);

            sf::Text text;
            sf::Vector2f textOffset(5, 5);
            text.setCharacterSize(30);
            text.setPosition(position+textOffset);
            text.setFillColor(sf::Color::Black);
            text.setFont(font);
            text.setString(std::string(1, node->data));
            nodeTexts.push_back(text);

    }
    void generateEdges(sf::Vector2f starting, sf::Vector2f goal) {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = (starting);
        line[0].color = sf::Color::Black;
        line[1].position = goal;
        line[1].color = sf::Color::Black;
        edges.push_back(line);
    }
    void generateTreeShape(QueueNode* node,sf::Vector2f position,int level,int xOffset, int yOffset) {
        //sf::Vector2f position = sf::Vector2f(rootPosition.x+xOffset, rootPosition.y + level * yOffset);
        if (level == 0) {
            tree.clear();
            nodeTexts.clear();
            edges.clear();
        }
            generateNodeShape(node,position);
            if (!isLeaf(node)) {
                sf::Vector2f leftPosition = sf::Vector2f(position.x - xOffset / (level + 1), position.y + yOffset);
                sf::Vector2f rightPosition = sf::Vector2f(position.x + xOffset / (level + 1), position.y + yOffset);
                generateTreeShape(node->left, leftPosition, level+1,xOffset, yOffset);
                generateTreeShape(node->right,rightPosition , level + 1, xOffset, yOffset);
                generateEdges(position+sf::Vector2f(nodeRaduis, nodeRaduis), leftPosition+sf::Vector2f(nodeRaduis, nodeRaduis));
                generateEdges(position + sf::Vector2f(nodeRaduis, nodeRaduis), rightPosition +sf::Vector2f(nodeRaduis, nodeRaduis));
            }

    }

    int run(std::string input)
    {
        int characterFrequency[128];
        std::vector<char> arr;
        std::vector<int> freq;
        for (int i = 0; i < 128; i++) {
            characterFrequency[i] = 0;
        }

        for (int i = 0; i < input.size(); i++) {
            characterFrequency[(int)input[i]]++;
        }
        for (int i = 0; i < 128; i++) {
            if (characterFrequency[i] > 0) {
                arr.push_back((char)i);
                freq.push_back(characterFrequency[i]);
            }
        }
        if (arr.size() > 1) {
            HuffmanCodes(&arr[0], &freq[0], arr.size());
        }

        return 0;
    }
};
