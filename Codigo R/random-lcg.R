lcg.rand <- function(n=10) {
  
  rng <- vector(length = n)
  
  # Mismos valores que para la implementación de ANSI C (Saucier,2000).
  m <- 2 ** 32
  a <- 1103515245
  c <- 12345

  # Seleccionamos la semilla con el tiempo actual en ms
  d <- as.numeric(Sys.time()) * 1000
  
  for (i in 1:n) {
    d <- (a * d + c) %% m
    rng[i] <- d / m
  }
  
  return(rng)
}