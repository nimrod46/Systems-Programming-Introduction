//
// Created by nimrod on 01-May-22.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Student.h"


struct Student {
    char name[64];
    char id[16];
    Grade grades[MAX_COURSES];
};

Student StudentCreate(const char *name, const char *id) {
    Student student = calloc(sizeof(struct Student), 1);
    strcpy(student->name, name);
    strcpy(student->id, id);
    for (int i = 0; i < MAX_COURSES; ++i) {
        student->grades[i] = NO_GRADE;
    }
    return student;
}

void StudentDestroy(Student student) {
    free(student);
}

void StudentSetGrade(Student student, Course course, Grade grade) {
    if(course >= MAX_COURSES) {
        fprintf(stderr, "%s/%u: Illegal course number: %d\n",
                __FILE__, __LINE__, course);
        exit(-1);
    }

    if(grade > 100) {
        fprintf(stderr, "%s/%u: Illegal grade number: %d\n",
                __FILE__, __LINE__, grade);
        exit(-1);
    }

    student->grades[course] = grade;

}

Grade StudentGetGrade(Student student, Course course) {
    if(course >= MAX_COURSES) {
        fprintf(stderr, "%s/%u: Illegal course number: %d\n",
                __FILE__, __LINE__, course);
        exit(-1);
    }

    return student->grades[course];
}