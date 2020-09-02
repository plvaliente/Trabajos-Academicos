%% 3P,2P,FT%,TRB,STL,TOV
%%
[Ae0,be0] = equipos(1,1,1,1,1,1); %lineal
[Ae2,be2] = equipos(0.5,1,1,2,2,1); %prioridad posesion 2
[Ae1,be1] = equipos(2,2,2,1,1,0.5); %prioridad  overall 1
%[Ae4,be4] = equipos(2,2,2,0.5,0.5,2); %prioridad perdidas
%[Ae5,be5] = equipos(1,1,2,2,2,1); %prioridad posesion y puntos
%%

[lc0,eCV0,x0CV] = validationCV(Ae0,be0);
[lt0,eT0,x0T] = validationTemp(Ae0,be0);

[lc2,eCV2,x2CV] = validationCV(Ae2,be2);
[lt2,eT2,x2T] = validationTemp(Ae2,be2);

[lc1,eCV1,x1CV] = validationCV(Ae1,be1);
[lt1,eT1,x1T] = validationTemp(Ae1,be1);
