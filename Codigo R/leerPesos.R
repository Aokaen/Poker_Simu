#Leer datos del framedata pesos

leerPesos<-function(mano,pesos)
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
value<-pesos[Num,Palo]
return(value)
}
