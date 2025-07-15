#include<iostream>
#include<vector>
#include<cstdio>
#include<windows.h>
using namespace std;
class trienode
{
public:
    char data;
    trienode*children[26];
    bool isterminal;
     trienode(char data)
    {
        this->data=data;
        for(int i=0;i<26;i++)
        {
            children[i]=NULL;
        }
        isterminal=false;
    }
};
class trie
{
public:
    trienode*root;
    trie()
    {
        root=new trienode('\0');
    }

    void inserhelp(trienode*root,string word)
    {
         if(word.length()==0)
        {
            root->isterminal=true;
            return;
        }
        int index;
        index=word[0]-'a';
        trienode*child;
        if(root->children[index]!=NULL)
        {
            child=root->children[index];

        }
        else
        {
            child=new trienode(word[0]);
            root->children[index]=child;
        }
       return inserhelp(child,word.substr(1));

    }
    void inser(string word)
    {
        inserhelp(root,word);
    }
   bool searchelp(trienode* root, string word)
   {
    if (word.length() == 0)
    {
        return root->isterminal;
        // if true then word exists.Example: time is present but tim is not
        //if this condition not here then it will show that tim also present.
    }

    int index = word[0] - 'a';
    trienode* child;

    if (root->children[index] != NULL)
    {
        child = root->children[index];
        return searchelp(child, word.substr(1));
    }

    else
    {
        return false;
    }
}

    bool searc(string word)
    {
        return searchelp(root,word);
    }

   void printsuggestions(trienode*curr,vector<string>&temp,string prefix)
   {
       if(curr->isterminal)
       {
           temp.push_back(prefix);//if already at terminal then we already have the full word and hence search result
       }
       for(char ch='a';ch<'z';ch++)
       {
           trienode*next=curr->children[ch-'a'];//indexing
           if(next!=NULL)
           {
               prefix.push_back(ch);//we had entered c and we also found let's say a so prefix is ca now.
               printsuggestions(next,temp,prefix);//recursive call to print suggestions as prefix is increased
               prefix.pop_back();//backtrack for exploring other children
           }
       }
   }

    vector<vector<string>> getquerysuggestion(string str)
    {
        trienode*prev=root;
        vector<vector<string>> output;
        string prefix="";

        for(int i=0;i<str.length();i++)
        {
            char lastchr=str[i];

            prefix.push_back(lastchr);
        //checking if this last character exists in the directory or not

            trienode*curr=prev->children[lastchr-'a'];

            //if character not found

            if(curr==NULL)
            {
                break;
            }

            //if found
            vector<string> temp;
            printsuggestions(curr,temp,prefix);
            output.push_back(temp);
            temp.clear();
            prev=curr;
        }
        return output;
    }

    void remove(string word)
    {
        removehelp(root, word, 0);
    }

    void removehelp(trienode* curr, string word, int depth)
    {
        if (depth == word.length()) {
            if (curr->isterminal) {
                curr->isterminal = false;
            }
            return;
        }

        int index = word[depth] - 'a';
        if (curr->children[index] == NULL) {
            return;
        }

        removehelp(curr->children[index], word, depth + 1);

        // Delete node if it's non-terminal, has no children, and isn't a prefix of another word
        if (!curr->isterminal && isemptynode(curr)) {
            delete curr->children[index];
            curr->children[index] = NULL;
        }
    }

    bool isemptynode(trienode* node)
    {
        for (int i = 0; i < 26; ++i)
        {
            if (node->children[i] != NULL) {
                return false;
            }
        }
        return true;
    }
};
vector<vector<string>> contactdirectory(vector<string>&contactlist,string query)
{
    trie*t=new trie();
    string lastchar;

    for(int i=0;i<contactlist.size();i++)
    {
        string str=contactlist[i];
        t->inser(str);
    }

    return t->getquerysuggestion(query);
}
void displaymenu() {
    cout << "===== Contact Directory Menu =====" << endl;
    cout << "1. Add a contact" << endl;
    cout << "2. Search for a contact" << endl;
    cout << "3. Get query suggestions" << endl;
    cout << "4. Remove a contact" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

int main()
{
      int coun=0;
    cout<<"Loading";
    for(coun;coun<77;++coun)
    {
        cout<<"   ";
        fflush(stdout);
        Sleep(1);
    }
     system("color f3");
    cout<<"*****************************************************************************************************"<<endl;
    cout<<"------------------------------->>>Welcome to PHONE DIRECTORY SYSTEM<<<-------------------------------"<<endl;
    cout<<"*****************************************************************************************************"<<endl;
    //printf("__________________________________________________ \n\n");
    //cout<<"                     WELCOME                  \n\n";
    trie* contactirectory = new trie();

    int choice;
    string contact, query;

    do
    {
        displaymenu();
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter contact to add: ";
                cin >> contact;
                contactirectory->inser(contact);
                cout << "Contact added successfully!\n";
                break;

            case 2:
                cout << "Enter contact to search for: ";
                cin >> contact;
                cout << "Search result: " << (contactirectory->searc(contact) ? "Found" : "Not found") << endl;
                break;

            case 3:
                cout << "Enter query for suggestions: ";
                cin >> query;
                {
                    vector<vector<string>> suggestions = contactirectory->getquerysuggestion(query);
                    cout << "Suggestions for '" << query << "': ";
                    for (int i = 0; i < suggestions.size(); ++i)
                    {
                       for (int j = 0; j < suggestions[i].size(); ++j)
                        {
                            cout << suggestions[i][j] << " ";
                        }
                    }
                    cout << endl;
                }
                break;

            case 4:
                cout << "Enter contact to remove: ";
                cin >> contact;
                contactirectory->remove(contact);
                cout << "Contact removed!\n";
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }

        cout << endl;

    } while (choice != 5);

    delete contactirectory; // Free allocated memory
    return 0;
}

