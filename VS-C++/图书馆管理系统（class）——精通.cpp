#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Book//ͼ����
{
private:
    string title;//����
    string author;//����
    string isbn;//���ʱ�׼��ţ�Ψһ��ʶһ����
    bool isBorrowed;//�Ƿ���
public:
    // ���캯������ʼ��ͼ����Ϣ
    Book(const string& t, const string& a, const string& i) :title(t), author(a), isbn(i), isBorrowed(false) {}

    // ��ȡͼ����Ϣ�Ľӿں���
    string getTitle() const { return title; }// ��ȡͼ����⣨������
    string getAuthor() const { return author; }// ��ȡͼ������
    string getISBN() const { return isbn; }// ��ȡ���ʱ�׼��ţ�ISBN��������ͼ���Ψһ��ʶ��
    bool getIsBorrowed() const { return isBorrowed; }// ���ͼ���Ƿ��ѱ����

    // ͼ����ĺ͹黹����
    void borrow() { isBorrowed = true; }// ��ͼ��״̬����Ϊ"�ѽ��"
    void returnBook() { isBorrowed = false; }// ��ͼ��״̬����Ϊ"�ɽ���"���黹������
    bool canBorrow() const { return !isBorrowed; }// ���ͼ�鵱ǰ�Ƿ�ɽ��ģ�δ�������
};

class Reader//������
{
private:
    string readerld;//����ID
    string name;//����
    vector<Book*> borrowedBooks;//���ĵ�ͼ���б�ʹ��ָ��ָ��Library�е�Book����
public:
    // ���캯������ʼ��������Ϣ
    Reader(const string& id, const string& n) :readerld(id), name(n) {}

    // ��ȡ������Ϣ�Ľӿں���
    string getReaderld() const { return readerld; }// ��ȡ���ߵ�Ψһ��ʶ����Reader ID��
    string getName() const { return name; }// ��ȡ��������
    const vector<Book*>& getBorrowedBooks() const { return borrowedBooks; }// ���ض��ߵ�ǰ���ĵ�����ͼ���б�ֻ�����ã�

    // ����ͼ�飺���ͼ��ɽ裬�����ͼ��״̬����ӵ������б�
    bool borrowBook(Book* book) {
        if (book->canBorrow()) {
            book->borrow();// ����ͼ�����״̬
            borrowedBooks.push_back(book);// ��ӵ������б�
            return true;
        }
        return false;
    }

    // �黹ͼ�飺�ӽ����б����Ƴ�ͼ�鲢����ͼ��״̬
    bool returnBook(Book* book) {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (*it == book) {
                book->returnBook();// ����ͼ��黹״̬
                borrowedBooks.erase(it);// �ӽ����б��Ƴ�
                return true;
            }
        }
        return false;
    }
};

class Library//ͼ�����
{
private:
    vector<Book> books;// ͼ�������ͼ��
    vector<Reader> readers; // ���ж���
public:
     // �������
    void addBook(const string& title, const string& author, const string& isbn) {
        books.emplace_back(title, author, isbn);
    }

     // ����¶���
    void addReader(const string& readerld, const string& name) {
        readers.emplace_back(readerld, name);
    }

    // ����ͼ����ģ����ݶ���ID��ISBN���Ҳ��������
    bool borrowBook(const string& readerld, const string& isbn) {
        Reader* reader = nullptr;
        Book* book = nullptr;

        // ���Ҷ���
        for (auto& r : readers) {
            if (r.getReaderld() == readerld) {
                reader = &r;
                break;
            }
        }

        // ����ͼ��
        for (auto& b : books) {
            if (b.getISBN() == isbn) {
                book = &b;
                break;
            }
        }

        // ����ҵ����ߺ�ͼ�飬ִ�н��Ĳ���
        if (reader && book) {
            return reader->borrowBook(book);
        }
        return false;
    }

