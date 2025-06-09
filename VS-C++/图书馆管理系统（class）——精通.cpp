#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Book//图书类
{
private:
    string title;//书名
    string author;//作者
    string isbn;//国际标准书号，唯一标识一本书
    bool isBorrowed;//是否借出
public:
    // 构造函数，初始化图书信息
    Book(const string& t, const string& a, const string& i) :title(t), author(a), isbn(i), isBorrowed(false) {}

    // 获取图书信息的接口函数
    string getTitle() const { return title; }// 获取图书标题（书名）
    string getAuthor() const { return author; }// 获取图书作者
    string getISBN() const { return isbn; }// 获取国际标准书号（ISBN），这是图书的唯一标识符
    bool getIsBorrowed() const { return isBorrowed; }// 检查图书是否已被借出

    // 图书借阅和归还操作
    void borrow() { isBorrowed = true; }// 将图书状态设置为"已借出"
    void returnBook() { isBorrowed = false; }// 将图书状态设置为"可借阅"（归还操作）
    bool canBorrow() const { return !isBorrowed; }// 检查图书当前是否可借阅（未被借出）
};

class Reader//读者类
{
private:
    string readerld;//读者ID
    string name;//姓名
    vector<Book*> borrowedBooks;//借阅的图书列表，使用指针指向Library中的Book对象
public:
    // 构造函数，初始化读者信息
    Reader(const string& id, const string& n) :readerld(id), name(n) {}

    // 获取读者信息的接口函数
    string getReaderld() const { return readerld; }// 获取读者的唯一标识符（Reader ID）
    string getName() const { return name; }// 获取读者姓名
    const vector<Book*>& getBorrowedBooks() const { return borrowedBooks; }// 返回读者当前借阅的所有图书列表（只读引用）

    // 借阅图书：如果图书可借，则更新图书状态并添加到借阅列表
    bool borrowBook(Book* book) {
        if (book->canBorrow()) {
            book->borrow();// 更新图书借阅状态
            borrowedBooks.push_back(book);// 添加到借阅列表
            return true;
        }
        return false;
    }

    // 归还图书：从借阅列表中移除图书并更新图书状态
    bool returnBook(Book* book) {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (*it == book) {
                book->returnBook();// 更新图书归还状态
                borrowedBooks.erase(it);// 从借阅列表移除
                return true;
            }
        }
        return false;
    }
};

class Library//图书馆类
{
private:
    vector<Book> books;// 图书馆所有图书
    vector<Reader> readers; // 所有读者
public:
     // 添加新书
    void addBook(const string& title, const string& author, const string& isbn) {
        books.emplace_back(title, author, isbn);
    }

     // 添加新读者
    void addReader(const string& readerld, const string& name) {
        readers.emplace_back(readerld, name);
    }

    // 处理图书借阅：根据读者ID和ISBN查找并处理借阅
    bool borrowBook(const string& readerld, const string& isbn) {
        Reader* reader = nullptr;
        Book* book = nullptr;

        // 查找读者
        for (auto& r : readers) {
            if (r.getReaderld() == readerld) {
                reader = &r;
                break;
            }
        }

        // 查找图书
        for (auto& b : books) {
            if (b.getISBN() == isbn) {
                book = &b;
                break;
            }
        }

        // 如果找到读者和图书，执行借阅操作
        if (reader && book) {
            return reader->borrowBook(book);
        }
        return false;
    }

    // 处理图书归还：根据读者ID和ISBN查找并处理归还
    bool returnBook(const string& readerld, const string& isbn) {
        Reader* reader = nullptr;
        Book* book = nullptr;

        // 查找读者
        for (auto& r : readers) {
            if (r.getReaderld() == readerld) {
                reader = &r;
                break;
            }
        }

        // 查找图书
        for (auto& b : books) {
            if (b.getISBN() == isbn) {
                book = &b;
                break;
            }
        }

         // 如果找到读者和图书，执行归还操作
        if (reader && book) {
            return reader->returnBook(book);
        }
        return false;
    }

    // 显示所有图书信息
    void displayBooks() const {
        for (const auto& book : books) {
            cout << "书名:" << book.getTitle() << ",作者:" << book.getAuthor() << ",ISBN:" << book.getISBN() 
                 << ",状态:" << (book.getIsBorrowed() ? "已借出" : "可借阅") << endl;
        }
    }

    // 显示所有读者信息及其借阅记录
    void displayReaders() const {
        for (const auto& reader : readers) {
            cout << "读者ID:" << reader.getReaderld() << "，姓名:" << reader.getName() << endl;
            const auto& borrowedBooks = reader.getBorrowedBooks();
            if (!borrowedBooks.empty()) {
                cout << "借阅的图书:" << endl;
                for (const auto& book : borrowedBooks) {
                    cout << "书名:" << book->getTitle() << ",ISBN:" << book->getISBN() << endl;
                }
            }
        }
    }
};

int main()
{
    Library library;// 创建图书馆实例
    int choice; // 用户选择的操作
    string title, author, isbn, readerld, name;// 临时存储输入信息
    do
    {
        cout << "1.添加图书" << endl;
        cout << "2.添加读者" << endl;
        cout << "3.借阅图书" << endl;
        cout << "4.归还图书" << endl;
        cout << "5.显示图书信息" << endl;
        cout << "6.显示读者信息" << endl;
        cout << "7.退出" << endl;
        cout << "请输入你的选择:";
        cin >> choice;
        cin.ignore(); // 清除缓冲区中的换行符
        
        switch (choice) {
        case 1: // 添加图书
            cout << "请输入书名:";
            getline(cin, title);
            cout << "请输入作者:";
            getline(cin, author);
            cout << "请输入ISBN:";
            cin >> isbn;
            cin.ignore(); // 清除缓冲区中的换行符
            library.addBook(title, author, isbn);
            break;
        case 2:// 添加读者
            cout << "请输入读者ID:";
            cin >> readerld;
            cin.ignore(); // 清除缓冲区中的换行符
            cout << "请输入读者姓名:";
            getline(cin, name);
            library.addReader(readerld, name);
            break;
        case 3:// 借阅图书
            cout << "请输入读者ID:";
            cin >> readerld;
            cout << "请输入ISBN:";
            cin >> isbn;
            if (library.borrowBook(readerld, isbn)) {
                cout << "借阅成功" << endl;
            }
            else {
                cout << "借阅失败" << endl;
            }
            break;
        case 4:// 归还图书
            cout << "请输入读者ID:";
            cin >> readerld;
            cout << "请输入ISBN:";
            cin >> isbn;
            if (library.returnBook(readerld, isbn)) {
                cout << "归还成功" << endl;
            }
            else {
                cout << "归还失败" << endl;
            }
            break;
        case 5:// 显示图书信息
            library.displayBooks();
            break;
        case 6:// 显示读者信息
            library.displayReaders();
            break;
        case 7:// 退出系统
            cout << "退出系统" << endl;
            break;
        default:
            cout << "无效的选择，请重新输入" << endl;
        }
    } while (choice != 7);
    return 0;
}