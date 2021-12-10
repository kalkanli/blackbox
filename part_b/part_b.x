struct input{
    string path<>;
    int number1;
    int number2;

};

program PART_B_PROGRAM{
    version PART_B_VERSION{
        string part_b(input)=1;
    }=1;
}=0x12345678;