    // ����ͼ��黹�����ݶ���ID��ISBN���Ҳ�����黹
    bool returnBook(const string& readerld, const string& isbn) {
        Reader* reader = nullptr;
        Book* book = nullptr;

        // ���Ҷ���
        for (auto& r : readers) {
            if (r.getReaderld() == readerld) {
                reader = &r;
                break;
            }
        }

        // ����ͼ��
        for (auto& b : books) {
            if (b.getISBN() == isbn) {
                book = &b;
                break;
            }
        }

         // ����ҵ����ߺ�ͼ�飬ִ�й黹����
        if (reader && book) {
            return reader->returnBook(book);
        }
        return false;
    }

    // ��ʾ����ͼ����Ϣ
    void displayBooks() const {
        for (const auto& book : books) {
            cout << "����:" << book.getTitle() << ",����:" << book.getAuthor() << ",ISBN:" << book.getISBN() 
                 << ",״̬:" << (book.getIsBorrowed() ? "�ѽ��" : "�ɽ���") << endl;
        }
    }

    // ��ʾ���ж�����Ϣ������ļ�¼
    void displayReaders() const {
        for (const auto& reader : readers) {
            cout << "����ID:" << reader.getReaderld() << "������:" << reader.getName() << endl;
            const auto& borrowedBooks = reader.getBorrowedBooks();
            if (!borrowedBooks.empty()) {
                cout << "���ĵ�ͼ��:" << endl;
                for (const auto& book : borrowedBooks) {
                    cout << "����:" << book->getTitle() << ",ISBN:" << book->getISBN() << endl;
                }
            }
        }
    }
};

int main()
{
    Library library;// ����ͼ���ʵ��
    int choice; // �û�ѡ��Ĳ���
    string title, author, isbn, readerld, name;// ��ʱ�洢������Ϣ
    do
    {
        cout << "1.���ͼ��" << endl;
        cout << "2.��Ӷ���" << endl;
        cout << "3.����ͼ��" << endl;
        cout << "4.�黹ͼ��" << endl;
        cout << "5.��ʾͼ����Ϣ" << endl;
        cout << "6.��ʾ������Ϣ" << endl;
        cout << "7.�˳�" << endl;
        cout << "���������ѡ��:";
        cin >> choice;
        cin.ignore(); // ����������еĻ��з�
        
        switch (choice) {
        case 1: // ���ͼ��
            cout << "����������:";
            getline(cin, title);
            cout << "����������:";
            getline(cin, author);
            cout << "������ISBN:";
            cin >> isbn;
            cin.ignore(); // ����������еĻ��з�
            library.addBook(title, author, isbn);
            break;
        case 2:// ��Ӷ���
            cout << "���������ID:";
            cin >> readerld;
            cin.ignore(); // ����������еĻ��з�
            cout << "�������������:";
            getline(cin, name);
            library.addReader(readerld, name);
            break;
        case 3:// ����ͼ��
            cout << "���������ID:";
            cin >> readerld;
            cout << "������ISBN:";
            cin >> isbn;
            if (library.borrowBook(readerld, isbn)) {
                cout << "���ĳɹ�" << endl;
            }
            else {
                cout << "����ʧ��" << endl;
            }
            break;
        case 4:// �黹ͼ��
            cout << "���������ID:";
            cin >> readerld;
            cout << "������ISBN:";
            cin >> isbn;
            if (library.returnBook(readerld, isbn)) {
                cout << "�黹�ɹ�" << endl;
            }
            else {
                cout << "�黹ʧ��" << endl;
            }
            break;
        case 5:// ��ʾͼ����Ϣ
            library.displayBooks();
            break;
        case 6:// ��ʾ������Ϣ
            library.displayReaders();
            break;
        case 7:// �˳�ϵͳ
            cout << "�˳�ϵͳ" << endl;
            break;
        default:
            cout << "��Ч��ѡ������������" << endl;
        }
    } while (choice != 7);
    return 0;
}