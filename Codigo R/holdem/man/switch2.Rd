\name{switch2}
\alias{switch2}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
Finds the cards corresponding to numbers between 1 and 52.
}
\description{
Takes each integer between 1 and 52 and turns it into a card. Used in 
deal1() and tourn1().
}
\usage{
switch2(x)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{x}{
a vector of integers between 1 and 52.
%%     ~~Describe \code{x} here~~
}
}

\value{
%%  ~Describe the value returned
%%  If it is a LIST, use
  \item{num }{numbers (2-14) of the cards}
  \item{st }{suits (1-4) of the cards}
%% ...
}

\author{
Frederic Paik Schoenberg
}

%% ~Make other sections like Warning with \section{Warning }{....} ~

\examples{
##---- Should be DIRECTLY executable !! ----
##-- ==>  Define data, use random,
##--	or do  help(data=index)  for the standard data sets.

## The function is currently defined as
function(x){
    ## takes a number 1-52, and turns it into a card: 
    ## returns a list, where the 1st is the number (2-14), and 2nd is suit (1-4).
    n = length(x)
    y = list(num=x, st=rep(1,n))
    for(i in c(1:n)){
	a = 1
	while(a>0){
	    if(y$num[i]<14) a = -1 else{y$st[i] = y$st[i]+1
		y$num[i] = y$num[i]-13
	    }
	}
    }
    y$num = y$num+1
    y
  } ## end of switch2
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
