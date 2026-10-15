#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// ===== 基类：资源 Resource (用来做继承) =====
class Resource
{
protected:
    string name;
    string id;          // 编号/ISBN
    int stock;
    bool isAvailable;
public:
    Resource(string n, string i, int s)
        : name(n), id(i), stock(s)
    {
        isAvailable = (stock > 0);
    }

    virtual ~Resource() {}   // 虚析构！delete派生类安全

    virtual void showInfo() = 0;   // 纯虚函数：不同资源显示不一样
    virtual string getType() = 0;

    string getName() { return name; }
    string getId() { return id; }
    int getStock() { return stock; }
    bool getAvailable() { return isAvailable; }

    void setStock(int s)
    {
        stock = s;
        isAvailable = (stock > 0);
    }

    void addStock(int num)
    {
        stock += num;
        isAvailable = (stock > 0);
    }

    bool reduceStock()
    {
        if (stock <= 0) return false;
        stock--;
        isAvailable = (stock > 0);
        return true;
    }
};

// ===== 派生类：Book 继承 Resource =====
class Book : public Resource
{
private:
    string publisher;
    double price;
    int pages;
public:
    Book(string n, string i, string pub, double pri, int pag, int sto)
        : Resource(n, i, sto), publisher(pub), price(pri), pages(pag)
    {}

    void showInfo() override
    {
        cout << "【图书】" << endl;
        cout << "书名：" << name << endl;
        cout << "ISBN：" << id << endl;
        cout << "出版社：" << publisher << endl;
        cout << "价格：" << fixed << setprecision(2) << price << " 元" << endl;
        cout << "页数：" << pages << " 页" << endl;
        cout << "库存：" << stock << " 本 | "
             << (isAvailable ? "状态：可借" : "状态：不可借") << endl;
    }

    string getType() override { return "Book"; }

    // 专属get
    string getPublisher() { return publisher; }
    double getPrice() { return price; }
    int getPages() { return pages; }
};

// ===== 学生类 =====
class Student
{
private:
    string stuName;
    string stuId;
    int borrowNum;
    vector<Resource*> borrowList;
    const int MAX_BORROW = 3;
public:
    Student(string name, string sid)
        : stuName(name), stuId(sid), borrowNum(0)
    {}

    string getName() { return stuName; }
    string getStuId() { return stuId; }
    int getBorrowCount() { return borrowNum; }

    // 借书：传指针，不再传值！
    bool borrowResource(Resource* res)
    {
        if (!res->getAvailable())
        {
            cout << ">> 借书失败：该资源暂无库存！\n";
            return false;
        }
        if (borrowNum >= MAX_BORROW)
        {
            cout << ">> 借书失败：已达到最大借书数量(3本)！\n";
            return false;
        }
        if (res->reduceStock())
        {
            borrowList.push_back(res);
            borrowNum++;
            cout << ">> 借书成功！\n";
            return true;
        }
        return false;
    }

    // 还书
    bool returnResource(string resId)
    {
        for (auto it = borrowList.begin(); it != borrowList.end(); ++it)
        {
            if ((*it)->getId() == resId)
            {
                (*it)->addStock(1);
                borrowList.erase(it);
                borrowNum--;
                cout << ">> 归还成功！\n";
                return true;
            }
        }
        cout << ">> 归还失败：未借阅该资源！\n";
        return false;
    }

    void showBorrowInfo()
    {
        cout << "\n===== 学生借阅信息 =====" << endl;
        cout << "姓名：" << stuName << "  学号：" << stuId << endl;
        cout << "当前已借数量：" << borrowNum << endl;
        if (borrowList.empty())
        {
            cout << "暂无借阅记录\n";
            return;
        }
        cout << "已借阅：";
        for (auto p : borrowList)
        {
            cout << p->getName() << "  ";
        }
        cout << endl;
    }
};

// ===== 图书馆类（组合：包含一堆Resource*，new/delete管理） =====
class Library
{
private:
    vector<Resource*> resList;
public:
    ~Library()
    {
        // 析构释放所有new出来的对象！
        for (auto p : resList)
        {
            delete p;
        }
        resList.clear();
    }

    // 添加一本新书（new动态创建）
    void addBook(string name, string isbn, string pub, double price, int pages, int stock)
    {
        Book* newBook = new Book(name, isbn, pub, price, pages, stock);
        resList.push_back(newBook);
        cout << ">> 图书添加成功！\n";
    }

    // 根据ID找资源
    Resource* findById(string id)
    {
        for (auto p : resList)
        {
            if (p->getId() == id)
                return p;
        }
        return nullptr;
    }

    // 增加已有图书库存
    bool addStock(string id, int num)
    {
        Resource* r = findById(id);
        if (!r) { cout << ">> 未找到该资源！\n"; return false; }
        r->addStock(num);
        cout << ">> 库存增加成功！\n";
        return true;
    }

