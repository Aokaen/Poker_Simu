calculaProbRiver<-function(mano,mesa,mazo,pesos,accion)
{
    FM<-calcularFuerzaMano(mano,mesa,mazo,pesos) #(inf,igual,sup)
    orden<-ordenarCartas(mano,mesa)
    valorjugada<-calcularJugada(orden)
    salida=ajusteBayes(FM, accion, 2,valorjugada)
    return(salida)
}