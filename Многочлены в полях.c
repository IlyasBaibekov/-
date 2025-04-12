#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>

#define N 3

int sum(int a, int b, int n)
{
    return((a+b)%n);
}

int sub(int a, int b, int n)
{
    int c = a-b;
    if(c>=n)
    {
        c = c%n;
    }
    if (c<0)
    {
        while(c<0)
        {
            c = c + n;
        }
    }
    return(c);
}

int mul(int a, int b, int n)
{
    return((a*b)%n);
}

int divv(int a, int b, int n)
{
    int c;
    for(int j=0;j<n;j++)
    {
        c = mul(b,j,n);
        if (c==a)
        {
            c = j;
            return(c);
        }
    }

}

int reducing(int a, int n)
{
    if (a >= 0)
    {
        return(a%n);
    }
    while(a<0)
    {
        a = a +n;
    }
    return a;

}


struct Node
{
    int pow;
    int value;
    struct Node* next;
};

struct Node* createNode(int pow, int value) 
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->pow = pow;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Функция для добавления узла в многочлен
void addNode(struct Node** poly, int pow, int value) {
    struct Node* newNode = createNode(pow, value);
    if (*poly == NULL) {
        *poly = newNode;
    } else {
        struct Node* temp = *poly;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}


struct Node* createpoly()
{
    int k, a;
    printf("Степень многочлена: ");
    scanf("%d", &k);
    struct Node* odnochlen = (struct Node*)malloc(sizeof(struct Node));
    if (odnochlen == NULL) {
        // Обработка ошибки выделения памяти
        return NULL;
    }
    odnochlen->pow = k;
    printf("Коэффициент при x^(%d): ", k);
    scanf("%d", &a);
    odnochlen->value = a;
    odnochlen->next = NULL;

    struct Node* polynom = odnochlen;
    struct Node* pred = odnochlen;

    for (int i = 0; i < k; i++)
    {
        struct Node* odnochlen = (struct Node*)malloc(sizeof(struct Node));
        if (odnochlen == NULL) {
            // Обработка ошибки выделения памяти
            // Освобождение уже выделенной памяти
            while (polynom != NULL) {
                struct Node* temp = polynom;
                polynom = polynom->next;
                free(temp);
            }
            return NULL;
        }
        pred->next = odnochlen;
        odnochlen->pow = k - i-1;
        printf("Коэффициент при x^(%d): ", k - i-1);
        scanf("%d", &a);
        odnochlen->value = a;
        odnochlen->next = NULL;
        pred = odnochlen;
    }
    return polynom;
}

void printpoly(struct Node* head)
{

    if(!head) // HEAD == NULL
        printf("Наш список пуст\n");
    printf("%dх^%d", head->value, head->pow);
    head = head->next;
    while(head) //Пока указатель на голову списка не равен нулл
    {
        if(head->value>0)
            printf("+%dх^%d", head->value, head->pow);

        if(head->value<0)
            printf("%dх^%d", head->value, head->pow);
        head = head->next;}
    printf("\n");
}

struct Node* copyPoly(struct Node* head) {
    if (head == NULL) {
        return NULL; // Если список пуст, возвращаем NULL
    }

    // Создаем новый узел с данными из первого узла исходного списка
    struct Node* newHead = (struct Node*)malloc(sizeof(struct Node));
    if (newHead == NULL) {
        return NULL; // Не удалось выделить память
    }
    newHead->value = head->value;
    newHead->pow = head->pow;
    newHead->next = NULL;

    // Последний узел нового списка, который мы будем заполнять
    struct Node* last = newHead;

    // Текущий узел исходного списка, начиная со второго
    struct Node* current = head->next;

    while (current != NULL) {
        // Создаем новый узел
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            // Очистка памяти в случае ошибки
            while (newHead != NULL) {
                struct Node* temp = newHead;
                newHead = newHead->next;
                free(temp);
            }
            return NULL;
        }

        // Копируем данные
        newNode->value = current->value;
        newNode->pow = current->pow;
        newNode->next = NULL;

        // Добавляем новый узел в конец нового списка
        last->next = newNode;
        last = newNode;

        // Переходим к следующему узлу исходного списка
        current = current->next;
    }

    return newHead; // Возвращаем новый список
}

