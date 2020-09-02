%% TS%,ORB%,DRB%,AST%,STL%,BLK% 
%%

[Aj1,bj1] = metrica1(); 
[Aj2,bj2] = metrica2(); 
[Aj3,bj3] = metrica3();  
[Aj4,bj4] = metricalineal();
%%

[MSEj1CV,CMLj1CV] = validationCV(Aj1,bj1);
[MSEj1T,CMLj1T] = validationTemp(Aj1,bj1);

[MSEj2CV,CMLj2CV] = validationCV(Aj2,bj2);
[MSEj2T,CMLj2T] = validationTemp(Aj2,bj2);

[MSEj3CV,CMLj3CV] = validationCV(Aj3,bj3);
[MSEj3T,CMLj3T] = validationTemp(Aj3,bj3);

[MSEj4CV,CMLj4CV] = validationCV(Aj4,bj4);
[MSEj4T,CMLj4T] = validationTemp(Aj4,bj4);

