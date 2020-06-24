
descarteTres<-function(cartas,mazo_triple)
{
  g<-nrow(mazo_triple)
    for(i in 1:g)
    {
      if(cartas[1]==mazo_triple[i,1]&&cartas[2]==mazo_triple[i,2])
      {
        mazo_triple[i,]=NA
      }
      else if(cartas[1]==mazo_triple[i,3]&&cartas[2]==mazo_triple[i,4])
      {
        mazo_triple[i,]=NA
      }
      else if(cartas[1]==mazo_triple[i,5]&&cartas[2]==mazo_triple[i,6])
      {
        mazo_triple[i,]=NA
      }
    }
  
  mazo_triple<-na.omit(mazo_triple)
  return(mazo_triple)
}