//
// Created by nimrod on 25-May-22.
//
void runDecomp(const char input[], const char output[]);
void runComp(const char input_file_name[], const char output_file_name[]);

int main(int argc, char *argv[]) {
    runComp(argv[1], argv[2]);
    runDecomp(argv[2], "textcomp.txt");
}
