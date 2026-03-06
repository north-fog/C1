// #include "TJobStream.h"
// #include <cstdlib>

// TJobStream::TJobStream(double Intens) {
//     if (Intens < 0 || Intens > 1) Intens = 0.5;
//     JobIntens = Intens;
// }

// bool TJobStream::GetNewJob() const {
//     // Генерация случайного числа от 0 до 1
//     double r = (double)rand() / RAND_MAX;
//     return r < JobIntens;
// }