#Funcion auxiliar para devolver el valor de la Carta Alta para su uso en la formula de chen

valorCartaAlta<-function(num)
{
if(num==14)
{
return(10)
}
if(num==13)
{
return(8)
}
if(num==12)
{
return(7)
}
if(num==11)
{
return(6)
}
else
{
a=num/2
return(a)
}
}