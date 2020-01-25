\name{many1}
\alias{many1}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
function to run many Texas Hold'em tournaments.
}
\description{
Runs the desired number of Texas Hold'em tournaments, and saves the 
results. By default, only the top 3 finishers receive payouts, and their 
payouts are 13, 8, and 5, respectively.
}
\usage{
many1(name1, decision1, k, winners1 = 3, payouts1 = c(13, 8, 5))
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{name1}{
names of the players
}
  \item{decision1}{
codes governing the players' betting
}
  \item{k}{
number of players
}
  \item{winners1}{
number of top finishers receiving payouts in each tournament
}
  \item{payouts1}{
payouts for the top finishers
}
}
\details{
If length(name1) < k or length(decision1) < k, there will be errors. 
%%  ~~ If necessary, more details than the description above ~~
}
\references{
Schoenberg, F. (2011). An Introduction to Probability with Texas Holdem 
Examples. Taylor and Francis, New York.
}
\author{
Frederic Paik Schoenberg
}

%% ~Make other sections like Warning with \section{Warning }{....} ~

\examples{
name1 = c("gravity","tommy","ursula","timemachine","vera","william","xena")
decision1 = list(gravity, tommy, ursula, timemachine, vera, william, xena) 
z1 = many1(name1, decision1, 7)
z2 = z1[[2]]
barplot(z2,names.arg=name1[1:7],cex.names=.9)

## The function is currently defined as
function(name1, decision1, k,winners1=3, payouts1 = c(13,8,5)){
    ## runs k tournaments
    nplayers1 = length(name1)
    d1 = matrix(0,ncol=winners1,nrow=k) ## matrix of results
    d2 = rep(0,nplayers1) ## total pts for each player
    for(i in 1:k){
	cat("\n\n...................  TOURNAMENT NUMBER ",i,":  ................... \n\n")
	d1[i,] = tourn1(name1, decision1)
	for(j in 1:winners1) d2[d1[i,j]] = d2[d1[i,j]] + payouts1[j]
	print(rbind(1:nplayers1,d2))
	#locator(1)
    }
    list(d1,d2)
  } ## end of many1
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
