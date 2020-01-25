#Funcion para descartar tanto los datos de una mano como de cualquier combinacion
#de cada una de las cartas de la mano para el framedata Pesos

descartePesosMano<-function(mano,mazo,datos)
{
datos<-modificaPesos(mano,datos,0)
datos<-descartePesosCarta(mano[1,],mazo,datos)
datos<-descartePesosCarta(mano[2,],mazo,datos)
}