#test de la funcion preflopini
test_preflopini<-function(mn1,mp1,mn2,mp2){
mano<-fijarMano(mn1,mp1,mn2,mp2)
mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
mazo<-descarteCartas(mano,mazo)
pesos<-cargaPesos()
triple<-cargaTriple()
pesos<-descartePesosMano(mano,mazo,pesos)
triple<-descarteTripleMano(mano,mazo,triple)
write.csv(mazo,"deck.csv",row.names = FALSE)
write.csv(pesos, "data.csv",row.names = TRUE)
write.csv(triple,"triple.csv",row.names = TRUE)
write.csv(mano, "mano.csv",row.names = FALSE)
salida<-calculaProbPreflopIni(mano,mazo)
return(salida)
}

#test de la funcion preflop
test_preflop<-function(mn1,mp1,mn2,mp2,a){ #*mni=numero de la carta i; mpi=palo de la carta i; a=accion (0= pass, 1= ver, 2= subir)
mano<-fijarMano(mn1,mp1,mn2,mp2)
mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
mazo<-descarteCartas(mano,mazo)
pesos<-cargaPesos()
triple<-cargaTriple()
pesos<-descartePesosMano(mano,mazo,pesos)
triple<-descarteTripleMano(mano,mazo,triple)
pesos<-actualizaPesos(a,pesos,triple)
triple<-calculoProbabilidadAccion(mesa,mazo,triple,1)
write.csv(mazo,"deck.csv",row.names = FALSE)
write.csv(pesos, "data.csv",row.names = TRUE)
write.csv(triple,"triple.csv",row.names = TRUE)
write.csv(mano, "mano.csv",row.names = FALSE)
salida<-calculaProbPreflop(mano,mazo,a)
return(salida)
}

#test de la funcion preflopact
test_preflopact<-function(a){
pesos<-cargaPesos()
triple<-cargaTriple()
mano<-read.csv("mano.csv",header=TRUE, sep=",", row.names=NULL)
mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
salida<-calculaProbPreflop(mano,mazo,a)
triple<-calculoProbabilidadAccion(mesa,mazo, triple,1)
pesos<-actualizaPesos(a,pesos,triple)
write.csv(pesos, "data.csv",row.names = TRUE)
write.csv(triple,"triple.csv",row.names = TRUE)
return(salida)
}

#test de la funcion flopini
test_flopini<-function(mn1,mp1,mn2,mp2,mn3,mp3,aa,ao){
mano<-read.csv("mano.csv",header=TRUE, sep=",", row.names=NULL)
mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
pesos<-cargaPesos()
triple<-cargaTriple()
mesa<-fijarMesaFlop(mn1,mp1,mn2,mp2,mn3,mp3)
mazo<-descarteCartas(mesa,mazo)
pesos<-descartePesosFlop(mesa,mazo,pesos)
triple<-descarteTripleFlop(mesa,mazo,triple)
pesos<-actualizaPesos(1,pesos,triple)
salida<-calculaProbFlop(mano,mesa,mazo,pesos,aa,ao,1)
triple<-calculoProbabilidadAccion(mesa,mazo,triple,2)
write.csv(mazo,"deck.csv",row.names = FALSE)
write.csv(pesos, "data.csv",row.names = TRUE)
write.csv(triple,"triple.csv",row.names = TRUE)
write.csv(mesa, "mesa.csv",row.names = FALSE)
return(salida)
}

#test de la funcion flop
test_flop<-function(mn1,mp1,mn2,mp2,mn3,mp3,a, aa,ao){
mano<-read.csv("mano.csv",header=TRUE, sep=",", row.names=NULL)
mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
pesos<-cargaPesos()
triple<-cargaTriple()
mesa<-fijarMesaFlop(mn1,mp1,mn2,mp2,mn3,mp3)
mazo<-descarteCartas(mesa,mazo)
pesos<-descartePesosFlop(mesa,mazo,pesos)
triple<-descarteTripleFlop(mesa,mazo,triple)
pesos<-actualizaPesos(a,pesos,triple)
salida<-calculaProbFlop(mano,mesa,mazo,pesos,aa,ao,a)
triple<-calculoProbabilidadAccion(mesa,mazo,triple,2)
write.csv(mazo,"deck.csv",row.names = FALSE)
write.csv(pesos, "data.csv",row.names = TRUE)
write.csv(triple,"triple.csv",row.names = TRUE)
write.csv(mesa, "mesa.csv",row.names = FALSE)
return(salida)
}

#test de la funcion flopact
test_flopact<-function(a,aa,ao){
  mano<-read.csv("mano.csv",header=TRUE, sep=",", row.names=NULL)
  mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
  mesa<-read.csv("mesa.csv",header=TRUE, sep=",", row.names=NULL)
  pesos<-cargaPesos()
  triple<-cargaTriple()
  pesos<-actualizaPesos(a,pesos,triple)
  salida<-calculaProbFlop(mano,mesa,mazo,pesos,aa,ao,a)
  write.csv(pesos, "data.csv",row.names = TRUE)
  return(salida)
}