    // 减少已有图书库存
    bool subStock(string id, int num)
    {
        Resource* r = findById(id);
        if (!r) { cout << ">> 未找到该资源！\n"; return false; }
        if (r->getStock() < num)
        {
            cout << ">> 库存不足，无法减少！\n";
            return false;
        }
        r->setStock(r->getStock() - num);
        cout << ">> 库存减少成功！\n";
        return true;
    }

    // 显示某一本
    void showOne(string id)
    {
        Resource* r = findById(id);
        if (!r) { cout << ">> 未找到该资源！\n"; return; }
        r->showInfo();
    }

    // 显示全部
    void showAll()
    {
        if (resList.empty())
        {
            cout << ">> 图书馆暂无资源！\n";
            return;
        }
        cout << "\n========== 全部馆藏 ==========\n";
        for (int i = 0; i < resList.size(); i++)
        {
            cout << "--- 第" << (i+1) << "本 ---\n";
            resList[i]->showInfo();
        }
    }

    // 删除某资源（delete释放）
    bool deleteRes(string id)
    {
        for (auto it = resList.begin(); it != resList.end(); ++it)
        {
            if ((*it)->getId() == id)
            {
                delete *it;
                resList.erase(it);
                cout << ">> 资源已删除！\n";
                return true;
            }
        }
        cout << ">> 未找到该资源！\n";
        return false;
    }
};

// 菜单
void showMenu()
{
    cout << "\n===== 图书借阅管理系统 =====" << endl;
    cout << "1. 添加新图书" << endl;
    cout << "2. 增加已有图书库存" << endl;
    cout << "3. 减少已有图书库存" << endl;
    cout << "4. 查询单本图书信息" << endl;
    cout << "5. 显示全部馆藏图书" << endl;
    cout << "6. 删除一本图书" << endl;
    cout << "7. 学生借书" << endl;
    cout << "8. 学生还书" << endl;
    cout << "9. 查看学生借阅情况" << endl;
    cout << "0. 退出系统" << endl;
    cout << "请输入您的选择：";
}

int main()
{
    Library lib;
    // 预先加两本样书
    lib.addBook("C++程序设计", "9787111544065", "机械工业出版社", 45.0, 320, 2);
    lib.addBook("数据结构", "9787111556778", "清华大学出版社", 52.0, 280, 1);

    Student stu("张三", "2025001");

    int op;
    while (true)
    {
        showMenu();
        cin >> op;
        cin.ignore();  // 吃掉换行，防止getline乱跳

        if (op == 1)
        {
            string name, isbn, pub;
            double price;
            int pages, stock;
            cout << "\n--- 添加新图书 ---" << endl;
            cout << "输入书名："; getline(cin, name);
            cout << "输入ISBN："; getline(cin, isbn);
            cout << "输入出版社："; getline(cin, pub);
            cout << "输入价格："; cin >> price;
            cout << "输入页数："; cin >> pages;
            cout << "输入初始库存："; cin >> stock;
            lib.addBook(name, isbn, pub, price, pages, stock);
        }
        else if (op == 2)
        {
            string id; int n;
            cout << "\n--- 增加库存 ---" << endl;
            cout << "输入图书ISBN："; getline(cin, id);
            cout << "输入要增加数量："; cin >> n;
            lib.addStock(id, n);
        }
        else if (op == 3)
        {
            string id; int n;
            cout << "\n--- 减少库存 ---" << endl;
            cout << "输入图书ISBN："; getline(cin, id);
            cout << "输入要减少数量："; cin >> n;
            lib.subStock(id, n);
        }
        else if (op == 4)
        {
            string id;
            cout << "\n--- 查询单本 ---" << endl;
            cout << "输入图书ISBN："; getline(cin, id);
            lib.showOne(id);
        }
        else if (op == 5)
        {
            lib.showAll();
        }
        else if (op == 6)
        {
            string id;
            cout << "\n--- 删除图书 ---" << endl;
            cout << "输入要删除图书ISBN："; getline(cin, id);
            lib.deleteRes(id);
        }
        else if (op == 7)
        {
            string id;
            cout << "\n--- 借书 ---" << endl;
            cout << "输入要借图书ISBN："; getline(cin, id);
            Resource* r = lib.findById(id);
            if (!r) { cout << ">> 找不到这本书！\n"; continue; }
            stu.borrowResource(r);
        }
        else if (op == 8)
        {
            string id;
            cout << "\n--- 还书 ---" << endl;
            cout << "输入归还图书ISBN："; getline(cin, id);
            stu.returnResource(id);
        }
        else if (op == 9)
        {
            stu.showBorrowInfo();
        }
        else if (op == 0)
        {
            cout << ">> 感谢使用，程序退出！\n";
            break;
        }
        else
        {
            cout << ">> 无效选项，请重新输入！\n";
        }
    }
    return 0;
}
