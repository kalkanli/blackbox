struct input{
    string path<>;
    int number1;
    int number2;

};

struct output{
    string message<>;
    int status_code;
};

program PART_B_PROGRAM{
    version PART_B_VERSION{
        output part_b(input)=1;
    }=1;
}=0x12345678;