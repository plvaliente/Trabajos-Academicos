#ifndef automovilH
#define automovilH

class Automovil {

    public:
        Automovil();
        Automovil(int cap, int litros);
        int capacidadDelTanque() const;
        int litrosEnElTanque() const;
        void llenalo();
        
    private:
        int capTanque;
        int litrosEnTanque;
};

#endif
