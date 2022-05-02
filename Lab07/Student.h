//
// Created by nimrod on 01-May-22.
//

#ifndef SYSTEMS_PROGRAMMING_INTRODUCTION_STUDENT_H
#define SYSTEMS_PROGRAMMING_INTRODUCTION_STUDENT_H

#define MAX_COURSES 100
#define NO_GRADE -1

typedef unsigned int Course;
typedef unsigned int Grade;

typedef struct Student *Student;

Student StudentCreate(const char *name, const char *id);

void StudentDestroy(Student student);

void StudentSetGrade(Student student, Course course, Grade grade);

Grade StudentGetGrade(Student student, Course course);

#endif //SYSTEMS_PROGRAMMING_INTRODUCTION_STUDENT_H
