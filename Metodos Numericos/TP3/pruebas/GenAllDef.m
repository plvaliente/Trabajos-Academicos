function C = GenAllDef()
	fileID = fopen('MatrizAllDef','r');
	sizeA = [9 Inf];
	C = fscanf(fileID,'%f %f %f %f %f %f %f %f %f', sizeA);
	C = C';
	%RB^2
	C(:,2) = C(:,2).^2;
	%sqrt(TOV)
	C(:,5) = sqrt(C(:,5));
	%FTperc^2
	C(:,7) = C(:,7).^2;
	%sqrt(log(PF))
	C(:,9) = sqrt(log(C(:,9)));     
	fclose('all');
   
