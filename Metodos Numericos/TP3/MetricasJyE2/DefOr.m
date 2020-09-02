%% TS%,ORB%,DRB%,AST%,STL%,BLK% 
%%

[Aj1,bj1] = jugadores(1,1,1,1,1,1); % lineal
[Aj2,bj2] = jugadores(1,2,1,2,2,1);  
[Aj3,bj3] = jugadores(0.5,1,2,1,2,2);  
[Aj4,bj4] = jugadores(2,1,1,2,1,0.5); 
[Aj5,bj5] = jugadores(2,2,1,2,2,0.5); 

%%

[MSEj1CV,CMLj1CV] = validationCV(Aj1,bj1);
[MSEj1T,CMLj1T] = validationTemp(Aj1,bj1);

[MSEj2CV,CMLj2CV] = validationCV(Aj2,bj2);
[MSEj2T,CMLj2T] = validationTemp(Aj2,bj2);

[MSEj3CV,CMLj3CV] = validationCV(Aj3,bj3);
[MSEj3T,CMLj3T] = validationTemp(Aj3,bj3);

[MSEj4CV,CMLj4CV] = validationCV(Aj4,bj4);
[MSEj4T,CMLj4T] = validationTemp(Aj4,bj4);

[MSEj5CV,CMLj5CV] = validationCV(Aj5,bj5);
[MSEj5T,CMLj5T] = validationTemp(Aj5,bj5);
