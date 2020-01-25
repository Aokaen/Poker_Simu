#funcion para determinar que tipo de jugada es la mano y devolver un valor acorde con esa jugada


calcularJugada<-function(jugada)
{
#Basado en la función handeval del paquete holdem y sus funciones usadas
Num<-jugada[,1]
Palo<-jugada[,2]
a1<-strflsh1(Num,Palo)
if(a1>0.5)
{ 
	if(a1==14)
	{
	return(9) #Escalera Real
	}
	else
	{
	return (8) #Escalera Color
	}
}
a1 <- four1(Num)
if(a1>0.5) 
{
return(7) # Poker
}
a1 <- full1(Num)
if(a1>0.5)
{
 return(6) #Full House
}
a1 <- flush1(Num,Palo)
if(a1>0.5)
{
 return(5) #Color
}
a1 <- straight1(Num) 
if(a1>0.5)
{
 return(4) #Escalera
}
a1 <- trip1(Num)
if(a1>0.5) 
{
return(3) #Trio
}
a1 <- twopair1(Num)
if(a1>0.5) 
{
return(2)#Doble Pareja
}
a1 <- onepair1(Num)
if(a1>0.5) 
{
return(1)#Pareja
}
return(0)
}

