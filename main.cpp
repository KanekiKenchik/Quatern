#include"quatern.cpp"

int main()
{
    cout << "Демонстрация моделирования  поворотов" 
         << "в трёхмерном пространстве с помощью  кватернионов" << endl << endl;
    cout << "Выберите операцию:" << endl << endl;
    cout << "1 - Сложение двух кватернионов" << endl << endl;
    cout << "2 - Перемножение двух кватернионов" << endl << endl;
    cout << "3 - Умножение кватерниона на константу" << endl << endl;
    cout << "4 - Поворот векторного кватерниона v вокруг" << endl
         << "    оси единичного кватерниона p на угол  phi против часовой стрелки" << endl
         << "    (кватернионы v и p не обязательно ортогональны)" << endl << endl
         << "Для продолжения нажмите любую клавишу..." << endl << endl;
    getchar();
    cout << "5 - Композиция поворотов:" << endl
         << "    (1) вначале  поворот вокруг  оси единичного векторного " << endl
         << "    кватерниона [p11,p12,p13] на угол  2*phi1 против часовой стрелки" << endl
         << "    (2) затем  поворот вокруг  оси единичного  векторного" << endl
         << "    кватерниона [q11,q12,q13] на угол 2*phi2 против часовой стрелки" << endl << endl;
    cout << "6 - Результат  поворота векторного кватерниона v" << endl
         << "    после применения к нему композиции поворотов:" << endl
         << "    (1) вначале  поворот вокруг  оси единичного векторного" << endl
         << "    кватерниона p на угол  2*phi1 против часовой стрелки" << endl
         << "    (2) затем  поворот вокруг  оси единичного  векторного " << endl
         << "    кватерниона q на угол 2*phi2 против часовой стрелки" << endl << endl;
    cout << "7 - Протестировать программу" << endl << endl;
    cout << "0 - Выход" << endl;
    
    vector<float> p, q, v;
    float c, phi, phi1, phi2;
    pair<pair<float, vector<float>> , vector<float>> res2;
    pair<float, vector<float>>  res1;
    
    char options;
    while (1)
    {
        cout << "\n\nВыберите действие: ";
        cin >> options;
        switch (options)
        {
        case '1':
            cout << endl << "Выбрано: Сложение двух кватернионов" << endl << endl;
            p = setQuat();
            q = setQuat();
            cout << "Результат сложения 2 кватернионов: ";
            output(summ(p,q));
        break;

        case '2':
            cout << endl << "Выбрано: Перемножение двух кватернионов" << endl << endl;
            p = setQuat();
            q = setQuat();
            cout << "Результат перемножения 2 кватернионов: ";
            output(mult(p,q));
        break;

        case '3':
            cout << endl << "Выбрано: Умножение кватерниона на константу" << endl << endl;
            p = setQuat();
            cout << "Введите константу: ";
            cin >> c; 
            cout << "\nРезультат умножения кватерниона на константу: ";
            output(multC(c,p));
        break;

        case '4':
            cout << endl << "Выбрано: POVOR2" << endl << endl;
            p = setVect("p");
            q = setVect("q");
            cout << "Введите угол phi (в градусах): ";
            cin >> phi;
            phi=phi*pi/180;
            cout << "Результат поворота: "; 
            output(povor2(p,q,phi));
        break;

        case '5':
            cout << endl << "Выбрано: POVOR3" << endl << endl;
            p = setVect("p");
            q = setVect("q");
            cout << "Введите углы phi1, phi2 (в градусах): ";
            cin >> phi1; 
            phi1=phi1*pi/180;
            cin >> phi2;
            phi2=phi2*pi/180;
            res1 =  povor3(p,q,phi1,phi2);
            cout << "Угол поворота: " << res1.first << endl;
            cout << "Ось поворота: "; 
            output(res1.second);
        break;

        case '6':
            cout << endl << "Выбрано: POVOR4" << endl << endl;
            p = setVect("p");
            q = setVect("q");
            cout << "Введите углы phi1, phi2 (в градусах): ";
            cin >> phi1; 
            phi1=phi1*pi/180;
            cin >> phi2;
            phi2=phi2*pi/180;
            v = setVect("v");
            res2 =  povor4(p,q,phi1,phi2,v);
            cout << "Угол поворота: " << res2.first.first << endl;
            cout << "Ось поворота: "; 
            output(res2.first.second);
            cout << "Результат поворота: "; 
            output(res2.second);
        break;   

        case '7':
            test();
        break;

        case '0': exit(1);     

        default:
            cout << "Нет такого варианта!" << endl;
        break;
        }
    }
    return 0;
}