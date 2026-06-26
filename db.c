 typedef struct {
    char* buffer;
    size_t buffer_length;

    }






int main(int argc, char* argv[]){
    // The Initial REPL (Read-Eval-Print-Loop) used for 
    // taking user input evaluating it and then return it to the 
    // user
    InputBuffer* input_buffer = new_input_buffer();
    while(true){
        print_prompt();
        read_input(input_buffer);

        if(strcmp(input_buffer ->buffer, ".exit") == 0){
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("unrecognized commend '%s' .\n", input_buffer -> buffer);
        }
    }
}
