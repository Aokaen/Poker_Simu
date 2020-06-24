
#Funcion de calculo de probabilidad triple
probabilidadTriple<-function(FM,Pot,OddMano,OddBote)
{
p=0
v=0
s=0

s=FM[3]+(1-FM[3])*Pot[1]+(OddMano-OddBote)
p=FM[1]+(1-FM[1])*Pot[2]+(OddBote-OddMamo)
v=1-(s+p)
if(p>v)
{
if(p>s)
{
gk=rnorm(1) #cambiar con PRNG
if(gk>=p)
{
v=v+p/2
s=s+p/2
p=0
}
}
}
prob=c(p,v,s)
return(prob)
}
