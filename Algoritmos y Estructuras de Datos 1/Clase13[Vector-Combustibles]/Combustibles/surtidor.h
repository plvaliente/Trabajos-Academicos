#ifndef surtidorH
#define surtidorH

class Surtidor {

    public:
        Surtidor();
        Surtidor(int litros, int precio);
        int litrosDisponibles() const;
        int precioPorLitro() const;
        void expender(int cant);
        
    private:
        int ltsDisponibles;
        int precioXLitro;
};

#endif