struct Node* createEmptyPoly(int l) {
    if (l <= 0) {
        return NULL; // Возвращаем NULL для некорректной длины
    }

    // Создаем головной узел для многочлена
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    if (head == NULL) {
        return NULL; // Не удалось выделить память
    }
    head->value = 0;
    head->pow = l - 1;
    head->next = NULL;

    struct Node* current = head;

    // Создаем остальные узлы многочлена
    for (int i = l - 2; i >= 0; --i) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            // Очистка памяти если ошибка
            while (head != NULL) {
                struct Node* temp = head;
                head = head->next;
                free(temp);
            }
            return NULL;
        }

        newNode->value = 0;
        newNode->pow = i;
        newNode->next = NULL;

        current->next = newNode;
        current = newNode;
    }

    return head; // Возвращаем указатель на созданный многочлен
}
int isZeroPoly(struct Node* head) {
    // Проверяем, не является ли список пустым
    if (head == NULL) {
        return -1; // Возвращаем -1, так как многочлен не может быть пустым
    }

    struct Node* current = head;
    while (current != NULL) {
        if (current->value != 0) {
            return -1; // Найден коэффициент, не равный нулю
        }
        current = current->next;
    }

    return 1; // Все коэффициенты равны нулю
}


void freePoly(struct Node* head) {
    struct Node* tmp;

    // Проходим по списку и освобождаем узлы по одному
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

struct Node* Delenie(struct Node* poly1, struct Node* poly2) {
    if (poly1 == NULL || poly2 == NULL || poly2->value == 0) {
        return NULL; // Нельзя делить на ноль или пустой многочлен
    }

    if ((poly1->pow)<(poly2->pow))
    {
        return NULL;
    }
    struct Node* copypoly1 = copyPoly(poly1);
    struct Node* resultat = createEmptyPoly(poly1->pow - poly2->pow + 1);
    struct Node* currentResult = resultat;

    while (copypoly1 != NULL && copypoly1->pow >= poly2->pow) {
        if (copypoly1->value != 0) {
            int coefficient = divv(copypoly1->value, poly2->value, N);
            currentResult->value = coefficient;
            currentResult->pow = copypoly1->pow - poly2->pow;

            struct Node* tempPoly2 = poly2;
            struct Node* tempCopyPoly1 = copypoly1;
            while (tempPoly2 != NULL) {
                tempCopyPoly1->value = sub(tempCopyPoly1->value, mul(coefficient, tempPoly2->value, N), N);
                tempPoly2 = tempPoly2->next;
                if (tempPoly2 != NULL) {
                    tempCopyPoly1 = tempCopyPoly1->next;
                }
            }
        }
        copypoly1 = copypoly1->next;
        if (currentResult->pow > 0) {
            currentResult->next = createEmptyPoly(currentResult->pow);
            currentResult = currentResult->next;
        }
    }

    if (isZeroPoly(copypoly1) == 1) {
        freePoly(copypoly1); // Функция freePoly должна корректно освобождать всю память связного списка
        return resultat;
    } else {
        freePoly(resultat); // Аналогично, функция freePoly должна освобождать память
        freePoly(copypoly1);
        return NULL;
    }
}

int* createmass(int k)
{
    int* massiv = (int*)malloc(sizeof(int)*(k+1));
    for (int i = 0; i<k+1;i++)
    {
        massiv[i] = 0;
    }
    massiv[0] = 1;
    return massiv;
}

struct Node* masstopoly(int* mass, int k)
{
    struct Node* a = createEmptyPoly(k+1);
    struct Node* b = a;
    for(int i=0;i<k+1;i++)
    {
        a->value=mass[i];
        a=a->next;
    }
    return b;
};


int* newarray(int length) {
    // Выделение памяти для массива
    int* array = (int*)malloc(length * sizeof(int));

    // Проверка на успешное выделение памяти
    if (array == NULL) {
        return NULL; // В случае ошибки выделения памяти возвращаем NULL
    }

    // Инициализация массива нулями
    for (int i = 0; i < length; i++) {
        array[i] = 0;
    }

    return array; // Возвращаем указатель на массив
}

void Reduc(struct Node** poly) {
    if (poly == NULL || *poly == NULL) {
        return; // Проверка на пустой список
    }

    struct Node* tm = *poly;
    struct Node* prev = NULL;
    int count=0;
    int c =0;
    // Редуцирование коэффициентов
    while (tm != NULL) {
        count++;
        if((reducing(tm->value,N)==0))
           {
               c++;
           }
        tm->value = reducing(tm->value,N);
        tm = tm->next;
    }
    if (count==c)
    {
        return;
    }
    // Удаление ведущих нулей
    tm = *poly;
    while (tm != NULL && tm->value == 0) {
        prev = tm;
        tm = tm->next;
        free(prev); // Освобождение памяти
    }

    *poly = tm; // Обновление указателя на голову списка
}


struct Node* Multipoly(struct Node* poly1, struct Node* poly2) {
    if (poly1 == NULL || poly2 == NULL) {
        return NULL;
    }

    struct Node* result = NULL;

    for (struct Node* p1 = poly1; p1 != NULL; p1 = p1->next) {
        for (struct Node* p2 = poly2; p2 != NULL; p2 = p2->next) {
            int pow = p1->pow + p2->pow;
            int value = p1->value * p2->value;

            // Добавление или обновление коэффициента в результирующем многочлене
            struct Node* temp = result;
            struct Node* prev = NULL;
            while (temp != NULL && temp->pow > pow) {
                prev = temp;
                temp = temp->next;
            }
            if (temp != NULL && temp->pow == pow) {
                temp->value += value;
            } else {
                struct Node* newNode = createNode(pow, value);
                if (prev == NULL) {
                    newNode->next = result;
                    result = newNode;
                } else {
                    newNode->next = temp;
                    prev->next = newNode;
                }
            }
        }
    }

    Reduc(&result);
    return result;
}

struct Node* Addpoly(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    struct Node* p1 = poly1;
    struct Node* p2 = poly2;

    while (p1 != NULL || p2 != NULL) {
        int pow;
        int value = 0;

        if (p1 != NULL && (p2 == NULL || p1->pow > p2->pow)) {
            pow = p1->pow;
            value = p1->value;
            p1 = p1->next;
        } else if (p2 != NULL && (p1 == NULL || p1->pow < p2->pow)) {
            pow = p2->pow;
            value = p2->value;
            p2 = p2->next;
        } else {
            pow = p1->pow;
            value = p1->value + p2->value;
            p1 = p1->next;
            p2 = p2->next;
        }

        if (value != 0) {
            addNode(&result, pow, value);
        }
    }

    Reduc(&result);

    return result;
}

struct Node* Subpoly(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    struct Node* p1 = poly1;
    struct Node* p2 = poly2;

    while (p1 != NULL || p2 != NULL) {
        int pow;
        int value = 0;

        if (p1 != NULL && (p2 == NULL || p1->pow > p2->pow)) {
            pow = p1->pow;
            value = p1->value;
            p1 = p1->next;
        } else if (p2 != NULL && (p1 == NULL || p1->pow < p2->pow)) {
            pow = p2->pow;
            value = -p2->value; // Обратите внимание на знак
            p2 = p2->next;
        } else {
            pow = p1->pow;
            value = p1->value - p2->value;
            p1 = p1->next;
            p2 = p2->next;
        }

        if (value != 0) {
            addNode(&result, pow, value);
        }
    }
    Reduc(&result);

    return result;
}


int main()
{
    setlocale(LC_ALL, "rus"); //для русского языка
    setlocale(LC_NUMERIC, "C"); //для русского языка
    struct Node* poly1 = createpoly();
    struct Node* poly2 = createpoly();
    Reduc(&poly1);
    Reduc(&poly2);
    //struct Node* poly3 = Delenie(poly1,poly2);
    struct Node* poly3 = Multipoly(poly1,poly2);

    printpoly(poly3);

    struct Node* poly4 = Addpoly(poly1,poly2);
    printpoly(poly4);
    return 0;
}




