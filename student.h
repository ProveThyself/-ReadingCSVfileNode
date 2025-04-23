#ifndef STUDENT_H
#define STUDENT_H

// ������������ ����� ���������� ����
#define MAX_FIELD 64

// �����, �������������� ��������
class student {
public:
    char last_name[MAX_FIELD];    // �������
    char first_name[MAX_FIELD];   // ���
    char middle_name[MAX_FIELD];  // ��������
    int age;                      // �������
    char gender[MAX_FIELD];       // ���

    student();                   // ����������� �� ���������
    void print() const;          // ����� ��� ������ ���������� � ��������
};

// ���������� ������������ �� ���������
inline student::student() {
    // ������������� ���� ��������� ����� ������� ��������
    last_name[0] = first_name[0] = middle_name[0] = gender[0] = '\0';
    age = 0;  // ������������� �������� �����
}

// ���������� ������ print
inline void student::print() const {
    // ����� ���������� � �������� � ������� CSV
    printf("%s;%s;%s;%d;%s\n", last_name, first_name, middle_name, age, gender);
}

#endif // STUDENT_H

