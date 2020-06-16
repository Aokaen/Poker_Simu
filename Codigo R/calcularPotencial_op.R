calcularPotencial_op<-function(mano,mesa,mazo,pesos)
{
  VPT<-c(0,0,0)
  VP<-matrix(0,nrow=3, ncol=3)
  x=-1
  mazo_triple<-read.csv("mazo_triple.csv",header=TRUE, sep=",", row.names=NULL)
  mazo_triple<-descarteTres(mano[1,],mazo_triple)
  mazo_triple<-descarteTres(mano[2,],mazo_triple)
  mazo_triple<-descarteTres(mesa[1,],mazo_triple)
  mazo_triple<-descarteTres(mesa[2,],mazo_triple)
  mazo_triple<-descarteTres(mesa[3,],mazo_triple)
  if(nrow(mesa)==4)
  {
    mazo_triple<-descarteTres(mesa[4,],mazo_triple)
  }
  jugada=ordenarCartas(mano,mesa)
  valorjugador=calcularJugada(jugada)
  n_manos<-nrow(mazo_triple)
  for(i in 1:n_manos)
  {
    mano_op<-fijarMano(mazo_triple[i,1],mazo_triple[i,2],mazo_triple[i,3],mazo_triple[i,4])
    jugada_op=ordenarCartas(mano_op,mesa)
    valor_op<-calcularJugada(jugada_op)
    peso_mano<-leerPesos(mano_op,pesos)
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
    mesaaux<-rbind(mesa,c(as.numeric(mazo_triple[i,5]),as.numeric(mazo_triple[i,6])))
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
  if(VPT[1]==0)
  {
    PotPositivo=0
  }else{
    PotPositivo<-VP[1,2]/VPT[1]
  }
  if(VPT[3]==0)
  {
    PotNegativo=0
  }else{
    PotNegativo<-VP[3,1]/VPT[3]
  }
  
  Pot<-c(PotPositivo,PotNegativo)
  
  return(Pot)
}
