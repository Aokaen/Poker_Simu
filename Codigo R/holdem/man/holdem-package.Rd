\name{holdem-package}
\alias{holdem-package}
\alias{holdem}
\docType{package}
\title{
Simulates Texas Hold'em hands and tournaments
}
\description{
This package can be used to simulate hands of Texas Holdem 
and can run Texas Holdem tournaments.
}
\details{
\tabular{ll}{
Package: \tab holdem\cr
Type: \tab Package\cr
Version: \tab 1.0\cr
Date: \tab 2011-06-15\cr
License: \tab What license is it under?\cr
LazyLoad: \tab yes\cr
}
The most important functions are tourn1(), many1(), deal1(), and 
handeval(). 
tourn1() playes a Texas Hold'em tournament between different 
functions which can bet arbitrary amounts depending on their cards, chips, 
blinds, etc. 
many1() plays multiple tournaments and stores the payouts for 
each player.
deal1() deals an individual hand of Texas Hold'em.
handeval() figures out who won the hand, when more than one player 
remains and all the cards are shown.
}
\author{
Frederic Paik Schoenberg

Maintainer: Frederic Paik Schoenberg <frederic@stat.ucla.edu>
}
\references{
Schoenberg, F. (2011). An Introduction to Probability with Texas Holdem 
Examples. Taylor and Francis, New York.
}
\keyword{ package }

\examples{
## out of 1000 hands with 2 players, see how many times 
## both players get at least a straight, if neither ever folds.
n = 1000 
result = rep(0,n)
for(i in 1:n){
x1 = deal1(2)
b1 = handeval(c(x1$plnum1[1,],x1$brdnum1), c(x1$plsuit1[1,],x1$brdsuit1))
b2 = handeval(c(x1$plnum1[2,],x1$brdnum1), c(x1$plsuit1[2,],x1$brdsuit1))
if(min(b1,b2) > 4000000) result[i] = 1
}
sum(result>.5)

## run a Texas Hold'em tournament between 
## 4 players with different strategies, where 
## each always goes all in or folds.
name1 = c("gravity","tommy","ursula","vera")
decision1 = list(gravity, tommy, ursula, vera) 
tourn1(name1, decision1, myfast1 = 2) ## run quickly
tourn1(name1, decision1, myfast1 = 0) ## run slowly, showing key hands
}
