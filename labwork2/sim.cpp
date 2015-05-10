//================================= sim.cpp =================================

#include "sim.h"

#include <QtConcurrent/QtConcurrentRun>

Sim::Sim(QObject *parent) : QObject(parent)
{
}

void Sim::init()
{
    // создаём файл
    logFile.setFileName(tr("log.txt"));
    logFile.open(QIODevice::WriteOnly);
    logFile.close();

    M = new int*[n]; // двумерный интовый массив
    R = new bool[n]; // одномерный булев массив

    // делаем массив массивов
    for (int i = 0; i < n; i++)
    {
        M[i] = new int[n];
    }
    // карта запуска
    for (char c = 'A'; c <= 'I'; c++)
        runMap.insert(c, true);
}

// ============================================

void Sim::start()
{
    init();
    // в первый момент одновременно стартую два независимых процесса
    QFuture<void> f1 = QtConcurrent::run(this, &Sim::a);
    QFuture<void> f2 = QtConcurrent::run(this, &Sim::b);
}

// ============================================

void Sim::a()
{
    log(QString("A started")); // пишем лог
    // совершаем некие действия над массивом согласно варианту
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            // закрываем мьютекс, соответсвующий редактируемому массиву
            QMutexLocker locker(&mMutex);
            M[i][j] = i * n + j;
            // изменяем состояние прогресс-бара
            emit progressChanged('A', float(i * n + j + 1) / n / n * 100);
        }

    QMutexLocker locker(&rmMutex); // закрываем мьютекс
    runMap['A'] = false; // снимаем о работе

    // если параллельный процесс уже снял свой флаг
    // то родителем следующего процесса будет текущий

    if (!runMap['A'] && !runMap['B'])
    {
        // запускаем процесс и передаём ему инфу о родителе
        QFuture<void> f1 = QtConcurrent::run(this, &Sim::c, 'B');
    }

    log(QString("A finished")); // пишем лог
}

// ============================================

void Sim::b()
{
    log(QString("B started"));
    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        {
            QMutexLocker locker(&rMutex);
            R[i] = true;
            emit progressChanged('B', float(i * n + j + 1) / n / n * 100);
        }

    QMutexLocker locker(&rmMutex);
    runMap['B'] = false;

    if (!runMap['A'] && !runMap['B'])
    {
        QFuture<void> f1 = QtConcurrent::run(this, &Sim::c, 'B');

    }
    log(QString("B finished"));
}

// ============================================

void Sim::c(char parent)
{
    log(QString("C started by %1").arg(parent));

    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        {
        QMutexLocker locker1(&mMutex);
        QMutexLocker locker2(&rMutex);
            R[i] = !R[i];
            M[i][j]++;
            emit progressChanged('C', float(i * n + j + 1) / n / n * 100);
        }

    QMutexLocker locker(&rmMutex);
    runMap['C'] = false;

    // поскольку родителем данных процессов может быть только текущий
    // то по его выполнению запускаем их безусловно
    QFuture<void> f1 = QtConcurrent::run(this, &Sim::d, 'C');
    QFuture<void> f2 = QtConcurrent::run(this, &Sim::e, 'C');
    QFuture<void> f3 = QtConcurrent::run(this, &Sim::f, 'C');

    log(QString("C finished"));
}

// ============================================

void Sim::d(char parent)
{
    log(QString("D started by %1").arg(parent));

    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        {
        QMutexLocker locker1(&mMutex);
        QMutexLocker locker2(&rMutex);
            R[i] = !R[i];
            M[i][j]++;
            emit progressChanged('D', float(i * n + j + 1) / n / n * 100);
        }

    QMutexLocker locker(&rmMutex);
    runMap['D'] = false;

    QFuture<void> f1 = QtConcurrent::run(this, &Sim::g, 'D');

    log(QString("D finished"));
}

// ============================================

void Sim::e(char parent)
{
    log(QString("E started by %1").arg(parent));

    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        {
        QMutexLocker locker1(&mMutex);
        QMutexLocker locker2(&rMutex);
            R[i] = !R[i];
            M[i][j]++;
            emit progressChanged('E', float(i * n + j + 1) / n / n * 100);
        }

    QMutexLocker locker(&rmMutex);
    runMap['E'] = false;

    QFuture<void> f1 = QtConcurrent::run(this, &Sim::h, 'E');

    log(QString("E finished"));
}

// ============================================

void Sim::f(char parent)
{
    log(QString("F started by %1").arg(parent));

    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        {
        QMutexLocker locker1(&mMutex);
        QMutexLocker locker2(&rMutex);
            R[i] = !R[i];
            M[i][j]++;
            emit progressChanged('F', float(i * n + j + 1) / n / n * 100);
        }
    QMutexLocker locker(&rmMutex);
    runMap['F'] = false;

    if (!runMap['G'] && !runMap['H'] &&  !runMap['F'])
    {
        QFuture<void> f1 = QtConcurrent::run(this, &Sim::i, 'F');
    }


    log(QString("F finished"));
}

// ============================================

void Sim::g(char parent)
{
    log(QString("G started by %1").arg(parent));


    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        {
        QMutexLocker locker1(&mMutex);
        QMutexLocker locker2(&rMutex);
            R[i] = !R[i];
            M[i][j]++;
            emit progressChanged('G', float(i * n + j + 1) / n / n * 100);
        }
    QMutexLocker locker(&rmMutex);
    runMap['G'] = false;

    if (!runMap['G'] && !runMap['H'] &&  !runMap['F'])
    {
        QFuture<void> f1 = QtConcurrent::run(this, &Sim::i, 'G');
    }
    log(QString("G finished"));
}

// ============================================

void Sim::h(char parent)
{
    log(QString("H started by %1").arg(parent));

    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        {
            QMutexLocker locker1(&mMutex);
            QMutexLocker locker2(&rMutex);
            R[i] = !R[i];
            M[i][j]++;
            emit progressChanged('H', float(i * n + j + 1) / n / n * 100);
        }
    QMutexLocker locker(&rmMutex);
    runMap['H'] = false;

    if (!runMap['G'] && !runMap['H'] &&  !runMap['F'])
    {
        QFuture<void> f1 = QtConcurrent::run(this, &Sim::i, 'H');
    }


    log(QString("H finished"));
}

// ============================================

void Sim::i(char parent)
{
    log(QString("I started by %1").arg(parent));

    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        {
        QMutexLocker locker1(&mMutex);
        QMutexLocker locker2(&rMutex);
            R[i] = !R[i];
            M[i][j]++;
            emit progressChanged('I', float(i * n + j + 1) / n / n * 100);
        }

    log(QString("I finished"));
    emit finished(); // это последний процесс - передаём сигнал
}

// ============================================

void Sim::log(QString text)
{
    // закрываем мьютекс работы с файлом
    QMutexLocker locker(&fileMutex);
    // узнаём время и дату
    QDateTime localTime(QDateTime::currentDateTimeUtc().toLocalTime());
    // создаём текстовый поток и присоединяем его к файлу
    QTextStream stream(&logFile);
    // открываем файл для дозаписи в конец
    logFile.open(QIODevice::Append);
    // пишем в него инфу
    stream << "[" << localTime.toString("hh:mm:ss") << "] " << text << "\r\n";
    logFile.close(); // закрываем файл
}

// ============================================

Sim::~Sim()
{
    // удаляем всё, что нужнл удалить
    for (int i = 0; i < n; i++)
    {
        delete [] M[i];
    }

    delete [] M;
    delete [] R;
}
//==============================================================================
