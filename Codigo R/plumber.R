# plumber.R

#* Funcion para el preflop siendo jugador inicial
#* @param mn1 numero de la carta 1
#* @param mp1 palo de la carta 1
#* @param mn2 numero de la carta 2
#* @param mp2 palo de la carta 2
#* @get /preflopini
function(mn1,mp1,mn2,mp2){
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

#* Funcion para el preflop no siendo jugador inicial
#* @param mn1 numero de la carta 1
#* @param mp1 palo de la carta 1
#* @param mn2 numero de la carta 2
#* @param mp2 palo de la carta 2
#* @param a accion
#* @get /preflop
function(mn1,mp1,mn2,mp2,a){ #*mni=numero de la carta i; mpi=palo de la carta i; a=accion (0= pass, 1= ver, 2= subir)
mano<-fijarMano(mn1,mp1,mn2,mp2)
a<-strtoi(a)
mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
mazo<-descarteCartas(mano,mazo)
pesos<-cargaPesos()
triple<-cargaTriple()
pesos<-descartePesosMano(mano,mazo,pesos)
triple<-descarteTripleMano(mano,mazo,triple)
salida<-calculaProbPreflop(mano,mazo,a)
triple<-calculoProbabilidadAccion(0,mazo,triple,1)
pesos<-actualizaPesos_op(a,pesos,triple)
write.csv(mazo,"deck.csv",row.names = FALSE)
write.csv(pesos, "data.csv",row.names = TRUE)
write.csv(triple,"triple.csv",row.names = TRUE)
write.csv(mano, "mano.csv",row.names = FALSE)
return(salida)
}

#* Funcion para actualizacion de pesos en preflop
#* @param a accion
#* @get /preflopact
function(a){
  a<-strtoi(a)
  pesos<-cargaPesos()
  triple<-cargaTriple()
  mano<-read.csv("mano.csv",header=TRUE, sep=",", row.names=NULL)
  mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
  salida<-calculaProbPreflop(mano,mazo,a)
  triple<-calculoProbabilidadAccion(mesa,mazo, triple,1)
  pesos<-actualizaPesos_op(a,pesos,triple)
  write.csv(pesos, "data.csv",row.names = TRUE)
  write.csv(triple,"triple.csv",row.names = TRUE)
  
  return(salida)
}

#*Funcion para el flop siendo mano inicial
#* @param mn1 numero de la carta 1
#* @param mp1 palo de la carta 1
#* @param mn2 numero de la carta 2
#* @param mp2 palo de la carta 2
#* @param mn3 numero de la carta 3
#* @param mp3 palo de la carta 3
#* @param aa apuesta del jugador
#* @param ao apuesta del adversario
#* @get /flopini
function(mn1,mp1,mn2,mp2,mn3,mp3,aa,ao){
mano<-read.csv("mano.csv",header=TRUE, sep=",", row.names=NULL)
mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
pesos<-cargaPesos()
triple<-cargaTriple()
aa<-strtoi(aa)
ao<-strtoi(ao)
mesa<-fijarMesaFlop(mn1,mp1,mn2,mp2,mn3,mp3)
pesos<-descartePesosFlop(mesa,mazo,pesos)
triple<-descarteTripleFlop(mesa,mazo,triple)
mazo<-descarteCartas(mesa,mazo)
triple<-calculoProbabilidadAccion(mesa,mazo,triple,2)
pesos<-actualizaPesos_op(1,pesos,triple)
salida<-calculaProbFlop(mano,mesa,mazo,pesos,aa,ao,1)
write.csv(mazo,"deck.csv",row.names = FALSE)
write.csv(pesos, "data.csv",row.names = TRUE)
write.csv(triple,"triple.csv",row.names = TRUE)
write.csv(mesa, "mesa.csv",row.names = FALSE)

return(salida)
}

#* Funcion para el flop no siendo mano inicial
#* @param mn1 numero de la carta 1
#* @param mp1 palo de la carta 1
#* @param mn2 numero de la carta 2
#* @param mp2 palo de la carta 2
#* @param mn3 numero de la carta 3
#* @param mp3 palo de la carta 3
#* @param a accion
#* @param aa apuesta del jugador
#* @param ao apuesta del adversario
#* @get /flop
function(mn1,mp1,mn2,mp2,mn3,mp3,a, aa,ao){
mano<-read.csv("mano.csv",header=TRUE, sep=",", row.names=NULL)
mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
pesos<-cargaPesos()
triple<-cargaTriple()
aa<-strtoi(aa)
ao<-strtoi(ao)
a<-strtoi(a)
mesa<-fijarMesaFlop(mn1,mp1,mn2,mp2,mn3,mp3)
pesos<-descartePesosFlop(mesa,mazo,pesos)
triple<-descarteTripleFlop(mesa,mazo,triple)
mazo<-descarteCartas(mesa,mazo)
triple<-calculoProbabilidadAccion(mesa,mazo,triple,2)
pesos<-actualizaPesos_op(a,pesos,triple)
salida<-calculaProbFlop(mano,mesa,mazo,pesos,aa,ao,a)
write.csv(mazo,"deck.csv",row.names = FALSE)
write.csv(pesos, "data.csv",row.names = TRUE)
write.csv(triple,"triple.csv",row.names = TRUE)
write.csv(mesa, "mesa.csv",row.names = FALSE)

return(salida)
}

#* Funcion para actualizar pesos durante el flop o turn
#* @param a accion
#* @param aa apuesta del jugador
#* @param ao apuesta del adversario
#* @get /flopact
function(a,aa,ao){
    mano<-read.csv("mano.csv",header=TRUE, sep=",", row.names=NULL)
  mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
  mesa<-read.csv("mesa.csv",header=TRUE, sep=",", row.names=NULL)
  aa<-strtoi(aa)
  ao<-strtoi(ao)
  a<-strtoi(a)
  pesos<-cargaPesos()
  triple<-cargaTriple()
  pesos<-actualizaPesos_op(a,pesos,triple)
  salida<-calculaProbFlop(mano,mesa,mazo,pesos,aa,ao,a)
  write.csv(pesos, "data.csv",row.names = TRUE)
  
  return(salida)
}

#*Funcion para el turn siendo mano inicial
#* @param mn numero de la carta 
#* @param mp palo de la carta 
#* @param aa apuesta del jugador
#* @param ao apuesta del adversario
#* @get /turnini
function(mn,mp,aa,ao){
   mano<-read.csv("mano.csv",header=TRUE, sep=",", row.names=NULL)
  mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
  mesa<-read.csv("mesa.csv",header=TRUE, sep=",", row.names=NULL)
  pesos<-cargaPesos()
  triple<-cargaTriple()
  mesa<-fijarMesaPostflop(mesa,mn,mp)
  mazo<-descarteCartas(mesa,mazo)
  aa<-strtoi(aa)
  ao<-strtoi(ao)
  carta<-mesa[4,]
  pesos<-descartePesosCarta(carta,mazo,pesos)
  triple<-descarteTripleCarta(carta,mazo,triple)
  triple<-calculoProbabilidadAccion(mesa,mazo,triple,3)
  pesos<-actualizaPesos_op(1,pesos,triple)
  salida<-calculaProbFlop(mano,mesa,mazo,pesos,aa,ao,1)
  write.csv(mazo,"deck.csv",row.names = FALSE)
  write.csv(pesos, "data.csv",row.names = TRUE)
  write.csv(triple,"triple.csv",row.names = TRUE)
  write.csv(mesa, "mesa.csv",row.names = FALSE)
  
  return(salida)
}

#*Funcion para el turn no siendo mano inicial
#* @param mn numero de la carta 
#* @param mp palo de la carta 
#* @param aa apuesta del jugador
#* @param ao apuesta del adversario
#* @param a accion
#* @get /turn
function(mn,mp,aa,ao,a){
  mano<-read.csv("mano.csv",header=TRUE, sep=",", row.names=NULL)
  mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
  mesa<-read.csv("mesa.csv",header=TRUE, sep=",", row.names=NULL)
  aa<-strtoi(aa)
  ao<-strtoi(ao)
  a<-strtoi(a)
  pesos<-cargaPesos()
  triple<-cargaTriple()
  mesa<-fijarMesaPostflop(mesa,mn,mp)
  mazo<-descarteCartas(mesa,mazo)
  carta<-mesa[4,]
  pesos<-descartePesosCarta(carta,mazo,pesos)
  triple<-descarteTripleCarta(carta,mazo,triple)
  triple<-calculoProbabilidadAccion(mesa,mazo,triple,3)
  pesos<-actualizaPesos_op(a,pesos,triple)
  salida<-calculaProbFlop(mano,mesa,mazo,pesos,aa,ao,a)
  write.csv(mazo,"deck.csv",row.names = FALSE)
  write.csv(pesos, "data.csv",row.names = TRUE)
  write.csv(triple,"triple.csv",row.names = TRUE)
  write.csv(mesa, "mesa.csv",row.names = FALSE)
  
  return(salida)
}

#* Funcion para el river siendo mano inicial
#* @param mn numero de la carta 
#* @param mp palo de la carta 
#* @get /riverini
function(mn,mp){
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
  triple<-calculoProbabilidadAccion(mesa,mazo,triple,4)
  pesos<-actualizaPesos_op(1,pesos,triple)
  salida<-calculaProbRiver(mano,mesa,mazo,pesos,1)
  write.csv(mazo,"deck.csv",row.names = FALSE)
  write.csv(pesos, "data.csv",row.names = TRUE)
  write.csv(triple,"triple.csv",row.names = TRUE)
  write.csv(mesa, "mesa.csv",row.names = FALSE)
  
  return(salida)
}

#* Funcion para el river no siendo mano inicial
#* @param mn numero de la carta 
#* @param mp palo de la carta 
#* @param a accion
#* @get /river
function(mn,mp,a){
  mano<-read.csv("mano.csv",header=TRUE, sep=",", row.names=NULL)
  mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
  mesa<-read.csv("mesa.csv",header=TRUE, sep=",", row.names=NULL)
  a<-strtoi(a)
  pesos<-cargaPesos()
  triple<-cargaTriple()
  mesa<-fijarMesaPostflop(mesa,mn,mp)
  mazo<-descarteCartas(mesa,mazo)
  carta<-mesa[5,]
  pesos<-descartePesosCarta(carta,mazo,pesos)
  triple<-descarteTripleCarta(carta,mazo,triple)
  triple<-calculoProbabilidadAccion(mesa,mazo,triple,4)
  pesos<-actualizaPesos_op(a,pesos,triple)
  salida<-calculaProbRiver(mano,mesa,mazo,pesos,a)
  write.csv(mazo,"deck.csv",row.names = FALSE)
  write.csv(pesos, "data.csv",row.names = TRUE)
  write.csv(triple,"triple.csv",row.names = TRUE)
  write.csv(mesa, "mesa.csv",row.names = FALSE)
  
  return(salida)
}


#* Funcion para actualizar pesos durante el flop o turn
#* @param a accion
#* @get /riveract
function(a){
  mano<-read.csv("mano.csv",header=TRUE, sep=",", row.names=NULL)
  mazo<-read.csv("deck.csv",header=TRUE, sep=",", row.names=NULL)
  mesa<-read.csv("mesa.csv",header=TRUE, sep=",", row.names=NULL)
  a<-strtoi(a)
  pesos<-cargaPesos()
  triple<-cargaTriple()
  pesos<-actualizaPesos_op(a,pesos,triple)
  salida<-calculaProbRiver(mano,mesa,mazo,pesos,a)
  write.csv(pesos, "data.csv",row.names = TRUE)
  
  return(salida)
}

#* Funcion para comunicar al algoritmo que su adversario ha pasado
#* @param r ronda
#* @get /pass
function(r){
  r<-strtoi(r)
  accionBayes(r,1)
}

#* Funcion para comunicar al algoritmo que su adversario ha visto la apuesta
#* @param r ronda
#* @get /check
function(r){
  r<-strtoi(r)
  accionBayes(r,2)
}

#* Funcion para resetar/inicializar los valores de mazo, pesos y triple
#* @get /reset
function(){
  mazo<-crearMazo()
  pesos<-read.csv("data_ini.csv",header=TRUE,row.names=1)
  colnames(pesos)<-c(11:14,21:24,31:34,41:44)
  triple<-read.csv("triple_ini.csv",header=TRUE)
  colnames(triple)<-c("Num1","Palo1","Num2","Palo2","Pasar","Ver","Subir")
  write.csv(mazo,"deck.csv",row.names = FALSE)
  write.csv(pesos, "data.csv",row.names = TRUE)
  write.csv(triple,"triple.csv",row.names = TRUE)
  
}


#* Echo back the input
#* @param msg The message to echo
#* @get /error
function(){
  list(msg = paste0("ERROR"))
}