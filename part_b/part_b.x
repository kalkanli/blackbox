struct input{
    string path<>;
    int number1;
    int number2;
};

struct output {
    string result<>;
};

program PART_B_PROGRAM{
    version PART_B_VERSION{
        output part_b(input)=1;
    }=1;
}=0x12345678;