// HashMap.cpp
//
// Code made by Aljon Viray, ID: 86285526
// ICS 45C Winter 2019
// Project #3: Maps and Legends

#include "HashMap.hpp"


namespace
{
    unsigned int myHasher(const std::string& string)
    {
        unsigned int hashNumber = 0;

        //Sum up ascii/int value of each character in the string
        for (int i = 0; i < string.length(); i++)
        {
            hashNumber += (int)(string[i]);
        }

        //Return raw hash number
        return hashNumber;
    }


    unsigned int getHashIndex(const HashMap::HashFunction& hasher, const std::string& key, const int& numOfBuckets)
    {
        unsigned int i = (hasher(key) % numOfBuckets);
        return i;
    }
}


////////////////////////////////////////////


//Constructor 1 (Uses myHasher)
HashMap::HashMap()
    : hasher{myHasher}, numOfBuckets{initialBucketCount}, hashmapSize{0}
{
    //Create new dynamically-allocated array of Node pointers/linked lists (aka "buckets")
    bucketArray = new Node*[numOfBuckets];

    //Fill bucketArray with null pointers
    fillWithNull(numOfBuckets, bucketArray);
}


//Constructor 2 (Uses given hasher from unit tests or graders)
HashMap::HashMap(HashFunction hasher)
    : hasher{hasher}, numOfBuckets{initialBucketCount}, hashmapSize{0}
{
    bucketArray = new Node*[numOfBuckets];
    fillWithNull(numOfBuckets, bucketArray);
}


//Destructor
HashMap::~HashMap()
{
    clearAll();
    delete[] bucketArray;
}


//Copy Constructor
HashMap::HashMap(const HashMap& hm)
    : hasher{hm.hasher}, numOfBuckets{hm.numOfBuckets}, hashmapSize{hm.hashmapSize}
{
    bucketArray = new Node*[numOfBuckets];
    fillWithNull(numOfBuckets, bucketArray);
    copyBucketArray(numOfBuckets, hm.bucketArray, bucketArray);
}


//Assignment Operator
HashMap& HashMap::operator=(const HashMap& hm)
{
    if(this != &hm)
    {
        //Destruct/Delete this HashMap's contents
        this->~HashMap();

        //Overwrite bucketArray
        bucketArray = new Node*[numOfBuckets];
        fillWithNull(numOfBuckets, bucketArray);
        copyBucketArray(numOfBuckets, hm.bucketArray, bucketArray);

        //Overwrite attributes
        hasher = hm.hasher;
        hashmapSize = hm.hashmapSize;
        numOfBuckets = hm.numOfBuckets;
    }

    //Return the overwritten HashMap object
    return *this;
}


////////////////////////////////////////////


//Public Functions
void HashMap::add(const std::string& key, const std::string& value)
{
    if (contains(key) == false)
    {
        if (loadFactor() >= 0.8)
        {
            //Remember original size between rehashing process, since no Nodes are deleted
            int x = size();
            rehashBucketArray(numOfBuckets, bucketArray);
            hashmapSize = x;
        }

        //Create new Node at "head" of linked list, with given values
        addNode(key, value, bucketArray, getHashIndex(hasher, key, numOfBuckets));

        // Print out memory address & array index of new Node
        // std::cout << "New Node = " << bucketArray[getHashIndex(hasher, key, numOfBuckets)] << std::endl;
        // std::cout << key << " --> " << getHashIndex(hasher, key, numOfBuckets) << std::endl;
        printAllNodes(numOfBuckets, bucketArray);

        //Add 1 "pair of key/value" to the HashMap
        hashmapSize++;
    }
}


void HashMap::remove(const std::string& key)
{
    if(contains(key) == true)
    {
        //Note: Saying bucketArray[i] gives THE NODE ITSELF, not pointer
        const int i = getHashIndex(hasher, key, numOfBuckets);
        Node* savedNode;


        //Checks if head/first Node of bucket/linked list is to be removed
        if(bucketArray[i]->key == key)
        {
            //Remember the next Node's position
            savedNode = bucketArray[i]->next;

            //Delete current Node
            delete bucketArray[i];

            //Set current Node to point to the the one we saved earlier
            bucketArray[i] = savedNode;

            hashmapSize--;
        }


        //Iterate through bucket/linked list at index i to find key
        else
        {
            Node* currentNode = bucketArray[i];

            while(currentNode->key != key && currentNode != nullptr)
            {
                //Remember current Node to re-link things later
                savedNode = currentNode;

                //Move on to next node
                currentNode = currentNode->next;
            }

            //Once while loop finishes, that means we found the key we wanted
            //The prev Node's next is set to the to-be-deleted Node's next.
            //AKA the linked list skips the node we are about to delete
            savedNode->next = currentNode->next;

            //The Node we wanted is deleted
            delete currentNode;

            hashmapSize--;
        }

        printAllNodes(numOfBuckets, bucketArray);
    }
}


