#include <iostream>
#include <string>
using namespace std;

// 图书类
class Book {
private:
    string name;       // 图书名称
    string isbn;       // 图书isbn
    string publisher;  // 出版社信息
    double price;      // 价格
    int pages;         // 页数
    bool status;       // 在馆状态：true可借，false不可借

public:
    // 初始化（构造函数）
    Book(string n, string i, string p, double pr, int pg, bool s) {
        name = n;
        isbn = i;
        publisher = p;
        price = pr;
        pages = pg;
        status = s;
    }

    // 修改
    void setName(string n)       { name = n; }
    void setIsbn(string i)       { isbn = i; }
    void setPublisher(string p)  { publisher = p; }
    void setPrice(double pr)     { price = pr; }
    void setPages(int pg)        { pages = pg; }
    void setStatus(bool s)       { status = s; }

    // 获取
    string getName()      { return name; }
    string getIsbn()      { return isbn; }
    string getPublisher() { return publisher; }
    double getPrice()     { return price; }
    int    getPages()     { return pages; }
    bool   getStatus()    { return status; }

    // 输出
    void show() {
        cout << "书名：" << name << endl;
        cout << "ISBN：" << isbn << endl;
        cout << "出版社：" << publisher << endl;
        cout << "价格：" << price << " 元" << endl;
        cout << "页数：" << pages << " 页" << endl;
        cout << "状态：" << (status ? "可借" : "不可借") << endl;
    }

    // 验证ISBN合法性（ISBN-13：13位数字，加权和能被10整除）
    static bool checkIsbn(string s) {
        if (s.length() != 13) return false;
        int sum = 0;
        for (int i = 0; i < 13; i++) {
            if (s[i] < '0' || s[i] > '9') return false;  // 必须全是数字
            int d = s[i] - '0';
            sum += (i % 2 == 0) ? d : d * 3;             // 奇数位乘1，偶数位乘3
        }
        return sum % 10 == 0;
    }
};

int main() {
    Book b("C++程序设计", "9787302147114", "清华大学出版社", 36.0, 320, true);
    b.show();

    cout << "\nISBN校验：" << endl;
    cout << "9787302147114 => " << (Book::checkIsbn("9787302147114") ? "合法" : "非法") << endl;
    cout << "1234567890123 => " << (Book::checkIsbn("1234567890123") ? "合法" : "非法") << endl;

    b.setPrice(32.5);       // 修改价格
    b.setStatus(false);     // 借出，改为不可借
    cout << "\n修改后：" << endl;
    b.show();

    return 0;
}
