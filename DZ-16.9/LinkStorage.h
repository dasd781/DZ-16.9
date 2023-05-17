#pragma once


template<typename T> class LinkStorage
{
public:
    LinkStorage();    //Конструкторы копирования, перемещения и прочее не реализуем, т.к. "хранилище взаимосвязей" предполагается только одно на всю программу
    ~LinkStorage();   //В деструктре удаляем динамически созданные данные
    void AddUser();             //Добавить новый элемент
    std::shared_ptr<T> Get(int ID1, int ID2) const;
    std::shared_ptr<T> GetMain() const;
    void PrintAddresses() const;      //Вывести на экран адреса указателей, записанные в каждой ячейке массива ТОЛЬКО ДЛЯ ОТЛАДКИ
    void PrintData();           //Вевести данные по указателю из каждой ячейки ТОЛЬКО ДЛЯ ОТЛАДКИ
private:
    //std::vector<std::vector<T*> > m_storage;   //двумерный массив, основанный на классе вектор для хранения указателей на пользовательские чаты
    //T* m_mainPtr;                              //указатель на основной объект (в случае чата - на общий чат)
    std::vector<std::vector<std::shared_ptr<T> > > m_storage;
    std::shared_ptr<T> m_mainPtr;
    int m_count;                                //число пользователей
};

template<typename T> LinkStorage<T>::LinkStorage()
{
    //m_mainPtr = new T;      //Создаём тольк общий для всех пользователей указатель (общий чат)
    m_mainPtr = std::make_shared<T>();
    m_count = 0;            //При создании количество пользователей равно нулю

    m_storage.resize(1);    //Создаём двумерый массив 1 на 1
    m_storage[0].resize(1);

    m_storage[0][0] = nullptr;  //Массив содержит просто один нулевой указатель, это можно было и не указывать

    std::cout << "Link storage " << this << " created\n";
}

template<typename T> LinkStorage<T>::~LinkStorage()
{
    /*  //после добавления умных указателей деструктор как таковой стал не нужен
    delete m_mainPtr;       //удаляем общий объект (общий чат)
    for (size_t i = 0; i < m_storage.size(); ++i)
    {
        delete m_storage[i][i];     //Удаляем диагональ 2д массива, т.е. удаляем чаты с самими собой
        m_storage[i][i] = nullptr;
    }
    size_t ctr = 1;             //счетчик для смещения диагонального элемента при переходе на новую строку
    for (size_t i = 0; i < m_storage.size() - 1; ++i)
    {
        for (size_t j = ctr; j < m_storage.size(); ++j)
        {
            delete m_storage[i][j];
            m_storage[i][j] = nullptr; //это делать не обязательно, просто для наглядности
            m_storage[j][i] = nullptr; //чтобы ещё раз напомнить, что m_storage[i][j] и m_storage[j][i] это один и тот же чат
        }
        ++ctr;                     //смещаем счетчик диагонального элемента при переходе на следующую строку
    }
    //*/
    std::cout << "Link storage " << this << " deleted\n";
}

template<typename T> void LinkStorage<T>::AddUser()
{
    ++m_count;  //увеличиваем количество пользователей на единицу при добавлении нового пользоваетля (в чат)

    if (m_count == 1) //Если это первый добавленный пользователь, то создается только чат с "самим собой", т.е. Заметки
    {
        //m_storage[0][0] = new T; 
        m_storage[0][0] = std::make_shared<T>();
        return;
    }
    else
    {
        //Добавляем +1 строку и +1 столбец
        m_storage.resize(m_count);
        for (size_t i = 0; i < m_storage.size(); ++i) { m_storage[i].resize(m_count); }

        //m_storage[m_storage.size() - 1][m_storage.size() - 1] = new T;    //Создаём чат с самим собой для новоиспеченного пользователя
        m_storage[m_storage.size() - 1][m_storage.size() - 1] = std::make_shared<T>();    //Создаём чат с самим собой для новоиспеченного пользователя
        for (size_t i = 0; i < m_storage.size() - 1; ++i)     //Добавляем личные сообщения пользователя с остальными пользователями
        {
            //m_storage[i][m_storage.size() - 1] = new T;       //создаём личный чат между пользователем A и B;
            m_storage[i][m_storage.size() - 1] = std::make_shared<T>();       //создаём личный чат между пользователем A и B;
            m_storage[m_storage.size() - 1][i] = m_storage[i][m_storage.size() - 1];    //Чат между пользователем B и A это тот же самый чат, что между A и B
        }
    }
}

template<typename T> void LinkStorage<T>::PrintAddresses() const
{
    if (m_count == 0) { std::cout << "контейнер пуст\n"; return; }

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
    if (m_count == 0) { std::cout << "контейнер пуст\n"; return; }

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

/*  //Класс для теста LinkStorage
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