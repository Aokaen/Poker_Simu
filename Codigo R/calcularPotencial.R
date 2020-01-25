#Funcion para el calculo del potencial de la mano

calcularPotencial<-function(mano,Mesa,mazo,pesos)
{
VPT<-c(0,0,0)
VP<-matrix(0,nrow=3, ncol=3)
x=-1
jugada=ordenarCartas(mano,mesa)
valorjugador=calcularJugada(jugada)
combinaciones<-combinaMazo(mazo)
n_manos<-nrow(combinaciones)
for(i in 1:n_manos)
{
	mano_op<-fijarMano(combinaciones[i,1],combinaciones[i,2],combinaciones[i,3],combinaciones[i,4])
	jugada_op=ordenarCartas(mano_op,Mesa)
	valor_op<-calcularJugada(jugada_op)
	peso_mano<-Leer(mano_op,pesos)
	mazoaux<-descarteCartas(mano_op,mazo)
	n_mazoaux<-nrow(mazoaux)
	if(valor_op>valorjugador)
	{
		x=1
	}
	if(valor_op==valorjugador)
	{
		x=2
	}
	if(valor_op<valorjugador)
	{
		x=3
	}
	VPT[x]<-VPT[x]+peso_mano

	for(j in 1:n_mazoaux)
	{
	mesaaux<-rbind(mesa,mazoaux[j,])
	jugada_aux<-ordenarCartas(mano,mesaaux)
	jugada_op_aux<-ordenarCartas(mano_op,mesaaux)
	valorjugador_aux<-calcularJugada(jugada_aux)
	valor_op_aux<-calcularJugada(jugada_op_aux)

	if(valor_op_aux>valorjugador_aux)
	{
		VP[x,1]<-VP[x,1]+peso_mano
	}
	if(valor_op_aux==valorjugador_aux)
	{
		VP[x,2]<-VP[x,2]+peso_mano
	}
	if(valor_op_aux<valorjugador_aux)
	{
		VP[x,3]<-VP[x,3]+peso_mano
	}
	}
	
}
PotPositivo<-VP[1,2]/VPT[1]
PotNegativo<-VP[3,1]/VPT[3]
Pot<-c(PotPositivo,PotNegativo)

return(Pot)
}
