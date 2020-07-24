#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;

class CustomNode
{
    public:
        string Title;
        CustomNode* Parent;
        vector<CustomNode*> Children;
        string path;

        CustomNode(string title, CustomNode* parent)
        {
            Parent = parent;
            Title = title;
            Children = vector<CustomNode*>();

            if (parent != NULL)
                parent->Children.push_back(this);
        }

        vector<string> split(const string &s, char delim)
        {
            vector<string> elems;
            this->split(s, delim, elems);
            return elems;
        }

        vector<string> &split(const string &s, char delim, vector<string> &elems)
        {
            stringstream ss(s);
            string item;
            while (getline(ss, item, delim))
                elems.push_back(item);

            return elems;
        }

        CustomNode* Find(string path)
        {
            if (this->Title.compare(path) == 0)
                return this;

            vector<string> pieces;

            if(path.find('/') != -1)
                pieces = this->split(path, '/');
            else
            {
                pieces.push_back("");
                pieces.push_back(path);
            }

            for (vector<CustomNode*>::iterator child = Children.begin(); child != Children.end(); ++child)
            {
                if ((*child)->Title.compare(pieces.at(1)) == 0)
                    return (*child)->Find(path.substr(this->Title.length() + 1));
            }

            return NULL;
        }
};

string GetShortestUniqueQualifier(CustomNode* root, CustomNode* target);
void RunTests(CustomNode* root, CustomNode* custom1, CustomNode* custom2, CustomNode* custom3);

int main()
{
    //Build a test tree (matches the example)
    CustomNode root("Root", NULL);
    CustomNode userData("UserData", &root);
    CustomNode ud_browser("Browser", &userData);
    CustomNode ud_word("Word", &userData);
    CustomNode priv("Private", &userData);
    CustomNode priv_word("Word", &priv);

    CustomNode windows("Windows", &root);
    CustomNode programs("Programs", &root);
    CustomNode notepad("Notepad", &programs);
    CustomNode prog_word("Word", &programs);
    CustomNode prog_browser("Browser", &programs);

    CustomNode custom1("Custom1", &root);
    CustomNode custom2("Custom2", &custom1);
    CustomNode custom3("Custom3", &custom2);

    RunTests(&root, &custom1, &custom2, &custom3);
    return 0;
}

void TestGetShortestUniqueQualifier(CustomNode* root, string targetAbsPath, string expected)
{
    string output;
    try {
        output = GetShortestUniqueQualifier(root, root->Find(targetAbsPath));
    } catch(...) {
        output = "exception";
    }

    if(output.compare(expected) == 0)
        cout << "Succeeded for " + targetAbsPath + "\n";
    else
        cout << ("Failed for " + targetAbsPath + ": Failed with [" + output + "] rather than [" + expected + "]\n");
}

void RunTests(CustomNode* root, CustomNode* custom1, CustomNode* custom2, CustomNode* custom3)
{
    //They are unique
    TestGetShortestUniqueQualifier(root, "Root", "Root");
    TestGetShortestUniqueQualifier(root, "Root/Programs", "Programs");
    TestGetShortestUniqueQualifier(root, "Root/Programs/Notepad", "Notepad");

    //They have duplicate names
    TestGetShortestUniqueQualifier(root, "Root/Programs/Browser", "Programs/Browser");
    TestGetShortestUniqueQualifier(root, "Root/UserData/Browser", "UserData/Browser");

    //Root has a duplicate name
    custom1->Title = "a";
    custom2->Title = "b";
    custom3->Title = "Root";
    TestGetShortestUniqueQualifier(root, "Root/a/b/Root", "b/Root");

    //Edge cases
    custom1->Title = "Root";
    custom2->Title = "b";
    custom3->Title = "c";
    TestGetShortestUniqueQualifier(root, "Root/Root", "Root/Root");

    custom1->Title = "a";
    custom2->Title = "a";
    custom3->Title = "a";
    TestGetShortestUniqueQualifier(root, "Root/a", "Root/a");
    TestGetShortestUniqueQualifier(root, "Root/a/a", "Root/a/a");
    TestGetShortestUniqueQualifier(root, "Root/a/a/a", "a/a/a");

    custom1->Title = "Root";
    custom2->Title = "UserData";
    custom3->Title = "Word";
    TestGetShortestUniqueQualifier(root, "Root/Root/UserData/Word", "Root/Root/UserData/Word");

    TestGetShortestUniqueQualifier(root, "Root", "/Root");
    TestGetShortestUniqueQualifier(root, "Root/UserData/Word", "/Root/UserData/Word");
}

//  helper function to split the string by "/"
const vector<string> explode(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;

    for(auto n:s)
    {
        if(n != c) buff+=n; else
        if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}

string GetShortestUniqueQualifier(CustomNode* root, CustomNode* target)
{
    // need to find all the paths from root the title
    string title=target->Title;
    //use BFS for traversing all paths
    vector<string> all_paths;
    //create and add first elements
    // children vector
    vector<CustomNode*>  children;
    string target_path;
    string new_path;
    queue<CustomNode*> que;
    que.push(root);
    CustomNode* top;
    root->path="";

    while(!que.empty()){
        // enque all childs
        top=que.front();
        children= top->Children;
        // add adjacent childs
        for(int i=0; i< children.size();i++){
            que.push(children[i]);
            children[i]->path= top->path+"/"+children[i]->Title;
            all_paths.push_back( children[i]->path);
        }
        que.pop();

    }

    // find the path of the target "this was supposed to be given"
    queue<CustomNode*> que2;
    que2.push(root);
    while(!que2.empty()){
            // enque all childs
            top=que2.front();
            if(top==target){
                target_path=top->path;
                break;
            }

            //
            children= top->Children;
            // add adjacent childs
            for(int i=0; i< children.size();i++){
                que2.push(children[i]);
            }
            que2.pop();

        }
    // split the string to possible obtain the shortest path
    vector<string> v{explode(target_path, '/')};

    // may need to iterate over the vector of possible paths
    string possible_path;
    int last=(int)v.size()-1;
    for(int i=0;i<v.size();i++){
        if(i==0){
            possible_path=v[last];;

        }else{
            possible_path=v[last]+"/"+possible_path;
        }
        last--;
        // iterate over all paths
        int iterator;
        int flag=0;
        for(iterator=0;iterator<all_paths.size();iterator++){

            if ((all_paths[iterator].find(possible_path) != std::string::npos)) {
                // should only be found once
                flag++;
            }
            if(flag>1)
                break;

        }
        // reachest this point this one was the shortest possible path
        if(iterator==all_paths.size()){
            return possible_path;
        }
    }

    return possible_path;
}
