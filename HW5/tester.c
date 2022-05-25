//
// Created by nimrod on 25-May-22.
//
void runUncomp(const char input[], const char output[]);
void runComp(const char input[], const char output[]);

int main(int argc, char *argv[]) {
    runComp(argv[1], argv[2]);
    runUncomp(argv[2], "textcomp.txt");
}
