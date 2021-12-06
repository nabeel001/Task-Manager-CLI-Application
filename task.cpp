#include <bits/stdc++.h>
using namespace std;
void help()
{
    cout << "Usage :-" << endl;
    cout << "$ ./task add 2 hello world    # Add a new item with priority 2 and text \"hello world\" to the list" << endl;
    cout << "$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order" << endl;
    cout << "$ ./task del INDEX            # Delete the incomplete item with the given index" << endl;
    cout << "$ ./task done INDEX           # Mark the incomplete item with the given index as complete" << endl;
    cout << "$ ./task help                 # Show usage" << endl;
    cout << "$ ./task report               # Statistics" << endl;
}

void ls()
{
    vector<string> tasks;

    ifstream file("task.txt");
    string item;
    while (getline(file, item))
    {
        if (item[item.size() - 1] == '\r')
            item.erase(item.size() - 1);
        tasks.push_back(item);
    }
    file.close();

    int list_size = tasks.size();
    if (list_size == 0)
    {
        cout << "There are no pending tasks!" << endl;
        return;
    }

    int i = 0;
    while (i < list_size)
    {
        int j = 0;
        string priority = "";
        while (tasks[i][j] != ' ')
        {
            priority += tasks[i][j];
            j++;
        }
        cout << i + 1 << ". " << tasks[i].substr(++j) << " [" << priority << "]" << endl;
        i++;
    }
}

bool sort_cond(string s1, string s2)
{
    int i = 0, j = 0;
    string priority_1 = "", priority_2 = "";
    while (s1[i] != ' ')
    {
        priority_1 += s1[i];
        i++;
    }
    while (s2[j] != ' ')
    {
        priority_2 += s2[j];
        j++;
    }
    return (priority_1 < priority_2);
}

void add_item(string priority, string task)
{
    vector<string> tasks;

    string item;
    ifstream file_rd("task.txt");
    while (getline(file_rd, item))
    {
        if (item[item.size() - 1] == '\r')
            item.erase(item.size() - 1);
        tasks.push_back(item);
    }
    file_rd.close();

    string new_task = priority + " " + task;
    tasks.push_back(new_task);
    cout << "Added task: \"" << task << "\" with priority " << priority << endl;
    sort(tasks.begin(), tasks.end(), sort_cond);

    int list_size = tasks.size();
    ofstream file_wr("task.txt");
    for (int i = 0; i < list_size; i++)
    {
        file_wr << tasks[i] << endl;
    }
    file_wr.close();
}

void del_item(int index)
{
    vector<string> tasks;

    string item;
    ifstream file_rd("task.txt");
    while (getline(file_rd, item))
    {
        if (item[item.size() - 1] == '\r')
            item.erase(item.size() - 1);
        tasks.push_back(item);
    }
    file_rd.close();

    int list_size = tasks.size();
    if (index > list_size)
    {
        cout << "Error: task with index #" << index << " does not exist. Nothing deleted." << endl;
        return;
    }

    ofstream file_wr("task.txt");
    for (int i = 1; i <= list_size; i++)
    {
        if (i != index)
            file_wr << tasks[i - 1] << endl;
    }
    file_wr.close();

    cout << "Deleted task #" << index << endl;
}

void mark_item(int index)
{
    vector<string> tasks;

    string item;
    ifstream file_rd("task.txt");
    while (getline(file_rd, item))
    {
        if (item[item.size() - 1] == '\r')
            item.erase(item.size() - 1);
        tasks.push_back(item);
    }
    file_rd.close();

    int list_size = tasks.size();
    if (index > list_size)
    {
        cout << "Error: no incomplete item with index #" << index << " exists." << endl;
        return;
    }

    ofstream file_wr_pend("task.txt");
    ofstream file_wr_cmplt("completed.txt", std::ios_base::app | std::ios_base::out);
    for (int i = 1; i <= list_size; i++)
    {
        if (i == index)
        {
            int j = 0;
            while (tasks[i - 1][j] != ' ')
                j++;
            file_wr_cmplt << tasks[i - 1].substr(++j) << endl;
        }
        else
            file_wr_pend << tasks[i - 1] << endl;
    }
    file_wr_pend.close();
    file_wr_cmplt.close();

    cout << "Marked item as done." << endl;
}

void report()
{
    vector<string> pend_tasks, cmplt_tasks;
    string item;

    ifstream file_pend("task.txt");
    while (getline(file_pend, item))
    {
        if (item[item.size() - 1] == '\r')
            item.erase(item.size() - 1);
        pend_tasks.push_back(item);
    }
    file_pend.close();

    ifstream file_cmplt("completed.txt");
    while (getline(file_cmplt, item))
    {
        if (item[item.size() - 1] == '\r')
            item.erase(item.size() - 1);
        cmplt_tasks.push_back(item);
    }
    file_cmplt.close();

    int pend_count = pend_tasks.size();
    int cmplt_count = cmplt_tasks.size();

    cout << "Pending : " << pend_count << endl;
    int i = 0;
    while (i < pend_count)
    {
        int j = 0;
        string priority = "";
        while (pend_tasks[i][j] != ' ')
        {
            priority += pend_tasks[i][j];
            j++;
        }
        cout << i + 1 << ". " << pend_tasks[i].substr(++j) << " [" << priority << "]" << endl;
        i++;
    }

    cout << "\nCompleted : " << cmplt_count << endl;
    i = 0;
    while (i < cmplt_count)
    {
        cout << i + 1 << ". " << cmplt_tasks[i] << endl;
        i++;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        help();
        return 0;
    }
    string cmd = argv[1];
    if (cmd == "add")
    {
        if (argc < 4)
            cout << "Error: Missing tasks string. Nothing added!" << endl;
        else if (stoi(argv[2]) < 0)
        {
            cout << "Error: Priority cannot be negative. Nothing added!" << endl;
        }
        else
            add_item(argv[2], argv[3]);
    }
    else if (cmd == "del")
    {
        if (argc < 3)
            cout << "Error: Missing NUMBER for deleting tasks." << endl;
        else if (stoi(argv[2]) <= 0)
        {
            cout << "Error: task with index #" << argv[2] << " does not exist. Nothing deleted." << endl;
        }
        else
            del_item(stoi(argv[2]));
    }
    else if (cmd == "done")
    {
        if (argc < 3)
            cout << "Error: Missing NUMBER for marking tasks as done." << endl;
        else if (stoi(argv[2]) <= 0)
        {
            cout << "Error: no incomplete item with index #" << argv[2] << " exists." << endl;
        }
        else
            mark_item(stoi(argv[2]));
    }
    else if (cmd == "ls")
        ls();
    else if (cmd == "report")
        report();
    else
        help();

    return 0;
}
