#Funcion para actualizar la tabla de pesos con la acción del oponente

actualizaPesos<-function(accion,pesos,triple)
{
  columna<-0
if(accion==0)
{
	columna=1
}
if(accion==1)
{
	columna=2
}
if(accion==2)
{
	columna=3
}
n_manos=nrow(triple)
for(i in 1:n_manos)
{
	mano<-fijarMano(triple[i,1],triple[i,2],triple[i,3],triple[i,4])
	valor_pesos<-leerPesos(mano,pesos)
	triple_prob<-leerTriple(mano,triple)
	valor_nuevo<-valor_pesos*triple_prob[columna]
	pesos<-modificaPesos(mano,pesos,valor_nuevo)

}

return(pesos)
}