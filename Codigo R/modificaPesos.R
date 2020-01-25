#Modificar datos del framepesos "pesos"

modificaPesos<-function(mano,pesos,valor)
{
if(mano[1,1]<mano[2,1])
{
Num<-NumtoChar(mano[2,1],mano[1,1])
Palo<-PalotoChar(mano[2,2],mano[1,2])
}
if(mano[1,1]>mano[2,1])
{
Num<-NumtoChar(mano[1,1],mano[2,1])
Palo<-PalotoChar(mano[1,2],mano[2,2])
}

if(mano[1,1]==mano[2,1])
{
Num<-NumtoChar(mano[1,1],mano[2,1])
	if(mano[1,2]>mano[2,2])
	{
	Palo<-PalotoChar(mano[2,2],mano[1,2])
	}
	else
	{
	Palo<-PalotoChar(mano[1,2],mano[2,2])
	}
}

pesos[Num,Palo]<-valor
return(pesos)
}

