#Funcion para obtener el valor asociado a una mano del dataframe Triple Probabilidad
leerTriple<-function(mano,datos)
{
  valores<-c(0,0,0)
if(mano[1,2]<mano[2,2])
{
	Num1<-mano[1,1]
	Num2<-mano[2,1]
	Palo1<-mano[1,2]
	Palo2<-mano[2,2]
}
if(mano[1,2]>mano[2,2])
{
	Num2<-mano[1,1]
	Num1<-mano[2,1]
	Palo2<-mano[1,2]
	Palo1<-mano[2,2]
}
if(mano[1,2]==mano[2,2])
{
  Palo1<-mano[1,2]
  Palo2<-mano[2,2]
	if(mano[1,1]>mano[2,1])
	{
	  Num2<-mano[1,1]
	  Num1<-mano[2,1]
	}
	else
	{
	  Num1<-mano[1,1]
	  Num2<-mano[2,1]
	}
}

n_filas=nrow(datos)
for(i in 1:n_filas)
{
	if(Num1==datos[i,1])
	{
		if(Palo1==datos[i,2])
		{
			if(Num2==datos[i,3])
			{
				if(Palo2==datos[i,4])
				{
					
					valores[1]<-datos[i,5]
					valores[2]<-datos[i,6]
					valores[3]<-datos[i,7]
				}
			}
		}
	}
}
	
return(valores)
}