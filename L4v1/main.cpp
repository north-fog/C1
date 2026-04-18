#include <iostream>
#include <cstdlib>
#include <ctime>
#include "TQueue.h"
#include "TJobStream.h"
#include "TProc.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    
    // Входные параметры
    int JobIntensity, ProcPower, TotalTicks, QueueSize;
    
    cout << "============================================" << endl;
    cout << "   ИМИТАЦИОННОЕ МОДЕЛИРОВАНИЕ ВС" << endl;
    cout << "============================================" << endl;
    
    // Ввод параметров
    cout << "\nВведите интенсивность потока заданий (0-100%): ";
    cin >> JobIntensity;
    cout << "Введите производительность процессора (0-100%): ";
    cin >> ProcPower;
    cout << "Введите максимальный размер очереди: ";
    cin >> QueueSize;
    cout << "Введите количество тактов имитации: ";
    cin >> TotalTicks;
    
    // Создание объектов
    TQueue queue(QueueSize);
    TJobStream jobStream(JobIntensity);
    TProc processor(ProcPower);
    
    // Статистика
    int totalJobs = 0;        // всего поступило заданий
    int rejectedJobs = 0;     // отказов (очередь полна)
    int completedJobs = 0;    // выполнено заданий
    int idleTicks = 0;        // такты простоя процессора
    int totalExecTime = 0;    // суммарное время выполнения
    
    // Для пошагового вывода
    bool stepByStep = (TotalTicks <= 50);
    
    cout << "\n--- НАЧАЛО ИМИТАЦИИ ---\n" << endl;
    
    // Основной цикл имитации
    for (int tick = 1; tick <= TotalTicks; tick++) {
        if (stepByStep) {
            cout << "\n===== ТАКТ " << tick << " =====" << endl;
        }
        
        // 1. ГЕНЕРАЦИЯ НОВОГО ЗАДАНИЯ
        int newJob = jobStream.GetNewJob();
        if (newJob) {
            totalJobs++;
            int jobId = totalJobs;
            
            if (stepByStep) {
                cout << "  Сгенерировано новое задание #" << jobId << endl;
            }
            
            // Пытаемся поставить в очередь
            if (!queue.IsFull()) {
                queue.Put(jobId);
                if (stepByStep) {
                    cout << "  Задание #" << jobId << " поставлено в очередь" << endl;
                }
            } else {
                rejectedJobs++;
                if (stepByStep) {
                    cout << "  ОТКАЗ: очередь переполнена, задание #" << jobId << " потеряно" << endl;
                }
            }
        }
        
        // 2. ОБСЛУЖИВАНИЕ ПРОЦЕССОРОМ
        // Проверяем, закончилось ли текущее задание
        if (processor.IsProcBusy()) {
            // С вероятностью ProcPower задание завершается
            int finish = (rand() % 100) < ProcPower;
            
            if (finish) {
                if (stepByStep) {
                    cout << "  Процессор завершил выполнение задания" << endl;
                }
                completedJobs++;
                // Процессор освободился
                // Пытаемся взять новое задание из очереди
                if (!queue.IsEmpty()) {
                    int newJobId = queue.Get();
                    processor.RunNewJob(newJobId);
                    if (stepByStep) {
                        cout << "  Процессор начал выполнение задания #" << newJobId << " из очереди" << endl;
                    }
                } else {
                    if (stepByStep) {
                        cout << "  Очередь пуста, процессор простаивает" << endl;
                    }
                }
            } else {
                if (stepByStep) {
                    cout << "  Процессор продолжает выполнение задания" << endl;
                }
            }
        } else {
            // Процессор свободен
            idleTicks++;
            if (stepByStep) {
                cout << "  Процессор свободен (такт простоя #" << idleTicks << ")" << endl;
            }
            
            // Пытаемся взять задание из очереди
            if (!queue.IsEmpty()) {
                int newJobId = queue.Get();
                processor.RunNewJob(newJobId);
                if (stepByStep) {
                    cout << "  Процессор начал выполнение задания #" << newJobId << " из очереди" << endl;
                }
            }
        }
        
        // Вывод состояния очереди (для пошагового режима)
        if (stepByStep) {
            cout << "  Очередь: ";
            if (queue.IsEmpty()) {
                cout << "пуста";
            } else {
                // Создаем копию для просмотра
                TQueue temp(queue);
                cout << "[";
                while (!temp.IsEmpty()) {
                    cout << " " << temp.Get();
                }
                cout << " ]";
            }
            cout << " (размер: " << queue.GetDataCount() << ")" << endl;
        }
    }
    
    // 3. ВЫВОД РЕЗУЛЬТАТОВ
    cout << "\n\n============================================" << endl;
    cout << "   РЕЗУЛЬТАТЫ ИМИТАЦИИ" << endl;
    cout << "============================================" << endl;
    
    cout << "\n--- ПАРАМЕТРЫ ЭКСПЕРИМЕНТА ---" << endl;
    cout << "Интенсивность потока заданий: " << JobIntensity << "%" << endl;
    cout << "Производительность процессора: " << ProcPower << "%" << endl;
    cout << "Максимальный размер очереди: " << QueueSize << endl;
    cout << "Количество тактов имитации: " << TotalTicks << endl;
    
    cout << "\n--- ПОКАЗАТЕЛИ ФУНКЦИОНИРОВАНИЯ ---" << endl;
    cout << "Всего поступило заданий: " << totalJobs << endl;
    cout << "Отказов в обслуживании: " << rejectedJobs << endl;
    
    if (totalJobs > 0) {
        double rejectPercent = (double)rejectedJobs / totalJobs * 100;
        cout << "Процент отказов: " << rejectPercent << "%" << endl;
    } else {
        cout << "Процент отказов: 0%" << endl;
    }
    
    cout << "Всего выполнено заданий: " << completedJobs << endl;
    cout << "Тактов простоя процессора: " << idleTicks << endl;
    
    double idlePercent = (double)idleTicks / TotalTicks * 100;
    cout << "Процент простоя процессора: " << idlePercent << "%" << endl;
    
    if (completedJobs > 0) {
        // Среднее время выполнения = количество тактов / количество выполненных заданий
        // Но в нашей модели каждое задание выполняется в среднем за (1 / (ProcPower/100)) тактов
        double avgExecTime = 100.0 / ProcPower;
        cout << "Среднее количество тактов выполнения задания: " << avgExecTime << endl;
    }
    
    cout << "\n============================================" << endl;
    cout << "   ИМИТАЦИЯ ЗАВЕРШЕНА" << endl;
    cout << "============================================" << endl;
    
    return 0;
}