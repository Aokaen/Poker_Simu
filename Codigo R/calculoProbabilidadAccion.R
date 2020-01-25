#Funcion para calcular cada probabilidad de accion del oponente

calculoProbabilidadAccion<-function(mesa,mazo,triple)
{
inferior=0
superior=0
igual=0
combinaciones<-combinaMazo(mazo)
n_manos<-nrow(combinaciones)
for(i in 1:n_manos)
{
	valor<-c(0,0,0)
	mano_op<-fijarMano(combinaciones[i,1],combinaciones[i,2],combinaciones[i,3],combinaciones[i,4])
	jugada_op=ordenarCartas(mano_op,mesa)
	valor_op<-calcularJugada(jugada_op)
	mazoaux<-descarteCartas(mano_op,mazo)
	comb_aux<-combinaMazo(mazoaux)
	n_manos_aux<-nrow(comb_aux)
	for(j in 1:n_manos_aux)
	{
		mano_aux<-fijarMano(comb_aux[j,1],comb_aux[j,2],comb_aux[j,3],comb_aux[j,4])
		jugada_aux<-ordenarCartas(mano_aux,mesa)
		valor_aux<-calcularJugada(jugada_aux)
		if(valor_op>valor_aux)
		{
			superior=superior+1
		}
		if(valor_op==valor_aux)
		{
			igual=igual+1
		}
		if(valor_op<valor_aux)
		{
			inferior=inferior+1
		}
	}
	total=superior+igual+inferior
	valor[1]=superior/total #pasar
	valor[2]=igual/total#ver
	valor[3]=inferior/total#subir
	triple<-modificaTriple(mano_op,triple,valor)


}
	
return (triple)
}