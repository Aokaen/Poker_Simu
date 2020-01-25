#Funcion de calculo de probabilidades de River

calculaProbRiver<-function(mano,mesa,mazo,pesos)
{
inferiores=0
iguales=0
superiores=0
jugada=ordenarCartas(mano,mesa)
valorjugador=calcularJugada(jugada)
combinaciones<-combinaMazo(mazo)
n_manos<-nrow(combinaciones)
for(i in 1:n_manos)
{
	mano_op<-fijarMano(combinaciones[i,1],combinaciones[i,2],combinaciones[i,3],combinaciones[i,4])
	jugada_op=ordenarCartas(mano_op,mesa)
	valor_op<-calcularJugada(jugada_op)
	peso_mano<-Leer(mano_op,pesos)
	if(valor_op>valorjugador)
	{
		superiores=superiores+peso_mano
	}
	if(valor_op==valorjugador)
	{
		iguales=iguales+peso_mano
	}
	if(valor_op<valorjugador)
	{
		inferiores=inferiores+peso_mano
	}

}
NT=(superiores+iguales+inferiores)
s=(inferiores/NT)
v=(iguales/NT)
p=(superiores/NT)

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

prob<-c(p,v,s)

return(prob)
}