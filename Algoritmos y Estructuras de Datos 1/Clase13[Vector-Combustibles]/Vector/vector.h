#ifndef vectorH
#define vectorH

class Vector {

    public:
        Vector();
        Vector(float a, float o);
        bool igualX(const Vector v);
        bool igualY(const Vector v);
        float modulo() const;
        float prodEscalar(const Vector v) const;
        void resta(const Vector v);

    private:
        int abscisa;
        int ordenada;
};

#endif

