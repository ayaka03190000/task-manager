#include <iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
using namespace std;


struct Task {

    string title;
    string detail;
    int priority;
    bool completed;
    string deadline;
};

vector<Task>tasks;

void addTask(){

    Task newTask;
    cin.ignore();

    cout << "タイトル：";
    getline(cin, newTask.title);
    cout << "内容：";
    getline(cin, newTask.detail);
    cout << "優先度(1-3)：";
    while (true) {
        cin >> newTask.priority;
        if (1 <= newTask.priority && 3 >= newTask.priority) {
            break;
        }
        else {
            cout << "無効な番号" << endl;
        }
    }
    cout << "期限（年-月-日）：";
    cin >> newTask.deadline;
    newTask.completed = false;
    tasks.push_back(newTask);
}

void showTask() {

    for (size_t i = 0;i < tasks.size();i++) {
        cout << i + 1 << "：";
        if (tasks[i].completed) {
            cout << "[完了]" << " ";
        }
        else {
            cout << "[未完了]" << " ";
        }
        cout << tasks[i].title << endl;
        cout << "優先度：" << tasks[i].priority << endl;
        cout << "期限：" << tasks[i].deadline << endl;
        cout << "内容：" << tasks[i].detail << endl;
        cout << endl;
    }
}

void deleteTask() {

    int num;

    cout << "削除するタスク番号：";
    cin >> num;
    if ((num < 1) || (num > (int)tasks.size())){
        cout << "無効な番号" << endl;
        return;
    }
    tasks.erase(tasks.begin() + num - 1);
}

bool comparepriority(const Task& x, const Task& y) {
    return x.priority < y.priority;
}

void sortpriorityTask() {

    vector<Task>stasks = tasks;
    sort(stasks.begin(), stasks.end(), comparepriority);

    for (size_t i = 0;i < stasks.size();i++) {
        if (!stasks[i].completed) {
            cout << i + 1 << "：" << stasks[i].title << " " << "（優先度：" << stasks[i].priority << "）" << endl;
        }
    }
}

bool comparedeadline(const Task& x, const Task& y) {
    return x.deadline < y.deadline;
}

void sortdeadlineTask() {

    vector<Task>stasks = tasks;
    sort(stasks.begin(), stasks.end(), comparedeadline);

    string today;
    cout << "今日の日付（年-月-日）：";
    cin >> today;
    for (size_t i = 0;i < stasks.size();i++) {
        if (!stasks[i].completed&&(stasks[i].deadline<=today)) {
            cout << i + 1 << "：" << stasks[i].title << " " << "（期限：" << stasks[i].deadline << "）" << "（優先度：" << stasks[i].priority << "）" << endl;
        }
    }
}

void completedTask() {

    int num;

    cout << "完了したタスク番号：";
    cin >> num;
    if ((num < 1) || (num > (int)tasks.size())) {
        cout << "無効な番号" << endl;
        return;
    }
    tasks[num - 1].completed = true;
}

void findTask() {

    string word;

    cout << "検索ワード：";
    cin >> word;

    for (size_t i = 0;i < tasks.size();i++) {
        if ((tasks[i].title.find(word) != string::npos)||(tasks[i].detail.find(word) != string::npos)){
            cout << i + 1 << "：";
            if (tasks[i].completed) {
                cout << "[完了]" << " ";
            }
            else {
                cout << "[未完了]" << " ";
            }
            cout << tasks[i].title << " " << "（期限：" << tasks[i].deadline << "）" << endl;
            cout << "内容：" << tasks[i].detail << endl;
            cout << endl;
        }
    }
}

void editTask() {

    size_t numtask;
    cout << "編集するタスク番号：";
    cin >> numtask;
    if (numtask<1 || numtask>tasks.size()) {
        cout << "無効な番号" << endl;
        return;
    }
    cout << endl;
    cout << "１　タイトル" << endl;
    cout << "２　内容" << endl;
    cout << "３　優先度" << endl;
    cout << "４　期限" << endl;
    cout << "５　変更点なし" << endl;
    while (true) {
        int numedit;
        cout << "編集箇所を選択（１-５）：";
        cin >> numedit;
        cin.ignore();
        if (numedit == 1) {
            cout << "新規タイトル：";
            getline(cin, tasks[numtask - 1].title);
        }
        else if (numedit == 2) {
            cout << "新規内容：";
            getline(cin, tasks[numtask - 1].detail);
        }
        else if (numedit == 3) {
            cout << "新規優先度：";
            cin >> tasks[numtask - 1].priority;
            if (1 > tasks[numtask-1].priority || 3 < tasks[numtask-1].priority) {
                cout << "無効な番号" << endl;
            }
            cin.ignore();
        }
        else if (numedit == 4) {
            cout << "新規期限：";
            getline(cin, tasks[numtask - 1].deadline);
        }
        else if (numedit == 5) {
            cout << "編集終了" << endl;
            return;
        }
        else {
            cout << "無効な番号";
        }
        cout << endl;
    }
}

void loadTask() {

    ifstream infile("tasks.txt");

    Task newTask;

    if (!infile.is_open()) {
        cout << "ファイルがありません" << endl;
        return;
    }
    while (getline(infile, newTask.title)) {
        getline(infile, newTask.detail);
        infile >> newTask.priority;
        infile >> newTask.completed;
        infile.ignore();
        getline(infile, newTask.deadline);
        tasks.push_back(newTask);
    }

    infile.close();
}

void saveTask() {

    ofstream outfile("tasks.txt");
    for (size_t i = 0;i < tasks.size();i++) {
        outfile << tasks[i].title << endl;
        outfile << tasks[i].detail << endl;
        outfile << tasks[i].priority << endl;
        outfile << tasks[i].completed << endl;
        outfile << tasks[i].deadline << endl;
    }

    outfile.close();
}

int main(){

    loadTask();

    int choose;

    while (true) {

        cout << "１　タスクを追加" << endl;
        cout << "２　タスクを削除" << endl;
        cout << "３　タスク一覧表示" << endl;
        cout << "４　優先度順に未完了タスク表示" << endl;
        cout << "５　期限が近いタスク表示" << endl;
        cout << "６　タスクを完了にする" << endl;
        cout << "７　タスク検索" << endl;
        cout << "８　タスク編集" << endl;
        cout << "９　何もしない" << endl;

        cin >> choose;

        if (choose == 1) {
            addTask();
        }
        else if (choose == 2) {
            deleteTask();
        }
        else if (choose == 3) {
            showTask();
        }
        else if (choose == 4) {
            sortpriorityTask();
        }
        else if (choose == 5) {
            sortdeadlineTask();
        }
        else if (choose == 6) {
            completedTask();
        }
        else if (choose == 7) {
            findTask();
        }
        else if (choose == 8) {
            editTask();
        }
        else if (choose == 9) {
            break;
        }
        else {
            cout << "無効な番号" << endl;
            return 0;
        }
    }

    saveTask();

    return 0;
}
