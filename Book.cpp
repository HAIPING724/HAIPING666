#include <iostream>
#include <string>
using namespace std;

// 图书类
class Book
{
private:
    string bookName;    // 图书名称
    string isbn;        // 图书isbn
    string publisher;   // 出版社
    double price;       // 价格
    int pages;          // 页数
    bool isAvailable;   // 在馆状态 true可借，false不可借

public:
    // 1.构造函数初始化
    Book(string name, string id, string pub, double pri, int pag, bool avail)
    {
        bookName = name;
        isbn = id;
        publisher = pub;
        price = pri;
        pages = pag;
        isAvailable = avail;
    }

    // 2.修改各个成员
    void setName(string name) { bookName = name; }
    void setIsbn(string id) { isbn = id; }
    void setPublisher(string pub) { publisher = pub; }
    void setPrice(double pri) { price = pri; }
    void setPages(int pag) { pages = pag; }
    void setStatus(bool avail) { isAvailable = avail; }

    // 3.获取各个成员
    string getName() { return bookName; }
    string getIsbn() { return isbn; }
    string getPublisher() { return publisher; }
    double getPrice() { return price; }
    int getPages() { return pages; }
    bool getStatus() { return isAvailable; }

    // 4.输出图书全部信息
    void showInfo()
    {
        cout << "图书名称：" << bookName << endl;
        cout << "ISBN：" << isbn << endl;
        cout << "出版社：" << publisher << endl;
        cout << "价格：" << price << "元" << endl;
        cout << "页数：" << pages << "页" << endl;
        if(isAvailable)
            cout << "在馆状态：可借" << endl;
        else
            cout << "在馆状态：不可借" << endl;
    }
};

int main()
{
    // 创建对象测试
    Book b1("C++程序设计", "9787111544065", "机械工业出版社", 45.0, 320, true);
    cout << "=====图书信息=====" << endl;
    b1.showInfo();

    // 修改状态：改为不可借
    b1.setStatus(false);
    cout << "\n=====修改状态后=====" << endl;
    b1.showInfo();

    // 获取单个成员测试
    cout << "\n获取图书名称：" << b1.getName() << endl;
    return 0;
}