#test de la funcion turnini
test_turnini<-function(mn,mp,aa,ao){
  mano<-read.csv("mano.csv",header=TRUE, sep=",", row.names=NULL)
  mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
  mesa<-read.csv("mesa.csv",header=TRUE, sep=",", row.names=NULL)
  pesos<-cargaPesos()
  triple<-cargaTriple()
  mesa<-fijarMesaPostflop(mesa,mn,mp)
  mazo<-descarteCartas(mesa,mazo)
  carta<-mesa[4,]
  pesos<-descartePesosCarta(carta,mazo,pesos)
  triple<-descarteTripleCarta(carta,mazo,triple)
  pesos<-actualizaPesos(1,pesos,triple)
  salida<-calculaProbFlop(mano,mesa,mazo,pesos,aa,ao,1)
  triple<-calculoProbabilidadAccion(mesa,mazo,triple,3)
  write.csv(mazo,"deck.csv",row.names = FALSE)
  write.csv(pesos, "data.csv",row.names = TRUE)
  write.csv(triple,"triple.csv",row.names = TRUE)
  write.csv(mesa, "mesa.csv",row.names = FALSE)
  return(salida)
}

#test de la funcion turn
test_turn<-function(mn,mp,aa,ao,a){
  mano<-read.csv("mano.csv",header=TRUE, sep=",", row.names=NULL)
  mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
  mesa<-read.csv("mesa.csv",header=TRUE, sep=",", row.names=NULL)
  pesos<-cargaPesos()
  triple<-cargaTriple()
  mesa<-fijarMesaPostflop(mesa,mn,mp)
  mazo<-descarteCartas(mesa,mazo)
  carta<-mesa[4,]
  pesos<-descartePesosCarta(carta,mazo,pesos)
  triple<-descarteTripleCarta(carta,mazo,triple)
  pesos<-actualizaPesos(a,pesos,triple)
  salida<-calculaProbFlop(mano,mesa,mazo,pesos,aa,ao,a)
  triple<-calculoProbabilidadAccion(mesa,mazo,triple,3)
  write.csv(mazo,"deck.csv",row.names = FALSE)
  write.csv(pesos, "data.csv",row.names = TRUE)
  write.csv(triple,"triple.csv",row.names = TRUE)
  write.csv(mesa, "mesa.csv",row.names = FALSE)
  return(salida)
}

#test de la funcion riverini
test_riverini<-function(mn,mp){
  mano<-read.csv("mano.csv",header=TRUE, sep=",", row.names=NULL)
  mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
  mesa<-read.csv("mesa.csv",header=TRUE, sep=",", row.names=NULL)
  pesos<-cargaPesos()
  triple<-cargaTriple()
  mesa<-fijarMesaPostflop(mesa,mn,mp)
  mazo<-descarteCartas(mesa,mazo)
  carta<-mesa[5,]
  pesos<-descartePesosCarta(carta,mazo,pesos)
  triple<-descarteTripleCarta(carta,mazo,triple)
  pesos<-actualizaPesos(1,pesos,triple)
  salida<-calculaProbRiver(mano,mesa,mazo,pesos,1)
  triple<-calculoProbabilidadAccion(mesa,mazo,triple,4)
  write.csv(mazo,"deck.csv",row.names = FALSE)
  write.csv(pesos, "data.csv",row.names = TRUE)
  write.csv(triple,"triple.csv",row.names = TRUE)
  write.csv(mesa, "mesa.csv",row.names = FALSE)
  return(salida)
}

#test de la funcion river
test_river<-function(mn,mp,a){
  mano<-read.csv("mano.csv",header=TRUE, sep=",", row.names=NULL)
  mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
  mesa<-read.csv("mesa.csv",header=TRUE, sep=",", row.names=NULL)
  pesos<-cargaPesos()
  triple<-cargaTriple()
  mesa<-fijarMesaPostflop(mesa,mn,mp)
  mazo<-descarteCartas(mesa,mazo)
  carta<-mesa[5,]
  pesos<-descartePesosCarta(carta,mazo,pesos)
  triple<-descarteTripleCarta(carta,mazo,triple)
  pesos<-actualizaPesos(a,pesos,triple)
  salida<-calculaProbRiver(mano,mesa,mazo,pesos,a)
  triple<-calculoProbabilidadAccion(mesa,mazo,triple,4)
  write.csv(mazo,"deck.csv",row.names = FALSE)
  write.csv(pesos, "data.csv",row.names = TRUE)
  write.csv(triple,"triple.csv",row.names = TRUE)
  write.csv(mesa, "mesa.csv",row.names = FALSE)
  return(salida)
}


#test de la funcion riveract
test_riveract<-function(a){
  mano<-read.csv("mano.csv",header=TRUE, sep=",", row.names=NULL)
  mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
  mesa<-read.csv("mesa.csv",header=TRUE, sep=",", row.names=NULL)
  pesos<-cargaPesos()
  triple<-cargaTriple()
  pesos<-actualizaPesos(a,pesos,triple)
  salida<-calculaProbRiver(mano,mesa,mazo,pesos,a)
  write.csv(pesos, "data.csv",row.names = TRUE)
  return(salida)
}


#test de la funcion reset
test_reset<-function(){
  mazo<-crearMazo()
  pesos<-read.csv("data_ini.csv",header=TRUE,row.names=1)
  colnames(pesos)<-c(11:14,21:24,31:34,41:44)
  triple<-read.csv("triple_ini.csv",header=TRUE)
  colnames(triple)<-c("Num1","Palo1","Num2","Palo2","Pasar","Ver","Subir")
  write.csv(mazo,"deck.csv",row.names = FALSE)
  write.csv(pesos, "data.csv",row.names = TRUE)
  write.csv(triple,"triple.csv",row.names = TRUE)
  
}