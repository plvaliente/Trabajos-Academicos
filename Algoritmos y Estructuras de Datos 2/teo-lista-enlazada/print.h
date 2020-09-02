#include <iostream>
#include <string>
#include <memory>

#ifndef PRINT_H_
#define PRINT_H_

#ifdef STACKTRACE
#define PRINT(msg)    stacktrace(msg, 2, 3)
#else
#define PRINT(msg)    print(msg)
#endif

class Print {
public:
    static Print& get_instance();
    
    void set(bool);
    void output(std::ostream* os);
    void close();
    
    
    template<class T>
    void out(const T& message) {
        if(do_print)
            *os << message;
    }
    
    
    /**
     * Imprime el stacktrace en el out definido.
     * 
     * from_frame determina la cantidad de frames a saltearse:
     * - cuando vale 0, se imprime todo
     * - cuando vale 1, se saltea esta funcion
     * - cuando vale x, se saltea las ultimas x funciones.
     * por lo tanto, si hay x funciones de impresion que se llaman hasta esta, conviene usar from_frame= x
     * 
     * Analogamente, skip_frames determina la cantidad de frames iniciales que se saltean.  Los primeros tres frames
     * suelen ser start, libc_start, y la funcion main.  Si ademas de esta se quieren saltear otras 5 funciones,
     * poner, por ejemplo, skip_frame = 3+5
     */
    void stacktrace(int from_frame=1, int skip_frames = 0, int max_frames=64);

private:
    Print();
    Print(const Print&);
    Print operator=(const Print&);

    //auto_ptr esta deprecado en C++11; habria que usar unique_ptr
    static std::auto_ptr<Print> print;

    std::ostream* os;
    bool do_print;
};

template<typename T>
void print(const T& message) {
    Print::get_instance().out(message);
    Print::get_instance().out('\n');
}

//quisiera poder usar variadic templates :(
template<typename T>
void stacktrace(const T& message, int from_frame=2, int skip_frames=0) {
    print(message);
    print("========== BEGIN STACKTRACE  ===========");
    Print::get_instance().stacktrace(from_frame, skip_frames);
    print("========== END OF STACKTRACE ===========");
}
#endif 
