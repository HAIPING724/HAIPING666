#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 图书类
class Book
{
private:
    string bookName;    // 图书名称
    string isbn;        // isbn
    string publisher;   // 出版社
    double price;       // 价格
    int pages;          // 页数
    bool isAvailable;   // 是否可借
    int stock;          // 图书库存数量

public:
    // 构造初始化
    Book(string name, string id, string pub, double pri, int pag, int sto)
    {
        bookName = name;
        isbn = id;
        publisher = pub;
        price = pri;
        pages = pag;
        stock = sto;
        isAvailable = (stock > 0); // 库存大于0才可以借
    }

    // 修改成员
    void setName(string name) { bookName = name; }
    void setIsbn(string id) { isbn = id; }
    void setPublisher(string pub) { publisher = pub; }
    void setPrice(double pri) { price = pri; }
    void setPages(int pag) { pages = pag; }
    void setStock(int sto)
    {
        stock = sto;
        isAvailable = (stock > 0);
    }

    // 获取成员
    string getName() { return bookName; }
    string getIsbn() { return isbn; }
    string getPublisher() { return publisher; }
    double getPrice() { return price; }
    int getPages() { return pages; }
    bool getAvailable() { return isAvailable; }
    int getStock() { return stock; }

    // 库存减1，借书调用
    void reduceStock()
    {
        stock--;
        isAvailable = (stock > 0);
    }

    // 输出图书信息
    void showInfo()
    {
        cout << "图书名称：" << bookName << endl;
        cout << "ISBN：" << isbn << endl;
        cout << "出版社：" << publisher << endl;
        cout << "价格：" << price << "元" << endl;
        cout << "页数：" << pages << "页" << endl;
        cout << "库存：" << stock << "本" << endl;
        cout << "可借状态：" << (isAvailable ? "可借" : "不可借") << endl;
    }
};

// 学生类
class Student
{
private:
    string stuName;     // 学生姓名
    string stuId;       // 学号
    int borrowNum;      // 当前借书数量
    vector<Book*> borrowBooks; // 记录借到的书的指针（依赖图书对象）
    const int MAX_BORROW = 3; // 最多借3本书

public:
    // 构造初始化
    Student(string name, string id)
    {
        stuName = name;
        stuId = id;
        borrowNum = 0;
    }

    // 修改
    void setName(string name) { stuName = name; }
    void setStuId(string id) { stuId = id; }

    // 获取
    string getName() { return stuName; }
    string getStuId() { return stuId; }
    int getBorrowNum() { return borrowNum; }

    // 借书函数，参数传递Book引用（依赖关系）
    bool borrowBook(Book &book)
    {
        // 判断条件：书可借 并且 学生没有达到借书上限
        if (!book.getAvailable())
        {
            cout << "借书失败：这本书库存不足，不可借！" << endl;
            return false;
        }
        if (borrowNum >= MAX_BORROW)
        {
            cout << "借书失败：你已经达到最大借书数量！" << endl;
            return false;
        }

        // 借书成功：修改双方状态
        book.reduceStock();          // 图书库存-1
        borrowBooks.push_back(&book);// 保存借到的书地址
        borrowNum++;
        cout << "借书成功！" << endl;
        return true;
    }

    // 输出学生借阅信息
    void showStuInfo()
    {
        cout << "\n====学生信息====" << endl;
        cout << "姓名：" << stuName << endl;
        cout << "学号：" << stuId << endl;
        cout << "已借图书数量：" << borrowNum << endl;
        cout << "借阅的图书：";
        for (auto p : borrowBooks)
        {
            cout << p->getName() << "  ";
        }
        cout << endl;
    }
};

int main()
{
    // 创建图书对象，库存2本
    Book b1("C++程序设计", "9787111544065", "机械工业出版社", 45.0, 320, 2);
    Book b2("数据结构", "9787111556778", "清华大学出版社", 52.0, 280, 1);

    // 创建学生对象
    Student s1("张三", "2025001");

    cout << "====初始图书信息====" << endl;
    b1.showInfo();

    // 第一次借书
    cout << "\n张三尝试借《C++程序设计》：" << endl;
    s1.borrowBook(b1);

    // 第二次借书
    cout << "\n张三尝试借《数据结构》：" << endl;
    s1.borrowBook(b2);

    // 打印学生借阅情况
    s1.showStuInfo();

    cout << "\n====借书后图书信息====" << endl;
    b1.showInfo();

    // 测试借已经借完的书（库存变成0）
    cout << "\n张三再次借《C++程序设计》：" << endl;
    s1.borrowBook(b1);

    return 0;
}