bool HashMap::contains(const std::string& key) const
{
    // Look at the bucket associated with the key
    Node* currentNode = bucketArray[getHashIndex(hasher, key, numOfBuckets)];

    while(currentNode != nullptr)
    {
        if(currentNode->key == key)
        {
            return true;
            break;
        }
        currentNode = currentNode->next;
    }

    return false;
}



std::string HashMap::value(const std::string& key) const
{
    if(contains(key) == false)
    {
        return "";
    }

    else
    {
        // Look at the bucket associated with the key
        Node* currentNode = bucketArray[getHashIndex(hasher, key, numOfBuckets)];

        while(currentNode != nullptr)
        {
            if(currentNode->key == key)
            {
                break;
            }
            else
            {
                currentNode = currentNode->next;
            }
        }

        return currentNode->value;
    }
}


unsigned int HashMap::size() const
{
    return hashmapSize;
}


unsigned int HashMap::bucketCount() const
{
    return numOfBuckets;
}


double HashMap::loadFactor() const
{   
    double x = size();
    return (x / bucketCount());
}


unsigned int HashMap::maxBucketSize() const
{
    int max = 0, temp = 0;

    for(int i = 0; i < numOfBuckets; i++)
    {
        Node* currentNode = bucketArray[i];

        //Add 1 for every non-null Node
        while(currentNode != nullptr)
        {
            temp++;
            currentNode = currentNode->next;
        }

        //Replace current max amount, if applicable
        if(temp > max)
        {
            max = temp;
        }

        temp = 0;
    }

    return max;
}


////////////////////////////////


//Private Functions
void HashMap::fillWithNull(const unsigned int& numOfBuckets, Node**& bucketArray)
{
    for (int i = 0; i < numOfBuckets; i++)
    {
        bucketArray[i] = nullptr;
    }
}


void HashMap::addNode(const std::string& key, const std::string& value, Node**& bucketArray, const int i)
{
    //Initialize new Node struct
    Node* newNode = new Node;

    //Fill new Node with given values
    newNode->key = key;
    newNode->value = value;
    newNode->next = bucketArray[i]; //Next equals the new "head" for that bucket/linked list

    //Place a new Node in the current position
    bucketArray[i] = newNode;
}


void HashMap::rehashBucketArray(unsigned int& numOfBuckets, Node**& bucketArray)
{
    //Doubles and adds 1 to numOfBuckets
    unsigned int newNumOfBuckets = (numOfBuckets*2) + 1;

    //Create new bucketArray & initialize it
    Node** newBucketArray = new Node*[newNumOfBuckets];
    fillWithNull(newNumOfBuckets, newBucketArray);

    //Go through old bucketArray, take its Nodes' data, and rehash Nodes to newBucketArray
    copyBucketArray(numOfBuckets, bucketArray, newBucketArray);

    //Overwrite variables
    this->~HashMap();
    numOfBuckets = newNumOfBuckets;
    bucketArray = newBucketArray;
}


void HashMap::copyBucketArray(const unsigned int& numOfBuckets, Node** const oldBucketArray, Node**& newBucketArray)
{
    for (int i = 0; i < numOfBuckets; i++)
    {
        Node* currentNode = oldBucketArray[i];

        while(currentNode != nullptr)
        {
            addNode(currentNode->key, currentNode->value, newBucketArray, getHashIndex(hasher, currentNode->key, numOfBuckets));
            currentNode = currentNode->next;
        }
    }
}


//For testing purposes
void HashMap::printAllNodes(const unsigned int& numOfBuckets, Node**& bucketArray) const
{
    for(int i = 0; i < numOfBuckets; i++)
    {
        Node* currentNode = bucketArray[i];
        std::cout << i << ") " << currentNode;

        while(currentNode != nullptr)
        {
            currentNode = currentNode->next;
            std::cout << " --> " << currentNode;
        }

        std::cout << std::endl;
    }
}


//Helper Function
void HashMap::clearAll()
{
    for(int i = 0; i < numOfBuckets; i++)
    {
        Node* currentNode = bucketArray[i];
        Node* savedNode;

        //Finds every key in order and removes them normally
        while(currentNode != nullptr)
        {
            savedNode = currentNode->next;
            delete currentNode;
            currentNode = savedNode;
        }

        bucketArray[i] = nullptr;
    }

    //Reset size
    hashmapSize = 0;
}