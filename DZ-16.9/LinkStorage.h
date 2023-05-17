#pragma once


template<typename T> class LinkStorage
{
public:
    LinkStorage();    //������������ �����������, ����������� � ������ �� ���������, �.�. "��������� ������������" �������������� ������ ���� �� ��� ���������
    ~LinkStorage();   //� ���������� ������� ����������� ��������� ������
    void AddUser();             //�������� ����� �������
    std::shared_ptr<T> Get(int ID1, int ID2) const;
    std::shared_ptr<T> GetMain() const;
    void PrintAddresses() const;      //������� �� ����� ������ ����������, ���������� � ������ ������ ������� ������ ��� �������
    void PrintData();           //������� ������ �� ��������� �� ������ ������ ������ ��� �������
private:
    //std::vector<std::vector<T*> > m_storage;   //��������� ������, ���������� �� ������ ������ ��� �������� ���������� �� ���������������� ����
    //T* m_mainPtr;                              //��������� �� �������� ������ (� ������ ���� - �� ����� ���)
    std::vector<std::vector<std::shared_ptr<T> > > m_storage;
    std::shared_ptr<T> m_mainPtr;
    int m_count;                                //����� �������������
};

template<typename T> LinkStorage<T>::LinkStorage()
{
    //m_mainPtr = new T;      //������ ����� ����� ��� ���� ������������� ��������� (����� ���)
    m_mainPtr = std::make_shared<T>();
    m_count = 0;            //��� �������� ���������� ������������� ����� ����

    m_storage.resize(1);    //������ �������� ������ 1 �� 1
    m_storage[0].resize(1);

    m_storage[0][0] = nullptr;  //������ �������� ������ ���� ������� ���������, ��� ����� ���� � �� ���������

    std::cout << "Link storage " << this << " created\n";
}

template<typename T> LinkStorage<T>::~LinkStorage()
{
    /*  //����� ���������� ����� ���������� ���������� ��� ������� ���� �� �����
    delete m_mainPtr;       //������� ����� ������ (����� ���)
    for (size_t i = 0; i < m_storage.size(); ++i)
    {
        delete m_storage[i][i];     //������� ��������� 2� �������, �.�. ������� ���� � ������ �����
        m_storage[i][i] = nullptr;
    }
    size_t ctr = 1;             //������� ��� �������� ������������� �������� ��� �������� �� ����� ������
    for (size_t i = 0; i < m_storage.size() - 1; ++i)
    {
        for (size_t j = ctr; j < m_storage.size(); ++j)
        {
            delete m_storage[i][j];
            m_storage[i][j] = nullptr; //��� ������ �� �����������, ������ ��� �����������
            m_storage[j][i] = nullptr; //����� ��� ��� ���������, ��� m_storage[i][j] � m_storage[j][i] ��� ���� � ��� �� ���
        }
        ++ctr;                     //������� ������� ������������� �������� ��� �������� �� ��������� ������
    }
    //*/
    std::cout << "Link storage " << this << " deleted\n";
}

template<typename T> void LinkStorage<T>::AddUser()
{
    ++m_count;  //����������� ���������� ������������� �� ������� ��� ���������� ������ ������������ (� ���)

    if (m_count == 1) //���� ��� ������ ����������� ������������, �� ��������� ������ ��� � "����� �����", �.�. �������
    {
        //m_storage[0][0] = new T; 
        m_storage[0][0] = std::make_shared<T>();
        return;
    }
    else
    {
        //��������� +1 ������ � +1 �������
        m_storage.resize(m_count);
        for (size_t i = 0; i < m_storage.size(); ++i) { m_storage[i].resize(m_count); }

        //m_storage[m_storage.size() - 1][m_storage.size() - 1] = new T;    //������ ��� � ����� ����� ��� ��������������� ������������
        m_storage[m_storage.size() - 1][m_storage.size() - 1] = std::make_shared<T>();    //������ ��� � ����� ����� ��� ��������������� ������������
        for (size_t i = 0; i < m_storage.size() - 1; ++i)     //��������� ������ ��������� ������������ � ���������� ��������������
        {
            //m_storage[i][m_storage.size() - 1] = new T;       //������ ������ ��� ����� ������������� A � B;
            m_storage[i][m_storage.size() - 1] = std::make_shared<T>();       //������ ������ ��� ����� ������������� A � B;
            m_storage[m_storage.size() - 1][i] = m_storage[i][m_storage.size() - 1];    //��� ����� ������������� B � A ��� ��� �� ����� ���, ��� ����� A � B
        }
    }
}

template<typename T> void LinkStorage<T>::PrintAddresses() const
{
    if (m_count == 0) { std::cout << "��������� ����\n"; return; }

    for (size_t i = 0; i < m_storage.size(); ++i)
    {
        for (size_t j = 0; j < m_storage.size(); ++j)
        {
            std::cout << m_storage[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

template<typename T> void LinkStorage<T>::PrintData()
{
    if (m_count == 0) { std::cout << "��������� ����\n"; return; }

    for (size_t i = 0; i < m_storage.size(); ++i)
    {
        for (size_t j = 0; j < m_storage.size(); ++j)
        {
            std::cout << *m_storage[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

template<typename T> std::shared_ptr<T> LinkStorage<T>::Get(int ID1, int ID2) const
{
    return m_storage[ID1][ID2];
}

template<typename T> std::shared_ptr<T> LinkStorage<T>::GetMain() const
{
    return m_mainPtr;
}

/*  //����� ��� ����� LinkStorage
struct staticInt
{
    static int i;
    int x = 0;
    staticInt() { x = i;  ++i; }
    friend std::ostream& operator<<(std::ostream& output, const staticInt& v);
};
int staticInt::i = 0;
std::ostream& operator<<(std::ostream& output, const staticInt& v)
{
    output << v.x;
    return output;
}
*/