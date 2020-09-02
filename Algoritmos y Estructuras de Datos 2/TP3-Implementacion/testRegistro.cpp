// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests

#include <algorithm>
#include "mini_test.h"
#include "aed2.h"
#include "Modulos.h"

using namespace modulos;

void test() {
    Registro reg1 = Registro();                       
    campo cmp1 = "aa";
    Dato dat1 = Dato(0);
    reg1.Definir(cmp1, dat1);                           //reg1= {("aa",0)}
    Conj<campo> cnj = reg1.Campos();                    //cnj = {"aa"}
    Conj<campo>::Iterador itcnj = cnj.CrearIt();
    
    ASSERT_EQ(itcnj.Siguiente() == cmp1, true);         //test Campos()
    
    Registro reg2, reg3, reg4;                       
    campo cmp2 = "bb";
    Dato dat2 = Dato(1);
    reg2.Definir(cmp1, dat1);                           //reg2= {("aa",0)}
    reg3.Definir(cmp1, dat2);                           //reg3= {("aa",1)}
    reg4.Definir(cmp2, dat1);                           //reg4= {("bb",0)}
    
    ASSERT_EQ(reg1.Borrable(reg2), true);
    ASSERT_EQ(reg1.Borrable(reg3), false);
    ASSERT_EQ(reg1.Borrable(reg4), false);              //test Borrable()
    
    campo cmp3 = "cc";
    Dato dat3 = Dato("cc");
    reg1.Definir(cmp2,dat2);                            //reg1= {("aa",0),("bb",1)}
    reg4.Definir(cmp3,dat3);                            //reg4= {("bb",0),("cc","cc")}
    Registro AgCmp = reg1.AgregarCampos(reg4);          //AgCmp={("aa",0),("bb",1),("cc","cc")} ?? 
    
    ASSERT_EQ(AgCmp.Definido(cmp1), true);
    ASSERT_EQ(AgCmp.Definido(cmp2), true);
    ASSERT_EQ(AgCmp.Definido(cmp3), true);
    ASSERT_EQ(AgCmp.Significado(cmp1) == dat1, true);
    ASSERT_EQ(AgCmp.Significado(cmp2) == dat2, true);   
    ASSERT_EQ(AgCmp.Significado(cmp3) == dat3, true);   //test AgregarCampos()
    
    Registro reg5;
    reg5.Definir(cmp2,dat1);                            //reg5= {("bb",0)}
    ASSERT_EQ(reg5.Definido(cmp2), true);
    Registro CopCmp = reg5.CopiarCampos(cnj, AgCmp);    //CopCmp = {("bb",0),("aa",0)}  ??
    
    ASSERT_EQ(CopCmp.Definido(cmp1), true);
    ASSERT_EQ(CopCmp.Definido(cmp2), true);
    ASSERT_EQ(CopCmp.Significado(cmp1) == dat1, true);
    ASSERT_EQ(CopCmp.Significado(cmp2) == dat1, true);   //test CopiarCampos()
    
    
    // Me da paja hacer test de las demas funciones.
}
  
int main()
{
  RUN_TEST( test );
  return 0;
}
