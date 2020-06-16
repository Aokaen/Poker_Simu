combinaMazosPot<-function(mazo,pesos)
{
  combina<-combinaMazo(mazo)
  n=nrow(combina)
  mano_salvada=c(0,0,0,0)
  tot=0
  media=0
  for(i in 1:91)
  {
    for(j in 1:16)
    {
      media=media+pesos[i,j]
      if(pesos[i,j]!=0)
      {
        tot=tot+1
      }
    }
  }
  media_f=media/tot
  for(i in 1:n)
  {
    mano_op<-fijarMano(combina[i,1],combina[i,2],combina[i,3],combina[i,4])
    peso<-leerPesos(mano_op,pesos)
    if(peso>media_f)
    {
      mano_salvada=rbind(mano_salvada,c(combina[i,1],combina[i,2],combina[i,3],combina[i,4]))
    }
    
  }
  mano_salvada=mano_salvada[-1,]
  return(mano_salvada)
}