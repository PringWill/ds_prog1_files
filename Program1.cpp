#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "timer.h"
using namespace std;

class Node
{
    public:
    string data;
    Node *next;
};

int getsize(Node *node)
{
    int size =0;
    while (node != NULL)
    {   
        size++;
        node = node->next;
    }
    return size;
}

void print(Node *node)
{
    while (node != NULL)
    {   
        cout << node->data << " ";
        node = node->next;
    }
}

bool isEmpty(Node *node)
{
    if (node = NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void insert (Node** head_ref, string new_data)
    {
        Node* new_node = new Node();
        new_node->data = new_data;
        new_node->next = (*head_ref);
        (*head_ref) = new_node;
    }

void remove(Node** head, int pos)
{
    Node* tmp;
    Node* prev;
    tmp = *head;
    tmp = *head;
    for (int i = 0; i < pos; i++)
    {
        if (i == 0 && pos == 1)
        {
        *head = (*head) -> next;
        free(tmp);
        }
        else
        {
            if (i == pos - 1 && tmp)
            {
                prev -> next = tmp -> next;
                free(tmp);
            }
            else
            {
                prev = tmp;
                if (prev == NULL)
                break;
                tmp = tmp -> next;
            }
        }
    }
}

int spellcheck(Node *node, string tocheck, double &numCompares)
{
    while (node != NULL)
    {   
        numCompares++;
        if (tocheck.compare(node->data) == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return 1;
}

string cleanword(string uncleanedword)
{
    char c;
    int i = 0;
    auto test = std::remove_if(uncleanedword.begin(), uncleanedword.end(), [](char const &c) {
        return !std::isalpha(c) && c != '\'';
    });


    while (uncleanedword[i])
    {
        c = uncleanedword[i];
        uncleanedword[i] = (tolower(c));
        i++;
    }
    uncleanedword.erase(test, uncleanedword.end());

    return uncleanedword;
}

int main()
{
    ifstream dict("dict.txt");                                  //open Dictionary
    
    string dictword;
    Node* head = NULL;

    while (dict >> dictword)                                    //read through Dictionary
    {
        insert(&head, dictword);                                //insert current Dictionary word into linked list
    }

    Timer Watch;                                                //initilize timer
    Watch.Start();                                              //start timer

    ifstream book("book.txt");                                  //open Book
    ofstream misspelled("misspelled.txt");                      //open a file to write misspelled words to
    int notchecked = 0, check = 0;
    double correct =0, incorrect = 0, compares = 0, wCompares = 0, rCompares = 0, tCompares;
    string bookword, tocheck, cleanedword;
    while (book >> bookword)                                    //read through Book
    {
        cleanedword = cleanword(bookword);                      //Clean the word
        if (cleanedword.empty())                                //If word is empty dont check it
        {
            notchecked++;
        }
        else
        {
            check = spellcheck(head, cleanedword, compares);    //Check word and itterate through the linked list
            if (check == 0)                                     //If word matches count correct
            {
                correct ++;                                     //Add to the number of correctly spelled words
                rCompares += compares;                          //Add to the number of rightly spelled compares   
                tCompares += compares;                          //Add to the total number of compares
                compares = 0;
            }
            else                                                //If word doesnt match count incorrect
            {
                incorrect ++;                                   //Add to the number of incorrectly spelled words
                wCompares += compares;                          //Add to the number of wrongly spelled compares
                tCompares += compares;                          //Add to the total number of comapres
                compares = 0;
                misspelled << cleanedword << endl;              //Print wrongly spelled words to a file
            }
        }
    }

    Watch.Stop();                                               //Stop Timer

    dict.close();                                               //Close the dictionary
    book.close();                                               //Close the Book
    misspelled.close();                                         //Close the misspelled word file


    cout <<  "Dictionary size " << getsize(head) << endl;
    cout << "Done Checking and these are the results" << endl;
    cout << "Finsihed in time: " << Watch.Time() <<endl;
    cout << "There are " << correct << " words found in the dictionary" << endl;
    cout << rCompares << " Compares. Average " << rCompares/correct << endl;
    cout << "There are " << incorrect << " words NOT found in the dictionary" << endl;
    cout << wCompares << " Compares. Average " << wCompares/incorrect << endl;
    cout << "There are " << notchecked << " words not checked." << endl;
    

    return 0;
}
