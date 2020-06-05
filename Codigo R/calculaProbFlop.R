calculaProbFlop<-function(mano,mesa,mazo,pesos,aa,ao,accion)
{
  FM<-calcularFuerzaMano(mano,mesa,mazo,pesos) #(inf,igual,sup)
  POT<-calcularPotencial(mano,mesa,mazo,pesos) #(Positivo,negativo)
  OdMano<-calculoOddMano(mano,mesa,mazo)
  OdBote<-calculoOddsBote(aa,ao)
  s=FM[3]+(1-FM[3])*POT[1]*(OdMano)+OdBote
  p=FM[1]+(1-FM[1])*POT[2]*OdMano-OdBote
  v=1-(s+p)
  salida=c(p,v,s)
  orden<-ordenarCartas(mano,mesa)
  valorjugada<-calcularJugada(orden)
  salida=ajusteBayes(salida, accion, 2,valorjugada)
  return(salida)
}