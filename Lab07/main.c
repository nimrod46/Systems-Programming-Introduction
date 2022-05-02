#include "Student.h"
#include <stdio.h>

int main() {
	Student itai = StudentCreate("Itai", "123456789");
	StudentSetGrade(itai, 2, 100);
	StudentSetGrade(itai, 15, 62);
	StudentSetGrade(itai, 39, 48);
	StudentSetGrade(itai, 51, 77);
	StudentSetGrade(itai, 69, 94);
	StudentSetGrade(itai, 81, 56);
	StudentSetGrade(itai, 97, 69);

	for(Course i=0; i<MAX_COURSES; i++) {
		Grade g = StudentGetGrade(itai, i);
		if(g != (Grade)NO_GRADE)
			printf("Itai\'s grade in %u is %u\n", i, g);
	}
	StudentDestroy(itai);

	return 0;
}
