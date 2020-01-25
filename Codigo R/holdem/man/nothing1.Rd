\name{nothing1}
\alias{nothing1}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
indicates strength of your hand when you have nothing
}
\description{
finds the strength of your hand when you have nothing. Used by handeval().
}
\usage{
nothing1(x)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{x}{
%%     ~~Describe \code{x} here~~
}
}

\value{
Returns 15^4*highest card + 15^3*next highest + 225*next + 15*next + next
%%  ~Describe the value returned
%%  If it is a LIST, use
%%  \item{comp1 }{Description of 'comp1'}
%%  \item{comp2 }{Description of 'comp2'}
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
## 15^4*highest + 15^3*next + 225*next + 15*next + next
y = c(x,rep(0,5))  ## this is in case x has length < 5
a1 = sort(y,decreasing=T)
15*15*15*15*a1[1] + 15*15*15*a1[2] + 225*a1[3] + 15*a1[4] + a1[5]
  }	## end of nothing1
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
